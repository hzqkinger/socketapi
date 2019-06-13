#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>

int main(int argc,char* argv[])
{
	int socketfd = socket(AF_INET,SOCK_DGRAM,0);
	printf("socketfd = %d\n",socketfd);

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = htonl(atoi(argv[2]));
	local.sin_port = inet_addr(argv[1]);

	int ret = bind(socketfd,(struct sockaddr*)&local,sizeof(local));
//	printf("domain = %d,ip address = 0x%x,port = %d\n",local.sin_family,local.sin_addr.s_addr,local.sin_port);
//	printf("ret = %d\n",ret);


//	struct sockaddr_in local2;
//	socklen_t addrlen;
//	int ret2 = getsockname(socketfd,(struct sockaddr*)&local2,&addrlen);
//
//	printf("domain = %d,ip address = 0x%x,port = %d\n",local2.sin_family,local2.sin_addr.s_addr,local2.sin_port);
//	printf("ret2 = %d   socklen = %d\n",ret2,addrlen);

	return 0;
}





// #include<fcntl.h>
// #include<sys/stat.h>
// int main()
// {
//  	int socketfd1 = socket(AF_INET,SOCK_DGRAM,0);
//  	int socketfd2 = socket(AF_INET,SOCK_DGRAM,0);
//  	int socketfd3 = socket(AF_INET,SOCK_DGRAM,0);
//  	int socketfd4 = socket(AF_INET,SOCK_DGRAM,0);
//  	printf("%d\n",socketfd1);
//  	printf("%d\n",socketfd2);
//  	printf("%d\n",socketfd3);
//  	printf("%d\n",socketfd4);
// 
// 	printf("\n\n");
// 	int filefd1 = open("day26.txt",O_RDWR | O_CREAT,0664);
// 	int filefd2 = open("day27.txt",O_RDWR | O_CREAT,0664);
// 	int filefd3 = open("day28.txt",O_RDWR | O_CREAT,0664);
// 	printf("%d\n",filefd1);
// 	printf("%d\n",filefd2);
// 	printf("%d\n",filefd3);
// 	//getsockname(socketfd,NULL,0);
// 	return 0;
// }
