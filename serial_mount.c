#include "grabber.h"

int fd_open(void)
{
	int fd;
	int check;
	
	char *port = "/dev/ttyS0";
	
	fd = open(port, O_RDONLY | O_NOCTTY);
	if (fd == -1)
	{
		close(fd);
		printf("Serial port not open (err 1)");
		return -1;
	}
		
	struct termios portSettings;
	
	check = tcgetattr(fd, &portSettings);
	if (check < 0)
	{
		close(fd);
		printf("Failed to retrieve attributes");
		return -1;
	}
	
	check = cfsetispeed(&portSettings, B38400);
	if (check < 0)
	{
		close(fd);
		printf("Failed to set baud rate");
		return -1;
	}
		
	/* PORT SETTINGS */
	portSettings.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);
	portSettings.c_iflag &= ~(IXON | IXOFF | IXANY);
	portSettings.c_lflag &= ~CSTOPB;
	portSettings.c_lflag &= ~ICANON;
	portSettings.c_lflag &= ~ISIG;
	portSettings.c_cflag &= ~CSIZE;
	portSettings.c_cflag |= CS8;
	portSettings.c_cflag &= ~PARENB;
	
	/* PORT CONTROL */
	portSettings.c_cc[VMIN] = 82 * sizeof(char);
	portSettings.c_cc[VTIME] = 20;
	
	check = tcsetattr(fd, TCSANOW, &portSettings);
	if (check < 0)
	{
		close(fd);
		printf("Failed to set attributes");
		return -1;
	}
	else
	{
		printf("BaudRate = 38400 \nStopBits = 1 \nParity = none \n");
	}

	return fd;
}
