/* generate the full 8 bit data file */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{	
	int				i  = 0;
	int				fd;
	unsigned char	buf[256];
	
	printf("creating test files ...\n");
	
	fd = open("test_256v1.txt", O_CREAT|O_TRUNC|O_WRONLY);	
	if (fd < 0)
		printf("error in opening file for writing\n");

	/* 0x00 - 0xFF */	
	for (i = 0; i < 256; i++)
		buf[i] = i;

	write(fd, &buf[0], 256);
	close(fd);
	printf("test_256v1.txt generated.\n");


	fd = open("test_256v2.txt", O_CREAT|O_TRUNC|O_WRONLY);	
	if (fd < 0)
		printf("error in opening file for writing\n");

	/* 0x80 - 0xFF */	
	for (i = 0; i < 128; i++)
		buf[i] = i+128;
		
	/* 0x00 - 0x7E */
	for (i = 128; i < 256; i++)
		buf[i] = i-128;
	
	write(fd, &buf[0], 256);
	close(fd);
	printf("test_256v2.txt generated.\n");
	printf("test file generation completed.\n");
	
	return 0;
}