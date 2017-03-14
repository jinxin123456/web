/*
*author:jinxin
*date:2017-1-5
*client.cpp
*/
#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")

void Sinput1();
void Sinput2();

struct input
{
	int mata[50][50];
	int matb[50][50];
	int ar;
	int ac;
	int br;
	int bc;
};
struct result
{
	int matres[50][50];
};

result result;
input input;
int ar,ac,br,bc,i,j,k;
char buff[1024];

int main()
{ 
	printf("请输入服务器IP地址，若服务器客户端在一台机子上，填本机IP或者127.0.0.1:\n");
	scanf("%s",&buff);
	WSADATA wsa; 
	SOCKET sockFD; 

	WSAStartup(MAKEWORD(2,2),&wsa); 
	sockFD = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); 
	struct sockaddr_in server; 
	server.sin_family = AF_INET; 
	server.sin_port = htons(9000); 
	server.sin_addr.s_addr=inet_addr(buff); 

	int err=connect(sockFD,(struct sockaddr *)&server,sizeof(server)); 

	if (err <0)
	{
		printf("\r\n连接错误");
		return -1;
	}
	else
	{
		Sinput1();
		Sinput2();
		send(sockFD,(char*)&input,sizeof(input),0);
	}
    
	recv(sockFD,(char*)&result,sizeof(result),0); 
	
	printf("得到运算结果:");
	for(i=0;i<input.ar;i++)
	{
		printf("\n");
		for(j=0;j<input.bc;j++)
		{
			printf("%d  ",result.matres[i][j]);
		}
	}
	printf("\n");
	system("pause");
	closesocket(sockFD); 
	WSACleanup();

	return 0; 
}



void Sinput1()
{
	printf("请输入第一个矩阵的行数列数，如2 2\n");
	scanf("%d%d",&input.ar,&input.ac);//接受矩阵a的行列值
	printf("请输入第一个矩阵\n");		
	for(i=0;i<input.ar;i++)
		for(j=0;j<input.ac;j++)
			scanf("%d",&input.mata[i][j]);
}	


void Sinput2()
{
	printf("请输入第二个矩阵的行数列数\n");		
	scanf("%d%d",&input.br,&input.bc);////接受矩阵b的行列值
	printf("请输入第二个矩阵\n");	
	for(i=0;i<input.br;i++)
		for(j=0;j<input.bc;j++)
			scanf("%d",&input.matb[i][j]);
}




