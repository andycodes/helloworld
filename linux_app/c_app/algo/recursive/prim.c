/*
1584
*/

/*
Prim�㷨
bfs
*/
int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize)
{
	int res = 0;
	int n = pointsSize;
	bool collected[n];
	int dist[n];    //dist[i]��ʾi�ŵ㵽�㼯����̾���
	int cost[n][n];  //cost[i][j] ��ʾi��j��������ķ���
	memset(collected, 0, sizeof(collected));

	for(int i = 0; i < n; i++) {
		cost[i][i] = 0;
		for(int j = i + 1; j < n; j++)
			cost[i][j] = cost[j][i] = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
	}

	//��0�ŵ㿪ʼ,��ʱ�㼯ֻ��0
	collected[0] = true;
	for(int i = 0; i < n; i++)
		dist[i] = cost[i][0];

	while(1) {
		//find mindist
		int v = -1;
		int mindist = INT_MAX;
		for(int i = 0; i < n; i++) {
			if(collected[i])
				continue;

			if(dist[i] < mindist) {
				mindist = dist[i];
				v = i;
			}
		}

		if(v == -1)
			break;

		res += mindist;

		collected[v] = true;
		dist[v] = 0;

		for(int i = 0; i < n; i++)  //����δ��¼��������¼�㼯����̾���
			if(collected[i] == false && dist[i] > cost[v][i])
				dist[i] = cost[v][i];
	}
	return res;
}
