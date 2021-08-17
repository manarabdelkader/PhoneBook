#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "phonebook.c"
char contlastname[25];
int choice,numberofcontacts,newnumberofcontacts,m,z;
struct date
{
    int day;
    int month;
    int year;
};

struct contact
{
    char Fname[25],
         Lname[25],
         PHno[20],
         address[150],
         email[100];
    struct date bd;
};
struct contact cont[100];
int load()
{
    int i=0;
    FILE *phonebook = fopen("/Users/HP/Documents/phonebook/phonebook.txt","r");
    if(phonebook!=NULL)
    {
        while(!feof(phonebook))
        {   fscanf (phonebook, "%[^,],",&cont[i].Lname);

            if(feof(phonebook))
            {
                break;
            }
            fscanf (phonebook, "%[^,],",&cont[i].Fname);
            fscanf (phonebook, "%d-",&cont[i].bd.day);
            fscanf (phonebook, "%d-",&cont[i].bd.month);
            fscanf (phonebook, "%d,",&cont[i].bd.year);
            fscanf (phonebook, "%[^,],",&cont[i].address);
            fscanf (phonebook, "%[^,],",&cont[i].email);
            fscanf (phonebook, "%s\n",&cont[i].PHno);
            i++;
        }
        printf ("# of Contacts saved= %d\n", i);
    }
    else
    {
        printf("FILE NOT FOUND!");
        exit(0);
    }
    fclose (phonebook);
    return i;
}
int searchcontact(int x)
{
    int noofrpt=0;
    printf("Enter the last name of the contact you want to search for:");
    scanf("%s",&contlastname);
    for(m=0; m<x; m++)
    {
        if(strcasecmp(contlastname,cont[m].Lname)==0)
        {
            noofrpt++;
            printf("Contact #%d:-\n",m+1);
            printf("First name: %s\n",cont[m].Fname);
            printf("Last name: %s\n",cont[m].Lname);
            printf("Phone number: %s\n",cont[m].PHno);
            printf("Date of birth: %d/%d/%d\n",cont[m].bd.day,cont[m].bd.month,cont[m].bd.year);
            printf("E-mail: %s\n",cont[m].email);
            printf("Address: %s\n===================================================\n",cont[m].address);
            z=m;
        }
    }
    if(noofrpt!=0)
        printf("Found %d contacts with the same last name.\n ",noofrpt);
    else
        printf("No contact with this last name is found");
    return noofrpt;
}
 void addcontact()
{
    do
    {
        printf("Enter First name:");
        scanf("%s",&cont[newnumberofcontacts].Fname);
    }
    while (!ValidName(cont[newnumberofcontacts].Fname));
    do
    {
        printf("Enter Last name:");
        scanf("%s",&cont[newnumberofcontacts].Lname);
    }
    while (!ValidName(cont[newnumberofcontacts].Lname));
    do
    {
        printf("Enter Day of Birth:");
        scanf("%d",&cont[newnumberofcontacts].bd.day);
        printf("Enter Month of Birth:");
        scanf("%d",&cont[newnumberofcontacts].bd.month);
        printf("Enter Year of Birth:");
        scanf("%d",&cont[newnumberofcontacts].bd.year);
    }
    while (!ValidDateofBirth(cont[newnumberofcontacts].bd.day,cont[newnumberofcontacts].bd.month, cont[newnumberofcontacts].bd.year ));
    do
    {
        printf("Enter E-mail:");
        scanf("%s",&cont[newnumberofcontacts].email);
    }
    while (!ValidEmail(cont[newnumberofcontacts].email));

    printf("Enter Address:");
    scanf (" %[^\n]s",&cont[newnumberofcontacts].address);

    do
    {
        printf("Enter Phone #:");
        scanf("%s",&cont[newnumberofcontacts].PHno);
    }
    while(!ValidPhoneNum(cont[newnumberofcontacts].PHno));
    printf("\n\tContact added!\n     *Press 6 to save*\n_____\n");
}




void deletecontact()
{
    int noofrpt=0;
    char contfirstname[25];
    printf("Enter the first name of the contact you want to delete:");
    scanf("%s",&contfirstname);
    printf("Enter the last name of the contact you want to delete:");
    scanf("%s",&contlastname);
    for(m=0; m<newnumberofcontacts; m++)
    {
        if(strcasecmp(contlastname,cont[m].Lname)==0&&strcasecmp(contfirstname,cont[m].Fname)==0)
        {
            noofrpt++;
            printf("Contact number (%d):\nFirst name: %s\n",m+1,cont[m].Fname);
            printf("Last name: %s\n",cont[m].Lname);
            printf("Day of birth: %d\n",cont[m].bd.day);
            printf("Month of birth: %d\n",cont[m].bd.month);
            printf("Year of birth: %d\n",cont[m].bd.year);
            printf("E-mail: %s\n",cont[m].email);
            printf("Address: %s\n",cont[m].address);
            printf("Phone #: %s\n",cont[m].PHno);
            break;
        }
    }
    if(noofrpt==0)
        printf("No contact with this name is found!");
    if(noofrpt)
    {
        do
        {
            printf("\nAre you sure you want to delete?\n1-Yes\t2-No\n");
            scanf("%d",&choice);
            if(choice!=1&&choice!=2)
                printf("ERROR! Wrong Entry.\n");
        }
        while(choice!=1&&choice!=2);
    }
    if(choice==1)
    {
        for(int i=m; i<=newnumberofcontacts; i++)
        {
            strcpy( cont[i].Fname,cont[i+1].Fname);
            strcpy(cont[i].Lname,cont[i+1].Lname);
            cont[i].bd.day=cont[i+1].bd.day;
            cont[i].bd.month=cont[i+1].bd.month;
            cont[i].bd.year=cont[i+1].bd.year;
            strcpy(cont[i].email,cont[i+1].email);
            strcpy(cont[i].address,cont[i+1].address);
            strcpy(cont[i].PHno,cont[i+1].PHno);
        }
        newnumberofcontacts--;


        if(noofrpt)
            printf("\n\tContact deleted!\n     **Press 6 to save**\n___________\n");
    }
}

void modifycontact(int x)
{
    int y = searchcontact(x);
    if(y!=0)
    {
        if(y>1)
        {
            printf("\n Enter number of the contact you want to modify:");
            scanf("%d",&z);
            z--;
        }
        do
        {
            printf("\nFirst name..\n1-Modify\n2-Skip:\n");
            scanf("%d",&choice);
            if(choice!=1&&choice!=2)
                printf("ERROR! Wrong Entry.\n");
        }
        while(choice!=1&&choice!=2);
        if(choice==1)
        {
            do
            {
                printf("Enter new First name:");
                scanf("%s",&cont[z].Fname);
            }
            while (!ValidName(cont[z].Fname));
        }

        do
        {
            printf("\nLast name..\n1-Modify\n2-Skip:\n");
            scanf("%d",&choice);
            if(choice!=1&&choice!=2)
                printf("ERROR! Wrong Entry.\n");
        }
        while(choice!=1&&choice!=2);
        if(choice==1)
        {
            do
            {
                printf("Enter new Last name:");
                scanf("%s",&cont[z].Lname);
            }
            while (!ValidName(cont[z].Lname));
        }
        do
        {
            printf("\nDay of Birth..\n1-Modify\n2-Skip:\n");
            scanf("%d",&choice);
            if(choice!=1&&choice!=2)
                printf("ERROR! Wrong Entry.\n");
        }

        while(choice!=1&&choice!=2);
        if(choice==1)
        {
            do
            {
                printf("Enter new Day of Birth:");
                scanf("%d",&cont[z].bd.day);
                if(cont[z].bd.day>31||cont[z].bd.day<1)
                    printf("Invalid entry. Please enter a valid day!\n");
            }
            while(cont[z].bd.day>31||cont[z].bd.day<1);
        }
        do
        {
            printf("\nMonth of Birth..\n1-Modify\n2-Skip:\n");
            scanf("%d",&choice);
            if(choice!=1&&choice!=2)
                printf("ERROR! Wrong Entry.\n");
        }

        while(choice!=1&&choice!=2);
        if(choice==1)
        {
            do
            {
                printf("Enter new Month of Birth:");
                scanf("%d",&cont[z].bd.month);
                if(cont[z].bd.month>12||cont[z].bd.month<1)
                    printf("Invalid entry. Please enter a valid month!\n");
            }
            while(cont[z].bd.month>12||cont[z].bd.month<1);
        }
        do
        {
            printf("\nYear of Birth..\n1-Modify\n2-Skip:\n");
            scanf("%d",&choice);
            if(choice!=1&&choice!=2)
                printf("ERROR! Wrong Entry.\n");

        }
        while(choice!=1&&choice!=2);
        if(choice==1)
        {
            do
            {
                printf("Enter new Year of Birth: ");
                scanf("%d",&cont[z].bd.year);
                if(cont[z].bd.year<1||cont[z].bd.year>2020)
                    printf("Invalid entry. Please enter a valid year!\n");
            }
            while(cont[z].bd.year<1||cont[z].bd.year>2020);
        }
        do
        {
            printf("\nE-mail..\n1-Modify\n2-Skip:\n");
            scanf("%d",&choice);
            if(choice!=1&&choice!=2)
                printf("ERROR! Wrong Entry.\n");
        }
        while(choice!=1&&choice!=2);
        if(choice==1)
        {
            do
            {
                printf("Enter new E-mail:");
                scanf("%s",&cont[z].email);
            }
            while (!ValidEmail(cont[z].email));
        }
        do
        {
            printf("\nAddress..\n1-Modify\n2-Skip:");
            scanf("%d",&choice);
            if(choice!=1&&choice!=2)
                printf("ERROR! Wrong Entry.\n");

        }
        while(choice!=1&&choice!=2);
        if(choice==1)
        {

                printf("Enter new Address:");
                scanf (" %s",&cont[z].address);


        }
        do
        {
            printf("\nPhone #..\n1-Modify\n2-Skip:\n");
            scanf("%d",&choice);
            if(choice!=1&&choice!=2)
                printf("ERROR! Wrong Entry.\n");

        }
        while(choice!=1&&choice!=2);
        if(choice==1)
        {
            do
            {
                printf("Enter new Phone #:");
                scanf("%s",&cont[z].PHno);
            }
            while(!ValidPhoneNum(cont[z].PHno));
        }
        printf("Contact number (%d) after modification:\nFirst name: %s\n",m+1,cont[z].Fname);
        printf("Last name: %s\n",cont[z].Lname);
        printf("Day of Birth: %d\n",cont[z].bd.day);
        printf("Month of Birth: %d\n",cont[z].bd.month);
        printf("Year of Birth: %d\n",cont[z].bd.year);
        printf("E-mail: %s\n",cont[z].email);
        printf("Address: %s\n",cont[z].address);
        printf("Phone #: %s\n\n\tContact added!\n     *Press 6 to save*\n_____\n",cont[z].PHno);
    }
}
void savecontact()
{
    int i;
    FILE *phonebook =fopen("/Users/HP/Documents/phonebook/phonebook.txt","w");
    for(i=0; i<newnumberofcontacts; i++)
    {

        fprintf (phonebook, "%s,", cont[i].Lname);
        fprintf (phonebook, "%s,", cont[i].Fname);
        fprintf (phonebook, "%d-", cont[i].bd.day);
        fprintf (phonebook, "%d-", cont[i].bd.month);
        fprintf (phonebook, "%d,", cont[i].bd.year);
        fprintf (phonebook, "%s,", cont[i].email);
        fprintf (phonebook, "%s,", cont[i].address);
        fprintf (phonebook, "%s\n", cont[i].PHno);
    }
    printf ("All changes have been saved\n");
    fclose (phonebook);
}

void printcontacts()
{
    do
    {
        printf("How do you want to sort the contacts?\n1-Last name\t2-Date of birth:");
        scanf("%d",&choice);
        if(choice!=1&&choice!=2)
            printf("ERROR! Wrong Entry.\n");
    }
    while(choice!=1&&choice!=2);
    if(choice==1)
    {
        printf("Sorting by last name...\n");
        sortbylname();
    }
    else
    {
        printf("Sorting by date of birth...\n");
        sortbydob();
    }
    for(m=0; m<newnumberofcontacts; m++)
    {
        printf("Contact #%d:-\n",m+1);
        printf("First name: %s\n",cont[m].Fname);
        printf("Last name: %s\n",cont[m].Lname);
        printf("Phone #: %s\n",cont[m].PHno);
        printf("Date of Birth: %d/%d/%d\n",cont[m].bd.day,cont[m].bd.month,cont[m].bd.year);
        printf("E-mail: %s\n",cont[m].email);
        printf("Address: %s\n===================================================\n",cont[m].address);


    }
}
void sortbylname()
{
    struct contact temp;
    for (m = 0; m < newnumberofcontacts-1; m++)
    {


        for (z = 0; z < newnumberofcontacts-m-1; z++)
        {

            if (strcasecmp(cont[z].Lname,cont[z+1].Lname)>0)
            {
                temp=cont[z];
                cont[z]=cont[z+1];
                cont[z+1]=temp;

            }



 else if(strcasecmp(cont[z].Lname,cont[z+1].Lname)==0){
    if (strcasecmp(cont[z].Fname,cont[z+1].Fname)>0)
            {
                temp=cont[z];
                cont[z]=cont[z+1];
                cont[z+1]=temp;

            }

}
}} }
void sortbydob()
{
    struct contact temp;
    for (m = 0; m < newnumberofcontacts-1; m++)
    {


        for (z = 0; z < newnumberofcontacts-m-1; z++)
        {

            if (cont[z].bd.year > cont[z+1].bd.year)
            {
                temp=cont[z];
                cont[z]=cont[z+1];
                cont[z+1]=temp;

            }
            else if(cont[z].bd.year == cont[z+1].bd.year)
            {
                if(cont[z].bd.month > cont[z+1].bd.month)
                {
                    temp=cont[z];
                    cont[z]=cont[z+1];
                    cont[z+1]=temp;
                }
                else if(cont[z].bd.month == cont[z+1].bd.month)
                {
                    if(cont[z].bd.day > cont[z+1].bd.day)
                    {
                        temp=cont[z];
                        cont[z]=cont[z+1];
                        cont[z+1]=temp;

                    }

                }

            }
        }
    }
}
int ValidName(char *name)
{
    int i, flag =0;
    for (i =0; i<strlen(name); i++)
    {
        if (!isalpha (name[i]))
            flag = 1;
    }
    if (flag == 1)
    {
        printf ("Invalid entry. Please enter a valid name!\n");
        return 0;
    }
    else
        return 1;
}

int ValidDateofBirth (int D, int M, int Y)
{
    if (Y>=0&&Y<= 2020)
    {
        if (M>= 1 && M<= 12)
        {
            if ((D >= 1 && D <= 31) && (M==1 || M==3 || M==5 || M==7 || M==8 || M==10 || M==12))
                return 1;
            else if ((D>=1 && D<=30) && (M==4 || M==6 || M==9 || M==11))
                return 1;
            else if ((D=1 && D<= 29) && (M== 2))
                return 1;
            else
            {
                printf ("Invalid entry. Please enter a valid day of birth!\n");
                return 0;
            }
        }
        else
        {
            printf ("Invalid entry. Please enter a valid month of birth!\n");
            return 0;
        }
    }
    else
    {
        printf ("Invalid entry. Please enter a valid year of birth!\n");
        return 0;
    }
}
int ValidPhoneNum(char *phonenumber)
{

    int i, flag = 0;

    for (i = 0; i < strlen(phonenumber); i++)

    {

        if (!isdigit (phonenumber[i]))

            flag = 1;

    }

    if (flag == 1)

    {
        printf ("Invalid entry. Please enter a valid phone number!\n");

        return 0;
    }
    else
        return 1;

}
int ValidEmail(char *email)
{
    int i,j,found=0;
    char postdot[4];
    int len=strlen(email);
    if ((isalpha(email[0]))||(isdigit(email[0]))&&email[len-4]=='.')
    {
        for(i=0; i<len; i++)
        {
            if(email[i]=='@')
            {
                for(i=len-3,j=0; i<len; i++,j++)
                {
                    postdot[j]=email[i];
                }
                postdot[3]='\0';
                if (strcmp(postdot,"com")==0||strcmp(postdot,"net")==0||strcmp(postdot,"org")==0||strcmp(postdot,"edu") == 0)
                    found=1;
            }
        }
        if(found==1)
            return 1;
        else
        {
            printf("Invalid entry. Please enter a valid email!\n");
            return 0;
        }
    }
    else
    {
        printf ("Invalid entry. Please enter a valid email!");
        return 0;
    }
}

int main()
{
    numberofcontacts=load();
    newnumberofcontacts=numberofcontacts;
    while(1)
    {
        printf("\nHow can I help you?\n\n1-Search\t\t2-Add\n\n3-Delete\t\t4-Modify\n\n5-Print\t\t\t6-Save\n\n\t   7-Exit\n\n");
        do {printf("\nPlease enter a number(1-7): \n");
             scanf("%d",&choice);
        if(choice<1||choice>7)
            printf("ERROR! Wrong Entry.\n");}
    while(choice<1||choice>7);
        switch (choice)
        {
        case 1:
            printf("Searching...\n");
            searchcontact(newnumberofcontacts);
            break;
        case 2:
            printf("Adding...\n");
            addcontact();
            newnumberofcontacts++;
            break;
        case 3:
            printf("Deleting...\n");
            deletecontact();
            break;
        case 4:
            printf("Modifying...\n");
            modifycontact(newnumberofcontacts);
            break;
        case 5:
            printcontacts();
            break;
        case 6:
            printf("Saving...\n");
            savecontact();
            break;
        case 7:
            do
            {
                printf("Are you sure you want to exit? ALL UNSAVED CHANGES WILL BE DELETED!\n1-Yes\t2-No\n");
                scanf("%d",&choice);
                if(choice==1)
                    exit(0);
                else if(choice==2)
                    break;
                else
                {
                    printf("ERROR! Wrong Entry.\n");
                }
            }
            while(choice!=1&&choice!=2);
        }
    }
    return 0;
}

