void dfs(int** M, int MColSize, int* visited, int i) {
        for (int j = 0; j < MColSize; j++) {
            if (M[i][j] == 1 && visited[j] == 0) {
                visited[j] = 1;
                dfs(M, MColSize,visited, j);
            }
        }
}

int findCircleNum(int** M, int MSize, int* MColSize){

	int *visited = malloc(MSize * sizeof(visited));
	int count = 0;
	memset((void*)visited,0,MSize * sizeof(visited));
	for (int i = 0; i < MSize; i++){
		if(visited[i] == 0){
			dfs(M,MColSize[i],visited,i);
			count++;
		}
	}

	return count;
}
