#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "zoomrecs.h"

typedef struct ZoomRecord *ZoomRecord;


ZoomRecord createNode();
ZoomRecord addZoomRecord(ZoomRecord head, char name[], char email[], int lab, int duration);
void generateAttendance(ZoomRecord head, FILE *outFile);
void freeList(ZoomRecord head);

int main(int argc, char* argv[]){
	
	FILE *file=fopen(argv[1], "r");	
	
	char line[200];
	char* token;
	int count = 0;
	int skip = 0;
	
	struct ZoomRecord *head=NULL;//Head pointer of the linked list

	while (fgets(line,sizeof(line),file))
	{
		
		char email[60];
		char name[60];
		int durations[9]={0};
		int labLetter;

		if (skip==1)
		{
			count = 0;
			token = strtok(line, ",");

			while(token!=NULL)
			{
				switch(count)
				{
					case 0:
						strcpy(email,token);
						break;
					case 1:
						strcpy(name,token);
						break;
					case 2:
						labLetter=token[0]; //"Converts" string to char (int)
						break;
					case 3:
						durations[labLetter-65]=atoi(token);
						break;
				}
				token = strtok(NULL, ",");
				count++;
				
			}
			head=addZoomRecord(head,name,email,labLetter,durations[labLetter-65]);
		}
		skip=1;
	}

	fclose(file);
	
       	FILE *outFile = fopen(argv[2],"w");
       	generateAttendance(head,outFile);
        
       	fclose(outFile);
        
       	freeList(head); //Free all used memory for nodes
       	return 0;
}
