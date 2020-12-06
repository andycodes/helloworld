
/*INT*/
struct Hashmap {
	int key;
	UT_hash_handle hh;
};

#define hash_add_int(hashmap, ikey)\
{\
	struct Hashmap* pnode = (struct Hashmap*)calloc(1, sizeof(struct Hashmap));\
	pnode->key = ikey;\
	HASH_ADD_INT(hashmap, key, pnode);\
}\

struct Hashmap* hash_find_int(struct Hashmap* hashmap, int target)
{
	struct Hashmap* find = NULL;
	HASH_FIND_INT(hashmap, &target, find);
	return find;
}

void hash_free_int(struct Hashmap* hashmap)
{
	struct Hashmap* pnode = NULL;
	struct Hashmap* tmp = NULL;

	HASH_ITER(hh, hashmap, pnode, tmp) {
		HASH_DEL(hashmap, pnode);
		free(pnode);
	}
}

/*STR*/
struct Hashmap {
	char key[KEY_SIZE];
	UT_hash_handle hh;
};

#define hash_add_str(hashmap, skey)\
{\
	struct Hashmap* pnode = (struct Hashmap*)calloc(1, sizeof(struct Hashmap));\
	pnode->key = skey;\
	HASH_ADD_STR(hashmap, key, pnode);\
}\

struct Hashmap* hash_find_str(struct Hashmap* hashmap, char* target)
{
	struct Hashmap* find = NULL;
	HASH_FIND_STR(hashmap, target, find);
	return find;
}

void hash_free_str(struct Hashmap* hashmap)
{
	struct Hashmap* pnode = NULL;
	struct Hashmap* tmp = NULL;

	HASH_ITER(hh, hashmap, pnode, tmp) {
		HASH_DEL(hashmap, pnode);
		free(pnode->key);
		free(pnode);
	}
}

/*KEYPTR*/
struct Hashmap {
	void* key;
	UT_hash_handle hh;
};

#define hash_add_ptr(hashmap, pkey)\
{\
	struct Hashmap* pnode = (struct Hashmap*)calloc(1, sizeof(struct Hashmap));\
	pnode->key = pkey;\
	HASH_ADD_PTR(hashmap, key, pnode);\
}\

struct Hashmap* hash_find_ptr(struct Hashmap* hashmap, void* target)
{
	struct Hashmap* find = NULL;
	HASH_FIND_PTR(hashmap, &target, find);
	return find;
}

HASH_SORT(hashmap, Cmp);
HASH_COUNT(hashmap);

