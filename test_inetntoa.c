#include<stdio.h>
#include<arpa/inet.h>

#include<unistd.h>
#include<pthread.h>
void *fun1(void *p)
{
	struct sockaddr_in *addr = (struct sockaddr_in*)p;
	while(1){
		printf("addr1:%s\n",inet_ntoa(addr->sin_addr));
		sleep(1);
	}
	return NULL;
}
void *fun2(void *p)
{
	struct sockaddr_in *addr = (struct sockaddr_in*)p;
	while(1){
		printf("addr2:%s\n",inet_ntoa(addr->sin_addr));
		sleep(2);
	}
	return NULL;
}
int main()
{
	
 	struct sockaddr_in addr1;
 	struct sockaddr_in addr2;
 	addr1.sin_addr.s_addr = 0;
 	addr2.sin_addr.s_addr = 0xffffffff;

	pthread_t tid1;
	pthread_t tid2;
	pthread_create(&tid1,NULL,fun1,&addr1);
	pthread_create(&tid2,NULL,fun2,&addr2);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	return 0;
}

// int main()
// {
// 	struct sockaddr_in addr1;
// 	struct sockaddr_in addr2;
// 	addr1.sin_addr.s_addr = 0;
// 	addr2.sin_addr.s_addr = 0xffffffff;
// 	char *p1 = inet_ntoa(addr1.sin_addr);
// 	char *p2 = inet_ntoa(addr2.sin_addr);
// 
// 	printf("p1:%s,p2:%s\n",p1,p2);
// 	//inet_ntoa函数,是把返回的结果放到了静态存储区
// 
// 	return 0;
// }
