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
	printf("�����������IP��ַ�����������ͻ�����һ̨�����ϣ����IP����127.0.0.1:\n");
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
		printf("\r\n���Ӵ���");
		return -1;
	}
	else
	{
		Sinput1();
		Sinput2();
		send(sockFD,(char*)&input,sizeof(input),0);
	}
    
	recv(sockFD,(char*)&result,sizeof(result),0); 
	
	printf("�õ�������:");
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
	printf("�������һ�������������������2 2\n");
	scanf("%d%d",&input.ar,&input.ac);//���ܾ���a������ֵ
	printf("�������һ������\n");		
	for(i=0;i<input.ar;i++)
		for(j=0;j<input.ac;j++)
			scanf("%d",&input.mata[i][j]);
}	


void Sinput2()
{
	printf("������ڶ����������������\n");		
	scanf("%d%d",&input.br,&input.bc);////���ܾ���b������ֵ
	printf("������ڶ�������\n");	
	for(i=0;i<input.br;i++)
		for(j=0;j<input.bc;j++)
			scanf("%d",&input.matb[i][j]);
}




