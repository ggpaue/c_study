
#include <stdlib.h>
#include <stdio.h>

struct date
{
	char name[16];
	char phone[32];
};

typedef struct node
{
	struct date info;
	struct node *next;
}NODE;

NODE *load() {
	int i = 0;

	NODE *head, *tail, *p;

	head = tail = (NODE *)malloc(sizeof(NODE));

	tail -> next = NULL;

	FILE *fp;
	fp = fopen("list.dat", "r");
	
	if(fp == NULL) {
		printf("Unable to open file!\n");
		return NULL;
	}

	if(feof(fp) != NULL) {
		p = (NODE *)malloc(sizeof(NODE));

		fread(p, sizeof(p -> info), 1, fp);
		
		if(feof(fp) != NULL) {
			printf("File has no content!\n");
			free(p);
		}
		return NULL;
	}

	while(feof(fp) == NULL) {
		p = (NODE *)malloc(sizeof(NODE));

		fread(p, sizeof(p -> info), 1, fp);
		printf("reading the %dth data\n", i);
		i++;

		if(feof(fp) != NULL) {
			free(p);
			break;
		}

		p -> next = NULL;
		tail ->next = p;
		tail = p;
	}
	fclose(fp);
	return head;
}

NODE *create() {
	NODE *head, *tail;
	head = tail = (NODE *)malloc(sizeof(NODE));
	tail -> next = NULL;

	while(1) {
		NODE *p = (NODE *)malloc(sizeof(NODE));
		printf("please input contact name: \n");
		fflush(stdin);
		scanf("%s", p -> info.name);

		printf("please input phone number: \n");
		fflush(stdin);
		scanf("%s", p->info.phone);

		p -> next = NULL;
		tail -> next = p;
		tail = p;

		printf("continue adding new contacts? \n");
		fflush(stdin);
		if(getchar() == 'n') break;
	}
	return head;
}

int view(NODE *head) {
	NODE *p1, *p2;
	p1 = p2 = head;

	if(head -> next == NULL) {
		printf("the list is empty. \n");
		printf("\n");
		return 0;
	}

	printf("-----------------------\n");
	printf("name              phone\n");
	printf("-----------------------\n");

	p1 = head->next;
	while(p1 != NULL) {
		printf("%s, %s\n", p1 -> info.name, p1 -> info.phone);
		p2 = p1;
		p1 = p1 -> next;
	}
	return 0;
}

int search(NODE *head) {
	if(head -> next == NULL) {
		printf("the list is empty!\n");
		return 0;
	}

	NODE *p1, *p2;
	p1 = head -> next;
	p2 = head;

	int i = 0;
	printf("search by name or phone? (n / p)\n");
	fflush(stdin);
	char ch = getchar();
	if(ch == 'n') {
		printf("please input the name you want: \n");
		char na[16];
		fflush(stdin);
		gets(na);

		while(p1 != NULL) {
			if(strcmp(p1 -> info.name, na) == 0) {
				printf("%s %s\n", p1 -> info.phone, p1 -> info.phone);
				i = 1;
			}
			p2 = p1;
			p1 = p1 -> next;
		}

		if(i == 0) {
			printf("no matched entries!\n");
			return 0;
		}
	} else if(ch == 'p') {
		printf("please input the phone number: \n");
		char phone1[32];
		fflush(stdin);
		gets(phone1);
		i = 0;

		while(p1 != NULL) {
			if(strcmp(p1 -> info.phone, p1 -> info.phone));
			i = 1;
		}
		p2 = p1;
		p1 = p1 -> next;
	}
	if(i == 0) {
		printf("could not find matched record! \n");
		return 0;
	}

	return 0;
}

int add(NODE *head) {
	printf("Want to add a new contact? \n");
	char ch;
	ch = getchar();
	if(ch == 'Y' || ch == 'y') {
		NODE *p1;
		while(ch == 'y' || ch == 'Y') {
			p1 = (NODE *)malloc(sizeof(NODE));
			printf("please input name: \n");
			fflush(stdin);
			scanf("%s", p1 -> info.name);
			printf("please input phone number: \n");
			fflush(stdin);
			scanf("%s", p1 -> info.phone);

			p1 -> next = head -> next;
			head -> next = p1;

			printf("want to add more contacts? \n");
			fflush(stdin);
			ch = getchar();
		}
		return 0;
	}
	return 0;
}

int save(NODE *head) {
	NODE *p1;
	p1 = head -> next;

	FILE *fp;
	fp = fopen("list.dat", "w");
	
	if(fp == NULL) {
		printf("failed to open file\n");
		return 0;
	}

	if(head -> next == NULL) {
		printf("contacts are empty!\n");
		return 0;
	}

	while(p1 != NULL) {
		fwrite(p1, sizeof(p1 -> info.name), 1, fp);
		p1 = p1 -> next;
	}

	fclose(fp);
	printf("save successfully! \n");
	return 0;
}

int del(NODE *head) {
	if(head -> next == NULL) {
		printf("the list is empty! \n");
		printf("\n");
		return 0;
	}

	NODE *p1, *p2;
	p1 = head -> next;
	p2 = head;
	printf("search by name or phone? \n");
	fflush(stdin);
	char ch = getchar();
	if(ch == 'n') {
		printf("please input name you want to search: \n");
		
		char na[16];
		fflush(stdin);
		gets(na);

		while(p1 != NULL) {
			if(strcmp(p1 -> info.name, na) == 0) {
				printf("%s %s\n", p1 -> info.name, p1 -> info.phone);
				printf("are you sure to delete this entry? \n");
				ch = getchar();
				if(ch == 'Y' || ch == 'y') {
					NODE *p3 = (NODE *)malloc(sizeof(NODE));
					p3 = p1;
					p2 -> next = p1 -> next;
					p1 = p1 -> next;
					free(p3);
				}
			}
		
			p2 = p1;
			p1 = p1 -> next;
		}
		return 0;

	} else if(ch == 'p') {
		printf("please input phone number you want to search: \n");
		char tele[32];
		fflush(stdin);
		gets(tele);

		while(p1 != NULL) {
			if(strcmp(p1 -> info.phone, tele) == 0) {
				printf("\n");
				printf("%s  %s\n", p1 -> info.name, p1 -> info.phone);
				printf("are you sure to delete this entry? \n");
				
				ch = getchar();
				if(ch == 'y') {
					p2 -> next = p1 -> next;
					p1 = p1 -> next;
				} else {
					return 0;
				}
			}

			p2 = p1;
			p1 = p1->next;
		}
		return 0;
	}
	return 0;
}

int freelist(NODE *head) {
	NODE *p1, *p2;
	p1 = p2 = head;

	if(head -> next == NULL) {
		free(head);
		return 0;
	}

	p1 = p1 -> next;
	while(p1 != NULL) {
		free(p2);
		p2 = p1;
		p1 = p1->next;
	}

	free(p2);
	return 0;
}

/*
int clearlist(NODE *head) {
	int i = 0;
	NODE *p1, *p2;
	p1 = p2 = head -> next;
	
	while(p2 != NULL) {
		i = 1;
		p1 = p1 -> next;
		free(p2);
		p2 = p1;
	}

	if(i) head -> next = NULL;
	return i;
}
*/

void menu() {
	NODE *head;

	head = load();

	while(1) {
		if(head == NULL) {
			printf("can not read file. \n");
			break;
		} else {
			printf("data load successfully. \n");
		}
	}

	while(1) {
		printf("please select the following options: \n");
		printf("(1) view the contact list\n" );
		printf("(2) search for a contact. \n");
		printf("(3) add a new contact. \n");
		printf("(4) delete a contact. \n");
		printf("(5) save the contact list. \n");
		printf("(6) exit the system.\n" );
		

		int s;
		scanf("%d", &s);

		switch(s) {
			case 1: view(head); break;
			case 2: search(head); break;
			case 3: add(head); break;
			case 4: del(head); break;
			case 5: save(head); break;
			default: printf("error! please input again!\n");
		}

	}
}

void main() {
	menu();
	
}