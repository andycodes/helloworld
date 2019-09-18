#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

/*
ע����˳����á�dp[i]:ȡ����i����Ʒʱ��ܵ���С�߶ȡ�
״̬ת��ʱ�п�ȵ����ơ�
��ô�Ϳ��Դӵ�ǰλ��-1��ǰ������
��ʾ�ڵ�j��λ�ÿ�ʼ����һ�㣬
j��i�ǵ�ǰ�㡣������ʱ��ά��high_max��ʾ��ǰ��ĸ߶ȡ�
ת�ƹ�ʽ : dp[i]=min(dp[i],dp[j-1]+high_max)
*/
int minHeightShelves(int** books, int booksSize, int* booksColSize, int shelf_width){
        int i;
        int dp[1005];
        dp[0]=books[0][1];
        int high_max;

        for(i=1;i<booksSize;i++)
        {
            high_max=books[i][1];
            dp[i]=dp[i-1]+high_max;//sum high
            int w=books[i][0];
            for(int j=i-1;j>=0 && w+books[j][0]<=shelf_width;j--)// width
            {
                high_max=max(high_max,books[j][1]);
                if(j-1<0){
                    dp[i]=high_max;
                }else {
                    dp[i]=min(dp[i],dp[j-1]+high_max);
                }
                w+=books[j][0];
            }
        }

        return dp[booksSize-1];

}
