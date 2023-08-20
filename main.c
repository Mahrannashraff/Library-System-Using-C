#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct libraryBooks
{
        int id;
        char name[50];
        int quantity;
};

struct libraryBooks m[50], n[50];
struct FILE* fptr, *fptr2;
typedef struct libraryBooks;

int i;
int y = 0;
int size =50;

char project[] = "project.txt";

int main()
{
    int p;
    char j;
    fptr = fopen(project , "r");
    int i =0;
    while(fscanf(fptr,"%d ",&m[i].id) != EOF )
    {
        fscanf(fptr, "%[^\n]s", m[i].name);
        fscanf(fptr,"%d ",&m[i].quantity);
        i++;
        y++;
    }
    for(int i=0 ; i<size ; i++){
        n[i].id = m[i].id;
        n[i].quantity = m[i].quantity;
        strcpy(n[i].name, m[i].name);
    }
    do{
        printf(" 1.For inserting a book\n");
        printf(" 2.For viewing the books\n");
        printf(" 3.For viewing the books sorted\n");
        printf(" 4.For searching on a book by id\n");
        printf(" 5.For deleting a book\n");
        printf(" 6.For searching on a book by name\n");
        printf("\tEnter what you want to do:\n ");
        scanf("%d",&p);
        char name[30];
        switch(p)
        {
        case 1 :
            InsertBook();
            break;
        case 2:
            viewBook();
            break;
        case 3:
            viewSorted();
            break;
        case 4:
            printf("Enter the id of the book to search:");

            int idm;
            scanf("%d",&idm);

            LinearSearchBook(0,idm);
            break;
        case 5:
            deleteBook();
            break;
        case 6:

            printf("enter the name : ");
            fflush(stdin);
            gets(name);
            searchByBinary();
            break;

        }
        printf(" Want something else ? (y/n)\n");
        fflush(stdin);
        scanf("%c",&j);



    }
    while(j=='y'||j=='Y');
    return 0;
}
void InsertBook()
{
    fptr = fopen("project.txt", "a");
    printf("Enter the book id\n");
    scanf("%d",&m[y].id);
    printf("Enter the book name\n");
    fflush(stdin);
    gets(m[y].name);
    printf("Enter the book quantity\n");
    scanf("%d",&m[y].quantity);
    fprintf(fptr,"%d\n%s\n%d\n",m[y].id,m[y].name,m[y].quantity);
    y++;

}

void viewBook()
{
    printf("\n\tid\tquantity\tname\n\n");
    for(int u=0;u<y;u++)
    {
        printf("\n\t%d",m[u].id);
        printf("\t%d",m[u].quantity);
        printf("\t\t%s\n",m[u].name);
    }


}

void LinearSearchBook(int index, int id)
{

    if(m[index].id == id){
        printf("name: %s\n", m[index].name);
        printf("quantity : %d\n", m[index].quantity);
        return;
    }
    else if(index == size){
            printf("Not found\n");
        return;
    }

    LinearSearchBook(index+1, id);


}

void deleteBook ()
{
    int idNum;
    printf("Enter the id of the book\n");
    scanf("%d",&idNum);
    int delete_line_no;
    int line_no=0;
    char gor[100];
    for (int b=0;b<y;b++)
    {
        if (idNum==m[b].id)
        {
            delete_line_no=b*3;
            y--;
        }
    }

    fptr = fopen(project,"r");
    fptr2 =fopen("test.txt","w");
    if (fptr == NULL){
        printf("ERROR\n");
    }

    while (fgets(gor, 99, fptr) != NULL )
    {

        if ((line_no != delete_line_no)&&(line_no != delete_line_no+1)&&(line_no != delete_line_no+2))
        {

          fputs(gor, fptr2);
        }
        line_no++;
    }
    fclose(fptr);
    fclose(fptr2);


    remove(project);
    rename("test.txt", project);

    int p;
    char j;
    fptr = fopen(project , "r");
    int i =0;
    while(fscanf(fptr,"%d ",&m[i].id) != EOF )
    {
        fgets(m[i].name,50,fptr);
        fscanf(fptr,"%d ",&m[i].quantity);
        i++;

    }


}

int searchByBinary(char name[])
{
    for(int i=0 ; i<size ; i++){
        n[i].id = m[i].id;
        n[i].quantity = m[i].quantity;
        strcpy(n[i].name, m[i].name);

    }
    int temph;
    char tempstr[30];
    for (int pass=1;pass<y;pass++)
    {

        for (i=0;i<y-pass;i++)
        {
            if (strcmp(n[i].name,n[i+1].name)>0)
            {
                temph=n[i].id;
                n[i].id=n[i+1].id;
                n[i+1].id=temph;

                temph=n[i].quantity;
                n[i].quantity=n[i+1].quantity;
                n[i+1].quantity=temph;

                strcpy(tempstr,n[i].name);
                strcpy(n[i].name,n[i+1].name);
                strcpy(n[i+1].name,tempstr);

            }
        }
    }

    int middle,low=0,high=y-1;


    while(low<=high)
    {

        middle=(low+high)/2;
        if (strcmp(name,n[middle].name)==0)
        {

            printf("%s\t%s\t%s\n","id","quantity","name");
            printf("%d\t%d\t\t%s\n",n[middle].id,n[middle].quantity,n[middle].name);
            return;

        }
        else if (strcmp(name,n[middle].name)<0)
        {

            high=middle-1;
        }
        else
        {
            low=middle+1;
        }

    }
    if (low>high){
        printf("Not found\n");
    }
}

void viewSorted ()
{
    fptr = fopen("project.txt","r");
    for(int i=0 ; i<size ; i++){
        n[i].id = m[i].id;
        n[i].quantity = m[i].quantity;
        strcpy(n[i].name, m[i].name);
    }
    int temph;
    char tempstr[30];
    for (int pass=1;pass<y;pass++)
    {

        for (i=0;i<y-pass;i++)
        {
            if (strcmp(n[i].name,n[i+1].name)>0)
            {
                temph=n[i].id;
                n[i].id=n[i+1].id;
                n[i+1].id=temph;

                temph=n[i].quantity;
                n[i].quantity=n[i+1].quantity;
                n[i+1].quantity=temph;

                strcpy(tempstr,n[i].name);
                strcpy(n[i].name,n[i+1].name);
                strcpy(n[i+1].name,tempstr);

            }
        }
    }
    printf("\n\tid\tquantity\tname\n\n");
    for (int i=0;i<y;i++){
        printf("\n\t%d",n[i].id);
        printf("\t%d",n[i].quantity);
        printf("\t\t%s\n",n[i].name);
    }
}
