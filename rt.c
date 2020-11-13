#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"rt.h"

int goal[MaxSize][2];
int s_vital[MaxSize][2];//建立重要点地存储区

int arcs[MaxSize][MaxSize];//建立邻接矩阵以保存路径
int dist[MaxSize];
int visited[MaxSize] = {0};
int pre[MaxSize];//存放路径
int s_path[MaxSize][MaxSize];//建立最短路径存储区(坐标转化为单个数字(下表为i*5+j))
int s_nodes[MaxSize];
int g_nodes[MaxSize];

Queue CreateQueue() {
    Queue Q;
    Q = (Queue)malloc(sizeof(struct QNode));
    Q->Front = NULL;
    Q->Rear = NULL;
    return Q;
}

int IsEmpty(Queue Q){
    return (Q->Front == NULL);
}

Queue AddQ(Queue Q,PtrRt Rt) {
    PtrToNode Cell;
    Cell = (PtrToNode)malloc(sizeof(struct Node));
    Cell->Rt = Rt;
    Cell->Next = NULL;
    if(IsEmpty(Q)){
        Q->Front = Cell;
        Q->Rear = Cell;
    }
    else{
        Q->Rear->Next = Cell;
        Q->Rear = Cell;
    }
    return Q;
}

PtrRt DeleteQ(Queue Q){
    PtrToNode Cell;
    PtrRt FrontElem;
    if  (IsEmpty(Q)) {
        printf("The queue is enpty!");
        return 0;
    }
    else {
        Cell = Q->Front;
        if (Q->Front == Q->Rear) // 若队列只有一个元素
            Q->Front = Q->Rear = NULL; // 删除后队列置为空
        else
            Q->Front = Q->Front->Next;
        FrontElem = Cell->Rt;

        free(Cell);  // 释放被删除结点空间
        return  FrontElem;
    }
}

//获取某一位置周围的元素的坐标
int** around(int pos[2]) {
    int **a;
    a = (int**)malloc(8*sizeof(int));
    for(int i=0;i<8;i++) {
        a[i] = (int*)malloc(2*sizeof(int));
    }
    a[2][0] = a[6][0] = pos[0];
    a[0][1] = a[4][1] = pos[1];
    a[0][0] = a[1][0] = a[7][0] = pos[0]-1;
    a[1][1] = a[2][1] = a[3][1] = pos[1]+1;
    a[3][0] = a[4][0] = a[5][0] = pos[0]+1;
    a[5][1] = a[6][1] = a[7][1] = pos[1]-1;
    return a;
}

//进行字符的判断.
int Judge(char c) {
    if(c=='+') return 3;
    else if(c=='#') return 6;
    else if(c=='*') return 9;
    else return 0;
}

//进行数据的存储与记录
void Record(PtrRt Rt,Queue Q,char expor[][MaxCNum]) {
    expor[Rt->Pos[0]][Rt->Pos[1]] = Rt->CTYPE;
}

//创建一个机器人
PtrRt CreateRt(int x,int y,char store[][MaxCNum],int Llen,int Clen) {
    PtrRt Rt;
    Rt = (PtrRt)malloc(sizeof(struct Robot));
    int pos[2] = {x,y};
    int** a = around(pos);
    Rt->Pos[0] = x;
    Rt->Pos[1] = y;
    Rt->CTYPE = store[x][y];
    for(int i=0;i<8;i++) {
        if((a[i][0]>-1)&&(a[i][0]<Llen)&&(a[i][1]>-1)&&(a[i][1]<Clen)) {
            Rt->Around[i].CType = store[a[i][0]][a[i][1]];
            Rt->Around[i].flag = Judge(Rt->Around[i].CType);
        }
        else{
            Rt->Around[i].CType = '0';
            Rt->Around[i].flag = 0;
        }
    }
    return Rt;
}

//保存行走路径(邻接矩阵)
void save_path(PtrRt Rt_1,PtrRt Rt_2,int Clen) {
    arcs[(Rt_1->Pos[0]*Clen+Rt_1->Pos[1])][Rt_2->Pos[0]*Clen+Rt_2->Pos[1]] = 1;
    arcs[(Rt_2->Pos[0]*Clen+Rt_2->Pos[1])][Rt_1->Pos[0]*Clen+Rt_1->Pos[1]] = 1;
}

//进行机器人行走
PtrRt move(PtrRt Rt,int pos[2],char store[][MaxCNum],int Llen,int Clen) {
    PtrRt temp;
    temp = (PtrRt)malloc(sizeof(struct Robot));
    int i;
    temp->Pos[0] = pos[0];
    temp->Pos[1] = pos[1];
    temp->CTYPE = store[pos[0]][pos[1]];
    int **a;
    a = around(temp->Pos);
    for(i=0;i<8;i++) {
        if((a[i][0]>-1)&&(a[i][0]<Llen)&&(a[i][1]>-1)&&(a[i][1]<Clen)) {
            temp->Around[i].CType = store[a[i][0]][a[i][1]];
            temp->Around[i].flag = Judge(temp->Around[i].CType);
        }
        else{
            temp->Around[i].CType = '0';
            temp->Around[i].flag = 0;
        }
    }
    save_path(Rt,temp,Clen);
    return temp;
}

//使用广度优先搜索(BFS)进行地图遍历。
void BFS(PtrRt Rt,Queue Q,char store[][MaxCNum],char expor[][MaxCNum],int Llen,int Clen) {
    int flag_B[MaxLNum][MaxCNum];
    for(int i=0;i<MaxLNum;i++) {
        for(int j=0;j<MaxCNum;j++) {
            flag_B[i][j] = 0;
        }
    }
    Q = AddQ(Q,Rt);
    int** a;
    int count_s = 0;
    int count_g = 0;
    while(!IsEmpty(Q)) {
        Rt = DeleteQ(Q);
        Record(Rt,Q,expor);
        if(Judge(Rt->CTYPE)==6){
            s_vital[count_s][0] = Rt->Pos[0];
            s_vital[count_s][1] = Rt->Pos[1];
            count_s++;
        }
        if(Judge(Rt->CTYPE)==9){
            goal[count_g][0] = Rt->Pos[0];
            goal[count_g][1] = Rt->Pos[1];
            count_g++;
        }
        a = around(Rt->Pos);
        for(int i=0;i<8;i++) {
            if((a[i][0]>-1)&&(a[i][0]<Llen)&&(a[i][1]>-1)&&(a[i][1]<Clen)&&(Rt->Around[i].flag)&&(!flag_B[a[i][0]][a[i][1]])) {
                flag_B[a[i][0]][a[i][1]] = 1;
                Q = AddQ(Q,move(Rt,a[i],store,Llen,Clen));
            }
        }
    }
}

//查找并输出从u到v的路径
void print_path(int path[],int u, int v,int Clen) {
    int k;
    k = path[v];
    if(k == -1) {
        printf("no path!");
        return;
    }
    printf("(%d,%d)",path[v]/Clen,path[v]%Clen);
    while(k != u) {
        printf(" <- ");
        printf("(%d,%d)",path[k]/Clen,path[k]%Clen);
        k = path[k];
    }
}

//Dijkstra(迪杰斯特拉)算法
void dijkstra(int begin,int nodes[],int Llen,int Clen) {
    int num;
    num = Llen*Clen;
    int temp;
    int min;
    pre[begin] = 0;

    for(int i=0;i<(Llen*Clen);i++) {//初始化dist、visited、pre数组
        visited[i] = 0;
        if(i==begin) {
            dist[i] = 0;
        }
        else if (arcs[begin][i]==1) {
            dist[i] = 1;
            pre[i] = begin;
        }
        else {
            dist[i] = inf;
            pre[i] = -1;
        }
    }
    visited[begin] = 1;
    for(int i=0;i<num;i++) {
        temp = begin;
        min = inf;
        for(int j=0;j<num;j++) {//找到目前尚未访问过的最近的点，并从该点出发向后查找.
            if(!visited[j]&&(dist[j]!=0)&&(dist[j]<min)) {
                min = dist[j];
                temp = j;
            }
        }
        if(temp==begin) continue;
        visited[temp] = 1;
        for(int k=0; k<num; k++)
        {
            if(visited[k] == 0 && arcs[temp][k]==1) {
                if(dist[temp] + arcs[temp][k] < dist[k]){
                    dist[k] = dist[temp] + arcs[temp][k];
                    pre[k] = temp;
                }
            }
        }
    }
}

/*完成行走并记录的综合操作
采取BFS进行遍历.*/
void Nicolas(char store[][MaxCNum],char expor[][MaxCNum],int Llen,int Clen) {
    PtrRt Rt;
    Queue Q;
    Rt = CreateRt(0,0,store,Llen,Clen);
    Q = CreateQueue();
    for(int i=0;i<MaxSize;i++) { //初始化邻接矩阵
        for(int j=0;j<MaxSize;j++) {
            arcs[i][j] = inf; 
        }
    }
    BFS(Rt,Q,store,expor,Llen,Clen);
}