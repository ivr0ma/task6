#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() 
	{
		int semid;
		key_t key;
		
		if ( (key = ftok("use_lift.c", 0)) == -1) 
			{
				fprintf(stderr, "не удалось получить доступ к use_lift.c\n");
				return -1;
			}
		
		if ((semid = semget(key, 1, 0)) == -1)  /*доступ к 1-му семафору*/
			{
				fprintf(stderr, "не удалось получить доступ к семафору\n");
				return -1;
			}
			
		semctl(semid, 0, IPC_RMID);  /*удаляем семафор*/
		
		return 0;
	}
