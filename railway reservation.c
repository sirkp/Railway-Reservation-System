#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdbool.h> 
#include<malloc.h>
#define CAPACITY 5

typedef struct Nodes//ticket
{
	int pnr;
	char name[20];
	int age;
	char status[20];
	struct Nodes* next;
} Node;

Node *head;//Linked list which stores confirmed tickets
Node *front;//queue stores waiting passengers
Node *rear;
int count_queue=0;//total element in queue
int count_linkedList=0;//total element in list
int num=11287;//to generate unique pnr

Node* create()//create a node
{
	Node *newNode;
	newNode=(Node*)malloc(sizeof(Node));
	num++;//as soons as node created, pnr is incremented
	newNode->pnr=num;
	printf(" Name: ");
	scanf("%s", newNode->name);
	printf(" Age : ");
	scanf("%d", &newNode->age);
	newNode->next=NULL;

	return newNode;
}

void push(Node* newNode)//push a node in linked list
{
	Node* itr = head;
	if(head==NULL)
	head = newNode;
	else
	{
		while(itr->next!=NULL)
		itr = itr->next;	
		itr->next = newNode;
	}	
}

void enque(Node* newNode)//enque in queue
{

	if(rear==NULL)
	{
		rear = newNode;
		front = rear;
	}
	else
	{
		rear->next = newNode;
		rear = newNode;
	}
}

int reserve(Node *head)//reserves ticket returns 1 if confirmed else 0
{
	
	Node* newNode = create(head);
	if(count_linkedList<CAPACITY)//seats are available, push in list
	{
		char ch[] = "Confirmed";
		strcpy(newNode->status,ch);
		push(newNode);	
		count_linkedList++;
		return 1;
	}
	else// push in queue
	{
		char ch[] = "Waiting";
		strcpy(newNode->status,ch);
		enque(newNode);
		count_queue++;
		return 0;
	}
}

bool pop(int pnr)// remove a element from list
{
	bool success=false;
	Node* itr = head;
	Node* prevNode=NULL;
	while(itr!=NULL&&itr->pnr!=pnr)
	{
		prevNode = itr;
		itr = itr->next;
	}

	if(itr != NULL)
	{
		if(prevNode==NULL)
		head = itr->next;
		else
		{
			prevNode->next = itr->next;
			free(itr);
		}	
		success = true;
	}
	return success;	
}

Node* deque(int pnr)// remove a element from queue
{
	Node* itr = front;
	Node* prevNode=NULL;
	while(itr!=NULL&&itr->pnr!=pnr)
	{
		prevNode = itr;
		itr = itr->next;
	}

	if(itr != NULL)
	{
		if(prevNode==NULL)
		{
			front = itr->next;
			if(front==NULL) 
			rear = NULL;	
		}
		else
		prevNode->next = itr->next;
		
		return itr;	
	}
	else
	free(itr);	
	return NULL;	
}

Node* getFront(){return front;}// returns front of queue

void cancel(int pnr)//cancel ticket
{
	bool success = pop(pnr);
	if(success)//confirmed ticket to be cancelled
	{
		count_linkedList--;
		printf(" Ticket cancelled Successfully\n");

		Node* newNode = getFront();
		if(newNode!=NULL)//push a passenger from waiting list to confirmed list
		{
			Node* temp = deque(newNode->pnr);
			count_queue--;
			char ch[] = "Confirmed";
			strcpy(newNode->status,ch);
			newNode->next = NULL;
			push(newNode);	
			count_linkedList++;
		}
	}
	else//waitlisted ticket to be deleted
	{
		Node* temp = deque(pnr);
		if(temp!=NULL)
		{
			printf(" Ticket cancelled Successfully\n");
			count_queue--;
			free(temp);
		}
		else
		printf(" Invalid PNR entered\n"); 
	}
}

void print(Node* itr)
{
	while(itr!=NULL)
	{
		printf("\n PNR: %d\n", itr->pnr);
		printf(" Name : %s\n", itr->name);
		printf(" Age : %d\n", itr->age);
		printf(" Status : %s\n\n", itr->status);
		itr=itr->next;
    }
}

void display()
{
	printf("\n Confirmed Tickets-\n");
	if(count_linkedList>0)
	print(head);
	else
	printf(" No Booking!\n");	
	printf(" Waiting List-\n");
	if(count_queue>0)
 	print(front);
 	else
 	printf(" No Waiting\n");   
}

int main()
{
	int choice, status=0,canc=0, pnr=0;
	head=NULL;
	rear=NULL;
	front=NULL;
	
	
	
	printf("\t\t\t***RAILWAY RESERVATION***\t\t\t\t\n");
	int ch =0;
	while(ch!=4)
	{
	printf("\n\n Do you want to - \n 1. Reserve a ticket? \n 2. Cancel Booking \n 3. Display passenger details \n 4. exit\n\n");
	printf(" choice: ");	
	scanf("%d", &choice); 
	switch(choice)
	{	
		case 1 :  status=reserve(head);
	              if(status==0)
	                printf("\n Booking Full!! \nYou are added to waiting list.Your PNR is %d and Waiting list number is %d \n",num,count_queue);
	              else
	                printf(" \nBooking Successful!!! Enjoy your journey! Your PNR is %d\n\n", num);
	              break;
	        
	    case 2:   printf(" \n Enter the PNR to be cancelled: ");
	              scanf(" %d", &pnr);
	              if(pnr>num)
	              printf(" Invalid PNR!!\n");
	              else
	              cancel(pnr);
	              break;
	              
	    case 3: display();
	    break;
	    case 4: exit(0);   
	    break;
	    default: printf("\n Wrong choice!\n");       
	}
	
}

}
