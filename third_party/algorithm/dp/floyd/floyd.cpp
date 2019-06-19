 #include <iostream>
 using namespace std;

 const int INF = 100000;
 int n=10,path[11][11],dist[11][11],map[11][11];

 void init(void)
 {
	int i,j;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
		map[i][j]=(i==j)?0:INF;

	map[1][2]=2,map[1][4]=20,map[2][5]=1;
	map[3][1]=3,map[4][3]=8,map[4][6]=6;
	map[4][7]=4,map[5][3]=7,map[5][8]=3;
	map[6][3]=1,map[7][8]=1,map[8][6]=2;
	map[8][10]=2,map[9][7]=2,map[10][9]=1;

	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++) {
			cout<<map[i][j]<<"        ";
			if (j== n) cout<<endl;
		}
 }

 void floyd(){
     int i,j,k;
     for(i=1;i<=n;i++)
         for(j=1;j<=n;j++)
             dist[i][j]=map[i][j],path[i][j]=0;
     for(k=1;k<=n;k++)
         for(i=1;i<=n;i++)
             for(j=1;j<=n;j++)
                 if(dist[i][k]+dist[k][j]<dist[i][j])
                     dist[i][j]=dist[i][k]+dist[k][j],path[i][j]=k;
 }
 void output(int i,int j){
     if(i==j) return;
     if(path[i][j]==0) cout<<j<<' ';
     else{
         output(i,path[i][j]);
         output(path[i][j],j);
     }
 }
 int main(){
     int u,v;
     init();
     floyd();
     while(cin>>u>>v,u||v){
         if(dist[u][v]==INF) cout<<"No path"<<endl;
         else{
             cout<<u<<' ';
             output(u,v);
             cout<<endl;
         }
     }
     return 0;
 }