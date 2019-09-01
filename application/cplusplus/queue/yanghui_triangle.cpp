#include <queue>
/**
* @brief 打印杨辉三角系数.
**
分行打印二项式(a+b)^n 展开式的系数。在输出上一行
* 系数的同时，将其下一行的系数预先计算好，放入队列中。
* 在各行系数之间插入一个0。
**
@param[in] n (a+b)^n
* @return 无
*/
void yanghui_triangle(const int n) {
queue<int> q;
/* 预先放入第一行的1 */
q.push(1);
for(int i = 0; i <= n; i++) { /* 逐行处理*/
int s = 0;
q.push(s); /* 在各行间插入一个0*/
/* 处理第i 行的i+2 个系数（包括一个0）*/
for(int j = 0; j < i+2; j++) {
int t;
int tmp;
t = q.front(); /* 读取一个系数，放入t*/
q.pop();
tmp = s + t; /* 计算下一行系数，并进队列*/
q.push(tmp);
s = t; /* 打印一个系数，第i+2 个是0*/
if(j != i+1) {
printf("%d ",s);
}
}
printf("\n");
}
}