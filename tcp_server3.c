#include<stdio.h>
#include<pthread.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>

void ProcessRequest(int client_fd,struct sockaddr_in *client_addr)
{
	char buf[1024];
	while(1){
		memset(buf,'\0',sizeof(buf));

		ssize_t read_size = read(client_fd,buf,sizeof(buf));
		if(read_size < 0){
			perror("read");
			continue;
		}else if(read_size == 0){
			printf("client:%s say bye bye!\n",inet_ntoa(client_addr->sin_addr));
			close(client_fd);
			break;
		}
		buf[read_size] = '\0';
		printf("client %s say:%s \n",inet_ntoa(client_addr->sin_addr),buf);
		write(client_fd,buf,strlen(buf));
	}
	return;
}

typedef struct Arg{
	int fd;
	struct sockaddr_in addr;
}Arg;
void* CreateWork(void *ptr)
{
	Arg *arg = (Arg*)ptr;
	ProcessRequest(arg->fd,&arg->addr);
	free(arg);
	return NULL;
}

int main()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)return 1;

	struct sockaddr_in server_sock;
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

	while(1){
		struct sockaddr_in client_addr;
		socklen_t len = 0;
		int cli_sock = accept(sockfd,(struct sockaddr*)&client_addr,&len);//一直在这里接收新客户端
		if(cli_sock < 0){
			printf("accept error");
			continue;
		}

		pthread_t tid;
		Arg *arg = (Arg*)malloc(sizeof(arg));
		arg->fd = cli_sock;
		arg->addr = client_addr;
		pthread_create(&tid,NULL,CreateWork,(void*)arg);
		pthread_detach(tid);
	}

	return 0;
}


