# Huffman_coding
DS_Homework3

程式目的

以頻率高低建立出由 0 跟 1 表示的字元句子，使存入的數字碼較原本直接指定個別字元數字碼的數量降低。

主要架構

typedef struct node *nodePointer;
typedef struct node {//binary tree 的 node
    char character;
    int frequency;
    nodePointer leftChild;
    nodePointer rightChild;
};(作業要求)

typedef struct {//定義字典數字組合
    char character;
    int frequency;
    char code[50];
    int code_num;
} dictionary;

nodePointer create(char c, int f);//用 malloc 製造 binary tree 的 node(作業要求)

nodePointer pop(nodePointer *priorityQueue, int n);//priorityQueue pop 出最小 frequency 節點

main():

首先讀入一行'/n'結尾的文字，先計算並記錄出現字元跟不同字元出現的頻率，

再來用這些得到的資料進行 priorityQueue(heap) 的建立，製造最小堆積。

利用最小堆積來建立 binary tree，每次 pop 出兩個 node 去建立一個 new node 連接 leftChild, rightChild，

最後 binary tree 存放至 priorityQueue[1]。

再利用 stack 進行走訪 binary tree 的行動，從左邊走到底，每次都將 node 存入 stack 並放上 0 到目前字典序中，

走到底後，叫出目前最後放入的 node (後進先出)，如果 character 非 0，代表 node 在字典中，所以把數字組記起來。

如果目前數字組的最後一個數字是 0 要換成 1，代表往右走，

因為每次都是兩個兩個建立 newnode，所以每個 leaf 的 parent 的 leftChild, rightChild 一定都有連接，

如果目前數字組的最後一個數字是 1 代表探訪完畢，所以刪除這個位元，

接下來往右邊走，直到 leftChild, rightChild 全部都沒有的時候完成探訪。

分別印出字典紀錄的字元數、個別字元的數字組、那句話的數字組版本以及那句話由多少個 0, 1 組成。

時間複雜度 : n>>e時，時間複雜度為O(n)

以n表示原本句子的字元數量，e表示不同字元的數量(不同字元只有有限多個，不會無限)

/* 計算各字元出現頻率 */: 1+2+3+...+e+e+e+... => O(n*e)

/* 製造priorityQueue(heap) */: O(e)*O(loge)=O(eloge)(迴圈跟父子節點移動)

/* 製造 binary tree 最後完整樹存至 priorityQueue[1] */:O(loge)*O(e*e)(每次只減少堆積內的一個node，e+...+2 => O(e*e))

/* 走訪 binary tree，定義出每個點的字典數字組合(使用stack) */:2*(e+...+2) => O(e*e)(binary tree edge數)

/* 印出所需 Output */:O(n)
