#include "grabber.h"

int main(void)
{
	int fd = fd_open();
	
	// Initialize our buffer with the correct size of memory
	int block = 82 * sizeof(char);
	char *buffer1 = malloc(block);
	char *FTYPE = ".csv";
	
	// Read and store our buffer and return the filename
	read(fd, buffer1, block);
	
	char *last_fname = stor(buffer1, FTYPE, NULL);
	free(buffer1);
	
	while (fd > 0)
	{
		char *buffer = malloc(block);
		read(fd, buffer, block);
		printf("\n Passing %s\n", last_fname);
		
		// Check if the last file name returned is valid
		if (last_fname != NULL)
		{
			last_fname = stor(buffer, FTYPE, last_fname);
		}
		else
		{
			last_fname = stor(buffer, FTYPE, NULL);
		}
		free(buffer);
		
	}
	return 0;

}
