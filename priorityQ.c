#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct patient
{
	char name[10];
	int priority;
	struct patient *next; 

}patient;

patient *PQ()
{
	patient *newpatient = NULL;
	return newpatient;
}


void display_patientQ(patient *head)
{
	if(head==NULL)
		printf("{} (empty)\n");
	else
	{
		printf("{ ");
		patient *temp = head;
		while(temp)
		{
			printf("%d:",temp->priority);
			printf("%s ",temp->name);
			if(temp->next!=NULL) printf(", ");
			temp=temp->next;
		}
		printf("}(not empty)\n");
	}
}

void newPT(patient **head)
{
	patient *newpatient = (patient *)malloc(sizeof(patient));
	printf("Name ? ");
	scanf("%s",newpatient->name);
	printf("Priority ? ");
	scanf("%d",&newpatient->priority);
	newpatient->next=NULL;

	if(*head == NULL)
		*head = newpatient;
	else
	{
		if(newpatient->priority < (*head)->priority )
		{
			newpatient->next = *head;
			*head = newpatient;
			
		}

		else 
		{
			patient *temp = *head;
			
			while(temp->next &&  newpatient->priority >= (temp->next)->priority )
				temp=temp->next;

			if(temp->next==NULL)
				temp->next=newpatient;
			else
			{
				newpatient->next = temp->next;
				temp->next = newpatient;
			}
		}

		
	}
}

void frontPriority(patient **head)
{
	printf("{ %s:%d }",(*head)->name,(*head)->priority);
}

void upgradePT(patient **head)
{
	char pname[10];
	printf("Name ? \n");
	scanf("%s",pname);

	patient *current=*head , *prev=*head;
	while(current && strcmp(current->name , pname) != 0 )
	{
		prev=current;
		current=current->next;
	}
	if(current==NULL)
	{
		printf("patient does not exist !\n");
		return;
	}

	prev->next = current->next;
	free(current);

	patient *newpatient  = (patient *)malloc(sizeof(patient));
	strcpy(newpatient->name , pname);
	printf("New Priority ?\n");
	scanf("%d",&newpatient->priority);
	newpatient->next=NULL;

	if(newpatient->priority < (*head)->priority )
        {
        	newpatient->next = *head;
                *head = newpatient;
	}

        else
        {
                patient *temp = *head;

                while(temp->next &&  newpatient->priority >= (temp->next)->priority )
                	temp=temp->next;

                if(temp->next==NULL)
                        temp->next=newpatient;
                else
                {
                	newpatient->next = temp->next;
                        temp->next = newpatient;
                }
         }

}

void processPT(patient **head)
{
	patient *temp=*head;
	*head=(*head)->next;
	free(temp);
}

void clear(patient **head)
{
	patient *temp = *head;
	
	while(temp)
	{
		patient *prev = temp;
		temp=temp->next;
		free(prev);
	}
	*head = NULL;
}

int main()
{
	patient *head = PQ();
	char choice = 1;
	while(choice != 'Q')
	{
		printf("\ncurrent patient queue:\n");

		display_patientQ(head);
		
		printf("N)ew, F)ront, U)pgrade, P)rocess, C)lear, Q)uit? : ");
		scanf("%c",&choice);
		switch(choice)
		{
			case 'N':
				newPT(&head);
				break;
				
			case 'F':
				frontPriority(&head);
				break;

			case 'U':
				upgradePT(&head);
				break;

			case 'P':
				processPT(&head);
				break;

			case 'C':
				clear(&head);
				break;

			default:
				printf("invalid choice!\n");
				break;
		}
		getchar();
	}
	printf("exiting...\n.");
	return 0;
}
