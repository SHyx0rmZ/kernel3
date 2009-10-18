void kernel(int multiboot, int magic)
{
	if(multiboot)
		multiboot = 0;
	if(magic)
		magic = 0;

	while(1) { asm("hlt"); };
}
