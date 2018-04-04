#include<stdbool.h>
#include <pthread.h>
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
