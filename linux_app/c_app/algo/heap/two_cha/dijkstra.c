/*
 可以使用HEAP 进行优化
*/

/*
743. 网络延迟时间
有 N 个网络节点，标记为 1 到 N。

给定一个列表 times，表示信号经过有向边的传递时间。 times[i] = (u, v, w)，其中 u 是源节点，v 是目标节点， w 是一个信号从源节点传递到目标节点的时间。

现在，我们从某个节点 K 发出一个信号。需要多久才能使所有节点都收到信号？如果不能使所有节点收到信号，返回 -1。



示例：



输入：times = [[2,1,1],[2,3,1],[3,4,1]], N = 4, K = 2
输出：2
*/
#define MAX_NODE_LEN 101
#define MAXVALUE 65535

int g_matirxGrap[MAX_NODE_LEN][MAX_NODE_LEN];

int Dijkstra(int **times, int timesSize, int vs, int N)
{
	int i, j, k;
	int flag[MAX_NODE_LEN];
	int dist[MAX_NODE_LEN];

	for (i = 1; i <= N; i++) {
		dist[i] = MAXVALUE;
		flag[i] = 0;
	}

	flag[vs] = 1;
	dist[vs] = 0;

    for (i = 1; i <= N; i++) {
        if (g_matirxGrap[vs][i] != MAXVALUE) {
            dist[i] = g_matirxGrap[vs][i];
        }
    }

	for (i = 1; i <= N; i++) {
		int min = MAXVALUE;
		for (j = 1; j <= N; j++) {
			if (flag[j] == 0 && dist[j] < min) {
				min = dist[j];
				k = j;
			}
		}

		flag[k] = 1;
		for (int j = 1; j <= N; j++) {
			int tmp = (g_matirxGrap[k][j] == MAXVALUE ? MAXVALUE : (min + g_matirxGrap[k][j]));
			if (flag[j] == 0 && tmp < dist[j]) {
				dist[j] = tmp;
			}
		}
	}

	int maxVal = -1;
	for (i = 1; i <= N; i++) {
		if (flag[i] == 0){
			return -1;
		}
		else {
			maxVal = maxVal < dist[i] ? dist[i] : maxVal;
		}
	}
	return maxVal;
}

int networkDelayTime(int **times, int timesSize, int* timesColSize, int N, int K){
	if (times == NULL || timesSize <= 0 || *timesColSize <= 0) {
		return 0;
	}

	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			g_matirxGrap[i][j] = MAXVALUE;
		}
	}

	for (int k = 0; k < timesSize; k++) {
		int i = times[k][0];
		int j = times[k][1];
		g_matirxGrap[i][j] = times[k][2];
	}

	return Dijkstra(times, timesSize, K, N);
}



