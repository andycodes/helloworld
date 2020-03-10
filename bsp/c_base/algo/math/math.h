
/*
INT_MAX
INT_MIN

LONG_MIN,
LONG_MAX
*/
#define INT_MAX ((int)(~0U >> 1))
#define INT_MIN (-INT_MAX - 1)

/*fmax fmin*/
#define fmax(a, b) ((a) > (b) ? (a) : (b))
#define fmin(a, b) ((a) < (b) ? (a) : (b))
#define MIN3(a,b,c) ((a)<(b)?((a)<(c)?(a):(c)):((b)<(c)?(b):(c)))

#define swap(a,b) ((a) ^= (b), (b) ^= (a) ,(a) ^= (b))

