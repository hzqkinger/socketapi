#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

int main()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)return 1;

	struct sockaddr_in server_sock;
	struct sockaddr_in client_sock;
	server_sock.sin_family = AF_INET;
	server_sock.sin_addr.s_addr = htonl(INADDR_ANY);
	server_sock.sin_port = htons(9999);
	if(bind(sockfd,(struct sockaddr*)&server_sock,sizeof(server_sock)) < 0){
		close(sockfd);
		return 2;
	}

	if(listen(sockfd,5) < 0){
		close(sockfd);
		return 3;
	}

	printf("bind and listen sucess,wait accept...\n");

	socklen_t len = 0;
	int cli_sock = accept(sockfd,(struct sockaddr*)&client_sock,&len);
	if(cli_sock < 0){
		close(sockfd);
		return 4;
	}
	printf("11111111\n");

	char buf_ip[INET_ADDRSTRLEN];
	memset(buf_ip,'\0',sizeof(buf_ip));
	inet_ntop(AF_INET,&client_sock.sin_addr,buf_ip,sizeof(buf_ip));
	printf("get connect,ip is:%s port is:%d\n",buf_ip,ntohs(client_sock.sin_port));

	while(1){
		char buf[1024];
		memset(buf,'\0',sizeof(buf));
		read(cli_sock,buf,sizeof(buf));
		printf("client:#%s\n",buf);

		printf("server:$");
		memset(buf,'\0',sizeof(buf));
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf)-1] = '\0';

		write(cli_sock,buf,strlen(buf)+1);
		printf("please wait..\n");
	}
	close(sockfd);
		
	return 0;
}
