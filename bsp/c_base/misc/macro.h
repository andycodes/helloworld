

#define mkstr(str)		#        str

#define create_1m(s) 	s##1m


// 获得结构体(TYPE)的变量成员(MEMBER)在此结构体中的偏移量。
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)



/*
根据"结构体(type)变量"中的"域成员变量(member)的指针(ptr)"来
获取指向整个结构体变量的指针
*/
#define container_of(ptr, type, member) ({          \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})


/*向上取整*/
/*#define roundup(x, y)		((((x) + ((y) - 1)) / (y)) * (y))*/
#define roundup(x, y) (					\
{							\
	const typeof(y) __y = y;			\
	(((x) + (__y - 1)) / __y) * __y;		\
}							\
)

/*向下取整*/
#define rounddown(x, y) (				\
{							\
	typeof(x) __x = (x);				\
	__x - (__x % (y));				\
}							\
)


