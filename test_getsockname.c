/*************************************************************************
    > File Name: test_getsockname.c
    > Author: 黄志强
    > Mail: 2069085311@qq.com 
    > Created Time: 2019年05月17日 星期五 17时20分50秒
 ************************************************************************/
//好像有问题，没有得到想要的结果

#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>

int main()
{
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = inet_addr("127.0.0.1");
	local.sin_port = htons(8080);

	int localSockfd = socket(AF_INET,SOCK_STREAM,0);
	bind(localSockfd,(struct sockaddr*)&local,sizeof(local));

	struct sockaddr_in here;
	socklen_t hereLen;
	getsockname(localSockfd,(struct sockaddr*)&here,&hereLen);

	printf("Family:\t%d\t%d\n",AF_INET,here.sin_family);
	printf("IP:\t%s\n",inet_ntoa(here.sin_addr));
	printf("Port:\t%d\n",ntohs(here.sin_port));
	return 0;
}
