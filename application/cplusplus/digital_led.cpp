#include<iostream>
#include<sstream>
#include <string.h>

using namespace std;
#define DIGITAL_SIZE 5
/*
-0
1||2
3-
4||5
6_

0 		1 		2 		3 		4 		5 		6 		7 		8		 9
0x77		0x24		0x5D	0x6D	0x2E		0x6B	0x7B	0x25		0x7F		0x2F
*/

void across(unsigned char data, string & result, unsigned char flag)
{
		if (data & flag) {
			for(int j = 0; j < DIGITAL_SIZE; j++){
				result.push_back('-');
			}
		}else {
			for(int j = 0; j < DIGITAL_SIZE; j++){
				result.push_back(' ');
			}
		}

		result.push_back('\n');
}

void vertical(unsigned char data, string & result, unsigned char flag,unsigned char flag1)
{
		for (int j = 0; j < DIGITAL_SIZE; j++){
			if (data & flag) {
				result.push_back('|');
			}else {
				result.push_back(' ');
			}

			for(int j = 0; j < DIGITAL_SIZE; j++){
				result.push_back(' ');
			}

			if (data & flag1) {
				result.push_back('|');
			}else {
				result.push_back(' ');
			}
			result.push_back('\n');
		}
}

int main(void)
{
	const char *input = "98765432";
	unsigned char code[] = {0x77,0x24,0x5D,0x6D,0x2E,0x6B,0x7B,0x25,0x7F,0x2F};
	unsigned char readdata[8] = {0x77,0x24,0x5D,0x6D,0x2E,0x6B,0x7B,0x7F};
	string result;
	unsigned char cur_char;
	if (strlen(input) > 8)
		return -1;
	for (int i = 0; i < strlen(input); i++) {
		cur_char = *(input + i);
		if (cur_char > '9' || cur_char < '0')
			return -1;
		readdata[i] = code[cur_char - '0'];
	}

	for (int i = 0; i < 8; i++){
		across(readdata[i], result, 0x01);
		vertical(readdata[i], result, 0x02,0x04);
		across(readdata[i], result, 0x08);
		vertical(readdata[i], result, 0x10,0x20);
		across(readdata[i], result, 0x40);

		//result.push_back(' ');
	}

	cout << result << endl;
}

