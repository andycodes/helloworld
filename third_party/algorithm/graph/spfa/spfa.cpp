/*
 * ��Դ���·�㷨SPFA,ʱ�临�Ӷ�O(kE),k��һ������²�����2,����ÿ������ʹ�ÿ�����O(VE)��ʱ�������ÿ�Խڵ�֮������·
 * ʹ���˶���,���������ڶ����еĵ����ŵĵ�����ɳ�,ͬʱ�����ڶ����е����ŵĵ����,ֱ���ӿ����㷨����,���·���
 * SPFA��Bellman-Ford���Ż���,���Դ����и�Ȩ�ߵ����
 * ���ڸ���,���ǿ���֤��ÿ������Ӵ������ᳬ��V,�������ǿ��Լ�¼ÿ�������Ӵ���,�������V���ʾ����ָ���,�㷨����
 * ����Ҫ�Ե��ÿһ���߽���ö��,�ʲ����ڽӱ�ʱʱ�临�Ӷ�ΪO(kE),���þ���ʱʱ�临�Ӷ�ΪO(kV^2)
 */
#include<cstdio>
#include<vector>
#include<queue>
#define MAXV 10000
#define INF 1000000000 //�˴����鲻Ҫ������С,�����׵�������ʱ���,��С���ܻᱻ�ж�Ϊ�����ľ���

using std::vector;
using std::queue;

struct Edge{
	int v; //��Ȩ
	int to; //���ӵĵ�
};

vector<Edge> e[MAXV]; //����һ�������E<<V*V,���ڴ�ѡ����vector��̬����洢,Ҳ����ʹ������洢
int dist[MAXV]; //�洢��ԭ��0�ľ���,���Կ���ά����洢ÿ�Խڵ�֮��ľ���
int cnt[MAXV]; //��¼��Ӵ���,����V���˳�
queue<int> buff; //����,���ڴ洢��SPFA�㷨�е���Ҫ�ɳڵĽڵ�
bool done[MAXV]; //�����жϸýڵ��Ƿ��Ѿ��ڶ�����
int V; //�ڵ���
int E; //����

bool spfa(const int st)
{ //����ֵ:TRUEΪ�ҵ����·����,FALSE��ʾ���ָ����˳�
	for(int i=0;i<V;i++){ //��ʼ��:������ԭ��st�ľ���������е㵽st�ľ��������һ������ֵ
		if(i==st){
			dist[st]=0; //ԭ�����Ϊ0;
			continue;
		}
		dist[i]=INF; //��ԭ����������
	}

	buff.push(st); //ԭ�����
	done[st]=1; //���ԭ���Ѿ����
	cnt[st]=1; //�޸���Ӵ���Ϊ1
	while(!buff.empty()){ //���зǿ�,��Ҫ�����ɳ�
		int tmp=buff.front(); //ȡ������Ԫ��
		for(int i=0;i<(int)e[tmp].size();i++){ //ö�ٸñ����ӵ�ÿһ����
			Edge *t=&e[tmp][i]; //����vector��Ѱַ�ٶȽ���,���ڴ˽���һ���Ż�
			if(dist[tmp]+(*t).v<dist[(*t).to]){ //���ĺ�������,�����ɳڲ���
				dist[(*t).to]=dist[tmp]+(*t).v; //���ı�Ȩֵ
				if(!done[(*t).to]){ //û�����,�������
					buff.push((*t).to); //���ڵ�ѹ�����
					done[(*t).to]=1; //��ǽڵ��Ѿ����
					cnt[(*t).to]+=1; //�ڵ���Ӵ�������
					if(cnt[(*t).to]>V){ //�Ѿ�����V��,���ָ���
						while(!buff.empty())buff.pop(); //��ն���,�ͷ��ڴ�
						return false; //����FALSE
					}
				}
			}
		}
		buff.pop();//�������׽ڵ�
		done[tmp]=0;//�����׽ڵ���Ϊδ���
	}
	return true; //����TRUE
} //�㷨����

int main(){ //������
	scanf("%d%d",&V,&E); //��������ͱ���
	for(int i=0,x,y,l;i<E;i++){
		scanf("%d%d%d",&x,&y,&l); //����x,y,l��ʾ��x->y��һ������߳���Ϊl
		Edge tmp; //����һ����ʱ����,�Ա����vector
		tmp.v=l; //���ñ�Ȩ
		tmp.to=y; //�������ӽڵ�
		e[x].push_back(tmp); //��������ѹ��x�ı���;Adjacent table
	}
	if(!spfa(0)){ //���ָ���
		printf("no\n");
	}else{ //�������·
		//�ڵ�0���ڵ�%d����̾���Ϊ%d
		printf("[%d][%d]",V-1,dist[V-1]);
	}
	return 0;
}