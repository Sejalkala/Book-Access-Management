

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/*
Assumptions
1. name of book,student is of a single word.
2. in every month there are 30 days.
*/
struct book_DB
{
    /* data */
    int book_id;
    char Title[50];
    char author[50];
    char subject[50];
    int number_of_copies_issued;
    int number_of_copies_available;
    struct book_DB *right;
    struct book_DB *left;
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

struct book_DB *root=NULL;
struct request_queue *head_request_queue=NULL;
struct borrower_list *head_borrower_list=NULL;


//supporting functions
int no_bo_list(char arr[50],struct borrower_list *head_borrower_list);//no of occurances of a given name in boroweer_list
int count_request(char arr_name[50],char arr_title[50],struct request_queue *head_request_queue);//no of occurances in request_queue
int totalCopies(struct book_DB *root);// calculates total number of available copies
int no_of_days(int d1[3],int d2[3]);//calculates the no of days between the two given dates
int isBook_available(char arr[50],struct book_DB *root,int flag);//checks if the book with given title is available or not
int no_re_queue(char arr[50],struct request_queue *head_request_queue);//no of occurances of a given title in request_queue
int no_list(char arr[50],struct borrower_list *head_borrower_list);//no of occurances of a given name in boroweer_list
void printInorder(struct book_DB *r);//prints the tree by inorder traversal
int idfromTitle(char title[50],struct book_DB *root);// returns id of the book
void bookIssued(int id,struct book_DB *root);//issues the book
int no_bo_list_by_name(char arr[50],struct borrower_list *head_borrower_list);//returns no of occurances of a given name in borrower_list
void make_available(int id,struct book_DB *root);//if a book is returned,this functions make sure that the book is now available

//funtions to insert node in the book_DB tree
struct book_DB *newNode(int book_id,char arr_title[50],char arr_author[50],char arr_subject[50]);
int height(struct book_DB *root);
int getBalanceFactor(struct book_DB *root);
struct book_DB *rightRotate(struct book_DB *y);
struct book_DB *leftRotate(struct book_DB *x);
struct book_DB *insert(struct book_DB *new_node,struct book_DB *root);

// functions to insert nodes in linked lists request_queue and borrower list
struct request_queue* insert_request_queue(struct request_queue* *head_request_queue);
void insert_borrower_list(struct borrower_list* *head_borrower_list,struct request_queue* *head_request_queue,struct book_DB *root);
void return_book(struct borrower_list* *head_borrower_list,struct book_DB *root);

//main functions
//question 1
void Display_names(struct request_queue *head_request_queue,struct borrower_list *head_borrower_list);
//question 2
int Book_in_mostDemand(struct book_DB *root,int max,struct borrower_list *head_borrower_list,struct request_queue *head_request_queue);
void question_2(struct book_DB *root,int max);
//question 3
void No_ofBooks_givenin_3Days(struct book_DB *root,struct borrower_list *head_borrower_list);
//question 4
void Sort_borrower_list(struct borrower_list *head_borrower_list);
//question 5
void sortNdisplay(struct book_DB *root,char abcd[50]);
//question 6
void Display_requested_books(struct request_queue *head_request_queue,struct book_DB *root);
//question 7
void Display_title(struct book_DB *root,struct request_queue *head_request_queue,struct borrower_list *head_borrower_list);
//question 8
void DisplayFrom_to(struct book_DB *root,int b1,int b2);


int main()
{
    printf("\n                                   WELCOME                               \n");
    printf("\n                                     TO                                  \n");
    printf("\n                                   SEJAL'S                               \n");
    printf("\n                           BOOK ACCESS MANAGEMENT SYSTEM                 \n");

    printf("\n We have following list of books \n");
    printf("\n title of the book and number of copies available: \n");
    root=insert(newNode(15,"atomic","gina","motivational"),root);
    root=insert(newNode(20,"space","john","scifi"),root);
    root=insert(newNode(5,"kalam","ross","biography"),root);
    root=insert(newNode(30,"happiness","neha","motivational"),root);
    root=insert(newNode(25,"courage","rachel","motivational"),root);
    root=insert(newNode(35,"earth","monica","scifi"),root);
    root=insert(newNode(40,"life","chandler","motivational"),root);
    root=insert(newNode(23,"family","lisa","biography"),root);
    root=insert(newNode(6,"emily","sejal","biography"),root);
    root=insert(newNode(8,"success","simran","motivational"),root);
    printInorder(root);
   
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
            insert_borrower_list(&head_borrower_list,&head_request_queue,root);
            printInorder(root);
        }
        else if(n==2)
        {
            return_book(&head_borrower_list,root);
            printInorder(root);
        }
        else if(n==3)
        {
            head_request_queue=insert_request_queue(&head_request_queue);
        }
        
        printf("\nEnter 0 to get out of this loop and 1 to continue\n");
        scanf("%d",&flag_1);
        printf("\n");
      }
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
        printf("\n6.Display the names of the requested books whose copies are available.\n");
        printf("\n7.Display the title of all the books which have not been issued by anyone.\n");
        printf("\n8.Given From-Book-ID and To-Book-ID, display all books with their IDs in the range defined by From-Book-ID and To-Book-ID.\n");

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
                int max=Book_in_mostDemand(root,0,head_borrower_list,head_request_queue);
                question_2(root,max);
                break;
            }
            case 3:
            {
                No_ofBooks_givenin_3Days(root,head_borrower_list);
                break;
            }
            case 4:
            {
                Sort_borrower_list(head_borrower_list);
                break;
            }
            case 5:
            {
                printf("\n enter one of the subjects given for sorting: \n");
                printf("\n subjects are: motivational,scifi,biography\n");
                char abcd[50];
                scanf("%s",&abcd);
                sortNdisplay(root,abcd);
                break; 
            }
            case 6:
            {
                Display_requested_books(head_request_queue,root);
                break;
            }
            case 7:
            {
                Display_title(root,head_request_queue,head_borrower_list);
                break;
            }
            case 8:
            {
                printf("\n enter the book-id 'from' which you want the books to display: \n");
                int b1;
                scanf("%d",&b1);
                printf("\n enter the book-id 'to' which you want the books to display: \n");
                int b2;
                scanf("%d",&b2);
                DisplayFrom_to(root,b1,b2);
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

//question 1
void Display_names(struct request_queue *head_request_queue,struct borrower_list *head_borrower_list)
{
    printf("\n names of students: \n");
    struct request_queue *temp=head_request_queue;
    while(temp!=NULL)
    {
        int a=no_bo_list(temp->Name_of_the_student,head_borrower_list);
        int b=count_request(temp->Name_of_the_student,temp->title_of_the_book_asking_for,head_request_queue);
        if(a+b<4)
        {
            printf("\n %s \n",temp->Name_of_the_student);
        }
        temp=temp->next;
    }
}
//question 2
char arr_2[50];
int Book_in_mostDemand(struct book_DB *root,int max,struct borrower_list *head_borrower_list,struct request_queue *head_request_queue)
{
    if(root==NULL)
     {
       return max;
     }
    if(root!=NULL)
    {
        int a=no_re_queue(root->Title,head_request_queue);
        int b=no_list(root->Title,head_borrower_list);
        if(max<a+b)
        {
            strcpy(arr_2,root->Title);
            max=a+b;
        }
    }
    max=Book_in_mostDemand(root->left,max,head_borrower_list,head_request_queue);  
    max=Book_in_mostDemand(root->right,max,head_borrower_list,head_request_queue);
    return max;
}
void question_2(struct book_DB *root,int max)
{
    if(max==0)
    {
      printf("\n Not a specific book\n");
    }
    else
    {
      printf("\nThe book with most demand is %s \n",arr_2);
   }
}
//question 3
int a_3;
void No_ofBooks_givenin_3Days(struct book_DB *root,struct borrower_list *head_borrower_list)
{
  printf("\n enter the present date:");
  int date[3];
  for(int i=0;i<3;i++)
  {
    scanf("%d",&date[i]);
  }
  int a=totalCopies(root);
  struct borrower_list *t=head_borrower_list;
  while(t!=NULL)
  {
    if(t->date_of_return[0]=='\0')
    {
      int i;
      for(i=0;i<3;i++)
      {   
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
//question 4
void Sort_borrower_list(struct borrower_list *head_borrower_list)
{
    struct borrower_list *temp=head_borrower_list;
    while(temp!=NULL)
    {
        printf("\n name of student:%s name of book:%s\n ",temp->Name_of_the_student,temp->title_of_the_book);
        temp=temp->next;
    }
}
//question 5
void sortNdisplay(struct book_DB *root,char abcd[50])
{
  if(root==NULL)
  {
    return;
  }
  if(strcmp(root->subject,abcd)==0)
  {
    printf("\n title:%s author:%s \n",root->Title,root->author);
  }
  sortNdisplay(root->left,abcd);
  sortNdisplay(root->right,abcd);
}
//question 6
void Display_requested_books(struct request_queue *head_request_queue,struct book_DB *root)
{
    struct request_queue *temp=head_request_queue;
    while(temp!=NULL)
    {
        if(isBook_available(temp->title_of_the_book_asking_for,root,0)==1)
        {
          printf("\n%s\n",temp->title_of_the_book_asking_for);
        }
        temp=temp->next;
    }
}
//question 7
void Display_title(struct book_DB *root,struct request_queue *head_request_queue,struct borrower_list *head_borrower_list)
{
  
  if(root!=NULL)
    {
        if(no_list(root->Title,head_borrower_list)==0 && no_re_queue(root->Title,head_request_queue)==0)
        {
            printf("\n %s \n",root->Title);
        }
        Display_title(root->left,head_request_queue,head_borrower_list);
        Display_title(root->right,head_request_queue,head_borrower_list);
    }
}
//question 8
void DisplayFrom_to(struct book_DB *root,int b1,int b2)
{
    if(root == NULL)
    {
      return;
    }
    DisplayFrom_to(root->left,b1,b2);
    if(root->book_id>=b1 && root->book_id<=b2)
    {
      printf("\n%s   %d\n",root->Title,root->book_id);
    }
    DisplayFrom_to(root->right,b1,b2); 
}

//insert functions
struct book_DB *newNode(int book_id,char arr_title[50],char arr_author[50],char arr_subject[50]) 
{
  struct book_DB *node = (struct book_DB *)malloc(sizeof(struct book_DB));
  node->book_id = book_id;
  node->left = NULL;
  node->right = NULL;
  strcpy(node->Title,arr_title);
  strcpy(node->author,arr_author);
  strcpy(node->subject,arr_subject);
  node->number_of_copies_available=10;
  node->number_of_copies_issued=0;
  return node;
}
int height(struct book_DB *root)
{
  if(root==NULL)
  {
    return -1;
  }
  else
  {
    int left_h=height(root->left);
    int right_h=height(root->right);

    if(left_h > right_h)
    {
      return (left_h+1);
    }
    else
    {
      return (right_h + 1);
    }
  }
}

int getBalanceFactor(struct book_DB *root)
{
  if(root==NULL)
  {
    return -1;
  }
  return height(root->left) - height(root->right);
}

struct book_DB* rightRotate(struct book_DB *y)
{
  struct book_DB *x=y->left;
  struct book_DB *T2=x->right;

  x->right=y;
  y->left=T2;
  return x;
}

struct book_DB* leftRotate(struct book_DB *x)
{
  struct book_DB *y=x->right;
  struct book_DB *T2=y->left;

  y->left=x;
  x->right=T2;
  return y;
}


struct book_DB* insert(struct book_DB *new_node,struct book_DB *root)
{
  if(root==NULL)
  {
    root=new_node;
   // printf("\n Value inserted successfully\n");
    return root;
  }
  if(new_node->book_id < root->book_id)
  {
    root->left=insert(new_node,root->left);
  }
  else if(new_node->book_id >root->book_id)
  {
    root->right=insert(new_node,root->right);
  }
  else
  {
    printf("\n No duplicate values allowed!\n");
    return root;
  }
  int bf=getBalanceFactor(root);
  //left left case
  if(bf >1 && new_node->book_id < root->left->book_id)
  {
    return rightRotate(root);
  }
  //right right case
  if(bf<-1 && new_node->book_id > root->right->book_id)
  {
    return leftRotate(root);
  }
  //left right case
  if(bf>1 && new_node->book_id>root->left->book_id)
  {
    root->left=leftRotate(root->left);
    return rightRotate(root);
  }
  //right left case
  if(bf<-1 && new_node->book_id<root->right->book_id)
  {
    root->right=rightRotate(root->right);
    return leftRotate(root);
  }
  return root;
}


//function to request a book,i.e.,add a node in the request_queue
struct request_queue* insert_request_queue(struct request_queue* *head_request_queue)
{
    struct request_queue *node_to_insert=(struct request_queue* ) malloc(sizeof(struct request_queue*));
    printf("\nEnter your name\n");//name of the student
    scanf("%s",&node_to_insert->Name_of_the_student);
    printf("\nEnter the Title of the book you are asking for\n");
    scanf("%s",&node_to_insert->title_of_the_book_asking_for);
    node_to_insert->next=NULL;
    node_to_insert->prev=NULL;
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
    return *head_request_queue;
}

//insert node in borrower list
void insert_borrower_list(struct borrower_list* *head_borrower_list,struct request_queue* *head_request_queue,struct book_DB *root)
{
    struct borrower_list *temp=(struct borrower_list* ) malloc(sizeof(struct borrower_list*));
    printf("\n Enter the name of the student\n");
    scanf("%s",&temp->Name_of_the_student);
    printf("\n Enter the title of the book \n");
    scanf("%s",&temp->title_of_the_book);
    int id=idfromTitle(temp->title_of_the_book,root);
    for(int i=0;i<3;i++)
    {
      temp->date_of_issue[i]=0;
      temp->date_of_return[i]=0;
    }
    temp->next=NULL;
    temp->prev=NULL;
  if(id>0)
    {
        if(no_bo_list_by_name(temp->Name_of_the_student,*head_borrower_list)>=3)
        {
            printf("\n You've already borrowed 3 or more books,so we can't issue you another book.\n");
            printf("\n Do you want to still request it? we can issue the book if you've returned previous books.\n");
            printf("\nPlease enter 1 if this is the case,otherwise 0.\n thank you\n");
            int flag;
            scanf("%d",&flag);
            if(flag==1)
            {
                insert_request_queue(head_request_queue);
            }
            return;
        }
        //else
        //{
            printf("\n Enter the present date\n Note that the format should be dd mm yyyy\n");
            int i;
            for(i=0;i<3;i++)
            {
                scanf("%d",&temp->date_of_issue[i]);
            }
            struct borrower_list *t=*head_borrower_list;
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
            
           bookIssued(id,root);
        //}
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
    if(*head_borrower_list!=NULL)
    {
     struct borrower_list *c=*head_borrower_list;
    while(c!=NULL)
    {
        printf("\n %s\n",c->Name_of_the_student);
        c=c->next;
    }
    }
    printf("\n success \n");
}

void return_book(struct borrower_list* *head_borrower_list,struct book_DB *root)
{
    printf("\n enter your name\n");
    char arr_name[50];
     scanf("%s",&arr_name);
    printf("\n enter the name of book you want to return\n");
    char arr_title[50];
    scanf("%s",&arr_title);
    struct borrower_list *temp=*head_borrower_list;
    while(temp!=NULL)
    {
        if(strcmp(temp->Name_of_the_student,arr_name)==0 && strcmp(temp->title_of_the_book,arr_title)==0)
        {
            int a=idfromTitle(temp->title_of_the_book,root);
            make_available(a,root);
            printf("\n enter the present date\n");
            int i;
            for(i=0;i<3;i++)
            {
                scanf("%d",&temp->date_of_return[i]);
            }
            return;
        }
        temp=temp->next;
    }
}

//supporting functions
int no_bo_list(char arr[50],struct borrower_list *head_borrower_list)
{
  printf("\n c \n");
    struct borrower_list *temp=(struct borrower_list* ) malloc(sizeof(struct borrower_list*));
    temp=head_borrower_list;
    printf("\n d \n");
    int count=0;
    while(temp!=NULL)
    {
      printf("\n e \n");
        if(strcmp(temp->Name_of_the_student,arr)==0)
         {
            count++;
            printf("\n f \n");
        }
        /*else
        {
          printf("\n g \n");
            continue;
        }*/
        temp=temp->next;
    }
    printf("\n h \n");
    return count;
}

int count_request(char arr_name[50],char arr_title[50],struct request_queue *head_request_queue)
{
  printf("\n h \n");
    struct request_queue *temp=head_request_queue;
    int count=0;
    while(strcmp(temp->Name_of_the_student,arr_name)==0 && strcmp(temp->title_of_the_book_asking_for,arr_title)==0)
    {
      printf("\n i \n");
        if(strcmp(temp->Name_of_the_student,arr_name)==0)
        {
            count++;
        }
        temp=temp->next;
    }
    printf("\n j \n");
    return count;
}


int totalCopies(struct book_DB *root)
{
  if(root==NULL)
  {
    return 0;
  }
  a_3=a_3+root->number_of_copies_available;
  totalCopies(root->left);
  totalCopies(root->right);
  return a_3;
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

int isBook_available(char arr[50],struct book_DB *root,int flag)
{
  if(root==NULL)
  {
    return 0;
  }
    if(root!=NULL && flag==0)
    {
        if(strcmp(root->Title,arr)==0)
        {
            if(root->number_of_copies_available>0)
            {
                flag=1;
                return 1;
            }
        }  
    }
    flag=isBook_available(arr,root->left,flag);
    if(flag==0)
    {
        flag=isBook_available(arr,root->right,flag);
    }
    if(flag==1)
    {
      return 1;
    }
    else
    {
      return 0;
    }
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
int no_list(char arr[50],struct borrower_list *head_borrower_list)
{
    struct borrower_list *temp=head_borrower_list;
    int count=0;
    while(temp!=NULL)
    {
        if(strcmp(temp->title_of_the_book,arr)==0)
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
void printInorder(struct book_DB *r) //  (Left, current node, Right)
{
    if (r == NULL)
      return;
    printInorder(r -> left);
    printf("\n%s   %d\n",r->Title,r->number_of_copies_available);
    printInorder(r -> right);
}

int idfromTitle(char title[50],struct book_DB *root)
{
  if(root==NULL)
  {
    return 0;
  }
  if(strcmp(root->Title,title)==0)
  {
    return root->book_id;
  }
  else
  {
    int a= idfromTitle(title,root->left);
    if(a==0)
    {
      return idfromTitle(title,root->right);
    }
    return a;
  }
}

void bookIssued(int id,struct book_DB *root)
{
  if(root->book_id==id)
  {
    root->number_of_copies_available-=1;
    root->number_of_copies_issued+=1;
  }
  else if(root->book_id>id)
  {
    bookIssued(id,root->left);
  }
  else
  {
    bookIssued(id,root->right);
  }
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

void make_available(int id,struct book_DB *root)
{
    if(root==NULL)
    {
        return;
    }
    if(root->book_id==id)
    {
      root->number_of_copies_available+=1;
      root->number_of_copies_issued-=1;
    }
    else if(root->book_id>id)
    {
      make_available(id,root->left);
    }
    else
    {
      make_available(id,root->right);
    }
}
