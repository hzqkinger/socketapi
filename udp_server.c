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

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(argv[2]));
	local.sin_addr.s_addr = inet_addr(argv[1]);

	int ret = bind(socketfd,(struct sockaddr*)&local,sizeof(local));

	char buf[1024];
	struct sockaddr_in client;
	while(1){
		socklen_t len = sizeof(client);
		ssize_t s = recvfrom(socketfd,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&len);

		if(s > 0){
			buf[s] = '\0';
			printf("[%s:%d]:%s\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port),buf);

			sendto(socketfd,buf,strlen(buf),0,(struct sockaddr*)&client,sizeof(client));
		}
	}
	
	return 0;
}
