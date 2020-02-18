typedef struct{
	int key;  //��
	int val;  //ֵ
}DataType; //�Ի����������ͽ��з�װ�����Ʒ���

typedef struct{
	DataType data;
	struct HashNode *next;  //key��ͻʱ��ͨ��nextָ���������
}HashNode;

typedef struct{
	int size;
	HashNode *table;
}HashMap,*hashmap;


/*
����hashmap->size=2*size; hashmap��table�ĳ���Ϊʲô�Ǹ������鳤�ȵ�2�������漰��hash���װ�����ӣ���ϸ���Բο���ε�������ݽṹ���еھ��²��ҵĹ�ϣ���½ڣ��������򵥽��ܣ�

��ϣ��װ������: a = m/n

        ����n Ϊ�ؼ��ָ�����mΪ��.
       װ�������Ǳ�ʾHsah����Ԫ�ص������ĳ̶ȡ���������Խ��,������Ԫ��Խ��,�ռ����������,����ͻ�Ļ���Ӵ��ˡ���֮,��������ԽС,������Ԫ��Խ��,��ͻ�Ļ����С��,���ռ��˷Ѷ��ˡ���ͻ�Ļ���Խ��,����ҵĳɱ�Խ�ߡ���֮,���ҵĳɱ�ԽС.���,����ʱ���ԽС.���,������ "��ͻ�Ļ���"��"�ռ�������"֮��Ѱ��һ��ƽ�⡣

*/
//���������������鹹��ΪHashMap,sizeΪ���鳤��
HashMap *CreateHashMap(int *nums,int size){
	//�����ڴ�ռ�
	HashMap *hashmap=(HashMap*)malloc(sizeof(HashMap));
	hashmap->size=2*size;
	//hash�����ռ�
	hashmap->table=(HashNode *)malloc(sizeof(HashNode)*hashmap->size);
	//��ʼ��
	int j=0;
	for(j=0;j<hashmap->size;j++){
		hashmap->table[j].data.val=INT_MIN;
		hashmap->table[j].next=NULL;
	}
	int i=0;
	//����HashMap
	while(i<size){
	    //��������Ԫ�ص�ֵ��������hashMap�е�λ��
		int pos=abs(nums[i])%hashmap->size;
		//�ж��Ƿ��ͻ
		if(hashmap->table[pos].data.val==INT_MIN){
		    //����ͻ
		    //��Ԫ���������е�������Ϊkey
			hashmap->table[pos].data.key=i;
			//��Ԫ��ֵ��Ϊvalue
			hashmap->table[pos].data.val=nums[i];
		}
		//��ͻ
		else{
		    //����ǰԪ�ط���һ����㣬��Ϊ��㸴��
			HashNode *lnode=(HashNode*)malloc(sizeof(HashNode)),*hashnode;
			lnode->data.key=i;
			lnode->data.val=nums[i];
			lnode->next=NULL;
			//�ӳ�ͻλ�ÿ�ʼ����������
			hashnode=&(hashmap->table[pos]);
			while(hashnode->next!=NULL){
				hashnode=hashnode->next;
			}
			//����ǰ������ӵ�����β��
			hashnode->next=lnode;
		}
		//������һ��Ԫ��
		i++;
	}
	//������ɣ�����HashMap
	return hashmap;
}


int hashmap_get(HashMap hashmap, int value){
	//����Ԫ��ֵ��������λ��
	int pos = abs(value) % hashmap.size;
	HashNode *pointer = &(hashmap.table[pos]);
	//�ڵ�ǰ����������Ҹý��
	while (pointer != NULL) {
	if (pointer->data.val == value)
		return pointer->data.key;
	else
		pointer=pointer->next;
	}
	//δ�ҵ�������-1
	return -1;
}


int hashmap_push(HashMap hashmap,int key,int value){
     int pos = abs(value) % hashmap.size;
     HashNode *pointer=&(hashmap.table[pos]);
     if(pointer->data.val == INT_MIN) {
         pointer->data.val=value;
         pointer->data.key=key;
      }else{
        while(pointer->next!=NULL)
             pointer=pointer->next;
        HashNode *hnode=(HashNode *)malloc(sizeof(HashNode));
        hnode->data.key=key;
        hnode->data.val=value;
        hnode->next=NULL;
        pointer->next=hnode;
   }
   return 1;
}

//f4_hashmap_print
void hashmap_print(HashMap* hashmap){
	printf("%===========hashmap_print==========\n");
	int i=0;
	HashNode *pointer;
	while(i < hashmap->size) {
		pointer = &(hashmap->table[i]);
		while(pointer != NULL) {
			if (pointer->data.val != INT_MIN)
				printf("%10d",pointer->data.val);
			else
				printf("        [ ]");
			pointer=pointer->next;
		}

		printf("\n---------------------------------");
		i++;
		printf("\n");
	}
	printf("===============End===============\n");
}


void DestoryHashMap(HashMap *hashmap){
	int i=0;
	HashNode *hpointer;
	while(i <hashmap->size) {
	    hpointer = hashmap->table[i].next;
	    while(hpointer != NULL) {
	        hashmap->table[i].next = hpointer->next;
	        //����ͷŽ��ռ䣬��ֹ�ڴ����
	        free(hpointer);
	        hpointer = hashmap->table[i].next;
	}
	    //������һ�����
	    i++;
	}

	free(hashmap->table);
	free(hashmap);
	printf("Destory hashmap Success!");
}

int main(int argc, char **argv)
{
	int nums[]={34,54,32,32,56,78};
	//����HashMap
	HashMap *hashmap=CreateHashMap(nums,6);

	hashmap_print(hashmap);

	//����Ԫ��
	printf("hashmap_get : %d\n",hashmap_get(*hashmap,78));

	hashmap_push(*hashmap, 8, 55);
	printf("hashmap_get : %d\n",hashmap_get(*hashmap,55));

	DestoryHashMap(hashmap);
	getchar();
	return 0;
}

