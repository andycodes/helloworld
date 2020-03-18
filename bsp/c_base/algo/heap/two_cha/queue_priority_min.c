#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INT_MAX ((int)(~0U >> 1))
#define INT_MIN (-INT_MAX - 1)

typedef int ElementType;

struct PriorityQueue
{
	int capacity;
	int size;
	ElementType Elements[0];
};

#if 0
struct PriorityQueue * pqueue_init(int MaxElements)
{
	struct PriorityQueue * H;

	H = malloc( sizeof( struct PriorityQueue ) );
	if ( H == NULL )
		printf( "Out of space!!!" );

	/* Allocate the array plus one extra for sentinel */
	H->Elements = malloc( ( MaxElements + 1 )
		* sizeof( ElementType ) );
	if ( H->Elements == NULL )
		printf( "Out of space!!!" );

	H->capacity = MaxElements;
	H->size = 0;
	H->Elements[ 0 ] = INT_MIN;

	return H;
}
#endif

struct PriorityQueue * pqueue_init(int MaxElements)
{
	struct PriorityQueue * H;

	/* Allocate the array plus one extra for sentinel */
	H = malloc(sizeof(struct PriorityQueue) + (MaxElements + 1)* sizeof( ElementType ));
	if ( H == NULL )
		printf( "Out of space!!!" );

	H->capacity = MaxElements;
	H->size = 0;
	H->Elements[0] = INT_MIN;

	return H;
}


int IsFull( struct PriorityQueue * H )
{
	return H->size == H->capacity;
}


int
IsEmpty( struct PriorityQueue * H )
{
	return H->size == 0;
}


/* H->Elements[ 0 ] is a sentinel */
void
Insert( ElementType X, struct PriorityQueue * H )
{
	int i;

	if ( IsFull( H ) )
	{
		printf( "Priority queue is full" );
		return ;
	}
	for ( i = ++H->size; H->Elements[ i / 2 ] > X; i /= 2) /* The new element is percolated up the heap  */
		H->Elements[ i ] = H->Elements[ i / 2 ];           /* until the correct location is found */
	H->Elements[ i ] = X;
}

ElementType
DeleteMin( struct PriorityQueue * H )
{
	int i, Child;
	ElementType MinElement, LastElement;

	if ( IsEmpty( H ) )
	{
		printf( "Priority queue is empty!" );
		return H->Elements[ 0 ];
	}
	MinElement = H->Elements[ 1 ];
	LastElement = H->Elements[ H->size-- ];

	for ( i = 1; i * 2 <= H->size; i = Child )
	{
		/* Find smaller child */
		Child = i * 2;
		if ( Child != H->size && H->Elements[ Child + 1 ]
								<H->Elements[ Child ] )
			Child++;

		/* Percolate one level */
		if ( LastElement > H->Elements[ Child ] )
			H->Elements[ i ] = H->Elements[ Child ];
		else
			break;
	}
	H->Elements[ i ] = LastElement;
	return MinElement;
}

void
MakeEmpty( struct PriorityQueue * H )
{
	H->size = 0;
}

ElementType
FindMin( struct PriorityQueue * H )
{
	if( !IsEmpty( H ) )
		return H->Elements[ 1 ];
	printf( "Priority Queue is Empty" );
	return H->Elements[ 0 ];
}


void
Destroy( struct PriorityQueue * H )
{
	free( H->Elements );
	free( H );
}


int
main()
{
	struct PriorityQueue * H = pqueue_init( 50 );
	int ar[] = { 32, 21, 16, 24, 31, 19, 68, 65, 26, 13 };
	int i;
	for ( i = 0; i < 10; i++ )
		Insert( ar[i], H );
	for ( i = 0; i < 10; i++ )
	{
		printf( "%d\n", DeleteMin( H ) );

	}
	return 0;
}

