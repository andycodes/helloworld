#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>


struct stack_load{
	int row;
	int col;
};

struct stack_blk{
	int count;
	int size;
	struct stack_load load[0];
};


struct stack_blk *create_array_stack(int sz)
{
	struct stack_blk * stack =
		(struct stack_blk  *)malloc(sizeof(struct stack_blk) + sz*sizeof(struct stack_load));
	if (stack == NULL) {
		printf("arr malloc error!");
		return NULL;
	}

	stack->size = sz;
	stack->count = 0;

	return stack;
}


void destroy_array_stack(struct stack_blk * stack)
{
	if (stack != NULL) {
		free(stack);
		stack = NULL;
	}
}


void push(struct stack_blk * stack,struct stack_load load)
{
	stack->load[stack->count++] = load;
	if (stack->count > stack->size) {
		printf("[%s] push count[%d] too big\n", __func__, stack->count);
		stack->count = stack->count % stack->size;
	}
}

// 返回“栈顶元素值”
struct stack_load  peek(struct stack_blk * stack)
{
	return stack->load[stack->count-1];
}

// 返回“栈顶元素值”，并删除“栈顶元素”
struct stack_load  pop(struct stack_blk * stack)
{
	struct stack_load  ret = stack->load[stack->count-1];
	stack->count--;
	return ret;
}

// 返回“栈”的大小
int size(struct stack_blk * stack)
{
	return stack->count;
}

// 返回“栈”是否为空
int is_empty(struct stack_blk * stack)
{
	return size(stack)==0;
}


/*tile see dfs floodFill*/
int** floodFill(int** image, int imageSize, int* imageColSize,
	int sr, int sc,
	int newColor, int* returnSize, int** returnColumnSizes)
{
	*returnSize = imageSize;
	*returnColumnSizes = malloc(sizeof(int) * imageSize);

	for (int i = 0; i < imageSize; i++) {
		(*returnColumnSizes)[i] = imageColSize[i];
	}

	if (newColor == image[sr][sc])
		return image;

	int directions[4][2] = {
		{1,0},
		{-1,0},
		{0,1},
		{0,-1}
	};

	int originalcolor = image[sr][sc];

	struct stack_blk * stack = create_array_stack(50);

	struct stack_load start;
	start.row = sr;
	start.col = sc;

	push(stack,start);

	while(!is_empty(stack)) {
		struct stack_load cur = pop(stack);
		image[cur.row][cur.col] = newColor;

		for(int i = 0; i < 4; i++) {
			int new_i = cur.row + directions[i][0];
			int new_j = cur.col + directions[i][1];
			if ((0 <= new_i) && (new_i < imageSize)  && (0 <= new_j) &&
				(new_j < imageColSize[0]) && image[new_i][new_j] == originalcolor) {
				start.row = new_i;
				start.col = new_j;
				push(stack,start);
			}
		}
	}

	return image;
}



