#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int w,h;
int flag;
int cnt,num,max;
int vis[255][255];
int a[255][255];
char s[80][80];

void init()
{
    memset(vis,0,sizeof(vis));
    memset(a,0,sizeof(a));
    cnt=num=max=0;
}

void transform_()
{
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            if(s[i][j]=='/')
            {
                a[(i+1)*3-0][(j+1)*3-2]=1;
                a[(i+1)*3-1][(j+1)*3-1]=1;
                a[(i+1)*3-2][(j+1)*3-0]=1;
            }
            else
            {
                a[(i+1)*3-2][(j+1)*3-2]=1;
                a[(i+1)*3-1][(j+1)*3-1]=1;
                a[(i+1)*3-0][(j+1)*3-0]=1;
            }
        }
    }
    for(int i=0;i<=h*3+1;i++)
    {
        a[i][0]=2;
        a[i][w*3+1]=2;
    }
    for(int i=0;i<=w*3+1;i++)
    {
        a[0][i]=2;
        a[h*3+1][i]=2;
    }
    for(int i=0;i<=3*h+1;i++)
    {
        for(int j=0;j<=3*w+1;j++)
            printf("%d",a[i][j]);
        printf("\n");
    }
}

void dfs(int x,int y)
{
	if(a[x][y]==2){
		flag=0;
		return;
	}

	if(vis[x][y]||a[x][y]==1)
		{return;}

	vis[x][y]=1;
	num++;

	dfs(x-1,y);
	dfs(x,y-1);
	dfs(x,y+1);
	dfs(x+1,y);
}

int main()
{
   while(scanf("%d%d",&w,&h)!=EOF) {
       if(w==0&&h==0)
           break;
       init();
       for(int i=0;i<h;i++)
		scanf("%s",s[i]);

       for(int i=0;i<h;i++)
		printf("%s\n",s[i]);
       transform_();
       int flag1=0;
       for(int i=1;i<=h*3;i++) {
           for(int j=1;j<=w*3;j++) {
               flag=1;num=0;
               if(!vis[i][j]&&!a[i][j]) {
                   dfs(i,j);
                   if(flag) {//result
                       cnt++;
                       flag1=1;
                       if(max<num)
                           max=num;
                   }
               }
            }
        }

        if(flag1)
            printf("%d Cycles; the longest has length %d.\n",cnt,max/3);
	else
            printf("There are no cycles.\n");
        printf("\n");
    }
    return 0;
}

