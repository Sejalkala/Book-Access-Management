

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/*
Assumptions
1. name of book,student is of a single word.
2. in every month there are 30 days.
*/
struct book_list
{
    /* data */
    char Title[50];
    char author[50];
    char subject[50];
    int number_of_copies_issued;
    int number_of_copies_available;
    struct book_list *next;
    struct book_list *prev;
};
struct request_queue
{
    char Name_of_the_student[50];
    char title_of_the_book_asking_for[50];
    struct request_queue *next;
    struct request_queue *prev;
};
struct borrower_list
{
    char Name_of_the_student[50];
    char title_of_the_book[50];
    int date_of_issue[3]; // date at which book was given to student
    int date_of_return[3];// date at which student returned the book
    struct borrower_list *next;
    struct borrower_list *prev;
};


//head of the three linked lists
struct book_list *head_book_list=NULL;
struct request_queue *head_request_queue=NULL;
struct borrower_list *head_borrower_list=NULL;


//supporting functions
int book_list_by_name(char arr[50],struct request_queue *head_request_queue); //returns no of occurances of a given name in request_queue
int no_bo_list_by_name(char arr[50],struct borrower_list *head_borrower_list);//returns no of occurances of a given name in borrower_list
int no_re_queue(char arr[50],struct request_queue *head_request_queue);//no of occurances of a given title in request_queue
int no_bo_list(char arr[50],struct borrower_list *head_borrower_list);//no of occurances of a given title in boroweer_list
void make_available(char arr[50],struct book_list* *head_book_list);//if a book is returned,this functions make sure that the book is now available
void print_book_list(struct book_list *head_book_list);//prints the book_list
void print_request_queue(struct request_queue *head_request_queue);//prints request_queue
void print_borrower_list(struct borrower_list *head_borrower_list);//prints borrower_list
int no_of_days(int d1[3],int d2[3]);//calculates the no of days between the two given dates
int isDefaulter(char arr[50],struct borrower_list *head_borrower_list);//checks if the given name is defaulter or not
int isBook_available(char arr[50],struct book_list *head_book_list);//checks if the book with given title is available or not
int willget_theBook(char arr[50],struct borrower_list *head_borrower_list);//no of occurances in borrower list
int count_request(char arr_name[50],char arr_title[50],struct request_queue *head_request_queue);////no of occurances in request_queue


//merge sort supporting functions
struct book_list *split(struct book_list *head);
struct book_list *merge(struct book_list *first, struct book_list *second);


//function to insert nodes in linked lists
void insert_book_list(char arr_title[50],char arr_author[50],char arr_subject[50],struct book_list* *head_book_list);
void insert_request_queue(struct request_queue* *head_request_queue);
void insert_borrower_list(struct borrower_list* *head_borrower_list,struct request_queue* *head_request_queue);
void return_book(struct borrower_list* *head_borrower_list,struct book_list* *head_book_list);


//main functions
//Question 1
void Display_names(struct request_queue *head_request_queue,struct borrower_list *head_borrower_list);
//Question 2
void Book_in_mostDemand(struct book_list *head_book_list);
//Question 3
void No_ofBooks_givenin_3Days(struct book_list *head_book_list,struct borrower_list *head_borrower_list);
//Question 4
void Sort_borrower_list(struct borrower_list *head_borrower_list);
//Question 5
struct book_list *mergeSort(struct book_list *head);
//Question 6
void DisplayDefaulter(struct request_queue* *head_request_queue);
//Question 7
void Display_students(struct borrower_list *head_borrower_list,struct request_queue *head_request_queue);
//Question 8
void Display_requested_books(struct request_queue *head_request_queue,struct book_list *head_book_list);
//Question 9
void Display_title(struct book_list *head_book_list,struct request_queue *head_request_queue,struct borrower_list *head_borrower_list);
//Question 10
void Students_withMaxNo_ofBooks(struct request_queue *head_request_queue);

int main()
{
    printf("\n                    WELCOME                    \n");
    printf("\n                      TO                       \n");
    printf("\n                    SEJAL'S                    \n");
    printf("\n            BOOK ACCESS MANAGEMENT SYSTEM      \n");

    printf("\n We have following list of books \n");
    printf("\nNAME  AUTHOR  SUBJECT  AVAILABLE_COPIES ISSUED_COPIES \n");
    insert_book_list("atomic","gina","motivational",&head_book_list);
    insert_book_list("space","john","scifi",&head_book_list);
    insert_book_list("kalam","ross","biography",&head_book_list);
    insert_book_list("happiness","neha","motivational",&head_book_list);
    insert_book_list("courage","rachel","motivational",&head_book_list);
    insert_book_list("earth","monica","scifi",&head_book_list);
    insert_book_list("life","chandler","motivational",&head_book_list);
    insert_book_list("family","lisa","biography",&head_book_list);
    insert_book_list("emily","sejal","biography",&head_book_list);
    insert_book_list("success","simran","motivational",&head_book_list);
    print_book_list(head_book_list);
    int flag_1=1;
    while(flag_1>0)
    {
         
        printf("\n1. Request a book\n");
        printf("\n2. Return book\n");
        printf("\n3. Insert directly in request_queue\n");
        int n;
        scanf("%d",&n);
        if(n==1)
        {
            insert_borrower_list(&head_borrower_list,&head_request_queue);
        }
        else if(n==2)
        {
            return_book(&head_borrower_list,&head_book_list);
        }
        else if(n==3)
        {
            insert_request_queue(&head_request_queue);
        }
        printf("\nEnter 0 to get out of this loop and 1 to continue\n");
        scanf("%d",&flag_1);
        printf("\n");
      }
    printf("\n updated book list \n");
    print_book_list(head_book_list);
    int flag_2=1;
    while(flag_2>0)
    {
        int option;
        printf("\nEnter the correct option number\n");
        printf("\n1.Display the name of the students who will get books\n");
        printf("\n2. find the book in most demand\n");
        printf("\n3.Within first 3 days how many books can be given to the students\n");
        printf("\n4.Sort the borrower_list according to the number of books issued in descending order.\n");
        printf("\n5.Sort and display the title and authors name for all books of a particular subject on the basis of number_of_copies_available.\n");
        printf("\n6.Remove the defaulters from the request_queue and insert them into a new list named as defaulter_list. Display the defaulter_list.\n");
        printf("\n7.Display the names of the students who have already borrowed books and are asking for other books.\n");
        printf("\n8.Display the names of the requested books whose copies are available.\n");
        printf("\n9.Display the title of all the books which have not been issued by anyone.\n");
        printf("\n10.Display the name of the student/s who has requested for the maximum number of books\n");
        scanf("%d",&option);
        switch(option)
        {
            case 1:
            {
                Display_names(head_request_queue,head_borrower_list);
                break;
            }
            case 2:
            {
                Book_in_mostDemand(head_book_list);
                break;
            }
            case 3:
            {
                No_ofBooks_givenin_3Days(head_book_list,head_borrower_list);
                break;
            }
            case 4://pending
            {
                Sort_borrower_list(head_borrower_list);
                break;
            }
            case 5:
            {
                head_book_list= mergeSort(head_book_list);
                print_book_list(head_book_list);
                break; 
            }
            case 6:
            {
                DisplayDefaulter(&head_request_queue);
                break;
            }
            case 7:
            {
                Display_students(head_borrower_list,head_request_queue);
                break;
            }
            case 8:
            {
                Display_requested_books(head_request_queue,head_book_list);
                break;
            }
            case 9:
            {
                Display_title(head_book_list,head_request_queue,head_borrower_list);
                break;
            }
            case 10:
            {
                Students_withMaxNo_ofBooks(head_request_queue);
                break;
            }
            default:
            {
                printf("\nEnter the correct option number");
                break;
            }
        }

        scanf("%d",&flag_2);
    }
    printf("\n                                                 HAPPY READING!                                                 \n");
    printf("\n                                           THANK YOU -BT20CSE057,SEJAL KALA                                      \n");
    return 0;
}


/*************************************************************************************************/
//Question 1
void Display_names(struct request_queue *head_request_queue,struct borrower_list *head_borrower_list)
{
    struct request_queue *temp=head_request_queue;
    while(temp!=NULL)
    {
        int a=willget_theBook(temp->Name_of_the_student,head_borrower_list);
        int b=count_request(temp->Name_of_the_student,temp->title_of_the_book_asking_for,head_request_queue);
        if(a+b<4)
        {
            printf("\n %s \n",temp->Name_of_the_student);
        }
        temp=temp->next;
    }
}
//Question 2
void Book_in_mostDemand(struct book_list *head_book_list)
{
    char arr[50];
    struct book_list *temp=head_book_list;
    int max=0;
    while(temp!=NULL)
    {
        int a=no_re_queue(temp->Title,head_request_queue);
        int b=no_bo_list(temp->Title,head_borrower_list);
        if(max<a+b)
        {
            strcpy(arr,temp->Title);
            max=a+b;
        }
        temp=temp->next;
    }
    if(max==0)
    {
        printf("\n Not a specific book\n");
    }
    else
    {
        printf("\nThe book with most demand is %s \n",arr);
    }
}
//Question 3
void No_ofBooks_givenin_3Days(struct book_list *head_book_list,struct borrower_list *head_borrower_list)
{
    struct book_list *temp=head_book_list;
    int a=0;
    while(temp!=NULL)
    {
        a=a+temp->number_of_copies_available;
        temp=temp->next;
    }
    struct borrower_list *t=head_borrower_list;
    while(t!=NULL)
    {
        if(t->date_of_return[0]=='\0')
        {
            printf("\n enter the present date:");
            int date[3];
            int i;
            for(i=0;i<3;i++)
            {
                scanf("%d",&date[i]);
                int b=no_of_days(t->date_of_issue,date);
                if(b+3<15)
                {
                    a++;
                }
            }
        }
        else
        {
            a++;
        }
        t=t->next;
    }
    printf("\n no of books : %d",a);
}
//Question 4
void Sort_borrower_list(struct borrower_list *head_borrower_list)
{
    struct borrower_list *temp=head_borrower_list;
    while(temp!=NULL)
    {
        printf("\n name of student:%s nmae of book:%s\n ",temp->Name_of_the_student,temp->title_of_the_book);
        temp=temp->next;
    }
}

//Question 5

struct book_list *mergeSort(struct book_list *head)
{

	if (!head || !head->next)
		return head;
	struct book_list *second = split(head);

	// Recur for left and right halves
	head = mergeSort(head);
	second = mergeSort(second);

	// Merge the two sorted halves
	return merge(head,second);
}
//Question 6
void DisplayDefaulter(struct request_queue* *head_request_queue)
{
    struct request_queue *temp=*head_request_queue;
    while(temp!=NULL)
    {
        if(isDefaulter(temp->Name_of_the_student,head_borrower_list)==1)
        {
            printf("\n%s\n",temp->Name_of_the_student);
            temp->prev->next=temp->next;
            temp->next->prev=temp->prev;
            struct request_queue *r=temp->next;
            free(temp);
            temp=r;
        }
        else
        {
            temp=temp->next;
        }
    }
}
//Question 7
void Display_students(struct borrower_list *head_borrower_list,struct request_queue *head_request_queue)
{
    struct request_queue *temp=head_request_queue;
    while(temp!=NULL)
    {
        if(no_bo_list_by_name(temp->Name_of_the_student,head_borrower_list)>0)
        {
            printf("\n %s \n",temp->Name_of_the_student);
        }
        temp=temp->next;
    }
}
//Question 8
void Display_requested_books(struct request_queue *head_request_queue,struct book_list *head_book_list)
{
    struct request_queue *temp=head_request_queue;
    while(temp!=NULL)
    {
        if(isBook_available(temp->title_of_the_book_asking_for,head_book_list)==1)
        {
             printf("\n%s\n",temp->title_of_the_book_asking_for);
        }
        temp=temp->next;
    }
}
//Question 9
void Display_title(struct book_list *head_book_list,struct request_queue *head_request_queue,struct borrower_list *head_borrower_list)
{
    struct book_list *temp=head_book_list;
    while(temp!=NULL)
    {
        if(no_bo_list(temp->Title,head_borrower_list)==0 && no_re_queue(temp->Title,head_request_queue)==0)
        {
            printf("\n %s \n",temp->Title);
        }
        temp=temp->next;
    }
}
//Question 10
void Students_withMaxNo_ofBooks(struct request_queue *head_request_queue)
{
    int max=0;
    struct request_queue *temp=head_request_queue;
    while(temp!=NULL)
    {
        int a=book_list_by_name(temp->Name_of_the_student,head_request_queue);
        if(a>max)
        {
            max=a;
        }
        temp=temp->next;  
    }
    struct request_queue *t=head_request_queue;
    while(t!=NULL)
    {
        if(book_list_by_name(t->Name_of_the_student,head_request_queue)==max)
        {
            printf("\n %s \n",t->Name_of_the_student);
            break;
        }
        t=t->next;
    } 
}
/*************************************************************************************/

/******************************************************************************************/
void insert_book_list(char arr_title[50],char arr_author[50],char arr_subject[50],struct book_list* *head_book_list) 
{
    struct book_list *node_to_insert=(struct book_list* ) malloc(sizeof(struct book_list));    
    strcpy(node_to_insert->Title,arr_title);
    strcpy(node_to_insert->author,arr_author);
    strcpy(node_to_insert->subject,arr_subject);
    node_to_insert->number_of_copies_available=10;
    node_to_insert->number_of_copies_issued=0;
    
    struct book_list *temp=*head_book_list;
      
    //insert node_to_insert to book_list
    if(*head_book_list==NULL)// book_list is empty
    {   
        *head_book_list=node_to_insert;
    }
    else
    {    
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=node_to_insert;
        node_to_insert->prev=temp;
        node_to_insert->next=NULL;
    }
   
}
//function to request a book,i.e.,add a node in the request_queue
void insert_request_queue(struct request_queue* *head_request_queue)
{
    struct request_queue *node_to_insert=(struct request_queue* ) malloc(sizeof(struct request_queue*));
    printf("\nEnter your name\n");//name of the student
    scanf("%s",&node_to_insert->Name_of_the_student);
    printf("\nEnter the Title of the book you are asking for\n");
    scanf("%s",&node_to_insert->title_of_the_book_asking_for);
    struct request_queue *temp=*head_request_queue;
    if(*head_request_queue==NULL)
    {
        *head_request_queue=node_to_insert;
    }
    else
    {
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=node_to_insert;
        node_to_insert->prev=temp;
        node_to_insert->next=NULL;
    }
}

//insert node in borrower list
void insert_borrower_list(struct borrower_list* *head_borrower_list,struct request_queue* *head_request_queue)
{
    struct borrower_list *temp=(struct borrower_list* ) malloc(sizeof(struct book_list*));
    printf("\n Enter the name of the student\n");
    scanf("%s",&temp->Name_of_the_student);
    printf("\n Enter the title of the book \n");
    scanf("%s",&temp->title_of_the_book);
    if(isBook_available(temp->title_of_the_book,head_book_list)==1)
    {
        if(no_bo_list_by_name(temp->Name_of_the_student,*head_borrower_list)>=3)
        {
            printf("\n You've already borrowed 3 or more books,so we can't issue you another book.\n");
            printf("\n Do you want to still request it? we can issue the book if you,ve returned previous books.\n");
            printf("\nPlease enter 1 if this is the case,otherwise 0.\n thank you\n");
            int flag;
            scanf("%d",&flag);
            if(flag==1)
            {
                insert_request_queue(head_request_queue);
            }
        }
        else
        {
            printf("\n Enter the present date\n Note that the format should be dd mm yyyy\n");
            int i;
            for(i=0;i<3;i++)
            {
                scanf("%d",&temp->date_of_issue[i]);
            }
            struct borrower_list *t=(struct borrower_list* ) malloc(sizeof(struct borrower_list*));
            t=*head_borrower_list;
            if(*head_borrower_list==NULL)
            {
                *head_borrower_list=temp; 
            }
            else
            {
                while(t->next!=NULL)
                {
                    t=t->next;
                }
                t->next=temp;
                temp->prev=t;
                temp->next=NULL;
            }
            struct book_list *r=head_book_list;
            while(r!=NULL)
            {
                if(strcmp(r->Title,temp->title_of_the_book)==0)
                {
                    r->number_of_copies_issued+=1;
                    r->number_of_copies_available-=1;
                    break;
                }
                r=r->next;
            }
        }
    }
    else
    {
        printf("\n The given book is not available right now. \n");
        printf("\n Do you want to request it so that it will be issued to you whenever we have stock? \nplease enter one if this is the case ,otherwise zero.\n Thank you.\n");
        int flag;
        scanf("%d",&flag);
        if(flag==1)
        {
            insert_request_queue(head_request_queue);
        }
        else
        {
            return;
        }
    }
}
void return_book(struct borrower_list* *head_borrower_list,struct book_list* *head_book_list)
{
    printf("\n enter your name\n");
    char arr_name[50];
     scanf("%s",&arr_name);
    printf("\n enter the name of book you want to return");
    char arr_title[50];
    scanf("%s",&arr_title);
    struct borrower_list *temp=*head_borrower_list;
    while(temp!=NULL)
    {
        if(strcmp(temp->Name_of_the_student,arr_name)==0 && strcmp(temp->title_of_the_book,arr_title)==0)
        {
            make_available(temp->title_of_the_book,head_book_list);
            printf("\n enter the present date");
            int i;
            for(i=0;i<3;i++)
            {
                scanf("%d",&temp->date_of_return[i]);
            }
        }
        temp=temp->next;
    }
}
/***************************************************************************************/


/*****************************************************************************************/
//supporting functions
int book_list_by_name(char arr[50],struct request_queue *head_request_queue)
{
    if(head_request_queue==NULL)
    {
        return 0;
    }
    struct request_queue *temp=head_request_queue;
    int count=0;
    while(temp!=NULL)
    {
        if(strcmp(temp->Name_of_the_student,arr)==0)
        {
            count++;
        }
        temp=temp->next;
    }
    return count;
}

int no_bo_list_by_name(char arr[50],struct borrower_list *head_borrower_list)
{
    if(head_borrower_list==NULL)
    {
        return 0;
    }
   struct borrower_list *temp=head_borrower_list;
    int count=0;
    while(temp!=NULL)
    {
        if(strcmp(temp->Name_of_the_student,arr)==0)
        {
            count++;
        }
        temp=temp->next;
    }
    return count;
}

int no_re_queue(char arr[50],struct request_queue *head_request_queue)
{    
    struct request_queue *temp=head_request_queue;
    int count=0;
    while(temp!=NULL)
    {   
        if(strcmp(temp->title_of_the_book_asking_for,arr)==0)
        {
            count++;
        }
        temp=temp->next;
    }      
    return count;
}

//number of occurances in borrower_list
int no_bo_list(char arr[50],struct borrower_list *head_borrower_list)
{
    struct borrower_list *temp=head_borrower_list;
    int count=0;
    while(temp!=NULL)
    {
        if(strcmp(temp->title_of_the_book,arr)==0)
        {   
            count++;
        }   
        temp=temp->next;
    }       
    return count;
}

void make_available(char arr[50],struct book_list* *head_book_list)
{
    struct book_list *temp=*head_book_list;
    while(temp!=NULL)
    {
        if(strcmp(temp->Title,arr)==0)
        {
            temp->number_of_copies_issued-=1;
            temp->number_of_copies_available+=1;
            break;
        }
    }
}

void print_book_list(struct book_list *head_book_list)
{
  struct book_list *temp=head_book_list;
   while(temp!=NULL)
   { 
       printf("\n");
       printf("%s",temp->Title);
       printf(" ");
       printf("%s",temp->author);
       printf(" ");
       printf("%s",temp->subject);
       printf(" ");
       printf("available: %d ",temp->number_of_copies_available);
       printf("issued: %d ",temp->number_of_copies_issued);
       printf("\n");
        temp=temp->next;
    } 
}
// function to print the request_queue
void print_request_queue(struct request_queue *head_request_queue)
{
    printf("\n request queue:\n");
    struct request_queue *temp=head_request_queue;
    while(temp!=NULL)
    {
        printf("\n");
        printf("%s",temp->Name_of_the_student);
        printf(" ");
        printf("%s",temp->title_of_the_book_asking_for);
        printf("\n");
        temp=temp->next;
    }
}
//function to print borrower_list
void print_borrower_list(struct borrower_list *head_borrower_list)
{
    printf("\n Borrower list:\n");
    struct borrower_list *temp=head_borrower_list;
    while(temp!=NULL)
    {
       printf("\n");
        printf("\n %s \n",temp->Name_of_the_student);
        printf(" ");
        printf("\n %s \n",temp->title_of_the_book);
        printf("\n");
        temp=temp->next;
    }
}

int no_of_days(int d1[3],int d2[3])
{
    if(d1[2]==d2[2])
    {
        if(d1[1]==d2[1])
        {
            return d2[0]-d1[0];
        }
        else
        {
            if(d2[1]-d1[1]>1)
            {
                return 100;
            }
            else
            {
                return 30-d1[0]+d2[0];
            }
        }
    }
    else
    {
        return 100;
    }
}
//supporting function
int isDefaulter(char arr[50],struct borrower_list *head_borrower_list)
{
    struct borrower_list *temp1=head_borrower_list;
    while(temp1!=NULL)
    {
        if(strcmp(temp1->Name_of_the_student,arr)==0)
        {
            if(temp1->date_of_return[0]=='\0')
            {
                printf("\n enter the present date");
                int date[3];
                int i;
                for(i=0;i<3;i++)
                {
                    scanf("%d",&date[i]);
                }
                int a=no_of_days(temp1->date_of_issue,date);
                if(a<15)
                {
                    return 1;
                }
            }
            else
            {
                int b=no_of_days(temp1->date_of_issue,temp1->date_of_return);
                if(b<15)
                {
                    return 1;
                }
            }
        }
        temp1=temp1->next;
    }
    return 0;
}

int isBook_available(char arr[50],struct book_list *head_book_list)
{
   struct book_list *temp=head_book_list;
    while(temp!=NULL)
    {
        if(strcmp(temp->Title,arr)==0)
        {
            if(temp->number_of_copies_available>0)
            {
                return 1;
            }
        }
        temp=temp->next;
    }
    return 0;
}

int willget_theBook(char arr[50],struct borrower_list *head_borrower_list)
{
    struct borrower_list *temp=(struct borrower_list* ) malloc(sizeof(struct borrower_list*));
    temp=head_borrower_list;
    int count=0;
    while(temp!=NULL)
    {
        if(strcmp(temp->Name_of_the_student,arr)==0)
         {
            count++;
        }
        else
        {
            continue;
        }
        temp=temp->next;
    }
    return count;
}

int count_request(char arr_name[50],char arr_title[50],struct request_queue *head_request_queue)
{
    struct request_queue *temp=head_request_queue;
    int count=0;
    while(strcmp(temp->Name_of_the_student,arr_name)==0 && strcmp(temp->title_of_the_book_asking_for,arr_title)==0)
    {
        if(strcmp(temp->Name_of_the_student,arr_name)==0)
        {
            count++;
        }
        temp=temp->next;
    }
    return count;
}
struct book_list *split(struct book_list *head)
{
    struct book_list *fast = head,*slow = head;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    struct book_list *temp = slow->next;
    slow->next = NULL;
    return temp;
}
struct book_list *merge(struct book_list *first, struct book_list *second)
{
	// If first linked list is empty
	if (!first)
		return second;

	// If second linked list is empty
	if (!second)
		return first;

	// Pick the smaller value
	if (first->number_of_copies_available > second->number_of_copies_available)
	{
		first->next = merge(first->next,second);
		first->next->prev = first;
		first->prev = NULL;
		return first;
	}
	else
	{
		second->next = merge(first,second->next);
		second->next->prev = second;
		second->prev = NULL;
		return second;
	}
}
/*******************************************************************************************************************/
