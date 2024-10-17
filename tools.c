#include "grabber.h"

void move(char* in, char *out)
{
	errno = 0;
	chmod(in, 0777);
	if (errno != 0)
	{
		printf("%i\nFailed setting permission on %s", errno, in);
		return;
	}
	
	errno = 0;
	FILE *fstart = fopen(in, "rb");
	if (errno != 0)
	{
		//fclose(fstart);
		printf("Move Unsuccessful");
		return;
	}
	
	errno = 0;
	FILE *fend = fopen(out, "wb");
	if (errno != 0)
	{
		perror("[-]");
		fclose(fstart);
		//fclose(fend);
		printf("Move Unsuccessful");
		return;
	}

		
	
	do
	{
		char ch = fgetc(fstart);
		fputc(ch, fend);
	} while(!feof(fstart));
	
	printf("%s\nsuccessfully moved to:\n	%s\n", in, out);
	fclose(fstart);
	remove(in);
	fclose(fend);
	
	chmod(out, 0777);
	if (errno != 0)
	{
		printf("%i\nFailed setting permission on %s", errno, out);
		return;
	}
	return;
}

void copy(char* in, char *out)
{
	int check1 = chmod(in, 0777);
	if (check1 != 0)
	{
		printf("Failed setting permission on %s", in);
	}
	
	FILE *start = fopen(in, "r");
	if (start == NULL)
	{
		fclose(start);
		printf("Move Unsuccessful");
	}
	
	FILE *end = fopen(out, "w");
	if (end == NULL)
	{
		fclose(start);
		fclose(end);
		printf("Move Unsuccessful");
	}
	
	do
	{
		char ch = fgetc(start);
		fputc(ch, end);
	} while(!feof(start));
	
	printf("%s\nsuccessfully moved to:\n	%s\n", in, out);
	fclose(start);
	fclose(end);
	
	int check2 = chmod(out, 0777);
	if (check2 != 0)
	{
		printf("Failed setting permission on %s", out);
	}
	
	return;
}

char *combf(char *a, char *b)
{
	int first = strlen(a);
	int last = strlen(b);
	int total = (first + last) + 3;
	char *new_fold = malloc(total);
	
	sprintf(new_fold, "%s/%s", a, b);
	printf("%s\n", new_fold);
	
	return new_fold;
}

char *refile(char *folder, char *f_n)
{
	int first = strlen(folder);
	int last = strlen(f_n);
	int total = (first + last) + 2;
	char *refold = malloc(total);
	
	sprintf(refold, "%s/%s", folder, f_n);
	
	return refold;
}

int cntf(char *fold)
{
	struct dirent *de;
	int counter = 0;
	
	DIR *folder = opendir(fold);
	if (folder == NULL)
	{
		closedir(folder);
		return -1;
	}
	
	while ((de = readdir(folder)) != NULL)
	{
		if (strlen(de->d_name) > 3)
		{
			counter++;
		}
	}
	
	closedir(folder);
	return counter;
}







