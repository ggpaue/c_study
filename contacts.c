
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

void main() {
	
}