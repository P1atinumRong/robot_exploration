#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#define MaxLNum 110
#define MaxCNum 110
#define MaxSize 10100
#define inf 10000

extern int arcs[MaxSize][MaxSize];
extern int s_nodes[MaxSize];
extern int g_nodes[MaxSize];
extern int dist[MaxSize];
extern int visited[MaxSize];
extern int pre[MaxSize];
extern int s_path[MaxSize][MaxSize];
extern int goal[MaxSize][2];
extern int s_vital[MaxSize][2];

//定义机器人(结构体)。
struct Robot{
    int Pos[2]; //当前位置
    char CTYPE; //当前的字符类型
    struct ArEle{
        char CType;
        int flag;
    }Around[8];  //周围结点的字符类型及其标记（从North开始，沿顺时针排列）
};
typedef struct QNode* Queue;
typedef struct Robot* PtrRt;
typedef struct Node* PtrToNode;
struct Node{ //队列中的结点
    PtrRt Rt;
    PtrToNode Next;
};

struct QNode {
    PtrToNode Front, Rear;  // 队列的头、尾指针
};

Queue CreateQueue();
Queue AddQ( Queue Q, PtrRt Rt );
int IsEmpty( Queue Q );
PtrRt DeleteQ( Queue Q );
int** around(int pos[2]);
int Judge(char c);
void Record(PtrRt Rt,Queue Q,char expor[][MaxCNum]);
PtrRt CreateRt(int x,int y,char store[][MaxCNum],int Llen,int Clen);
void save_path(PtrRt Rt_1,PtrRt Rt_2,int Clen);
PtrRt move(PtrRt Rt,int pos[2],char store[][MaxCNum],int Llen,int Clen);
void BFS(PtrRt Rt,Queue Q,char store[][MaxCNum],char expor[][MaxCNum],int Llen,int Clen);
void print_path(int path[],int u, int v,int Clen);
void dijkstra(int begin,int nodes[],int Llen,int Clen);
void Nicolas(char store[][MaxCNum],char expor[][MaxCNum],int Llen,int Clen);


#endif // FUNC_H_INCLUDED