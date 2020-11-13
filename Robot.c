#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"rt.h"

int main() {
    char store[MaxLNum][MaxCNum] = {0};   //建立存储区并初始化
    FILE *fp = fopen("map.txt","r");
    int Clen;             /*行字符个数*/
    int Llen = 0;
    int i,j;

    if(fp==NULL) {
        printf("Can't find the file!");
        exit(0);
    }
    for(i=0;i<MaxLNum;i++) {
        if(!feof(fp)) {
            fgets(store[i],MaxLNum,fp);
            Llen++;
        }
        else break;
    }
    Llen = Llen;
    Clen = strlen(store[0])-1;
    fclose(fp);

    char expor[MaxLNum][MaxCNum];
    for(i=0;i<Llen;i++){
        for(j=0;j<Clen;j++) {
            expor[i][j] = ' ';
        }
    }   //建立存储区并初始化
    Nicolas(store,expor,Llen,Clen); //调用函数使机器人开始探险

    FILE *fpw = fopen("record_data.txt","w+");
    for(i=0;i<Llen;i++) {
        for(j=0;j<Clen;j++) {
            fprintf(fpw,"%c",expor[i][j]);
            printf("%c",expor[i][j]);
        }
        fprintf(fpw,"\n");
        printf("\n");
    }
    fclose(fpw);
    int goal_num = 0,s_num = 0;
    for(int k=0;k<MaxSize;k++)
        if(goal[k][0]&&goal[k][1]) goal_num++;
    for(int k=0;k<MaxSize;k++)
        if(s_vital[k][0]&&s_vital[k][1]) s_num++;
    printf("The number of goal points and special points are %d,%d.\n",goal_num,s_num);

    for(int i=0;i<goal_num;i++) g_nodes[i] = goal[i][0]*Clen+goal[i][1];
    for(int i=0;i<s_num;i++) s_nodes[i] = s_vital[i][0]*Clen+s_vital[i][1];
    dijkstra(0,g_nodes,Llen,Clen);
    for(int i=0;i<goal_num;i++){
        print_path(pre,0,goal[i][0]*Clen+goal[i][1],Clen);
        printf("\n");
    }


    return 0;
}

