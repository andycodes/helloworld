#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

/*
注意是顺序放置。dp[i]:取到第i个物品时书架的最小高度。
状态转移时有宽度的限制。
那么就可以从当前位置-1向前遍历，
表示在第j个位置开始了新一层，
j到i是当前层。遍历的时候维护high_max表示当前层的高度。
转移公式 : dp[i]=min(dp[i],dp[j-1]+high_max)
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
