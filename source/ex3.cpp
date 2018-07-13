// ex3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int front =1, rear =0;
int queue[1001];
int back[1001] = {-1};
bool Free[300];
int a[100][100]={0};
int n,m,u,v;
int Max;

void push(int i){
	queue[++rear] = i;
}
int pop(){
	return queue[front++];
}
bool isEmpty(){
	return front > rear;
}
void findPath(int u, int v, int back[]){
    if (u == v)
        printf("%d ",v);
    else if (back[v] == -1)
        printf("Can't find path");
    else {
        findPath(u,back[v],back);
        printf("%d ",v);
    }

}
void BFS(int k){
	push(k);
	Free[k] = false;
	while (!isEmpty())
     {
        int j = pop();

        //printf("\t%d\n",j);

        for (int i=1; i<=Max; i++)
            if (Free[i] && a[j][i]==1)
            {
                Free[i] = false;
                back[i] = j;
                if (i==v) break;
                push(i);
				//if (i == v) break;
            }
     }
     findPath(u,v,back);
}
int max(int a, int b){
    return a > b ? a : b;
}
int _tmain()
{
    int i,j;
	int l,r;

	scanf("%d %d %d %d",&n,&m,&u,&v);
	for (i =0; i< m; i++){
		scanf("%d %d",&l,&r);
		Max = max (Max,max(l,r));
		a[l][r] = 1;
	}

    for (i =0; i< Max; i++){
        Free[i+1] = true;
    }
    BFS(u);
 return 0;
}

