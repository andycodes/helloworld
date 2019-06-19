// Slash Maze ��б���Թ���  
// PC/UVa IDs: 110904/705, Popularity: B, Success rate: average Level: 2  
// Verdict: Accepted  
// Submission Date: 2011-09-28  
// UVa Run Time: 0.012s  
//  
// ��Ȩ���У�C��2011�����metaphysis # yeah dot net  
//  
// [��������]  
// ͨ����б�ߣ�/���ͷ�б�ߣ�\�������һ�����Σ�����Եõ�һ��С�Թ������磺  
//  
// ������ gedit ���ܲ���ͼƬ����ο� UVa ��ԭ���ͼƬ��ԭ�����ӣ�http://uva.onlinejudge.o  
// rg/index.php?option=com_onlinejudge&Itemid=8&category=37&page=show_problem&pr  
// oblem=646����  
//  
// �������������ģ��Թ��е�ͨ·�Ӳ��ֲ棬��������Թ���ֻ�У�1����״ͨ·�Լ���2����һ���ط����벢  
// ������һ���ط���ȥ��ͨ·������ֻ�Ի�����Ȥ������������������������  
//  
// ���������Ҫдһ��������������Ļ��ĳ��ȡ����ĳ��ȱ�����Ϊ����������С�����Σ���ͼ���û�ɫ  
// ������ǣ��������������������У������ĳ���Ϊ 16���̻��ĳ���Ϊ 4��  
//  
// [����]  
// ����������������ݡ�ÿ�����ݵĵ�һ���������� w �� h��1 <= w��h <= 75�����ֱ�����Թ��Ŀ��  
// �͸߶ȡ��������� h �У�ÿ���� w ���ַ������������Թ�����Щ�ַ����ǡ�/����\����  
//  
// �� w = h = 0 ʱ�����������һ�в��ش���  
//  
// [���]  
// ����ÿ���Թ��������һ�С�Maze #n:�������� n Ϊ�Թ���š�Ȼ�����һ�С�k Cycles; the longest  
// has length l.�������� k Ϊ�Թ��л���������l ������ĳ��ȡ��������Թ���û�л��������There  
// are no cycles.��  
//  
// ��ÿ�����ݵ�������ӡһ�����С�  
//  
// [��������]  
// 6 4  
// \//\\/  
// \///\/  
// //\\/\  
// \/\///  
// 3 3  
// ///  
// \//  
// \\\  
// 0 0  
//  
// [�������]  
// Maze #1:  
// 2 Cycles; the longest has length 16.  
//  
// Maze #2:  
// There are no cycles.  
//  
// [���ⷽ��]  
// �����������Թ�����ƽ��ֱ����Ȼ�ǱȽϺý���ģ����Ǹ�������б�߱�ʾ���Թ����������Ǻܺô���ʵ  
// ���Ͻ�б�ߺͷ�б�߹��ɵ��Թ���������ͼ��ʽ�Ĺ���������ת����ֱ���͵��Թ���Ȼ��ʹ��ͼ�������㷨  
// ���� Flood fill �㷨�� Union-Find �㷨������󻷳��ȡ�  
//  
// �۲���Ŀ������ͼ����֪����б�ߺͷ�б��ռ��������С�����εıߣ���ô���Խ�б��ռ�ݵı�ʹ�� 1 ��  
// ��ʾ����б��ռ�ݵı��� 2 ����ʾ��δռ�ݵı�ʹ�� 0 ����ʾ����ô��Ŀ������ͼת�������µľ���  
//  
// 200101202001  
// 021010020210  
// 200101012001  
// 021010100210  
// 010120200120  
// 101002021002  
// 200120010101  
// 021002101010  
//  
// ����ת��Ϊ�ڴ˾�����Ѱ�Ҵ�ֵΪ 0 ��λ�ó����ܹ��ص�����λ�õ��·�����ȴӾ���������Ѱ��Ϊ  
// 0 ��λ�ã�ʹ�� Flood fill �㷨����� 0 λ����ͨ��λ��ȫ����Ϊ 3����ʾ��Щ���Ѿ����������Ϊ  
// ��Щλ���ǲ����ܹ��ɻ��ģ�����Ǻ����Եģ������׵Ļ�����һ��...�����������ܱߵ� 0 λ��ȫ����  
// ����󣬾����ɣ�  
//  
// 233131232331  
// 321310023213  
// 233101012331  
// 321010100213  
// 310120200123  
// 101002021332  
// 200120013131  
// 321332131313  
//  
// ������������в��ܹ��ɻ��� 0 λ�ö��Ѿ�������ˣ���ʱ�Ӿ���������ѡ��һ�� 0 λ�ã�ʹ��  
// Flood fill �㷨������� 0 λ������ͨ������λ�ã���������Ϊ 3����¼����������ҵ� 0 �Ĵ�����  
// ��Ϊ�û��ĳ��ȡ�  
//  
// Ψһ��Ҫע������ڱ���ʱ�����ѡ�����⣬�����Ѿ�������б�����Ա�ǣ�ֻ�賯λ��Ϊ 0 �ķ����߼��ɣ�  
// ���ߵĹ�����Ҫ���ݵ�ǰ���ڵ�����б�߾������еķ���  
//  
// Flood fill �㷨���ܣ�  
// http://en.wikipedia.org/wiki/Flood_fill��  
//  
// Union-Find �㷨���ܣ�  
// http://www.cs.princeton.edu/~rs/AlgsDS07/01UnionFind.pdf��  
  
#include <iostream>  
 
using namespace std;  
  
#define MAXV 150  
  
#define EMPTY 0  
#define SLASH 1  
#define BACKSLASH 2  
#define VISITED 3  
  
#define LEFT_UP 0  
#define UP 1  
#define RIGHT_UP 2  
#define LEFT 3  
#define RIGHT 4  
#define LEFT_BOTTOM 5  
#define DOWN 6  
#define RIGHT_BOTTOM 7  
  
struct mazes  
{  
    int status[MAXV][MAXV];  
    int width, height;  
};  
  
int length;  
int offset[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0},  
    {1, 1} };  
  
// ��������Ƿ��ھ����ڡ�  
inline bool in_range(int line, int row, int width, int height)  
{  
    return ((0 <= line && line < height) && (0 <= row && row < width));  
}  
  
// ʹ�� Flood fill �㷨����λ�ã�line��row������ͨ��λ����ֵ��Ϊ VISITED��Flood fill �㷨  
// ʵ�������������������˼�롣  
void flood_fill(mazes * maze, int line, int row)  
{  
    length++;  
    maze->status[line][row] = VISITED;  
  
    for (int d = LEFT_UP; d <= RIGHT_BOTTOM; d++)  
    {  
        int tline = line + offset[d][0];  
        int trow = row + offset[d][1];  
  
        if (in_range(tline, trow, maze->width, maze->height))  
            if (maze->status[tline][trow] == EMPTY)  
            {  
                // ���ң��ϣ��µ� 0 λ�����ǿ���ֱ���ߵġ�  
                if (tline == line || trow == row)  
                    flood_fill(maze, tline, trow);  
                // �Խ����ϵ� 0 λ�ò���Ҫ�жϡ�  
                else  
                {  
                    // ���Ͻǵ� 0 λ�ÿ��е�����������಻Ϊб�ߡ�  
                    if (d == LEFT_UP)  
                        if (maze->status[line][row - 1] != SLASH)  
                            flood_fill(maze, tline, trow);  
                    // ���½ǵ� 0 λ�ÿ��е����������Ҳ಻Ϊб�ߡ�  
                    if (d == RIGHT_BOTTOM)  
                        if (maze->status[line][row + 1] != SLASH)  
                            flood_fill(maze, tline, trow);  
                    // ���½ǵ� 0 λ�ÿ��е�����������಻Ϊ��б�ߡ�  
                    if (d == LEFT_BOTTOM)  
                        if (maze->status[line][row - 1] != BACKSLASH)  
                            flood_fill(maze, tline, trow);  
                    // ���Ͻǵ� 0 λ�ÿ��е����������Ҳ಻Ϊ��б�ߡ�  
                    if (d == RIGHT_UP)  
                        if (maze->status[line][row + 1] != BACKSLASH)  
                            flood_fill(maze, tline, trow);  
                }  
            }  
    }  
}  
  
int main(int ac, char *av[])  
{  
    mazes maze;  
    int width, height, cases = 1;  
    char slash;  
    bool is_backslash;  
  
    while (cin >> width >> height, width && height)  
    {  
        // ע���ڶ�������ʱ�ǽ������Թ����Ϳ��������������ʾ��  
        for (int i = 0; i < height; i++)  
            for (int j = 0; j < width; j++)  
            {  
                cin >> slash;  
                  
                is_backslash = (slash == '\\');  
                maze.status[i * 2][j * 2] = is_backslash ? BACKSLASH : EMPTY;  
                maze.status[i * 2][j * 2 + 1] = is_backslash ? EMPTY : SLASH;  
                maze.status[i * 2 + 1][j * 2] = is_backslash ? EMPTY : SLASH;  
                maze.status[i * 2 + 1][j * 2 + 1] = is_backslash ? BACKSLASH : EMPTY;  
            }  
  
        maze.width = 2 * width;  
        maze.height = 2 * height;  
  
        // ��������ܱߵ� 0��  
        for (int i = 0; i < maze.height; i++)  
            for (int j = 0; j < maze.width; j++)  
                if (maze.status[i][j] == EMPTY)  
                    if (i == 0 || j == 0 || i == (maze.height - 1)  
                        || j == (maze.width - 1))  
                        flood_fill(&maze, i, j);  
  
        // ��ȡ��󻷳��ȡ�  
        int maximum = 0, cycles = 0;  
        for (int i = 0; i < maze.height; i++)  
            for (int j = 0; j < maze.width; j++)  
                if (maze.status[i][j] == EMPTY)  
                {  
                    cycles++;  
                      
                    length = 0;  
                    flood_fill(&maze, i, j);  
  
                    if (maximum < length)  
                        maximum = length;  
                }  
  
        // ��������ע��ÿ�����ݺ���Ҫ������С�  
        cout << "Maze #" << cases++ << ":" << endl;  
        if (maximum > 0)  
        {  
            cout << cycles;  
            cout << " Cycles; the longest has length ";  
            cout << maximum << ".";  
        }  
        else  
            cout << "There are no cycles.";  
        cout << endl << endl;  
    }  
  
    return 0;  
} 
