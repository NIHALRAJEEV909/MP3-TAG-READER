#include <stdio.h>
#include "main.h"
/*
Name          :NIHALRAJEEV P
Date          :
Description   :
Sample input  :
Sample output :
*/

int Mp3edit(char *argv[])
{
   // printf("vasu");
    char *label[6] = {"TIT2","TPE1","TALB","TYER","TCON","COMM"};
    char temp[5] = {'\0'};
    char version[3];
    int size;
    FILE *fptr = fopen(argv[4],"r+");
    if(fptr == NULL)
    {
	fprintf(stderr, "ERROR: FIle Failed to open\n");
    }
 //printf("vasu");
    fread(temp,3,1,fptr);
    printf("%s",temp);
    if(!strcmp(temp,"ID3"))                                                  //check for IDE tag
    {
	//printf("vasu");
        fread(version,2,1,fptr);
	if(version[0] == 0x03 && version[1] == 0x00);                        //checking version
	{
	    fseek(fptr,10,SEEK_SET);
	    int i,j;
	    for(i = 0 ; i < 6 ;i++)
	    {
		fread(temp,4,1,fptr);
		size = read_size(&fptr,4) - 1;
		fseek(fptr,3,SEEK_CUR);                                      //skip flag
		for( j = 0 ; j < 6 ; j++)
		{
		    if(strcmp(temp,label[j]) == 0)                           //compare for tags
		    {
			break;
		    }
		}
		printf("vasu");
		switch(j)
		{
		    case 0:
			if(!strcmp(argv[2], "-t"))                                  //options are check for title
			{
			    printf("-----------------  CHANGE THE TITLE  ----------------------\n");
			    printf("TITLE    : %.*s\n",size,argv[3]);                                        //to prompt the user
			    edit(&fptr, argv, size);                                                          //function to write the input to
			    printf("---------------  THE TITLE CHANGED SUCCESSFULLY--------------------\n");
			    return SUCCESS;
			}
			else
			{
			    fseek(fptr,size,SEEK_CUR);                                                        //move the pointer for next tag
			}
			break;

		    case 1:
                        if(!strcmp(argv[2], "-a"))                                  //options are check for ARTIST
                        {
                            printf("-----------------  CHANGE THE ARTIST  ----------------------\n");
                            printf("ARTIST    : %.*s\n",size,argv[3]);                                        //to prompt the user
                            edit(&fptr, argv, size);                                                          //function to write the input to
                            printf("---------------  THE ARTIST CHANGED SUCCESSFULLY--------------------\n");
                            return SUCCESS;
                        }
                        else
                        {
                            fseek(fptr,size,SEEK_CUR);                                                        //move the pointer for next tag
                        }
                        break;

			case 2:
                        if(!strcmp(argv[2], "-A"))                                  //options are check for ALBUM
                        {
                            printf("-----------------  CHANGE THE ALBUM  ----------------------\n");
                            printf("ALBUM    : %.*s\n",size,argv[3]);                                        //to prompt the user
                            edit(&fptr, argv, size);                                                          //function to write the input to
                            printf("---------------  THE ALBUM CHANGED SUCCESSFULLY--------------------\n");
                            return SUCCESS;
                        }
                        else
                        {
                            fseek(fptr,size,SEEK_CUR);                                                        //move the pointer for next tag
                        }
                        break;

			case 3:
                        if(!strcmp(argv[2], "-y"))                                  //options are check for year
                        {
                            printf("-----------------  CHANGE THE YEAR   ----------------------\n");
                            printf("YEAR    : %.*s\n",size,argv[3]);                                        //to prompt the user
                            edit(&fptr, argv, size);                                                          //function to write the input to
                            printf("---------------  THE YEAR CHANGED SUCCESSFULLY--------------------\n");
                            return SUCCESS;
                        }
                        else
                        {
                            fseek(fptr,size,SEEK_CUR);                                                        //move the pointer for next tag
                        }
                        break;

			case 4:
                        if(!strcmp(argv[2], "-m"))                                  //options are check for music
                        {
                            printf("-----------------  CHANGE THE MUSIC  ----------------------\n");
                            printf("MUSIC    : %.*s\n",size,argv[3]);                                        //to prompt the user
                            edit(&fptr, argv, size);                                                          //function to write the input to
                            printf("---------------  THE MUSIC CHANGED SUCCESSFULLY--------------------\n");
                            return SUCCESS;
                        }
                        else
                        {
                            fseek(fptr,size,SEEK_CUR);                                                        //move the pointer for next tag
                        }
                        break;

			case 5:
                        if(!strcmp(argv[2], "-c"))                                  //options are check for comment
                        {
                            printf("-----------------  CHANGE THE COMMENT  ----------------------\n");
                            printf("COMMENT    : %.*s\n",size,argv[3]);                                        //to prompt the user
                            edit(&fptr, argv, size);                                                          //function to write the input to
                            printf("---------------  THE COMMENT CHANGED SUCCESSFULLY--------------------\n");
                            return SUCCESS;
                        }
                        else
                        {
                            fseek(fptr,size,SEEK_CUR);                                                        //move the pointer for next tag
                        }
                        break;

			default :
			fseek(fptr, size, SEEK_CUR);
		}
	    }
	}
	return FAILURE;
    }
    return FAILURE;
}


void edit(FILE **ptr, char *argv[], int size)
{
    int len = strlen(argv[3]);
    if(len < size)                                                               //check if entered text is less than the size
    {
	fwrite(argv[3], len + 1 , 1 , *ptr);                                     //write the string to mp3file
    }
    else
    {
	fwrite(argv[3], size , 1, *ptr);                                         //if string size is greater than size write only the size number of characters
    }
}
