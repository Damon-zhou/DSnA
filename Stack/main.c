#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node * pNext;
}NODE, * PNODE;

typedef struct Stack{
    PNODE pTop;
    PNODE pBottom;
}STACK, *PSTACK;

bool empty(PSTACK pS){
    if(pS->pTop == pS->pBottom)
        return true;
    else
        return false;
}

void init(PSTACK);
void push(PSTACK,int);
void traverse(PSTACK);
bool pop(PSTACK,int*);
void clear(PSTACK);

int main() {
    STACK S;
    int val;

    init(&S);
    push(&S,1);
    push(&S,2);
    push(&S,5);
    push(&S,7);
    push(&S,3);
    traverse(&S);
    //clear(&S);

    //pop(&S,&val);
    if(pop(&S,&val))
        printf("出栈成功！出栈的元素是%d\n",val);
    else
        printf("出栈失败");
    traverse(&S);

    clear(&S);
    traverse(&S);


    return 0;
}

void init(PSTACK pS){
    pS->pTop = (PNODE)malloc(sizeof(NODE));
    if(pS->pTop == NULL){
        printf("动态内存分配失败！");
        exit(-1);
    }else{
        pS->pBottom = pS->pTop;
        pS->pTop->pNext = NULL; //Bottom的指针域清空也行
    }

}

void push(PSTACK pS, int val){
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    pNew->data = val;
    pNew->pNext = pS->pTop;

    pS->pTop = pNew;
}

void traverse(PSTACK pS){
    PNODE p = pS->pTop;

    while (p != pS->pBottom){
        printf("%d",p->data);
        p = p->pNext;
    }
    printf("\n");
}

//把pS所指向的栈出栈一次，并把出栈元素存入pVal这个形参所指向的变量中，如果出栈失败，返回false
bool pop(PSTACK pS, int * pVal){
    if(empty(pS)){  //pS本身存放的就是S的地址
        return false;
    }else{
        PNODE r = pS->pTop;
        *pVal = r->data;
        pS->pTop = r->pNext;
        free(r);
        r = NULL;
        return true;
    }

}

//清空数据，但不是删除栈
void clear(PSTACK pS){
    if(empty(pS))
        return;
    else{
        PNODE  p = pS->pTop;
        /*PNODE  q = NULL;

        while(p != pS->pBottom){
            q = p->pNext;
            free(p);
            p = q;*/

        while(p != pS->pBottom){
            p = pS->pTop->pNext;
            free(pS->pTop);
            pS->pTop = p;
        }


        }
        pS->pTop = pS->pBottom;
    }
