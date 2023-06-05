#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int value;
    struct Node *next;
} Node;

void push(Node **head, int data) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
}

int pop(Node **head) {
    Node* prev = NULL;
    int val;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    val = prev->value;
    (*head) = (*head)->next;
    free(prev);
    return val;
}

Node* getNth(Node* head, int n) {
    int counter = 0;
    while (counter < n && head) {
        head = head->next;
        counter++;
    }
    return head;
}

Node* getLast(Node *head) {
    if (head == NULL) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}

void pushBack(Node *head, int value) {
    Node *last = getLast(head);
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->value = value;
    tmp->next = NULL;
    last->next = tmp;
}

Node* getLastButOne(Node* head) {
    if (head == NULL) {
        exit(-2);
    }
    if (head->next == NULL) {
        return NULL;
    }
    while (head->next->next) {
        head = head->next;
    }
    return head;
}

int popBack(Node **head) {
    Node *pFwd = NULL;
    Node *pBwd = NULL;
    if (!head) {
        exit(-1);
    }
    if (!(*head)) {
        exit(-1);
    }

    pFwd = *head;
    while (pFwd->next) {
        pBwd = pFwd;
        pFwd = pFwd->next;
    }

    if (pBwd == NULL) {
        free(*head);
        *head = NULL;
    } else {
        free(pFwd->next);
        pBwd->next = NULL;
    }
}

int GetSize(Node* head){
    int size = 0;
    if (head != NULL)
    {
    size = 1 + GetSize(head->next);//переход к следующему элементу}
    }
    return size;
}

void insert(Node *head, unsigned n, int val) {
    unsigned i = 0;
    Node *tmp = NULL;
    if (n > GetSize(head) || n < 0){
        printf("Error, wrong index.\n");
        return 0;
    }
    else{
        while (i < n && head->next) {
            head = head->next;
            i++;
        }
        tmp = (Node*) malloc(sizeof(Node));
        tmp->value = val;
        if (head->next) {
            tmp->next = head->next;
        } else {
            tmp->next = NULL;
        }
        head->next = tmp;
    }

}

int deleteNth(Node **head, int n) {
    if (n == 0) {
        return pop(head);
    } else {
        Node *prev = getNth(*head, n-1);
        Node *elm  = prev->next;
        int val = elm->value;

        prev->next = elm->next;
        free(elm);
        return val;
    }
}

void deleteList(Node **head) {
    Node* prev = NULL;
    while ((*head)->next) {
        prev = (*head);
        (*head) = (*head)->next;
        free(prev);
    }
    free(*head);
}

void fromArray(Node **head, int *arr, size_t size) {
    size_t i = size - 1;
    if (arr == NULL || size == 0) {
        return;
    }
    do {
        push(head, arr[i]);
    } while(i--!=0);
}

int* toArray(const Node *head) {
    int leng = sizeof(head);
    int *values = (int*) malloc(leng*sizeof(int));
    while (head) {
        values[--leng] = head->value;
        head = head->next;
    }
    return values;
}

void printLinkedList(const Node *head) {
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

void main() {
    Node* head = NULL;
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    fromArray(&head, arr, 10);

    int status = 0;
    int index,number;
    while (1){
        printf("pushBack - 1, insert - 2, delete - 3, printList - 4\n");
        scanf("%d",&status);
        switch(status){
        case 1:
            printf("Enter your number:\n");
            scanf("%d",&number);
            pushBack(head,number);
            break;
        case 2:
            printf("Enter your index:\n");
            scanf("%d",&index);
            printf("Enter your number:\n");
            scanf("%d",&number);
            insert(head,index,number);
            break;
        case 3:
            printf("Enter your index:\n");
            scanf("%d",&index);
            if (index > GetSize(head) || index < 0){
                printf("Error, wrong index.\n");
            }else{
                deleteNth(&head,index-1);
            }
            break;
        case 4:
            printLinkedList(head);
            break;
        default:
            printf("Bye bye!");
            return 0;
        }

    }
    //Delete list
    deleteList(&head);

    getch();
}
