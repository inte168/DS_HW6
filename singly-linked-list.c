/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
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

	printf("-----허정윤 2021041047-----\n");

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
	//생성하는 함수
	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	//h와 연결된 모든 메모리를 해제시킴.
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
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
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	//새로운 노드를 만들고 값을 삽입.
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
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

	while(n!=NULL){//n과 trail을 옮겨가며 반복.
		if(n->key >= key){//n노드의 key가 입력된 key보다 크거나 같은경우
			if(n == h->first){//그중 맨 앞의 경우(h->first를 바꿔줘야함.)
				h->first = node;
				node->link = n;
			}
			else{//그 외의 경우
				node->link = n;
				trail->link = node;
			}
			return 0;
		}
		trail = n;
		n=n->link;
	}
	//if문 안에 return이 있기 때문에 여기로 왔다는 것은 처음 if를 만족시키지 못했다는 것.==모든 노드의 값보다 크다.
	//마지막에 삽입해준다.(이때 n은 null이지만, trail은 그 이전 노드)
	trail->link = node; 
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));//노드를 생성하고 key값을 넣어준다. 연결된 link는 없음(null)
	node->key = key;
	node->link = NULL;

	if(h->first == NULL){//h가 비어있는 리스트인 경우는 node를 first로 설정하고 리턴.
		h->first = node;
		return 0;
	}
	listNode* n = h->first;				//넘겨줄 listNode n
	for(;n->link!=NULL; n = n->link){}//반복 for문 버전, 조건을 만족하는 동안 n을 다음으로 넘긴다.
	n->link = node;

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {//리스트가 비어있을 경우 에러 메시지 출력 후 리턴
	if(h->first == NULL){
		printf("List is Empty. Can't Delete\n");
		return 0;
	}//n에 h->first를 넘기고 link를 first로 만들어서 n 해제.
	listNode* n = h->first;
	h->first = n->link;
	free(n);

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	
	if(h->first == NULL){//리스트가 비어있을 경우 에러 메시지 출력 후 리턴.
		printf("List is Empty. Can't Delete\n");
		return 0;
	}
	//이동용 n과 traill
	listNode* n = h->first;
	listNode* trail = NULL;

	while(n != NULL){//전체적으로 삽입때와 유사.(n을 이동시키면서 반복)
		if(n->key == key){//키를 찾으면
			if(n == h->first){//처음인 경우
				h->first = n->link;
			}
			else{//그외
				trail->link = n->link;
			}
			//n->link가 다른 노드에 넘어갔으므로 n을 해제할 수 있다.
			free(n);
			return 0;
		}
		trail = n;
		n=n->link;
	}
	//여기까지 왔으면 찾지 못한 경우.
	printf("Can't find the key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if(h->first == NULL){//리스트가 비어있을 경우 에러 메시지 출력 후 리턴.
		printf("List is Empty. Can't Delete\n");
		return 0;
	}
	listNode* n = h->first;
	listNode* trail = NULL;

	if(n->link == NULL){//노드가 하나(==다음 노드가 없음)면 first도 null로 만들고 n을 해제
		h->first = NULL;
		free(n);
		return 0;
	}

	while(n->link != NULL){//n을 마지막 노드까지 옮기는 과정
		trail = n;
		n=n->link;
	}
	//trail->link는 원래 n이 연결되어있는데 연결을 끊고, n을 해제
	trail->link = NULL;
	free(n);

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	if(h->first == NULL) {//비어있을 경우 에러메시지 출력 후 리턴.
		printf("List is Empty. Can't Invert.\n");
		return 0;
	}
	//여기서는 h->first로 노드를 가져오기에 n으로 따로 빼준다.
	//trail은 이전값을 연결하기 위해, middle은 새로 연결하기 위해 사용
	listNode* middle = NULL;
	listNode* trail = NULL;
	listNode* n = h->first;

	while(n){
		//middle과 n은 앞 노드부터 나아가게되고, trail은 middle의 값을 받아서 middle->link로 연결한다.
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}
	//새로 연결된 middle을 h->first로 넣어서 사용할 수 있게 한다.
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

