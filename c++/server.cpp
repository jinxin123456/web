/*
*author: jinxin
*date:2016-11-25
*server.cpp
*/
#include <malloc.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#pragma comment(lib,"ws2_32.lib")

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

input input;
result result;
int matres[100][100],i,j,k;


int main() 
{   
	WSADATA wsa; 
	SOCKET listenFD; 
	WSAStartup(MAKEWORD(2,2),&wsa);            

	listenFD = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); 
	struct sockaddr_in server; 
	server.sin_family = AF_INET; 
	server.sin_port = htons(9000); 
	server.sin_addr.s_addr=ADDR_ANY; 

	bind(listenFD,(sockaddr *)&server,sizeof(server)); 
	listen(listenFD,2); 
	printf("服务器端启动。。。\n等待数据。。。\n");

	int iAddrSize = sizeof(server); 
	
	while(1)
	{
	SOCKET clientFD=accept(listenFD,(sockaddr *)&server,&iAddrSize); 
	printf("\n请求运算。。。");
		
	recv(clientFD,(char*)&input,sizeof(input),0); 
	printf("\n矩阵一:");
	for(i=0;i<input.ar;i++)
	{
		printf("\n");
		for(j=0;j<input.ac;j++)
		{
			printf("%d  ",input.mata[i][j]);
		}
	}
	printf("\n矩阵二:");
	for(i=0;i<input.br;i++)
	{
		printf("\n");
		for(j=0;j<input.bc;j++)
		{
			printf("%d  ",input.matb[i][j]);
		}
	}
    printf("\n正在计算。。。");
	printf("\n");
	printf("得到计算矩阵：\n");

	for(i=0;i<input.ar;i++)
	{
		for(j=0;j<input.bc;j++)
		{
			for(k=0;k<input.ac;k++)
			{
				matres[i][j]+=input.mata[i][k]*input.matb[k][j];
			}
			printf("%d ",matres[i][j]);
		}
		printf("\n");
	}
    for(i=0;i<input.ar;i++)
	{
		for(j=0;j<input.ac;j++)
		{
			result.matres[i][j]=matres[i][j];
		}
	}
	printf("\n返回计算结果。。。");
	send(clientFD,(char*)&result,sizeof(result),0);
	}
	WSACleanup(); 
	return 0; 

}

