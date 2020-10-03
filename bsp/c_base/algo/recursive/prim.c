/*
1584
*/

//Prim算法

int res;

int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize){
    res = 0;
    int n = pointsSize;
    bool collected[n];
    int dist[n];    //dist[i]表示i号点到点集的最短距离
    int fee[n][n];  //fee[i][j] 表示i、j连接所需的费用
    memset(collected, 0, sizeof(collected));

    for(int i = 0; i < n; i++){
        fee[i][i] = 0;
        for(int j = i + 1; j < n; j++)
            fee[i][j] = fee[j][i] = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
        }
    //从0号点开始,此时点集只有0
    collected[0] = true;
    for(int i = 0; i < n; i++) dist[i] = fee[i][0];

    while(1){
        int v = -1;
        int mindist = INT_MAX;
        for(int i = 0; i < n; i++){
            if(collected[i]) continue;
            if(dist[i] < mindist){
                mindist = dist[i];
                v = i;
                }
            }
        if(v == -1) break;
        res += mindist;
        collected[v] = true;
        dist[v] = 0;
        for(int i = 0; i < n; i++)  //更新未收录顶点与收录点集的最短距离
            if(!collected[i] && dist[i] > fee[v][i])
                dist[i] = fee[v][i];
        }
    return res;
}

