/*
http://acm.fzu.edu.cn/problem.php?pid=2285
*/

#include<stdio.h>
#include<iostream>
#include<string.h>
#include<queue>
using namespace std;


char a[1010][1010];//记录整个图形的
int vis[1010][1010];//用来标记的走没走过

struct Point{
	int x, y;
}tmp1, tmp2;

int mt[4][2] = {1,0,-1,0,0,1,0,-1};//移动的四个方向

queue<Point>q;

int main(){
    int n, i, j;
    while(~scanf("%d", &n)){
	for(i = 0; i < n; i++){
		scanf("%s", a[i]);
		printf("%s\n",a[i]);
	}

	int sx, sy;/*find S point*/
	int ex, ey;/*find E point*/
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			vis[i][j] = 0;//初始化标记
			if(a[i][j] == 'S'){//找到初始位置
			sx = i;
			sy = j;
			}
			else if(a[i][j] == 'E'){//终点位置
				ex = i;
				ey = j;
			}
		}
	}

         while(!q.empty()){//队列初始化
             q.pop();/*队列头部数据出队*/
         }

         tmp1.x = sx;
         tmp1.y = sy;
         vis[tmp1.x][tmp1.y] = 1;//首先压入起始位置
         q.push(tmp1);

         int flag = 0;
         while(!q.empty()){
		tmp1 = q.front();/*返回队列头部数据*/
		q.pop();
		for(i = 0; i < 4; i++){
			tmp2.x = tmp1.x + mt[i][0];//引动的方向
			tmp2.y = tmp1.y + mt[i][1];
			if(tmp2.x >=0 && tmp2.x < n && tmp2.y >= 0 && tmp2.y < n && !vis[tmp2.x][tmp2.y] && a[tmp2.x][tmp2.y] != '#'){
				//判断条件
				vis[tmp2.x][tmp2.y] = vis[tmp1.x][tmp1.y] + 1;//原来的位置加一
				q.push(tmp2);
			}
		}

		if(vis[ex][ey]){//如果到达终点就标记一下，表示能到达终点
			flag = 1;
			break;
		}
         }

         if(flag) {
		 	printf("%d\n", vis[ex][ey]-1);//终点位置也包括在内，所以减1
         }else {
         	printf("-1\n");
	 }
    }

	return 0;
}