/*
��һ���ַ��� s ��һ���ַ����б� dict ������Ҫ�����ַ����б��г��ֹ��� s ���Ӵ���ӼӴֱպϱ�ǩ <b> �� </b> ����������Ӵ����ص����֣�����Ҫ������һ����һ���պϱ�ǩ��Χ������ͬ������������ַ����������Ӵ֣���ô��Ҳ��Ҫ�����Ǻ�������һ���Ӵֱ�ǩ��Χ��

���� 1��

���룺
s = "abcxyz123"
dict = ["abc","123"]
�����
"<b>abc</b>xyz<b>123</b>"


���� 2��

���룺
s = "aaabbcc"
dict = ["aaa","aab","bc"]
�����
"<b>aaabbc</b>c"

*/

char * addBoldTag(char * s, char ** dict, int dictSize){
char *bmap = NULL;
char *output = NULL;
char *outputcur = NULL;
char *inputcur = NULL;
int offset,i,inputLen;

//1 output� 1000/2 * 7
output = (char *)malloc(3600);
memset(output,0,3600);

//�ڴ���ǰ���Ԥ��1λ������1000+2
bmap = (char *)malloc(1002);
memset(bmap,0,1002);

//2.1 ���ÿ���ؼ��֣����input��ƥ�䵽���Ӵ���ע:bmap��1��ʼ��¼
for (i = 0; i < dictSize; i++) {
    inputcur = strstr(s, dict[i]);
    while (inputcur != NULL) {
        offset = inputcur - s;
        memset(bmap + offset + 1, 1, strlen(dict[i]));
        inputcur = strstr(inputcur + 1, dict[i]);
    }
}

//2.2 �������Ϊ1���Ӵ�Ϊ�ؼ��ָ�����ϣ�N��Keyword�ĺϲ���ȥ�أ�,��һ������ǳ��ؼ�
//2.2 ��Ա߽�0->1 (��ʼ) ��1->0�������� ������
inputLen = strlen(s);
inputcur  = s;
outputcur = output;
for (i=1;i<=inputLen+1;i++){
	//2.2.1 bmap[i] == 1
	if (bmap[i] == 1){
		//0->1
		if (bmap[i-1] == 0){
		    // ����<b>
            		strcpy(outputcur,"<b>");
			outputcur +=strlen("<b>");
		}
        	*(outputcur++) = *(inputcur++);
		continue;
	}
	//2.2.2 bmap[i] == 0
    	//1->0
	if (bmap[i-1] == 1){
		// ����</b>
        strcpy(outputcur,"</b>");
		outputcur +=strlen("</b>");
	}
    *(outputcur++) = *(inputcur++);
}
// 3 output
return output;
}

