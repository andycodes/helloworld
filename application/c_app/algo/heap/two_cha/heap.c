/*
����"��һ��Ԫ��"�������е�����Ϊ 0 �Ļ���
�򸸽ڵ���ӽڵ��λ�ù�ϵ���£�
��� i=0�����Ǹ��ڵ�
��� i>0�����ĸ��ڵ������Ϊ floor����i-1��/  2��
��� 2i + 1 <=  n-1���������ӽڵ������Ϊ 2i + 1
��� 2i + 2 <=  n-1���������ӽڵ������Ϊ 2i + 2
��� 2i + 1 > n-1���������ӽڵ�
��� 2i + 2 > n-1���������ӽڵ�

�����Ա�������Ĳ����������!!!

����ѵĺ�����"��ӽڵ�"��"ɾ���ڵ�"

��KСԪ�� ----���ջ

��Ҷ�ӽ�㶼�Ǵ��ڵ� h �� h - 1�㣨hΪ���ĸ߶ȣ�
*/
/*
����"��һ��Ԫ��"�������е�����Ϊ 0 �Ļ���
�򸸽ڵ���ӽڵ��λ�ù�ϵ���£�
(01) ����Ϊi�����ӵ������� (2*i+1);
(02) ����Ϊi�����ӵ������� (2*i+2);
(03) ����Ϊi�ĸ����������� floor((i-1)/2);

����ѵĺ�����"��ӽڵ�"��"ɾ���ڵ�"

��KСԪ�� ----���ջ
*/

#ifdef PRIORITY_QUEUE_MAX
struct heapEntry {
	int key;
};

struct HeapCtrl{
	int size;
	int cap;
	struct heapEntry node[0];
};

bool heapFull(struct HeapCtrl *hp)
{
	return hp->size == hp->cap;
}

bool heapEmpty(struct HeapCtrl *hp)
{
	return hp->size == 0;
}

int heapSize(struct HeapCtrl *hp)
{
	return hp->size;
}

#ifdef PRIORITY_QUEUE_MAX
void heapPush(struct HeapCtrl *hp, struct heapEntry node)
{
	if(heapFull(hp)) {
		return;
	}

	int cidx = hp->size;
	int fidx  = (cidx - 1) / 2;

	while(cidx > 0) {
		if(hp->node[fidx].key < node.key) {
			hp->node[cidx] = hp->node[fidx];//�³�
			cidx = fidx;
			fidx = (cidx - 1) / 2;
		} else {
			break;
		}
	}

	hp->node[cidx] = node;
	hp->size++;
}

struct heapEntry heapPop(struct HeapCtrl *hp)
{
	if (heapEmpty(hp)) {
		return hp->node[0]; /* err */
	}

	struct heapEntry top;
	top = hp->node[0];

	struct heapEntry cmp = hp->node[--hp->size];
	int fidx  = 0;
	int cidx = 2 * fidx + 1;

	while(cidx < hp->size) {
		if (cidx < hp->size -1 && hp->node[cidx].key < hp->node[cidx + 1].key)
			cidx++; // ������������ѡ��ϴ���

		if (hp->node[cidx].key > cmp.key) {
			hp->node[fidx] = hp->node[cidx];
			fidx = cidx;
			cidx = 2 * fidx + 1;
		} else {
			break;
		}
	}

	hp->node[fidx] = cmp;

	return top;
}

/*
 * ����data�ڶ�����е�����
 *
 * ����ֵ��
 *     ���� -- ����data�������е�����
 *     ������ -- -1
 */
int get_index(struct HeapCtrl *hp, int data)
{
    int i=0;

    for(i=0; i<hp->size; i++)
        if (data==hp->node[i].key)
            return i;

    return -1;
}

/*
 * ���ѵ����µ����㷨
 *
 * ע������ʵ�ֵĶ��У���N���ڵ�����ӵ�����ֵ��(2N+1)���Һ��ӵ�������(2N+2)��
 *
 * ����˵����
 *     start -- ���µ��ڵ����ʼλ��(һ��Ϊ0����ʾ�ӵ�1����ʼ)
 *     end   -- ������Χ(һ��Ϊ���������һ��Ԫ�ص�����)
 */
static void maxheap_filterdown(struct HeapCtrl *hp, int start, int end)
{
    int c = start;          // ��ǰ(current)�ڵ��λ��
    int l = 2*c + 1;     // ��(left)���ӵ�λ��
    struct heapEntry tmp = hp->node[c];    // ��ǰ(current)�ڵ�Ĵ�С

    while(l <= end)
    {
        // "l"�����ӣ�"l+1"���Һ���
        if(l < end && hp->node[l].key < hp->node[l+1].key)
            l++;        // ������������ѡ��ϴ��ߣ���m_heap[l+1]
        if(tmp.key >= hp->node[l].key)
            break;        //��������
        else
        {
            hp->node[c] = hp->node[l];
            c = l;
            l = 2*l + 1;
        }
    }

    hp->node[c] = tmp;
}

/*
 * ɾ�������е�data
 *
 * ����ֵ��
 *      0���ɹ�
 *     -1��ʧ��
 */
int maxheap_remove(struct HeapCtrl *hp, int data)
{
    int index;
    // ���"��"�ѿգ��򷵻�-1
    if(hp->size== 0)
        return -1;

    // ��ȡdata�������е�����
    index = get_index(hp, data);
    if (index==-1)
        return -1;

    hp->node[index] = hp->node[--hp->size];        // �����Ԫ���
    maxheap_filterdown(hp, index, hp->size-1);    // ��indexλ�ÿ�ʼ�������µ���Ϊ����

    return 0;
}

#endif

#ifdef PRIORITY_QUEUE_MIN
void heapPush(struct HeapCtrl *hp, struct heapEntry node)
{
	if(heapFull(hp)) {
		return;
	}

	int cidx = hp->size;
	int fidx = (cidx - 1) / 2;

	while(cidx > 0) {
		if (hp->node[fidx].key > node.key) {
			hp->node[cidx] = hp->node[fidx]; // �³�
			cidx = fidx;
			fidx = (cidx - 1) / 2;
		} else {
			break;
		}
	}

	hp->node[cidx] = node;
	hp->size++;
}

struct heapEntry heapPop(struct HeapCtrl *hp)
{
	struct heapEntry top = hp->node[0];
	if (heapEmpty(hp)) {
		return top; // err
	}

	struct heapEntry cmp =  hp->node[--hp->size];// �����Ԫ���
	int fidx = 0;
	int cidx = 2* fidx + 1;

	while(cidx < hp->size) {
		if(cidx < hp->size -1 && hp->node[cidx].key > hp->node[cidx+1].key)
			cidx++;// ������������ѡ���С�ߣ�

		if(hp->node[cidx].key < cmp.key) {
			hp->node[fidx] = hp->node[cidx];
			fidx = cidx;
			cidx = 2 * fidx + 1;
		} else {
			break;
		}
	}

	hp->node[fidx] = cmp;
	return top;
}
#endif

struct HeapCtrl *heapInit(int cap)
{
	struct HeapCtrl * hp = (struct HeapCtrl *)calloc(1, sizeof(struct HeapCtrl) + sizeof(struct heapEntry) * cap);
	hp->cap = cap;
	return hp;
}
#endif
