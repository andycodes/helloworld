#include <stdio.h>
#include <string.h>

int w,h, last_x, last_y;
char str[100][100], map[300][300];
int dir[8][2]={{1,0}, {-1,0}, {0,1},{0,-1}, // ��һ�����������ҷ�����
               {-1,1},{1,1},{1,-1},{-1,-1}}; // ��һ����б�ķ����ߣ������Ͽ�ʼ��˳ʱ��

bool vis[300][300];

// ���������ת��
void change(int row){
    for(int i=0; i<strlen(str[row]); ++i){
        int m_row=row*2, m_col=i*2;
        if(str[row][i] == '\\' ){
            map[m_row][m_col] = '\\';
            map[m_row+1][m_col+1] = '\\';
            map[m_row][m_col+1] = ' ';
            map[m_row+1][m_col] = ' ';
        }
        else if(str[row][i] == '/'){
            map[m_row][m_col+1] = '/';
            map[m_row+1][m_col] = '/';
            map[m_row][m_col] = ' ';
            map[m_row+1][m_col+1] = ' ';
        }
    }
}

// �����б���ߣ���Ҫ���������ܷ���
bool isPass(int x, int y, int dirNo){
    int x1,y1,x2,y2;  // x1Ϊͬrow, x2Ϊͬcol
    x1 = x, y1=y+dir[dirNo][1];
    x2 = x+dir[dirNo][0], y2=y;

    if(dirNo==4 || dirNo==6){
        if(map[x1][y1]=='/' && map[x2][y2]=='/')
            return true;
    }
    else{
        if(map[x1][y1]=='\\' && map[x2][y2]=='\\')
            return true;
    }
    return false;
}


void dfs(int x,int y,int &cnt){
    for(int i=0; i<8; ++i){
        int dx=x+dir[i][0], dy=y+dir[i][1];
        if(i<4) { // ��������ϣ��£�������
            if(dx>=0 && dx<2*h && dy>=0 && dy<2*w && map[dx][dy]!='\\'&&map[dx][dy]==' ' && map[dx][dy]!='/' && !vis[dx][dy]){
                vis[dx][dy] = true;
                last_x = dx, last_y = dy;  // ��ס���һ����ջ��λ��
                ++cnt;
                dfs(dx,dy,cnt);
            }
        }
        else{ // �������б�ķ�����
            if(dx<0 || dx>=2*h || dy<0 || dy>=2*w || map[dx][dy]=='\\' || map[dx][dy]=='/' || vis[dx][dy])
                continue;
            if(isPass(x,y,i)){
                vis[dx][dy] = true;
                ++cnt;
                last_x = dx, last_y = dy;
                dfs(dx, dy, cnt);
            }
        }
    }
}

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
   int cas=1;
   while(~scanf("%d %d%*c",&w, &h) && w && h){
       memset(str, 0, sizeof(str));
       memset(map, 0, sizeof(map));
       memset(vis, 0, sizeof(vis));
       for(int i=0; i<h; ++i){
		scanf("%s",str[i]);
           change(i);
       }
       int maxNum=-2147483646, cnt, circleNum=0;
       bool haveCircle = false;

       for(int i=0; i<2*h; ++i){
           for(int j=0; j<2*w; ++j){
               if(map[i][j]==' ' && !vis[i][j]){
                   map[i][j] = '#';
                   cnt=1;
                   vis[i][j] = true;
                   dfs(i,j,cnt);
                   // �ж��Ƿ��ǻ��ģ�����Ҫ�жϽ������ǵ��Ƿ�Ϳ�ʼ������
                   bool flag = false;
                   for(int k=0; k<8; ++k){
                       int dx=last_x+dir[k][0];
                        int dy=last_y+dir[k][1];
                        if(dx==i && dy==j){
                            flag=true; break;
                        }
                    }
                    // ���ڵĻ�����������������4�����γɻ�״
                    if(flag && cnt>=4){
                        haveCircle = true;
                        ++circleNum;
                        if(cnt > maxNum)
                            maxNum = cnt;
                    }
                }

            }
        }
        printf("Maze #%d:\n",cas++);

        if(haveCircle){
            printf("%d Cycles; the longest has length %d.\n\n", circleNum, maxNum);
        }
        else{
            printf("There are no cycles.\n\n");
        }
    }
    return 0;
}
