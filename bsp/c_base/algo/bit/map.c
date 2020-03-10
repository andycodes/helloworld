/*
给一个字符串 s 和一个字符串列表 dict ，你需要将在字符串列表中出现过的 s 的子串添加加粗闭合标签 <b> 和 </b> 。如果两个子串有重叠部分，你需要把它们一起用一个闭合标签包围起来。同理，如果两个子字符串连续被加粗，那么你也需要把它们合起来用一个加粗标签包围。

样例 1：

输入：
s = "abcxyz123"
dict = ["abc","123"]
输出：
"<b>abc</b>xyz<b>123</b>"


样例 2：

输入：
s = "aaabbcc"
dict = ["aaa","aab","bc"]
输出：
"<b>aaabbc</b>c"

*/

char * addBoldTag(char * s, char ** dict, int dictSize){
char *bmap = NULL;
char *output = NULL;
char *outputcur = NULL;
char *inputcur = NULL;
int offset,i,inputLen;

//1 output最长 1000/2 * 7
output = (char *)malloc(3600);
memset(output,0,3600);

//在串的前后各预留1位，长度1000+2
bmap = (char *)malloc(1002);
memset(bmap,0,1002);

//2.1 针对每个关键字，标记input中匹配到的子串，注:bmap从1开始记录
for (i = 0; i < dictSize; i++) {
    inputcur = strstr(s, dict[i]);
    while (inputcur != NULL) {
        offset = inputcur - s;
        memset(bmap + offset + 1, 1, strlen(dict[i]));
        inputcur = strstr(inputcur + 1, dict[i]);
    }
}

//2.2 连续标记为1的子串为关键字各种组合（N个Keyword的合并或去重）,这一步抽象非常关键
//2.2 针对边界0->1 (起始) 或1->0（结束） 插入标记
inputLen = strlen(s);
inputcur  = s;
outputcur = output;
for (i=1;i<=inputLen+1;i++){
	//2.2.1 bmap[i] == 1
	if (bmap[i] == 1){
		//0->1
		if (bmap[i-1] == 0){
		    // 插入<b>
            		strcpy(outputcur,"<b>");
			outputcur +=strlen("<b>");
		}
        	*(outputcur++) = *(inputcur++);
		continue;
	}
	//2.2.2 bmap[i] == 0
    	//1->0
	if (bmap[i-1] == 1){
		// 插入</b>
        strcpy(outputcur,"</b>");
		outputcur +=strlen("</b>");
	}
    *(outputcur++) = *(inputcur++);
}
// 3 output
return output;
}

