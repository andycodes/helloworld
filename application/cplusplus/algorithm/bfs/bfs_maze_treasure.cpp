/*
http://acm.fzu.edu.cn/problem.php?pid=2285
*/

#include<stdio.h>
#include<iostream>
#include<string.h>
#include<queue>
using namespace std;


char a[1010][1010];//��¼����ͼ�ε�
int vis[1010][1010];//������ǵ���û�߹�

struct Point{
	int x, y;
}tmp1, tmp2;

int mt[4][2] = {1,0,-1,0,0,1,0,-1};//�ƶ����ĸ�����

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
			vis[i][j] = 0;//��ʼ�����
			if(a[i][j] == 'S'){//�ҵ���ʼλ��
			sx = i;
			sy = j;
			}
			else if(a[i][j] == 'E'){//�յ�λ��
				ex = i;
				ey = j;
			}
		}
	}

         while(!q.empty()){//���г�ʼ��
             q.pop();/*����ͷ�����ݳ���*/
         }

         tmp1.x = sx;
         tmp1.y = sy;
         vis[tmp1.x][tmp1.y] = 1;//����ѹ����ʼλ��
         q.push(tmp1);

         int flag = 0;
         while(!q.empty()){
		tmp1 = q.front();/*���ض���ͷ������*/
		q.pop();
		for(i = 0; i < 4; i++){
			tmp2.x = tmp1.x + mt[i][0];//�����ķ���
			tmp2.y = tmp1.y + mt[i][1];
			if(tmp2.x >=0 && tmp2.x < n && tmp2.y >= 0 && tmp2.y < n && !vis[tmp2.x][tmp2.y] && a[tmp2.x][tmp2.y] != '#'){
				//�ж�����
				vis[tmp2.x][tmp2.y] = vis[tmp1.x][tmp1.y] + 1;//ԭ����λ�ü�һ
				q.push(tmp2);
			}
		}

		if(vis[ex][ey]){//��������յ�ͱ��һ�£���ʾ�ܵ����յ�
			flag = 1;
			break;
		}
         }

         if(flag) {
		 	printf("%d\n", vis[ex][ey]-1);//�յ�λ��Ҳ�������ڣ����Լ�1
         }else {
         	printf("-1\n");
	 }
    }

	return 0;
}