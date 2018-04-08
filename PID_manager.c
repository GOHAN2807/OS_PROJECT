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
		pthread_mutex_unlock(&lock);
		break;
	}
	release_pid(PID);
}
