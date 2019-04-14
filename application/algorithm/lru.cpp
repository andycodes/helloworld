#include <iostream>
using namespace std;


#define Len 100
int CachePoll[Len];


int exit (int queue[],int head,int tail,int num)
{
	int i;

	for( i=head;i<tail;i++)
	{
		if(queue[i] == num)
		return i;/*hit:return hit index*/
	}

	if(i == tail)/*not hit:return -1*/
		return -1;
}

void show (int queue[],int head,int tail)
{
	cout<<";CachePoll:";
	for(int i=head;i<tail;i++)
		cout<<queue[i]<<"  ";
}

void FIFO (int in[],int length)
{
	int tail = 0;
	int head = 0;
	int target = 0;

	for(int i = 0;i < length; i++) {
		if(tail - head - 3 == 0)
		{
			if(exit(CachePoll,head,tail,in[i]) > -1)//内存中存在in[i]
			{
				cout<<in[i]<<" Hit:"<<++target<<endl;
			}else{
				CachePoll[tail++] = in[i];
				cout<<in[i]<<" in Cache;"<<CachePoll[head++]<<" out Cache;";
				show(CachePoll,head,tail);
				cout<<"Missing page Cnt:"<<tail<<endl;
			}
		}else{
			CachePoll[tail++] = in[i];
			cout<<in[i]<<" in Cache;";
			show(CachePoll,head,tail);
			cout<<";Missing page Cnt:"<<tail<<endl;
		}
	}
	cout<<"Missing page Cnt:"<<tail<<endl<<"HIT:"<<target<<endl;
}


void LRU(int in[],int length)
{
    int tail = 0;
    int head = 0;

    for(int i=0;i<length;i++)
    {
        if(tail - head - 4 == 0)
        {
            if(exit(CachePoll,head,tail,in[i]) > -1)//内存中存在in[i]
            {
                int local = exit(CachePoll,head,tail,in[i]);
                int temp = CachePoll[local];
                int j;

                for(j=local;j<tail-1;j++)
                    CachePoll[j] = CachePoll[j+1];

                CachePoll[j] = temp;

                cout<<in[i]<<" hit;";
                show(CachePoll,head,tail);
                cout<<endl;
            }
            else
            {
                CachePoll[tail++] = in[i];
                cout<<in[i]<<" Call in Mem;Eliminated:"<<CachePoll[head++];
                show(CachePoll,head,tail);
                cout<<"Missing page Cnt:"<<tail<<endl;
            }
        }
        else {
            CachePoll[tail++] = in[i];
            cout<<in[i]<<" Call in Mem;";
            show(CachePoll,head,tail);
            cout<<";Missing page Cnt:"<<tail<<endl;
        }
    }
}


int main()
{
    int in[16]={0,1,2,3,2,1,3,2,5,2,3,6,2,1,4,2};
    int in2[19]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0};
    //FIFO(in,16);
    cout<<endl<<endl<<endl;
    LRU(in2,19);
    return 0;
}
