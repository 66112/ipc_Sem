#include "comm.h"

static int CommSemSet(int nums,int flags)
{
	key_t _key=ftok(PATHNAME,PROJ_ID);
	if(_key < 0){
		perror("ftok");
		return -1;
	}
	int semid = semget(_key,nums,flags); //创建时nums是信号量集中信号量的个数  //访问时是信号量集中的第几号信号量
	if(semid < 0){
		perror("semget");
		return -1;
	}
	return semid;  
}

int CreatSemSet(int nums)
{
	return CommSemSet(nums,IPC_CREAT | IPC_EXCL | 0666);
}

int GetSemSet(int nums)
{
	return CommSemSet(nums,IPC_CREAT);
}

int initSem(int semid,int nums,int initVal)
{
	union semun _un;   //nums是第0号信号量，initVal是初始值
	_un.val = initVal;
	if(semctl(semid,nums,SETVAL,_un)<0){
		perror("semctl");
		return -1;
	}
	return 0;
}

static int CommPV(int semid,int who,int op)
{
	struct sembuf _sf;
	_sf.sem_num = who;  //操作第who号信号量，
	_sf.sem_op = op;   // <1,P操作，申请临界资源，>1,V操作，释放临界资源
	_sf.sem_flg = 0;
	if(semop(semid,&_sf,1)<0){
		perror("semop");
		return -1;
	}
	return 0;
}

int P(int semid,int who)
{
	return CommPV(semid,who,-1);
}

int V(int semid,int who)
{
	return CommPV(semid,who,1);
}

int DestorySemSet(int semid)
{
	if(semctl(semid,0,IPC_RMID)<0){
		perror("destory");
		return -1;
	}
	return 0;
}


