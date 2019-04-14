#include <pthread.h>
#include <unistd.h>
#include <iostream>
using namespace std;




 pthread_spinlock_t lock = 0;
 int count = 0;


 void* work(void* param)
 {
	for (int i = 0; i < 100; i++)
	{
		pthread_spin_lock(&lock);
		++count;
		pthread_spin_unlock(&lock);
	}
	return NULL;
 }


 int main()
 {
	pthread_t pt = 0;
	pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);
	pthread_create(&pt, NULL, work, NULL);

	for (int i = 0; i < 100; i++)
	{
		pthread_spin_lock(&lock);
		++count;
		pthread_spin_unlock(&lock);
	}
	pthread_join(pt, NULL);
	pthread_spin_destroy(&lock);

	cout<<count<<endl;
	return 0;
 }

 /* g++ pthread_cond.cpp -lpthread */

