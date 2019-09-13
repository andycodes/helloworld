/** ����Ԫ�ص�����*/
typedef int elem_t;
/**
* @brief ����˳�����۰�����㷨.
**
@param[in] a �������Ԫ�ص����飬���ź���
* @param[in] n �����Ԫ�ظ���
* @param[in] x Ҫ���ҵ�Ԫ��
* @return ����ҵ�x���򷵻����±ꡣ�����
* ����x ��x С��array �е�һ������Ԫ�أ���Ϊһ���������ø����Ǵ�
* ��x �ĵ�һ��Ԫ�ص������İ�λ�󲹡�����Ҳ���x ��x ����array �е�
* �κ�Ԫ�أ���Ϊһ���������ø����ǣ����һ��Ԫ�ص�������1���İ�λ�󲹡�
*/
int binary_search(const elem_t a[], const int n, const elem_t x) {
    int left = 0, right = n -1, mid;
    while(left <= right) {
        mid = left + (right - left) / 2;
        if(x > a[mid]) {
            left = mid + 1;
        } else if(x < a[mid]) {
            right = mid - 1;
        } else {
            return mid;
        }
    }
    return -(left+1);
}