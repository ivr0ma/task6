#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define LIFT_MAX_WEIGHT 500

int main() 
	{
		int semid;
		key_t key; 
		
		if ( (key = ftok("use_lift.c", 0)) == -1) 
			{
				fprintf(stderr, "не удалось получить доступ к use_lift.c\n");
				return -1;
			}
		
		if ( (semid = semget(key, 1, IPC_CREAT | 0644) ) == -1)  /*доступ к 1-му семафору*/
			{
				fprintf(stderr, "не удалось создать семафор\n");
				return -1;
			}
			
		semctl(semid, 0, SETVAL, LIFT_MAX_WEIGHT);  /*устанавливаем значение семафора с номером 0 равным */
		
		return 0;
	}
