/*
 *   ASXSoft Nuke - Operating System
 *   Copyright (C) 2009 Alexander H. Kluth
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <system/stdarg.h>

#define ZEROPAD 1               /* pad with zero */
#define SIGN    2               /* unsigned/signed long */
#define PLUS    4               /* show plus */
#define SPACE   8               /* space if plus */
#define LEFT    16              /* left justified */
#define SPECIAL 32              /* 0x */
#define SMALL   64              /* use 'abcdef' instead of 'ABCDEF' */

/// Nice macro as an equivalent for the libc-function
#define is_digit(c)     ((c) >= '0' && (c) <= '9')

#define do_div(n,base) ({ \
int __res; \
__asm__("divl %4":"=a" (n), "=d" (__res) : "0" (n), "1" (0), "r" (base)); \
__res; })

static char printbuf[1024];



/**
 * Prints a character to the screen, is used
 * by kprintf and kputs
 *
 * @param c Character to print
 **/
void kputch(unsigned char c)
{
    unsigned short *where;
    unsigned att = get_attribute() << 8;


    if(c == 0x08)
    {
		/// ! SELBER SCHREIBEN !
        if(get_cursor_x() != 0) set_cursor_x(get_cursor_x() - 1);
    }

	//
    else if(c == 0x09)
    {
        int newx;

		/// ! SELBER SCHREIBEN !
        newx = (get_cursor_x() + 8) & ~(8 - 1);

        set_cursor_x(newx);
    }

	// Carriage return? Set the cursor to the beginning of the current line
    else if(c == '\r')
    {
		/// ! SELBER SCHREIBEN !
        set_cursor_x(0);
    }

	// Linefeed? Set the cursor to the next line
    else if(c == '\n')
    {
		/// ! SELBER SCHREIBEN !
        set_cursor_x(0);
        set_cursor_y(get_cursor_y() + 1);
    }

    else if(c >= ' ')
    {
		/// ! SELBER SCHREIBEN !
        //FIXME: get_textmemptr() doesn't work here (whyever...)
        where = (unsigned short*)0xB8000 + (get_cursor_y() * 80 + get_cursor_x());
        *where = c | att;
        set_cursor_x(get_cursor_x() + 1);
    }

	/// ! SELBER SCHREIBEN !

    // More than 80 lines? Scroll the screen
    if(get_cursor_x() >= 80)
    {
        set_cursor_x(0);
        set_cursor_y(get_cursor_y() + 1);
    }

	/// ! SELBER SCHREIBEN !

    // Scroll the screen and move the cursor
    scroll_screen();
    move_cursor();
}


/**
 * Prints a string to the screen
 *
 * Uses kputc for this.
 *
 * @param text Pointer to the screen should been printed
 **/
void kputs(const char *text)
{
    int i;

    for (i = 0; i < strlen(text); i++)
    {
        kputch(text[i]);
    }
}


/**
 * Simple string-to-integer-function
 *
 * @param s Pointer to the address where the string is
 *
 * @return Converted number
 **/
static inline int skip_atoi(const char **s)
{
        int i=0;

        while (is_digit(**s))
                i = i*10 + *((*s)++) - '0';
        return i;
}


/**
 * Helperfunction for printing out several number-formats
 *
 * @param str String to format
 * @param num Number
 * @param base Base
 * @param size Size
 * @param precision Precision
 * @param type Type
 *
 * @return Formatted string
 **/
static char *number(char * str, int num, int base, int size, int precision, int type)
{
	char c, sign, tmp[36];
    const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;

    if (type & SMALL)
    	digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if (type & LEFT)
    	type &= ~ZEROPAD;

    if (base <2  || base > 36)
    	return 0;

    c = (type & ZEROPAD) ? '0' : ' ' ;

    if ((type & SIGN) && (num < 0))
    {
    	sign='-';
        num = -num;
    }

    else
        sign=(type&PLUS) ? '+' : ((type&SPACE) ? ' ' : 0);


    if (sign)
    	size--;

    if (type&SPECIAL)
    {
        if (base==16)
        	size -= 2;

        else if (base==8)
        	size--;
    }

    i = 0;

    if (num == 0)
    	tmp[i++]='0';

    else
    {
    	while (num != 0)
    	{
    		tmp[i++]=digits[do_div(num,base)];
    	}
    }

    if (i > precision)
    	precision = i;

    size -= precision;

    if (!(type&(ZEROPAD + LEFT)))
    {
    	while(size-->0)
    	{
    		*str++ = ' ';
    	}
    }

    if (sign)
    	*str++ = sign;

    if (type & SPECIAL)
    {
    	if (base == 8)
    		*str++ = '0';

    	else if (base == 16)
    	{
    		*str++ = '0';
    		*str++ = digits[33];
        }
    }

    if (!(type&LEFT))
    {
    	while(size-->0)
    	{
    		*str++ = c;
    	}

        while(i<precision--)
        {
        	*str++ = '0';
        }

        while(i-->0)
        {
        	*str++ = tmp[i];
        }

        while(size-->0)
        {
        	*str++ = ' ';
        }

    }

    return str;
}


/**
 * Helper for kprintf, formats the string
 *
 * @param buf Buffer with stored string
 * @param fmt Fmt
 * @param args Arguments
 *
 * @return Returns something
 **/
int vsprintf(char *buf, const char *fmt, va_list args)
{
    int len;
    int i;
    char *str;
    char *s;
    int *ip;

    int flags;              /* flags to number() */

    int field_width;        /* width of output field */
    int precision;          /* min. # of digits for integers; max
                                   number of chars for from string */
    int qualifier;          /* 'h', 'l', or 'L' for integer fields */

    for (str=buf ; *fmt ; ++fmt)
    {
    	if (*fmt != '%')
    	{
    		*str++ = *fmt;
            continue;
        }

        /* process flags */
        flags = 0;
        repeat:
        ++fmt;          /* this also skips first '%' */

        switch (*fmt)
        {
			case '-': flags |= LEFT; goto repeat;
            case '+': flags |= PLUS; goto repeat;
            case ' ': flags |= SPACE; goto repeat;
            case '#': flags |= SPECIAL; goto repeat;
            case '0': flags |= ZEROPAD; goto repeat;
         }

         /* get field width */
         field_width = -1;

         if (is_digit(*fmt))
        	 field_width = skip_atoi(&fmt);

         else if (*fmt == '*')
         {
         	/* it's the next argument */
            field_width = va_arg(args, int);

            if (field_width < 0)
            {
            	field_width = -field_width;
                flags |= LEFT;
            }
         }

         /* get the precision */
         precision = -1;

         if (*fmt == '.')
         {
             ++fmt;

             if (is_digit(*fmt))
            	 precision = skip_atoi(&fmt);

             else if (*fmt == '*')
             {
             	/* it's the next argument */
                precision = va_arg(args, int);
             }

             if (precision < 0)
             	precision = 0;
          }

          /* get the conversion qualifier */
          qualifier = -1;

          if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L')
          {
        	  qualifier = *fmt;
              ++fmt;
          }

          switch (*fmt)
          {
				case 'c':
					if (!(flags & LEFT))
					{
                    	while (--field_width > 0)
                    	{
                    		*str++ = ' ';
                    	}

                        *str++ = (unsigned char) va_arg(args, int);

                        while (--field_width > 0)
                        {
                        	*str++ = ' ';
                        }
					}

                    break;

                case 's':
                    s = va_arg(args, char *);
                    len = strlen(s);

                    if (precision < 0)
                    	precision = len;

                    else if (len > precision)
                        len = precision;

                    if (!(flags & LEFT))
                    {
                    	while (len < field_width--)
                    	{
							*str++ = ' ';
                    	}
                    }

                    for (i = 0; i < len; ++i)
                    {
                    	*str++ = *s++;
                    }

                    while (len < field_width--)
                    {
                    	*str++ = ' ';
                    }

                    break;

                case 'o':
                    str = number(str, va_arg(args, unsigned long), 8, field_width, precision, flags);
                    break;

                case 'p':
                    if (field_width == -1)
                    {
                    	field_width = 8;
                        flags |= ZEROPAD;
                    }

                    str = number(str, (unsigned long) va_arg(args, void *), 16, field_width, precision, flags);
                    break;

                case 'x':
                    flags |= SMALL;

                case 'X':
                    str = number(str, va_arg(args, unsigned long), 16, field_width, precision, flags);
                    break;

                case 'd':
                case 'i':
                    flags |= SIGN;

                case 'u':
                	str = number(str, va_arg(args, unsigned long), 10, field_width, precision, flags);
                    break;

                case 'n':
                    ip = va_arg(args, int *);
                    *ip = (str - buf);
                    break;

                default:
                    if (*fmt != '%')
                    	*str++ = '%';

                    if (*fmt)
                       *str++ = *fmt;

                    else
                       --fmt;
                       break;
					}
	}

    *str = '\0';

    kputs(buf);
    return 1;
}


/**
 * Kernel-printf
 *
 * @param fmt Format-String
 * @param ... Additional parameters
 *
 * @returns Returns something
 **/
int kprintf(const char *fmt, ...)
{
    va_list args;
    int i;

    va_start(args, fmt);
    i = vsprintf(printbuf, fmt, args);
    va_end(args);

    return i;
}



