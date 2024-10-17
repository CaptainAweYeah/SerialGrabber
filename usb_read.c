#include <errno.h>
#include "grabber.h"

struct dirent *de;
bool storage(char *usb_name, char *dname);
char *fn(char *stage);
bool eof(char *fname);
extern int errno;

int main(void)
{
	bool stor = false;
	
	char *usb[256];
	
	
	int usb_save = 0;

	char *dirname = "/media/pi";
	char *staging = "/home/pi/grabber/usb_staging";
	errno = 0;
	chmod(staging, 0777);
	if (errno != 0)
	{
		printf(" 70 Failed setting permissions on %s", staging);
	}
	
	int go = 1;
	while (go == 1)
	{
		char *check = fn(staging);
		
		char *fcheck = refile(staging, check);
		
		if (cntf(staging) > 0)
		{
			int cnt = 0;
			DIR *dr = opendir(dirname);
			if (dr == NULL)
			{
				closedir(dr);
				printf("Could not open directory");
				return 1;
			}

			while ((de = readdir(dr)) != NULL)
			{	
				char *dd = de->d_name;
				
				DIR *dr1 = opendir(dd);
				if (dr1 == NULL)
				{	
					printf("%s\n", dd);
					printf("	Possible storage\n");
					usb[cnt] = dd;
					closedir(dr1);
					cnt++;
				}
				else
				{
					printf("%s\n", dd);
					printf("	Could not open directory\n");
					closedir(dr1);
				}
			}
			closedir(dr);
			
			int usb_final = 0;
			
			for (int i = 0; i < cnt; i++)
			{
				if (!storage(usb[i], dirname))
				{
					continue;
				}
				else
				{
					printf("	Storage device detected\n");
					stor = true;
					usb_final = i;
					char *addin = combf(dirname, usb[usb_final]);
					char *new_loc = refile(addin, check);

					move(addin, new_loc);

					break;
				}
			}
		}
		else
		{
			continue;
		}
	}
	
	return 0;
}

bool storage(char *usb_name, char *dname)
{
	char *location = combf(dname, usb_name);
	char *testf = "test.txt";
	char *dn = refile(location, testf);
	
	printf("\n%s\n\n", dn);
	
	errno = 0;
	FILE *usb = fopen(dn, "w");
	if (errno != 0)
	{
		//fclose(usb);
		free(dn);
		printf("%d\n", errno);
		perror("[!]");
		return false;
	}
	
	fprintf(usb, "test");
	
	fclose(usb);
	free(dn);
	return true;
}

// This function returns the name of our staging file;
char *fn(char *stage)
{
	int foldlen = cntf(stage);
	if (foldlen == 0)
	{
		return "empty";
	}
	
	char *sf[foldlen];
	int cnt = 0;
	int sf_final = 0;
	
	DIR *stagefolder = opendir(stage);
	if (stagefolder == NULL)
	{
		closedir(stagefolder);
		printf("Could not open directory");
		return "empty";
	}
	
	while ((de = readdir(stagefolder)) != NULL)
	{
		
		if (strlen(de->d_name) > 3)
		{	
			printf("%s\n", de->d_name);
			sf[cnt] = malloc(strlen(de->d_name) * sizeof(char));
			
			sf[cnt] = de->d_name;
			printf("%s\n", sf[cnt]);
			cnt++;
		}
	}
	closedir(stagefolder);
	printf("after this\n");
	
	
	for (int i = 0, n = cnt, t = strlen(sf[i]); i < n; i++)
	{		
		if (sf[i][t - 1] == 'v')
		{
			if (sf[i][t - 2] == 's')
			{
				if (sf[i][t - 3] == 'c')
				{
					sf_final = i;
					printf("true");
					break;
				}
			}
		}
		else
		{
			printf("false");
		}
		
	}
	
	char *end = malloc(strlen(sf[sf_final]) * sizeof(char));
	
	sprintf(end, "%s", sf[sf_final]);
	
	printf("\n%s\n", end);
	
	printf("winner\n");
	
	
	return end;		
}

bool eof(char *fname)
{
	FILE *in = fopen(fname, "r");
	if (in == NULL)
	{
		fclose(in);
		return false;
	}
	int block = 82;
	char *buff = malloc(block * sizeof(char));
	
	while (fread(&buff, sizeof(char), block, in))
	{
		for (int i = 0; i < block; i++)
		{
			if (buff[i] == 'E')
			{
				if (buff[i + 1] == 'O')
				{
					if (buff[i + 2] == 'F')
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}
