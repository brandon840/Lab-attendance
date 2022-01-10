#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "zoomrecs.h"

typedef struct ZoomRecord *ZoomRecord;

ZoomRecord createNode(){
	ZoomRecord temp;
	temp=(struct ZoomRecord*)malloc(sizeof(struct ZoomRecord));

	if (temp==NULL){
		printf("Error! program ran out of memory");
	        return NULL;
	}

	temp->next = NULL;

	//Initialize all elements in durations[] to 0
	int i;
	for(i=0;i<9;i++)
	{
	temp->durations[i]=0;
	}

	return temp;
}


ZoomRecord addZoomRecord(ZoomRecord head, char name[], char email[], int lab, int duration){
	
	//Create a new node with corresponding attributes
	ZoomRecord temp = createNode();
	strcpy(temp->name,name);
	strcpy(temp->email,email);
	temp->durations[lab-65]=duration;

	ZoomRecord p,beforep;

	//Check if list is empty at the start
	if (head==NULL){
		head=temp;
		return head;
	}
	
	if(head->next == NULL)
	{
		if(strcmp(temp->email,head->email)<0) //temp comes before the current head alphabetically
		{
			p=head;
			head=temp;
			head->next=p;

		}
		else if(strcmp(temp->email,head->email)==0) //Same email id
		{
			head->next = temp;
			head->durations[lab-65]+=duration;
		}
		else
		{
			head->next = temp;
		}
		
		return head;
	}	
	
	int firstNode = 0; //Used to next beforep at the right timing
	int count = 0;
	p=head;

	while(p->next!=NULL) //Check for alphabetical order
	{ 
		if (strcmp(temp->email,p->email)==0)
		{
			p->durations[lab-65]+=duration;
			return head;
		}
		else if(strcmp(temp->email,p->email)>0) //temp comes after p alphabetically
		{
			if(firstNode == 0)
			{
				p=p->next;
				beforep=head;
			}else{
				p=p->next;
				beforep=beforep->next;
			}

		}
		else //temp comes right before p alphabetically
		{
			if(firstNode == 0)
			{
				head=temp;
				head->next=p;
			}
			else
			{
				beforep->next=temp;
				temp->next=p;
			}
			return head;
		}
		firstNode=1;
	}


	if(strcmp(temp->email,p->email)>0)
	{
		p->next=temp;
	}
	else if(strcmp(temp->email,p->email)<0)
	{
		beforep->next=temp;
		temp->next=p;
	}
	else
	{
		p->durations[lab-65]+=duration;
	}

	return head;

}

void generateAttendance(ZoomRecord head,FILE *outFile){

	ZoomRecord p=head;

	fprintf(outFile, "User Email,Name (Original Name),A,B,C,D,E,F,G,H,I,Attendance (Percentage)\n");
	while(p!=NULL)
	{
		int count=0;
		int i=0;
		for(i=0;i<10;i++)
		{
			if(p->durations[i]==0){continue;}
			count++;
		}
		
		float score=(count/9.0)*100;

		fprintf(outFile, "%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%.2f\n", p->email,p->name,p->durations[0],p->durations[1],p->durations[2],p->durations[3],p->durations[4],p->durations[5],p->durations[6],p->durations[7],p->durations[8],score);
		p=p->next;
	}


	return;
}

void freeList(ZoomRecord head)
{
	ZoomRecord tmp;

	while (head!=NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}
