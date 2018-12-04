#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE_TRACE 128
typedef struct node *nodePointer;
typedef struct node {//binary tree 的 node
    char character;
    int frequency;
    nodePointer leftChild;
    nodePointer rightChild;
};
typedef struct {//定義字典數字組合
    char character;
    int frequency;
    char code[50];
    int code_num;
} dictionary;
nodePointer create(char c, int f){//製造 binary tree 的 node
    nodePointer temp;
    temp=(nodePointer)malloc(sizeof(nodePointer));
    temp->character=c;
    temp->frequency=f;
    temp->leftChild=NULL;
    temp->rightChild=NULL;
    return temp;
}
nodePointer pop(nodePointer *priorityQueue, int n){//priorityQueue pop 出最小 frequency 字元
    int parent, child;
    nodePointer item, temp;
    item = priorityQueue[1];
    temp = priorityQueue[n];
    parent = 1;
    child = 2;
    n--;
    while (child <= n) {
        if ((child < n)&&( priorityQueue[child]->frequency > priorityQueue[child+1]->frequency))//從目前父節點找最小的child
            child++;
        if (temp->frequency <= priorityQueue[child]->frequency) break;
        priorityQueue[parent] = priorityQueue[child];//移至下層
        parent=child;
        child *= 2;
    }
    priorityQueue[parent] = temp;
    return item;
}
int main()
{
    int i,j,char_count;
    int parent,child,k,x,top;
    short int add;
    char sen[200];
    int MAX_QUEUE_SIZE=64;
    nodePointer *priorityQueue;
    nodePointer newnode;
    priorityQueue=(nodePointer)malloc(MAX_QUEUE_SIZE*sizeof(nodePointer));
    nodePointer *stack;
    stack=(nodePointer)malloc(MAX_STACK_SIZE_TRACE*sizeof(nodePointer));
    freopen("text.txt","r",stdin);
    freopen("code.txt","w",stdout);
    while(gets(sen)!=NULL){
        int seq[200];
        dictionary a[200];
        if(sen[strlen(sen)-1]==13)
    		sen[strlen(sen)-1]='\0';
        char_count=0;
	/* 計算各字元出現頻率 */
        for(i=0;i<strlen(sen);i++){
            add=1;
            for(j=0;j<char_count;j++)
                if(a[j].character==sen[i]){
                    a[j].frequency++;
                    add=0;
                    break;
                }
            if(add){
                a[char_count].character=sen[i];
                a[char_count++].frequency=1;
            }
        }
	/* 製造priorityQueue(heap) */
        int index=1;
        for(j=0;j<char_count;j++){
            child=index;
            parent=index/2;
            while(child!=1&&(priorityQueue[parent]->frequency > a[j].frequency)){
                priorityQueue[child]=priorityQueue[parent];
                child=parent;
                if(parent) parent/=2;
            }
            priorityQueue[child]=create(a[j].character,a[j].frequency);
            index++;
        }
	/* 製造 binary tree 最後完整樹存至 priorityQueue[1] */
        nodePointer np1,np2;
        index--;
        while(index>1){
            np1=pop(priorityQueue,index);
            np2=pop(priorityQueue,index-1);
            newnode=create(0,np1->frequency+np2->frequency);//新節點連接pop出的兩個node
            newnode->leftChild=np1;
            newnode->rightChild=np2;
            index--;
            child=index;
            parent=index/2;
            while(child!=1&&(priorityQueue[parent]->frequency > (np1->frequency+np2->frequency))){
                priorityQueue[child]=priorityQueue[parent];
                child=parent;
                if(parent) parent/=2;
            }
            priorityQueue[child]=newnode;
        }
	/* 走訪 binary tree，定義出每個點的字典數字組合(使用stack) */
        x = 0;
        k = 0;
        top = -1;
        stack[++top]=create(0,0);
        newnode=priorityQueue[child];
        while(1){
            for(;newnode;newnode=newnode->leftChild){
                stack[++top]=newnode;
                if(newnode->leftChild)
                    seq[x++]=0;
            }
            newnode=stack[top--];
            if(newnode->frequency==0)
                break;
            if(newnode->character!=0){
                for(j=0;j<char_count;j++)
                    if(a[j].character==newnode->character)
                        break;
                for(i=0;i<x;i++)
                    a[j].code[i]=seq[i];
                a[j].code_num=x;
                for(i=x-1;i>=0;i--){
                    if(seq[i]==1) x--;
                    if(seq[i]==0){
                        seq[i]=1;
                        break;
                    }
                }
            }
            newnode=newnode->rightChild;
        }
	/* 印出所需 Output */
        printf("%d\n",char_count);
        for(i=0;i<char_count;i++){
            if(a[i].character==' ')
                printf("space ");
            else
                printf("%c ",a[i].character);
            printf("%d ",a[i].frequency);
            for(j=0;j<a[i].code_num;j++)
                printf("%d",a[i].code[j]);
            printf("\n");
        }
        k = 0;
        for(i=0;i<strlen(sen);i++){
            for(x=0;x<char_count;x++)
                if(a[x].character==sen[i])
                    break;
            k+=a[x].code_num;
            for(j=0;j<a[x].code_num;j++)
                printf("%d",a[x].code[j]);
        }
        printf("\n");
        printf("%d\n",k);
    }
    return 0;
}
