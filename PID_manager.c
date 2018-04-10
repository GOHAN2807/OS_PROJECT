#include<pthread.h>
#include<stdbool.h>
#include <stdio.h>
#include <assert.h>

#define PID_MIN 100
#define PID_MAX 1000

int tVar = 0;
int last;
pthread_mutex_t lock;

struct pid_tab
{
	int pid;
	bool bitmap;
}pArr[901];

int allocate_map(void) 
{
	int i,j;
	for (i = PID_MIN; i <= PID_MAX; i++)
	{
		pArr[i-PID_MIN].pid = i;
		pArr[i-PID_MIN].bitmap = 0;
	}
	last = PID_MIN-1;
	if(i-1 == PID_MAX)
	return 1;
	else
	return -1;
}
int allocate_pid(void)
{
	int n_loops = 0;

	int next;

	if (last == PID_MAX)
		next = PID_MIN-100;
	else
		next = last + 1-100;

	while ( (n_loops <= (PID_MAX - PID_MIN)) && (pArr[next].bitmap == 1) ) {	
		++n_loops;
		++next;
		if (next > PID_MAX)
			next = PID_MIN;
	}

	if (n_loops == (PID_MAX - PID_MIN) + 1) {
		return -1;
	}
	
	pArr[next].bitmap = 1;
	pArr[next].pid = next + 100;

	last = next+100;

	return last;
}

void release_pid(int pid)
{
	int i;
	for(i = 0;i <=900; i++)
	{
		if(pArr[i].pid == pid)
		{
			pArr[i].bitmap = 0;
			break;
		}
	}
}

void* threadFunc(void* arg)
{
	int PID = allocate_pid();
	while(tVar <100)
	{
		pthread_mutex_lock(&lock);
		tVar++;
		Sleep(100);
		printf("\nThread no : %d",tVar);
		printf("\nProcess Id : %d",PID);
		pthread_mutex__unlock(&lock);
		break;
	}
	release_pid(PID);
}
int main()
{
	int map = allocate_map();
	if(map == -1)
	{
		printf("\nBitmap Data Structure can't be initialized.");
		return;
	}
	if(map == 1)
	{
		printf("\nBitmap Data Structure initialized.");	
	}
	pthread_t threads[100];
	int thread_args[100];
	int result_code;
	int index;
	pthread_mutex_init(&lock,NULL);
	
	for(index = 0;index < 100;++index)
	{
		thread_args[index]=index+1;
		printf("\nCreation of thread %d",index+1);
		result_code = pthread_create(&threads[index],NULL,threadFunc, &thread_args[index]);
		assert(!result_code);
	}
	for(index = 0;index <100;++index)
	{
		result_code = pthread_join(threads[index],NULL);
		printf("\nThread No. : %d has completed ",index+1);
	}
	return 0;
}
