#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ALPHABET 26
#define MAX_LEN 255
#define MAX_ELEMENT 1000

typedef struct {
    int alpha; // 알파벳 저장을 위한 배열
    int freq; // 빈도수 저장을 위한 배열
}AlphaType;

typedef struct TreeNode{
    AlphaType weight;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;

typedef struct {
    TreeNode *pTree;
    int key;
}Element;

typedef struct {
    Element heap[MAX_ELEMENT];
    int heap_size;
}HeapType;


void InsertHeap(HeapType *h,Element item)
{
    int i;
    i=++(h->heap_size);

    while(i != 1 && item.key < h->heap[i/2].key) // 부모노드와 비교
    {
        h->heap[i]=h->heap[i/2];
        i/=2;
    }

    h->heap[i]=item;
}

Element DeleteHeap(HeapType *h)
{
    int parent=1,child=2;
    Element data,temp;

    data = h->heap[parent];
    temp = h->heap[(h->heap_size)--]; // 삭제에 의한 size 감소

    while(child <= h->heap_size)
    {
        //자식 노드간 작은 수 비교
        if((child < h->heap_size) && (h->heap[child].key) > h->heap[child+1].key)
            child++;

        if(temp.key <= h->heap[child].key) break;

        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2; // 다음 자식 노드와 비교
    }

    h->heap[parent]=temp;
    return data;
}

TreeNode* MakeNode(TreeNode *left,TreeNode *right) // 노드 생성
{
    TreeNode *node=(TreeNode*)malloc(sizeof(TreeNode));

    if(node == NULL)
    {
        printf("메모리 할당 에러\n");
        exit(-1);
    }

    node->left=left;
    node->right=right;

    return node;
}

void PrintTree(TreeNode *p,int i,char *pCode)
{
    if(p)
    {
        i++;
        pCode[i]='1';
        PrintTree(p->left,i,pCode);
        pCode[i]='0';
        PrintTree(p->right,i,pCode);
        pCode[i]='\0';

        if(p->left == NULL && p->right == NULL)
        {
            printf("char: %3c\t freq: %3d\t code: %s\n",p->weight.alpha,p->weight.freq,pCode);

        }
    }


}

int DestroyTree(TreeNode *p)
{
    if(p == NULL) return -1;

    DestroyTree(p->left);
    DestroyTree(p->right);

    free(p);

    return 1;
}

void HuffmanTree(AlphaType *pArr,int n)
{
    TreeNode *node,*temp;
    Element e,e1,e2;
    HeapType heap;
    char binaryCode[100];
    int i;

    heap.heap_size=0;

    for(i=0;i<n;i++)
    {
        node=MakeNode(NULL,NULL);
        node->weight.alpha=pArr[i].alpha;
        e.key=node->weight.freq=pArr[i].freq;
        e.pTree=node;
        InsertHeap(&heap,e); // 생성한 노드를 힙에 삽입
    }

    for(i=0;i<n-1;i++) // n-1까지 반복, 마지막 남은 노드가 루트
    {
        e1=DeleteHeap(&heap); // 최소값을 가지는 노드 2개를 빼낸다
        e2=DeleteHeap(&heap);

        temp=MakeNode(e1.pTree,e2.pTree); // 2개의 노드를 가지는 노드 생성

        e.key=temp->weight.freq=e1.key+e2.key; // 2개의 노드 값을 더한다
        e.pTree=temp; // 위에서 만든 노드를 대입

        InsertHeap(&heap,e); // 트리로 구성된 노드를 힙에 삽입
    }
    e = DeleteHeap(&heap); // 여기서 꺼낸 데이터는 완성된 트리

    PrintTree(e.pTree,-1,binaryCode); // 허프만 코드 출력


    DestroyTree(e.pTree); // 메모리 반환

}

void Init(AlphaType *p)
{
    for(int i=0;i<ALPHABET;i++)
    {
        p[i].alpha=i+65;
        p[i].freq=0;
    }
}

int main()
{

    AlphaType data[ALPHABET]; // 문자열의 갯수 저장을 위한 변수
    AlphaType *copyData; // 존재하는 문자열의 갯수 저장을 위한 변수

    Init(data);

    char *str=(char*)malloc(sizeof(char)*MAX_LEN);

    int i,j,k=0;
    int flag,count=0;

    FILE* file = fopen("C:\\Users\\user\\CLionProjects\\untitled6\\test.txt", "rt");
    fgets(str, MAX_LEN, file);

    strupr(str); // 모든 문자를 대문자로 변환
    printf("%s", str);
    printf("\n");

    for(i='A';i<='Z';i++)
    {
        flag=0;
        for(j=0;j<strlen(str);j++)
        {
            if(i == str[j])
            {
                data[i-65].freq++;
                flag=1; // i값의 알파벳이 존재
            }
        }
        if(flag==1)
            count++; // 알파벳이 존재하므로 카운터 증가
    }

    copyData=(AlphaType*)malloc(sizeof(AlphaType)*count);

    for(i=0;i<ALPHABET;i++)
    {
        if(data[i].freq != NULL) // 존재하는 문자만 복사
        {
            copyData[k].alpha=i+65;
            copyData[k].freq=data[i].freq;
            k++;
        }
    }

    printf("\n- Huffman Tree Code -\n");
    HuffmanTree(copyData,count);


    free(str);
    free(copyData);

    return 0;
}