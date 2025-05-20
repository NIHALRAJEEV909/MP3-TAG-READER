#include <stdio.h>
#include "main.h"
/*
Name          :NIHALRAJEEV P
Date          :
Description   :
Sample input  :
Sample output :
*/

int main(int argc,char *argv[])
{
    int mode = validate(argc,argv);
    if(mode == 1)
    {
	help();                                               //help menu
    }
    else if(mode == 2)
    {
	if(mp3_view(argv) == SUCCESS)                           //view function call
	{
	    printf("------------------DONE--------------\n");
	}
	else
	{
	    printf("------------------Failure-----------\n");
	}

    }
    else if(mode == 3)
    {
	Mp3edit(argv);                         //edit function call
    }
    else
    {
	fprintf(stderr, "ERROR: ./a.out : INVALID ARGUMENTS\n");
	fprintf(stderr, "USAGE:\n");
	fprintf(stderr, "To view please pass like : ./a.out -v mp3file_name\n");
	fprintf(stderr, "To edit please pass like : ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3file_name\n");
	fprintf(stderr, "To get help pass link    : ./a.out --help\n");

    }



}

int validate(int argc,char *argv[])
{
    if(argc == 2 && !strcmp(argv[1],"--help"))
    {
	return 1;
    }
    else if(argc == 3 && !strcmp(argv[1],"-v"))
    {
	if((strstr(argv[2],".") != NULL) && (!strcmp(strstr(argv[2],"."),",.mp3")))
	{
	return 2;                                              //returing 2 for view
	}
    }
    else if(argc == 5 && !strcmp(argv[1],"-e"))
    {
	char *edit[6] = {"-t","-a","-A","-y","-m","-c"};            //array of string containing options available
	int i = 0;
	for(i = 0 ; i < 6 ; i++)
	{
	    //printf("vasu");
	    if(!strcmp(edit[i],argv[2]))
	    {
		break;
	    }
	}
	if(i != 6)
	{
	    if(strstr(argv[4],".") != NULL && !strcmp(strstr(argv[4],"."),".mp3"))
	    {
		return 3;
	    }
	}
    }
    else
    {
	printf("vasu");
	return 0;
    }


}


void help(void)
{
      printf("--------------------------HELP MENU-------------------------\n\n");
      printf("1. -v ---> To view MP3 file contents\n");
      printf("2. -e ---> To edit MP3 file contents\n");
      printf("    2.1   -t  ---> To edit song title\n");
      printf("    2.2   -a  ---> To edit artist name\n");
      printf("    2.3   -A  ---> To edit album name\n");
      printf("    2.4   -y  ---> To edit year\n");
      printf("    2.5   -m  ---> To edit content\n");
      printf("    2.6   -c  ---> To edit comment\n");
      printf("--------------------------------------------------------------\n");

 }


