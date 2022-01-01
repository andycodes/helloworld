#define SET_BIT(x,n)    (x | 1U<<(n-1))
#define CLEAR_BIT(x,n)    (x & ~(1U<<(n-1)))
#define SET_BITS(x,n,m)    (x | ~(~0U<<(m-n+1))<<(n-1))
#define GET_BIT(x,n,m)    (x & ~(~0U<<(m-n+1))<<(n-1)) >>(n-1)