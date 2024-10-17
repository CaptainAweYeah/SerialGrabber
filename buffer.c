#include "grabber.h"

int endOfFile(char *f, char *new_f);

const int S_BLOCK = 82;

char *stor(char *in_buff, char *type, char *fn)
{
	printf("%s", in_buff);
	
	bool eof = false;
	char *EOF_buff = malloc(S_BLOCK);
	
	char *buff = malloc(S_BLOCK * sizeof(char));
	char *buff2 = malloc(S_BLOCK * sizeof(char));

	int counter = 0;
	int EOF_counter = 0;
	int f_counter = 0;

	// If the filename doesnt come through first
	if (in_buff[0] != '<')
	{
		for (int i = 0; in_buff[i] != '<'; i++)
		{
			counter++;
			for (int i = 0; in_buff[i] != '\0'; i++)
			{
			EOF_counter++;
			if (in_buff[i] == 'E')
			{
				if (in_buff[i + 1] == 'O')
				{
					if (in_buff[i + 2] == 'F')
					{
						eof = true;
						counter + 3;
					}
					else
					{
						continue;
					}
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;
			}
		}
		EOF_counter++;
		}
		for (int i = 0; in_buff[i + counter] != '>'; i++)
		{
			f_counter++;
		}
		f_counter++;
	}
	// If the filename does come through first
	else
	{
		for (int i = 0; in_buff[i] != '>'; i++)
		{
			f_counter++;
		}
		f_counter++;
		for (int i = f_counter; in_buff[i] != '\0'; i++)
		{
			EOF_counter++;
			if (in_buff[i] == 'E')
			{
				if (in_buff[i + 1] == 'O')
				{
					if (in_buff[i + 2] == 'F')
					{
						eof = true;
					}
					else
					{
						continue;
					}
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;
			}
		}
		EOF_counter++;
	}
	
	// create the buffer for our filename
	
	int new_count = counter + f_counter;
	
	// If there was no file name returned
	if (fn == NULL)
	{
		char *new_name = malloc(f_counter * sizeof(char));	
		
		// add the new fname to our buffer
		for (int i = 0; i < f_counter; i++)
		{
			new_name[i] = in_buff[i + counter];
		}
		
		// check it in the prompt
		printf("%s", new_name);
		
		// check if the file name is valid
		// if not throw away the string and return NULL
		if (new_name[0] == '<')
		{
			char *new_fname = malloc((f_counter - 1) * sizeof(char));
			for (int i = 0; new_name[i + 1] != '>'; i++)
			{
				new_fname[i] = new_name[i + 1];
			}

			// Return save location (usb_read) 
			char *fold = "/home/pi/Documents/";
			int fl = strlen(fold) + strlen(new_fname);
			char *fname = malloc(fl + 4);
			sprintf(fname, "%s%s.csv", fold, new_fname);			
			printf("%s\n", fname);
			
			/*------------------------*/
			FILE *output = fopen(fname, "ab");
			if (output == NULL)
			{
				fclose(output);
				free(fname);
				printf("err");
				return fn;
			}
			
			for (int i = new_count; i < strlen(in_buff); i++)
			{
				fprintf(output, "%c", in_buff[i]);
			}
			fprintf(output, "\n");
			printf("after this\n");
			fclose(output);
			
			if (eof)
			{
				int errid = endOfFile(fname, new_fname);
				if (errid == 1)
				{
					free(fname);
					printf("err 1\n");
					return NULL;
				}
				else if (errid == 2)
				{
					free(fname);
					printf("err 2\n");
					return NULL;
				}
				else
				{
					remove(fname);
					free(new_fname);
					printf("File ready for transfer\n");
					return NULL;
				}
			}
			free(fname);
			printf("\n%s\n", new_fname);
			return new_name;
		}
		else
		{
			return new_name;
		}
	}
	else
	{
		char *fold = "/home/pi/Documents/";
		char *fswitch = malloc(f_counter);	
		
		if (in_buff[0] != '<')
		{
			if (f_counter > 1)
			{
				for (int i = 0; i < f_counter; i++)
				{
					fswitch[i] = in_buff[i + counter];
				}
				for (int i = 0; i < S_BLOCK - 1; i++)
				{
					buff2[i] = in_buff[i + (new_count + 1)];
				}
				for (int i = 0; i < counter; i++)
				{
						buff[i] = in_buff[i];
				}
			}
			else
			{
				for (int i = 0; i < counter; i++)
				{
					buff[i] = in_buff[i];
				}
			}

		}
		
		int fl = (strlen(fold) + strlen(fn)) + 5;
		
		printf("\n%i\n", fl);
		
		char *fname = malloc(fl);
		
		sprintf(fname, "%s%s.csv", fold, fn);			
		printf("%s\n", fname);
		
		/*------------------------*/
		FILE *out1 = fopen(fname, "ab");
		if (out1 == NULL)
		{
			printf("this");
			free(buff);
			fclose(out1);
			return NULL;
		}
		
		printf("After here\n");
		// Add our buffer to the file
		for (int i = 0; i < strlen(buff); i++)
		{
			fprintf(out1, "%c", buff[i]);

		}
		fprintf(out1, "dont close it\n");
		fclose(out1);
		printf("and here\n");
		
		
		// If end of file is triggered
		if (eof)
		{
			int errid = endOfFile(fname, fn);
			if (errid == 1)
			{
				free(fname);
				printf("err 1\n");
				return NULL;
			}
			else if (errid == 2)
			{
				free(fname);
				printf("err 2\n");
				return NULL;
			}
			else
			{
				remove(fname);
				printf("File ready for transfer\n");
				return NULL;
			}
		}
		else if (fswitch[0] == '<')
		{
			printf("this is the one");
			char *fold = "/home/pi/Documents/";
			
			int fl2 = strlen(fold) + strlen(fswitch);
			
			char *fname2 = malloc(fl2 + 2);
			
			sprintf(fname2, "%s%s.csv", fold, fswitch);
			
			/*------------------------*/
			FILE *out2 = fopen(fname2, "ab");
			if (out2 == NULL)
			{

				fclose(out1);
				return fn;
			}
			
			for (int i = 0; i < strlen(buff2); i++)
			{
				fprintf(out2, "%c", buff2[i]);
			}
			fprintf(out2, "\n");
			fclose(out2);

			return fswitch;
		}
		else
		{
			printf("wtf");
			return fn;
		}
		printf("why is this even here");
		return fn;
	}

	printf("in case you are stupid");
	return fn;
}

int endOfFile(char *f, char *new_f)
{
	FILE *output = fopen(f, "rb");
	if (output == NULL)
	{		
		fclose(output);
		return 1;
	}

	int u = strlen(new_f);
	char *stage = malloc((33 + u) * sizeof(char));
	sprintf(stage, "/home/pi/grabber/usb_staging/%s.csv", new_f);
	
	FILE *staging = fopen(stage, "wb");
	if (staging == NULL)
	{		
		fclose(staging);
		return 2;
	}

	do
	{
		char ch = fgetc(output);
		fputc(ch, staging);
	} while(!feof(output));
	
	free(stage);	
	fclose(staging);	
	return 0;
}
