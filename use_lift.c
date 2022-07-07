#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define LIFT_MAX_WEIGHT 500

int main(int argc, char ** argv) 
	{
		key_t key;
		int weight, seconds;
		int semid;
		struct sembuf sops;
	
		if (argc != 3) 
			{
				fprintf(stderr, "должно быть 3 параметра\n");
				return -1;
			}
		
		if ( (key = ftok("use_lift.c", 0)) == -1) 
			{
				fprintf(stderr, "не удалось получить доступ к use_lift.c\n");
				return -1;
			}
		
		if ( (semid = semget(key, 1, 0)) == -1)    /*доступ к 1-му семафору*/
			{
				fprintf(stderr, "не удалось получить доступ к семафору\n");
				return -1;
			}
		
		sscanf(argv[1], "%d", &seconds);
		sscanf(argv[2], "%d", &weight);
		
		if (weight < 0 || weight > LIFT_MAX_WEIGHT || seconds < 0) 
			{
				fprintf(stderr, "неправильный формат\n");
				return -1;
			}
		
		sops.sem_op = -weight;
		sops.sem_flg = 0;
		sops.sem_num = 0;
		
		if (semop(semid, &sops, 1) == -1)  /*применяем операцию*/
			exit(0);
		
		printf("%d массы %d зашел в лифт на %d секунд\n", getpid(), weight, seconds);
		sleep(seconds);
		printf("%d вышел из лифта\n", getpid());
		
		sops.sem_op = weight;
		
		semop(semid, &sops, 1);
		
		return 0;
	}
