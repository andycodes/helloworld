#ifdef HASHMAP_STR
#define HASHMAP_NULL NULL
#endif

#ifdef HASHMAP_INT
#define HASHMAP_NULL INT_MIN
#endif

typedef struct{
	int id;
#ifdef HASHMAP_STR
	void* key;
	void* val;
#endif
#ifdef HASHMAP_INT
	int key;
	int val;
#endif

}DataType;

typedef struct{
	DataType data;
	struct HashNode *next;  //key��ͻʱ��ͨ��nextָ���������
}HashNode;

typedef struct hashMap HashMap;
typedef unsigned int(*HashCode)(HashMap *hashmap, DataType* entry);
typedef int(*HashEqual)(DataType* obj1, DataType* obj2);
typedef struct hashMap{
	unsigned int size;
	HashCode hashcode;
	HashEqual hashequal;
	HashNode *table;
}HashMap;


unsigned int hashcode_int(HashMap * hashmap, DataType* entry)
{
	return abs((int)(entry->key)) % hashmap->size;
}

int hashequal_int(DataType* obj1, DataType* obj2)
{
	return (int)obj1->key == (int)obj2->key;
}

unsigned int hashcode_str(HashMap * hashmap, DataType* entry)
{
	unsigned int hash = 0;
	char *p = (char *)entry->key;
	while(*p != '\0') {
		hash = hash*33+*p;
		p++;
	}
	return hash % hashmap->size;
}

int hashequal_str(DataType* obj1, DataType* obj2)
{
	if ((char *)obj1->key == HASHMAP_NULL || (char *)obj2->key == HASHMAP_NULL)
		return 0;

	return !strcmp((char *)obj1->key,  (char *)obj2->key);
}

/*
����hashmap->size=2*size; hashmap��table�ĳ���Ϊʲô�Ǹ������鳤�ȵ�2����
���漰��hash���װ�����ӣ�
��ϣ��װ������: a = m/n
����n Ϊ�ؼ��ָ�����mΪ��.
װ�������Ǳ�ʾHsah����Ԫ�ص������ĳ̶ȡ�
��������Խ��,������Ԫ��Խ��,�ռ����������,����ͻ�Ļ���Ӵ��ˡ�
��֮,��������ԽС,������Ԫ��Խ��,��ͻ�Ļ����С��,���ռ��˷Ѷ��ˡ�
��ͻ�Ļ���Խ��,����ҵĳɱ�Խ�ߡ���֮,���ҵĳɱ�ԽС.���,����ʱ���ԽС.
���,������ "��ͻ�Ļ���"��"�ռ�������"֮��Ѱ��һ��ƽ�⡣

*/
//���������������鹹��ΪHashMap,sizeΪ���鳤��
HashMap *hashmap_init(unsigned int size, HashCode hashcode, HashEqual hashequal)
{
	HashMap *hashmap=(HashMap*)malloc(sizeof(HashMap));
	if (hashmap == NULL) {
		return NULL;
	}
	hashmap->hashcode = hashcode;
	hashmap->hashequal = hashequal;
	hashmap->size = 3 * size;
	hashmap->table = (HashNode *)calloc(hashmap->size, sizeof(HashNode));
	if (hashmap->table == NULL) {
		free(hashmap);
		return NULL;
	}

	for (int i = 0; i < hashmap->size; i++) {
		hashmap->table[i].data.key = HASHMAP_NULL;
	}

	return hashmap;
}


int hashmap_push(HashMap *hashmap,DataType entry)
{
     int pos = hashmap->hashcode(hashmap, &entry);

     HashNode *pointer=&(hashmap->table[pos]);
     if(pointer->data.key == HASHMAP_NULL) {
	 pointer->data = entry;
	 pointer->data.id = pos;
      }else{
        HashNode *hnode = (HashNode *)calloc(1, sizeof(HashNode));
	if (hnode == NULL) {
		return -1;
	}

	hnode->data = entry;
	hnode->data.id = pos;
        hnode->next = NULL;

        while(pointer->next != NULL)
             pointer = pointer->next;
        pointer->next = hnode;
   }

   return 0;
}


void hashmap_getValue(HashMap *hashmap, DataType *entry)
{
	int pos = hashmap->hashcode(hashmap, entry);

	HashNode *pointer = &(hashmap->table[pos]);
	while (pointer != NULL) {
		if (hashmap->hashequal(&pointer->data, entry)) {
			*entry = pointer->data;
			return;
		}else {
			pointer=pointer->next;
		}
	}

	entry->id = -1;
}


//f4_hashmap_print
void hashmap_print(HashMap* hashmap)
{
	printf("%===========hashmap_print==========\n");
	int i=0;
	HashNode *pointer;
	while(i < hashmap->size) {
		pointer = &(hashmap->table[i]);
		while(pointer != NULL) {
			if (pointer->data.val != HASHMAP_NULL)
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


void hashmap_exit(HashMap *hashmap)
{
	int i = 0;
	HashNode *hpointer;
	while(i < hashmap->size) {
		hpointer = hashmap->table[i].next;
		while(hpointer != NULL) {
			hashmap->table[i].next = hpointer->next;
			free(hpointer);
			hpointer = hashmap->table[i].next;
		}
		i++;
	}

	free(hashmap->table);
	free(hashmap);
}


int test_int(int argc, char **argv)
{
	int nums[]={34,54,32,32,56,78};
	int size = sizeof(nums)/sizeof(nums[0]);
	HashMap *hashmap = hashmap_init(size, 0);

	for (int i = 0; i < size; i++) {
		DataType entry;
		entry.key = i;
		entry.val = nums[i];
		hashmap_push(hashmap, entry);
	}

	hashmap_print(hashmap);

	DataType entry;
	entry.key = 5;
	hashmap_getValue(hashmap, &entry);
	printf("hashmap_getValue val[78 is %d]id[%d]\n",entry.val, entry.id);

	entry.key = 8;
	entry.val = 55;
	hashmap_push(hashmap, entry);
	entry.val = -1;
	hashmap_getValue(hashmap, &entry);
	printf("hashmap_getValue val[55 is %d]id[%d]\n",entry.val, entry.id);

	hashmap_exit(hashmap);
	return 0;
}

