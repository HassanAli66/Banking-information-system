/* 	NAME: HASSAN ALI HASSAN
	SUPERVISOR: DR.MAYSAA NOUBY
	GROUP-SECTION: 1C1
	CONTENT: BANKING SYSTEM IN C PROGRAMMING LANGUAGE BASED ON LINKED LIST.
	FUNCTIONS USED:
			ADD CLIENTS.
			EDIT CLIENT INFORMATION.
			DELETE(REMOVING) CLIENTS.
			LISTING CLIENTS.
			DISPLAYING INFORMATION FOR A SPECIFIC CLIENT.
			SEARCHING FOR CLIENTS BY THEIR NATIONAL ID.
			SORTING CLIENTS BY NAME.				*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void addClient(int NID,int w,int d,char cname1[],char cname2[],char dt[],char phon[],time_t ldt,time_t lwt);

void editClientInfo(int NID,int w,int d,char cname1[],char cname2[],char dt[],char phon[],int flag,time_t ldt,time_t lwt);

void deleteClient(int NID);

void listingClients(void);

void dispClient(int NID);

int searchingID(int NID);

void sortingClients(void);

int BankSystem_IO(void);

void createBackup(time_t exitTime);

struct client{
	int ID;
	char name1st[10];
	char name2nd[10];
	char DOB[10];
	char PHN[13];
	int withdrawal;
	int deposit;
	int balance;
	time_t lastdeposit;
	time_t lastwithdrawal;
	struct client *next;
};

struct client *headclient;


int main(){
	printf("\n***********************************\n");
	printf("****BANK ACCOUNTING SYSTEM IN C****\n");
	printf("***********************************\n\n");
	printf("> List of options:\n\n");
	printf("1-Add a client account.\n2-Edit client information.\n3-Delete client account.\n");
	printf("4-Display client information.\n5-List of Bank clients .\n6-Quit\n");
	BankSystem_IO();
}

int BankSystem_IO(){
	int choice,editchoice;
	int NID,w=0,d=0;
	time_t ldt=0,lwt=0;
	char cname1[10],cname2[10],dt[10],phon[13],yon;
	printf("\n- OPTION: ");
	scanf("%d",&choice);
	switch(choice){
		case 1:
			printf("\nEnter the client's national ID: ");
			scanf("%d",&NID);
			printf("Enter the client's first name: ");
			scanf("%s",cname1);
			printf("Enter the client's last name: ");
			scanf("%s",cname2);
			printf("Date of birth in the form of dd/mm/yyyy: ");
			scanf("%s",dt);
			printf("Enter the client's Phone number: ");
			scanf("%s",phon);
			printf("Enter the ammount of deposit in EGP: ");
			scanf("%d",&d);
			ldt=time(NULL);
			addClient(NID,w,d,cname1,cname2,dt,phon,ldt,lwt);
			BankSystem_IO();

		case 2:
			printf("\nEnter the client's National ID: ");
			scanf("%d",&NID);
			if(searchingID(NID)==1){
				printf("> Editing options:\n\n1-personal information.\n2-Deposit.\n3-Withdrawal.\n>>> ");
				scanf("%d",&editchoice);
				switch(editchoice){
					case 1:
						printf("\nEnter the client's new first name: ");
						scanf("%s",cname1);
						printf("Enter the client's new last name: ");
						scanf("%s",cname2);
						printf("Date of birth in the form of dd/mm/yyyy: ");
						scanf("%s",dt);
						printf("Enter the client's Phone number: ");
						scanf("%s",phon);
						editClientInfo(NID,w,d,cname1,cname2,dt,phon,editchoice,ldt,lwt);
						BankSystem_IO();
					case 2:
						printf("Enter the ammount of deposit added in EGP: ");
						scanf("%d",&d);
						ldt=time(NULL);
						editClientInfo(NID,w,d,cname1,cname2,dt,phon,editchoice,ldt,lwt);
						BankSystem_IO();
					case 3:
						printf("Enter the ammount of withdrawal in EGP: ");
						scanf("%d",&w);
						lwt=time(NULL);
						editClientInfo(NID,w,d,cname1,cname2,dt,phon,editchoice,ldt,lwt);
						BankSystem_IO();
					default:
						printf("\nError: Please enter a valid option.\n");
						BankSystem_IO();
				}
			}
			else{
				printf("\nSorry, Account wasn't found.\n\n");
				BankSystem_IO();
			}
		case 3:
			printf("\nEnter the client's National ID: ");
			scanf("%d",&NID);
			if(searchingID(NID)==1)
				deleteClient(NID);
			else
				printf("\nThis account is already unavailable.\n\n");
			BankSystem_IO();
		case 4:
			printf("Enter the client's National ID: ");
			scanf("%d",&NID);
			if(searchingID(NID)==1)
				dispClient(NID);
			else
				printf("\nSorry, Account wasn't found.\n\n");
			BankSystem_IO();
		case 5:
			sortingClients();
			listingClients();
			BankSystem_IO();
		case 6:
			printf("Are you sure you want to QUIT?(y/n): ");
			while(yon!='y'&& yon!='Y'&& yon!='n'&& yon!='N')
				scanf("%c",&yon);
			if(yon=='Y'||yon=='y'){
				printf("\n***ALL CLIENTS INFORMATION ARE SAVED SUCCESSFULY***\n");			
				
			}
			else if(yon=='N'||yon=='n')
				BankSystem_IO();
		default:
			printf("\nError: Please enter a valid option.\n");
			BankSystem_IO();		
	}
}

void addClient(int NID,int w,int d,char cname1[],char cname2[],char dt[],char phon[],time_t ldt,time_t lwt){
	struct client* newclient;
	newclient=(struct client*)malloc(sizeof(struct client));
	newclient->ID=NID;
	for(int i=0;(i<10 && cname1[i] != '\0');i++)
		newclient->name1st[i]=cname1[i];
	for(int i=0;(i<10 && cname2[i] != '\0');i++)
		newclient->name2nd[i]=cname2[i];
	for(int i=0;(i<10 && dt[i] != '\0');i++)
		newclient->DOB[i]=dt[i];
	for(int i=0;(i<13 && phon[i] != '\0');i++)
		newclient->PHN[i]=phon[i];
	newclient->withdrawal=w;
	newclient->deposit=d;
	newclient->balance= newclient->deposit - newclient->withdrawal;
	newclient->lastdeposit=ldt;
	newclient->lastwithdrawal=lwt;
	newclient->next=headclient;
	headclient=newclient;
	printf("\n*MR/MRS.%s's account is added successfully*\n\n",newclient->name1st);
}

void editClientInfo(int NID,int w,int d,char cname1[],char cname2[],char dt[],char phon[],int flag,time_t ldt,time_t lwt){
	struct client* toedit;
	toedit=headclient;
	while(toedit != NULL){
		if(toedit->ID==NID){
			if(flag==1){
				for(int i=0;(i<10 && cname1[i] != '\0');i++)
					toedit->name1st[i]=cname1[i];
				for(int i=0;(i<10 && cname2[i] != '\0');i++)
					toedit->name2nd[i]=cname2[i];
				for(int i=0;(i<10 && dt[i] != '\0');i++)
					toedit->DOB[i]=dt[i];
				for(int i=0;(i<13 && phon[i] != '\0');i++)
					toedit->PHN[i]=phon[i];
				printf("\n*Personal information is edited successfully*\n\n");
			}
			else if(flag==2){
				toedit->deposit=toedit->deposit+d;
				toedit->balance=toedit->balance + d - w;
				toedit->lastdeposit=ldt;
				printf("\n*Deposit process is done successfully*\n\n");
			}
			else if(flag==3){
				toedit->withdrawal=toedit->withdrawal+w;
				toedit->balance=toedit->balance + d - w;
				toedit->lastwithdrawal=lwt;
				printf("\n*Withdrawal process is done successfully*\n\n");
			}
		}
		toedit=toedit->next;			
	}
}

void deleteClient(int NID){
	struct client* todelete;
	struct client*prev;
	todelete=headclient;

	if(todelete != NULL && todelete->ID==NID){
		headclient=todelete->next;
		free(todelete);
	}
	else{
		while(todelete != NULL && todelete->ID != NID){
			prev=todelete;
			todelete=todelete->next;	
		}

		prev->next=todelete->next;
		free(todelete);
	}
	printf("\n***Account is deleted successfully***\n\n");
}

void listingClients(){
	if(headclient==NULL)
		printf("\n***NO CLIENTS FOUND***\n");
	else{
		struct client* tolist=headclient;
		printf("\n*********************************************\n");
		printf("*********************************************\n");
		printf("*********** LIST OF BANK CLIENTS ************\n");
		printf("*********************************************\n");
		while(tolist != NULL){
			printf("*********************************************\n");
			printf("*  Name: %s %s\n\n",tolist->name1st,tolist->name2nd);
			printf("*  National ID: %d\n\n",tolist->ID);
			printf("*  Date of birth: %s\n\n",tolist->DOB);
			printf("*  Phone number: %s\n\n",tolist->PHN);
			printf("*  Balance: %d EGP\n\n",tolist->balance);
			printf("*  Last deposit: %s\n",ctime(&(tolist->lastdeposit)));
			if(tolist->lastwithdrawal != 0)
				printf("*  Last withdrawal: %s",ctime(&(tolist->lastwithdrawal)));
			if(tolist->lastwithdrawal == 0)
				printf("*  NO withdrawals yet..\n");
			printf("*********************************************\n");
			tolist=tolist->next;
		}
	}
}

void dispClient(int NID){
	struct client* todisp;
	todisp=headclient;
	while(todisp != NULL){
		if(todisp->ID==NID){
			printf("\n********************************************\n");
			printf(">>CLIENT'S INFORMATION:\n\n\n");
			printf("> National ID: %d\n\n",todisp->ID);
			printf("> Name: %s %s\n\n",todisp->name1st,todisp->name2nd);
			printf("> Date of birth: %s\n\n",todisp->DOB);
			printf("> Phone number: %s\n\n",todisp->PHN);
			printf("> Balance: %d EGP\n\n",todisp->balance);
			printf("> Last deposit: %s\n",ctime(&(todisp->lastdeposit)));
			if(todisp->lastwithdrawal != 0)
				printf("> Last withdrawal: %s",ctime(&(todisp->lastwithdrawal)));
			if(todisp->lastwithdrawal == 0)
				printf("> NO withdrawals yet..\n");
			printf("********************************************\n\n");
		}
		todisp=todisp->next;
	}
}

int searchingID(int NID){
	int found=0;
	struct client* tosearch;
	tosearch=headclient;
	while(tosearch != NULL){
		if(tosearch->ID==NID)
			found=1;
		tosearch=tosearch->next;
	}
	return found;
}

void sortingClients(){
	struct client* m, *n,*tempNode;
	tempNode=(struct client*)malloc(sizeof(struct client));
	m=(struct client*)malloc(sizeof(struct client));
	n=(struct client*)malloc(sizeof(struct client));
	for(m=headclient;m != NULL;m=m->next){
		for(n=m->next; n!=NULL ;n=n->next){
			for(int c=0;c<10;c++){
				if(m->name1st[c] > n->name1st[c]){
					for(int i=0;i<10;i++)
						tempNode->name1st[i]=m->name1st[i];
					for(int i=0;i<10;i++)
						tempNode->name2nd[i]=m->name2nd[i];
					for(int i=0;i<10;i++)
						tempNode->DOB[i]=m->DOB[i];
					for(int i=0;i<13;i++)
						tempNode->PHN[i]=m->PHN[i];
					tempNode->ID=m->ID;
					tempNode->withdrawal=m->withdrawal;
					tempNode->deposit=m->deposit;
					tempNode->balance=m->balance;
					tempNode->lastdeposit=m->lastdeposit;
					tempNode->lastwithdrawal=m->lastwithdrawal;
					for(int i=0;i<10;i++)
						m->name1st[i]=n->name1st[i];
					for(int i=0;i<10;i++)
						m->name2nd[i]=n->name2nd[i];
					for(int i=0;i<10;i++)
						m->DOB[i]=n->DOB[i];
					for(int i=0;i<13;i++)
						m->PHN[i]=n->PHN[i];
					m->ID=n->ID;
					m->withdrawal=n->withdrawal;
					m->deposit=n->deposit;
					m->balance=n->balance;
					m->lastdeposit=n->lastdeposit;
					m->lastwithdrawal=n->lastwithdrawal;
					for(int i=0;i<10;i++)
						n->name1st[i]=tempNode->name1st[i];
					for(int i=0;i<10;i++)
						n->name2nd[i]=tempNode->name2nd[i];
					for(int i=0;i<10;i++)
						n->DOB[i]=tempNode->DOB[i];
					for(int i=0;i<13;i++)
						n->PHN[i]=tempNode->PHN[i];
					n->ID=tempNode->ID;
					n->withdrawal=tempNode->withdrawal;
					n->deposit=tempNode->deposit;
					n->balance=tempNode->balance;
					n->lastdeposit=tempNode->lastdeposit;
					n->lastwithdrawal=tempNode->lastwithdrawal;
					break;
				}
			}
		}
	}
}
