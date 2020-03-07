

#define mkstr(str)		#        str

#define create_1m(s) 	s##1m


// ��ýṹ��(TYPE)�ı�����Ա(MEMBER)�ڴ˽ṹ���е�ƫ������
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)



/*
����"�ṹ��(type)����"�е�"���Ա����(member)��ָ��(ptr)"��
��ȡָ�������ṹ�������ָ��
*/
#define container_of(ptr, type, member) ({          \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})


/*����ȡ��*/
/*#define roundup(x, y)		((((x) + ((y) - 1)) / (y)) * (y))*/
#define roundup(x, y) (					\
{							\
	const typeof(y) __y = y;			\
	(((x) + (__y - 1)) / __y) * __y;		\
}							\
)

/*����ȡ��*/
#define rounddown(x, y) (				\
{							\
	typeof(x) __x = (x);				\
	__x - (__x % (y));				\
}							\
)


