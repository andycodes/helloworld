/*
1584
*/

//Prim�㷨

int res;

int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize){
    res = 0;
    int n = pointsSize;
    bool collected[n];
    int dist[n];    //dist[i]��ʾi�ŵ㵽�㼯����̾���
    int fee[n][n];  //fee[i][j] ��ʾi��j��������ķ���
    memset(collected, 0, sizeof(collected));

    for(int i = 0; i < n; i++){
        fee[i][i] = 0;
        for(int j = i + 1; j < n; j++)
            fee[i][j] = fee[j][i] = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
        }
    //��0�ŵ㿪ʼ,��ʱ�㼯ֻ��0
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
        for(int i = 0; i < n; i++)  //����δ��¼��������¼�㼯����̾���
            if(!collected[i] && dist[i] > fee[v][i])
                dist[i] = fee[v][i];
        }
    return res;
}

