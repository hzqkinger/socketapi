#include<stdio.h>
#include<arpa/inet.h>


int main()
{
//	struct sockaddr_in local;
//   	local.sin_addr.s_addr = inet_addr("192.168.10.15");
//	printf("0x%x\n",local.sin_addr.s_addr);
//	
//	inet_aton("192.168.12.16",&local.sin_addr);
//	printf("0x%x\n",local.sin_addr.s_addr);
//
//
//	printf("sin_addr: %s\n",inet_ntoa(local.sin_addr));

	int ret = inet_addr("127.0.0.1");
	printf("%d\n",ret);

	inet_aton("127.0.0.1",(struct in_addr*)&ret);
	printf("%d\n",ret);

	return 0;
}
