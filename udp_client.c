#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char* argv[])
{
	int socketfd = socket(AF_INET,SOCK_DGRAM,0);
	printf("socketfd = %d\n",socketfd);

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	server.sin_addr.s_addr = inet_addr(argv[1]);

	char buf[1024];
	//struct sockaddr_in peer;
	while(1){
	//	socklen_t len = sizeof(peer);
		printf("please enter#");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf)-1);

		if(s > 0){
			buf[s - 1] = 0;
			sendto(socketfd,buf,strlen(buf),0,(struct sockaddr*)&server,sizeof(server));

			//ssize_t _s = recvfrom(socketfd,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
			ssize_t _s = recvfrom(socketfd,buf,sizeof(buf)-1,0,NULL,NULL);//加入不关心源主机的IP和端口,这里填NULL即可
			if(_s > 0){
				buf[_s] = 0;
				printf("server echo## %s\n",buf);
			}
		}

	}
	
	return 0;
}

