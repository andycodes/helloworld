#include<iostream>
#include<cstring>
#define M 30010
#define N 30
using namespace std;

int d[M],a[N],b[N];

int max(int x,int y)
{
    return x>y?x:y;
}

int main()
{
    int test,m,n,i,j;
    cin>>test;
    while(test--)
    {
        cin>>m>>n;
        for(i=1;i<=n;i++) cin>>a[i]>>b[i];
        memset(d,0,sizeof(d));
        for(i=1;i<=n;i++)
        {
            for(j=m;j>=a[i];j--)
            {
                d[j]=max(d[j],d[j-a[i]]+a[i]*b[i]);
            }
        }
        cout<<d[m]<<endl;
    }
    return 0;
}
