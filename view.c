#include <stdio.h>
#include <string.h>
#include "main.h"
/*
Name          :NIHALRAJEEV P
Date          :
Description   :
Sample input  :
Sample output :
 */

int mp3_view(char *argv[])
{
    tag tags = {'\0'};
    FILE *fptr = fopen(argv[2],"r");                                  //file oprned in read mode
    char *label[] = {"TIT2","TPE1","TALB","TYER","TCON","COMM"};      //array of string containing tags
    if(fptr == NULL)                                                  //file is opened or not
    {
	return FAILURE;
    }
    char temp[5] = {0};
    char version[3];
    int size;
    fread(temp,3,1,fptr);
    if(!strcmp(temp,"ID3"))                                              //first 3bytes of header is ID3
    {
	fread(version,2,1,fptr);                                         //next 2byte version
	if(version[0] == 0x03 && version[1] == 0x00)                     //comparing the version is 0x0300
	{
	    fseek(fptr,10,SEEK_SET);                                     //skip header
	    int i,j;
	    for(i = 0; i < 6 ; i++)                                      //loop for reading all 6 tag
	    {
		fread(temp,4,1,fptr);                                    //each tag is 4bytes
		size = read_size(&fptr,4) - 1;                           //next bytes for size (-1 for reducing 1 flag byte)
		fseek(fptr,3,SEEK_CUR);                		//skip flag
		for(j = 0 ; j < 6 ; j++)
		{
		    if(strcmp(temp,label[j]) == 0)                       //check if read tag is in 6 tags
		    {
			break;
		    }
		}
		switch(j)                                               //read the bytes size times to corresponding string from structure
		{
		    case 0:
			fread(tags.title, size, 1, fptr);
			tags.title[size] = '\0';
			break;

		    case 1:
			fread(tags.artist, size, 1, fptr);
			printf(" size of artist %d",size);
			tags.artist[size + 1] = '\0';
			break;

		    case 2:
			fread(tags.album, size, 1, fptr);
			tags.album[size + 1] = '\0';
			break;

		    case 3:
			fread(tags.year, size, 1,fptr);
			tags.year[size] = '\0';
			break;	
		    case 4:
			fread(tags.music, size, 1, fptr);
			tags.music[size] = '\0';
			break;
		    case 5:
			fread(tags.comment, size, 1, fptr);
			break;
		    default :
			fseek(fptr, size, SEEK_CUR);                        //if tags are not matching skip size times and countinue the iteration
		}
	    }
	    printf("-------------------SELECTED VIEW DETAILS-------------------------\n");
	    printf("-----------------------------------------------------------------\n");
	    printf("             MP3 TAG READER AND EDITOR FOR ID3V2\n");
	    printf("-----------------------------------------------------------------\n");
	    if(tags.title[0] != '\0')
	    {
		printf("TITLE     : %s\n",tags.title);
	    }
	    if(tags.artist[0] != '\0')
	    {
		printf("ARTIST     : %s\n",tags.artist);
	    }
	    if(tags.album[0] != '\0')
	    {
		printf("ALBUM     : %s\n",tags.album);
	    }
	    if(tags.year[0] != '\0')
	    {
		printf("YEAR     : %s\n",tags.year);
	    }
	    if(tags.music[0] != '\0')
	    {
		printf("MUSIC     : %s\n",tags.music);
	    }
	    if(tags.comment[0] != '\0')
	    {
		printf("COMMENT  : %s\n", tags.comment);
	    }
	    printf("---------------------------------------------------------------------------\n");
	    return SUCCESS;
	}
    }
    else
    {
	return FAILURE;
    }
}

int read_size(FILE **ptr,int count)
{
    int size = 0;
    char ch;
    for(int i = count - 1; i >= 0; i--)
    {
	fread(&ch,1,1,*ptr);
	size = size | (ch << i * 8);
    }
    return size;
}

