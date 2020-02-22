void test_input(void)
{
	int **put = (int **)calloc(1024, sizeof(int *));
	for (int i = 0; i < 1024; i++) {
		put[i] = (int *)calloc(1024, sizeof(int));
	}

	put[0][0] = 10;
	put[0][0] = 1;
	put[0][0] = 2;
	put[0][0] = 7;
	put[0][0] = 6;
	put[0][0] = 1;
	put[0][0] = 5;
	int intput[] = {10,1,2,7,6,1,5};
	int target = 8;

	int retSize;
	int *retColSize;
	int **ret;
	ret = combinationSum2(intput, 7, target, &retSize, &retColSize);
	for (int i = 0; i < retSize; i++) {
		 for(int j = 0; j < retColSize[i]; j++) {
			printf("ret %d\n", ret[i][j]);
		 }
	}
}

