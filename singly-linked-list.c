/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("-----������ 2021041047-----\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {
	//�����ϴ� �Լ�
	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	//h�� ����� ��� �޸𸮸� ������Ŵ.
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
	//���ο� ��带 ����� ���� ����.
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if(h->first == NULL){
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;

	while(n!=NULL){//n�� trail�� �Űܰ��� �ݺ�.
		if(n->key >= key){//n����� key�� �Էµ� key���� ũ�ų� �������
			if(n == h->first){//���� �� ���� ���(h->first�� �ٲ������.)
				h->first = node;
				node->link = n;
			}
			else{//�� ���� ���
				node->link = n;
				trail->link = node;
			}
			return 0;
		}
		trail = n;
		n=n->link;
	}
	//if�� �ȿ� return�� �ֱ� ������ ����� �Դٴ� ���� ó�� if�� ������Ű�� ���ߴٴ� ��.==��� ����� ������ ũ��.
	//�������� �������ش�.(�̶� n�� null������, trail�� �� ���� ���)
	trail->link = node; 
	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));//��带 �����ϰ� key���� �־��ش�. ����� link�� ����(null)
	node->key = key;
	node->link = NULL;

	if(h->first == NULL){//h�� ����ִ� ����Ʈ�� ���� node�� first�� �����ϰ� ����.
		h->first = node;
		return 0;
	}
	listNode* n = h->first;				//�Ѱ��� listNode n
	for(;n->link!=NULL; n = n->link){}//�ݺ� for�� ����, ������ �����ϴ� ���� n�� �������� �ѱ��.
	n->link = node;

	return 0;
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {//����Ʈ�� ������� ��� ���� �޽��� ��� �� ����
	if(h->first == NULL){
		printf("List is Empty. Can't Delete\n");
		return 0;
	}//n�� h->first�� �ѱ�� link�� first�� ���� n ����.
	listNode* n = h->first;
	h->first = n->link;
	free(n);

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	
	if(h->first == NULL){//����Ʈ�� ������� ��� ���� �޽��� ��� �� ����.
		printf("List is Empty. Can't Delete\n");
		return 0;
	}
	//�̵��� n�� traill
	listNode* n = h->first;
	listNode* trail = NULL;

	while(n != NULL){//��ü������ ���Զ��� ����.(n�� �̵���Ű�鼭 �ݺ�)
		if(n->key == key){//Ű�� ã����
			if(n == h->first){//ó���� ���
				h->first = n->link;
			}
			else{//�׿�
				trail->link = n->link;
			}
			//n->link�� �ٸ� ��忡 �Ѿ���Ƿ� n�� ������ �� �ִ�.
			free(n);
			return 0;
		}
		trail = n;
		n=n->link;
	}
	//������� ������ ã�� ���� ���.
	printf("Can't find the key = %d\n", key);
	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	if(h->first == NULL){//����Ʈ�� ������� ��� ���� �޽��� ��� �� ����.
		printf("List is Empty. Can't Delete\n");
		return 0;
	}
	listNode* n = h->first;
	listNode* trail = NULL;

	if(n->link == NULL){//��尡 �ϳ�(==���� ��尡 ����)�� first�� null�� ����� n�� ����
		h->first = NULL;
		free(n);
		return 0;
	}

	while(n->link != NULL){//n�� ������ ������ �ű�� ����
		trail = n;
		n=n->link;
	}
	//trail->link�� ���� n�� ����Ǿ��ִµ� ������ ����, n�� ����
	trail->link = NULL;
	free(n);

	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	if(h->first == NULL) {//������� ��� �����޽��� ��� �� ����.
		printf("List is Empty. Can't Invert.\n");
		return 0;
	}
	//���⼭�� h->first�� ��带 �������⿡ n���� ���� ���ش�.
	//trail�� �������� �����ϱ� ����, middle�� ���� �����ϱ� ���� ���
	listNode* middle = NULL;
	listNode* trail = NULL;
	listNode* n = h->first;

	while(n){
		//middle�� n�� �� ������ ���ư��Եǰ�, trail�� middle�� ���� �޾Ƽ� middle->link�� �����Ѵ�.
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}
	//���� ����� middle�� h->first�� �־ ����� �� �ְ� �Ѵ�.
	h->first = middle;

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

