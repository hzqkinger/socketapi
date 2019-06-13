#include<stdio.h>

#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
	int ret = htons(1);//网络字节序是按大端存储的
	printf("%d\n",ret);

	ret = ntohs(1);//网络字节序是按大端存储的
	printf("%d\n",ret);
	return 0;
}

//不管主机是大端机还是小端机，都会按照这个tcp/ip规定的网络字节序来发送/接收数据
//
//     #include<arpa/inet.h>
// uint32_t htonl(uint32_t hostlong);
// uint32_t htons(uint32_t hostshort);
// uint32_t ntohl(uint32_t netlong);
// uint32_t ntohs(uint32_t netshort);
