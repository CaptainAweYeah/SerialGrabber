#include "grabber.h"

int main (void)
{	
	char *change = "cd";
	char *path = "/home/pi/grabber";
	char *downpath = "/home/pi/Desktop/grabber";

	char *comp1 = "gcc";
	char *comp2 = "-o";
	char *comp3 = "-Wall";
	
	char *exen1 = "ACSGrab";
	char *exen2 = "ACSRead";
	char *stagef = "usb_staging";
	
	char *arg1 = "grabber.h";
	char *arg2 = "main.c";
	char *arg3 = "tools.c";
	char *arg4 = "usb_read.c";
	char *arg5 = "serial_mount.c";
	char *arg6 = "buffer.c";

	char *admin1 = "sudo";
	char *admin2 = "chmod";
	char *admin3 = "+x";

	struct stat st = {0};
	
	char *head 	= refile(downpath, arg1);
	char *main 	= refile(downpath, arg2);
	char *tools	= refile(downpath, arg3);
	char *read 	= refile(downpath, arg4);
	char *mount = refile(downpath, arg5);
	char *buff	= refile(downpath, arg6);
	
	char *n_head	= refile(path, arg1);
	char *n_main 	= refile(path, arg2);
	char *n_tools 	= refile(path, arg3);
	char *n_read	= refile(path, arg4);
	char *n_mount	= refile(path, arg5);
	char *n_buff	= refile(path, arg6);
	
	char *start_grab = refile(downpath, exen1);
	char *start_read = refile(downpath, exen2);
	char *end_grab = refile(path, exen1);
	char *end_read = refile(path, exen2);
	char *n_stagef = combf(path, stagef);
	
	if (stat(path, &st) == 0)
	{
		remove(path);
		remove(n_head);
		remove(n_main);
		remove(n_tools);
		remove(n_read);
		remove(n_mount);
		remove(n_buff);
	}
	else
	{
		printf("Failed");
	}
	mkdir(path, 0777);
	
	
	if (stat(n_stagef, &st) == 0)
	{
		printf("%s already exists", stagef);
	}
	else
	{
		mkdir(n_stagef, 0777);
	}
	
	pid_t son;

	son = fork();

	if (son == -1) /* report */
	{
		printf("compilation failed");
	}
	else if (son == 0) 
	{
		execlp(admin1, comp1, comp1, comp2, end_read, arg1, arg4, arg3, NULL);
	}
		
	
	son = fork();
	
	if (son == -1) /* report */
	{
		printf("compilation failed");
	}
	else if (son == 0) 
	{
		execlp(comp1, comp1, comp2, end_grab, arg1, arg2, arg5, arg6, NULL);
		return 0;
	}

	return 0;
}
