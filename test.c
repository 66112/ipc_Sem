#include "comm.h"

int main()
{
	int semid = CreatSemSet(1); //创建一个信号量集，返回标识码即arr[1];
	initSem(semid,0,1);  //0表示信号集中信号量的下标，1表示设置该信号量的计数值
	pid_t id=fork();  //创建子进程
	if(id==0){  //child
		int _semid = GetSemSet(1); //访问信号量集(根据名字访问),若不存在则创建arr[1];
		int i=2;
		while(i--){
			P(_semid,0);  //对0号信号量进行P操作，占用临界资源
			printf("A");  //此时显示器就是临界资源
			fflush(stdout);
			sleep(1);
			printf("A");
			fflush(stdout);
			sleep(1);
			V(_semid,0);  //对0号信号量进行V操作，释放临界资源
		}
		exit(0);
	}
	else{
		int i=1;
		while(i--){
			P(semid,0);
			printf("B");
			fflush(stdout);
			sleep(1);
			printf("B");
			fflush(stdout);
			sleep(1);
			V(semid,0);
		}
		wait(NULL);
	}
	printf("\n");
	DestorySemSet(semid);
	return 0;
}
