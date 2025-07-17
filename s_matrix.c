#include<stdio.h>
#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct node
{ 
	int rowi, columni; 
	double value; 
	struct node* nxtinr; 
	struct node* nxtinc; 
}node;

typedef struct matrix 
{
	node **rowList;		/* rowList is a pointer to the array of rows */
	node** columnList; 	/* column list is a pointer to the array of columns.*/
	int rows, columns; 	/* store the number of rows and columns of the matrix */
}matrix;



matrix *create_smatrix(int m , int n)
{
	matrix *SM = (matrix *)malloc(sizeof(matrix));
	SM->rows = m;
	SM->columns = n;
	SM->rowList = (node **) calloc(m , sizeof(node*));
	SM->columnList = (node **) calloc(n , sizeof(node*));

	return SM;	
}

void print_smatrix(matrix *sm)
{
	int cno;
	for(int i = 0; i < sm->rows; i++)
	{
		node *inrow = *(sm->rowList+i);
		cno=0;

		while(cno < sm->columns)
		{
			if(inrow==NULL)
			{
                                printf("0.0\t");
				cno++;
			}

			else 
			{
				if(inrow->columni == cno)
				{
					while(inrow != NULL && inrow->columni == cno )
					{
						printf("%.1f\t",inrow->value);
						inrow=inrow->nxtinr;
						cno++;
					}
				}
				else
				{
					while(inrow->columni - cno > 0)
					{
						printf("0.0\t");
						cno++;
					}
				}
				
			}			
		}
		printf("\n\n");
	}
	
}

void insert_at_beg(matrix *sm)
{
	/* inreasing one row and one column in matrix */
	sm->rows+=1;
        sm->columns+=1;
	sm->rowList = (node **) realloc(sm->rowList ,(sm->rows)*sizeof(node*));
        sm->columnList = (node **) realloc(sm->columnList ,(sm->columns)*sizeof(node*));

	node *newnode = (node *)malloc(sizeof(node));
	newnode->rowi=0;
	newnode->columni=0;
	newnode->nxtinr=NULL;
	newnode->nxtinc=NULL;
	printf("newnode added(matrix expanded), enter the value at index (0,0):");
	scanf("%lf", &newnode->value);
	

	sm->rowList += sm->rows-1;
	sm->columnList += sm->columns-1;

	int rcounter = sm -> rows-1;
	int colcounter = sm -> columns-1;
	while(rcounter)
	{
		*(sm->rowList) = *(sm->rowList - 1);
		(sm->rowList)--;
		rcounter--;		
	}

	while(colcounter)
	{
		*(sm->columnList) = *(sm->columnList - 1);
		(sm->columnList)--;
		colcounter--;
	}

	*(sm->rowList)=newnode;
	*(sm->columnList)=newnode;


	/* update index */
	for(int i = 1; i < sm->rows; i++)
        {
                node *inrow = *(sm->rowList+i);

                if(inrow==NULL)
                        continue;
                else
                {
                        while(inrow != NULL)
                        {
                                inrow->rowi += 1;
                                inrow->columni += 1;
                                inrow=inrow->nxtinr;

                        }
                }
        }
}


int duplicate(matrix *sm , double dupvalue )
{
        for(int i = 0; i < sm->rows; i++)
        {
                node *inrow = *(sm->rowList+i);

                if(inrow==NULL)
                        continue;
                else
                {
                        while(inrow != NULL)
                        {
                                if(inrow->value == dupvalue )
					return 1;
				inrow=inrow->nxtinr;
			}
                }
        }

	return 0;

}


void insert_node(matrix *sm)
{
	node *newnode = (node *)malloc(sizeof(node));

	printf("enter row(0 - %d) and column(0 - %d) of node:\n",sm->rows - 1 , sm->columns - 1);
	scanf("%d",&newnode->rowi);
	scanf("%d",&newnode->columni);
	printf("enter value in the node:\n");
	scanf("%lf",&newnode->value);
	newnode->nxtinr=NULL;
	newnode->nxtinc=NULL;
	
	/* for rows */
	if(*(sm->rowList + newnode->rowi) == NULL)
		*(sm->rowList + newnode->rowi) = newnode;

	else
	{
		if( newnode->columni < (*(sm->rowList + newnode->rowi)) -> columni )
                {
                        newnode->nxtinr = *(sm->rowList + newnode->rowi);
                        *(sm->rowList + newnode->rowi) = newnode;
                }
                else
                {
                        node *inrow = *(sm->rowList + newnode->rowi);
                        while(inrow->nxtinr!=NULL)
                        {
                                if( (inrow->nxtinr)->columni > newnode->columni )
                                {
                                        newnode->nxtinr = inrow->nxtinr;
                                        inrow->nxtinr = newnode;
					break;
                                }
                                inrow = inrow->nxtinr;
                        }
                        if(inrow->nxtinr==NULL)
                                inrow->nxtinr = newnode;
                }
	}
	
	/* for columns */
	if(*(sm->columnList + newnode->columni) == NULL)
		*(sm->columnList + newnode->columni) = newnode;
	
	else
        {
                if( newnode->rowi < (*(sm->columnList + newnode->columni)) -> rowi )
                {
			newnode->nxtinc = *(sm->columnList + newnode->columni);
                        *(sm->columnList + newnode->columni) = newnode;
                }
                else
                {
			node *incol = *(sm->columnList + newnode->columni);
                        while(incol->nxtinc!=NULL)
			{
                         	if( (incol->nxtinc)->rowi > newnode->rowi )
				{
					newnode->nxtinc = incol->nxtinc;
					incol->nxtinc = newnode;
					break;
				}
				incol = incol->nxtinc;
			}
			if(incol->nxtinc==NULL)
				incol->nxtinc = newnode;	
                }
        }		
}

int resize(matrix **sm)
{
	(*sm)->rows *= 2;
	(*sm)->columns *= 2;

	(*sm)->rowList = (node **) realloc( (*sm)->rowList ,  (*sm)->rows * sizeof(node*) );
        (*sm)->columnList = (node **) realloc( (*sm)->columnList ,  (*sm)->columns * sizeof(node*) );
	
	if( (*sm)->rowList == NULL || (*sm)->columnList == NULL)
	{
		printf("matrix is not resized(doubled), memory allocation failed!\n");
		return 1;
	}

	(*sm)->rowList += (*sm)->rows/2 - 1;
        (*sm)->columnList += (*sm)->columns/2 - 1;

        int rowcounter = (*sm) -> rows/2;
	int colcounter = (*sm) -> columns/2;

	while(rowcounter)
	{
		*( (*sm)->rowList + (*sm)->rows/2 ) = *( (*sm)->rowList );
		*( (*sm)->rowList ) = NULL; 
		if(rowcounter>1)	
			((*sm)->rowList)--;
		rowcounter--;		
	}

	while(colcounter)
        {
                *( (*sm)->columnList + (*sm)->columns/2 ) = *( (*sm)->columnList );
		*( (*sm)->columnList ) = NULL;
                if(colcounter>1) 
			((*sm)->columnList)--;
                colcounter--;
        }



	/* update index */
        for(int i = 0; i < (*sm)->rows; i++)
        {
                node *inrow = *( (*sm)->rowList+i );

                if(inrow==NULL)
                        continue;
                else
                {
                        while(inrow != NULL)
                        {
                                inrow->rowi += (*sm)->rows/2;
                                inrow->columni += (*sm)->columns/2;
                                inrow=inrow->nxtinr;

                        }
                }
        }

	return 0;

	

}

void transpose(matrix *m , matrix *tm)
{
 	for(int i = 0; i < m->columns; i++)
        {
                node *temp = *(m->columnList+i);
                if(temp==NULL)
                        continue;
                else
                {	while(temp)
			{
				node *newnode = (node *)malloc(sizeof(node));
				newnode->rowi = temp->columni;
            			newnode->columni = temp->rowi;
            			newnode->value = temp->value;
				newnode->nxtinr=NULL;
        			newnode->nxtinc=NULL;

        			/* for rows */
       				if(*(tm->rowList + newnode->rowi) == NULL)
                			*(tm->rowList + newnode->rowi) = newnode;

        			else
        			{
                			if( newnode->columni < (*(tm->rowList + newnode->rowi)) -> columni )
                			{
                       	 			newnode->nxtinr = *(tm->rowList + newnode->rowi);
                        			*(tm->rowList + newnode->rowi) = newnode;
                			}
                			else
                			{
                        			node *inrow = *(tm->rowList + newnode->rowi);
                        			while(inrow->nxtinr!=NULL)
                        			{
                                			if( (inrow->nxtinr)->rowi > newnode->rowi )
                                			{
                                        			newnode->nxtinr = (inrow->nxtinr);
                                        			(inrow->nxtinr) = newnode;
                                			}
                                			inrow = inrow->nxtinr;
                        			}
                        			if(inrow->nxtinr==NULL)
                                			inrow->nxtinr = newnode;
                			}
        			}

        			/* for columns */
        			if(*(tm->columnList + newnode->columni) == NULL)
                			*(tm->columnList + newnode->columni) = newnode;

        			else
        			{
                			if( newnode->rowi < (*(tm->columnList + newnode->columni)) -> rowi )
                			{
                        			newnode->nxtinc = *(tm->columnList + newnode->columni);
                        			*(tm->columnList + newnode->columni) = newnode;
                			}
                			else
                			{
                        			node *incol = *(tm->columnList + newnode->columni);
                        			while(incol->nxtinc!=NULL)
                        			{
                                			if( (incol->nxtinc)->columni > newnode->columni )
                                			{
                                        			newnode->nxtinc = (incol->nxtinc);
                                        			(incol->nxtinc) = newnode;
                                			}
                                			incol = incol->nxtinc;
                        			}
                        			if(incol->nxtinc==NULL)
                                			incol->nxtinc = newnode;
                			}
        			}
				temp=temp->nxtinc;
			}



			                       	
                }
        }	
}


void destroy(matrix *sm)
{
	for(int i = 0; i < sm->rows; i++)
        {
                node *temp = *(sm->rowList+i), *inrow = *(sm->rowList+i);

                if(inrow==NULL)
                        continue;
                else
                {
                        while(inrow != NULL)
                        {
                                inrow=inrow->nxtinr;
				free(temp);
				temp=inrow;
                        }
                }
        }
	free(sm->rowList);
	free(sm->columnList);
	free(sm);

        
}
int main()
{
        printf("enter the size of matrix(m X n):\n");
        int m,n;
        scanf("%d",&m);
        scanf("%d",&n);
        matrix *mysm = create_smatrix(m,n);

	char choice='y';
	while(choice == 'y' || choice == 'Y')
	{
		insert_node(mysm);
		getchar();
		printf("do you want to insert another node?\n");
		scanf("%c",&choice);
	}
	print_smatrix(mysm);

	insert_at_beg(mysm);
	print_smatrix(mysm);

	int a = duplicate(mysm , 1);
	printf("%d\n",a);

	resize(&mysm);
	print_smatrix(mysm);

	matrix *mtm = create_smatrix(mysm->columns , mysm->rows);
       	transpose(mysm , mtm);
	printf("\n");
	print_smatrix(mtm);

	destroy(mysm);
	destroy(mtm);


return 0;
}
