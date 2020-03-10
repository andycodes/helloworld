#include <stdio.h>
#include <stdlib.h>


#define Error( Str )        FatalError( Str )
#define FatalError( Str )   fprintf( stderr, "%s\n", Str ), exit( 1 )

typedef int ElementType;

struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;


#define MinPQSize (10)
#define MinData (-32767)

struct HeapStruct
{
	int Capacity;
	int Size;
	ElementType *Elements;
};

PriorityQueue Initialize( int MaxElements )
{
	PriorityQueue H;

	if ( MaxElements < MinPQSize )
		Error( "Priority queue size is too small!" );

	H = malloc( sizeof( struct HeapStruct ) );
	if ( H == NULL )
		FatalError( "Out of space!!!" );

	/* Allocate the array plus one extra for sentinel */
	H->Elements = malloc( ( MaxElements + 1 )
		* sizeof( ElementType ) );
	if ( H->Elements == NULL )
		FatalError( "Out of space!!!" );

	H->Capacity = MaxElements;
	H->Size = 0;
	H->Elements[ 0 ] = MinData;

	return H;
}

/* H->Elements[ 0 ] is a sentinel */
void
Insert( ElementType X, PriorityQueue H )
{
	int i;

	if ( IsFull( H ) )
	{
		Error( "Priority queue is full" );
		return ;
	}
	for ( i = ++H->Size; H->Elements[ i / 2 ] > X; i /= 2) /* The new element is percolated up the heap  */
		H->Elements[ i ] = H->Elements[ i / 2 ];           /* until the correct location is found */
	H->Elements[ i ] = X;
}

ElementType
DeleteMin( PriorityQueue H )
{
	int i, Child;
	ElementType MinElement, LastElement;

	if ( IsEmpty( H ) )
	{
		Error( "Priority queue is empty!" );
		return H->Elements[ 0 ];
	}
	MinElement = H->Elements[ 1 ];
	LastElement = H->Elements[ H->Size-- ];

	for ( i = 1; i * 2 <= H->Size; i = Child )
	{
		/* Find smaller child */
		Child = i * 2;
		if ( Child != H->Size && H->Elements[ Child + 1 ]
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
MakeEmpty( PriorityQueue H )
{
	H->Size = 0;
}

ElementType
FindMin( PriorityQueue H )
{
	if( !IsEmpty( H ) )
		return H->Elements[ 1 ];
	Error( "Priority Queue is Empty" );
	return H->Elements[ 0 ];
}

int
IsEmpty( PriorityQueue H )
{
	return H->Size == 0;
}

int
IsFull( PriorityQueue H )
{
	return H->Size == H->Capacity;
}

void
Destroy( PriorityQueue H )
{
	free( H->Elements );
	free( H );
}


int
main()
{
	PriorityQueue H = Initialize( 50 );
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

