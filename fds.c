#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int main(int argc,char *argv[])
{
int c,s;

struct sockaddr_in sadd,cadd;
socklen_t clen;

char recvBuffer[1000],sendBuffer[1000];
pid_t cpid;
bzero(&sadd,sizeof(sadd));

sadd.sin_family=AF_INET;
sadd.sin_addr.s_addr=htonl(INADDR_ANY);
sadd.sin_port=htons(5501);

s=socket(AF_INET,SOCK_STREAM,0);

bind(s,(struct sockaddr*)&sadd,sizeof(sadd));


listen(s,5);
printf("%s\n","Server is running ...");


c=accept(s,(struct sockaddr*)&cadd,&clen);

cpid=fork();

if(cpid==0)
{
while(1)
{
bzero(&recvBuffer,sizeof(recvBuffer));

recv(c,recvBuffer,sizeof(recvBuffer),0);
printf("\nCLIENT : %s\n",recvBuffer);
}
}
else
{
while(1)
{

bzero(&sendBuffer,sizeof(sendBuffer));
printf("\nType a message here ...  ");

fgets(sendBuffer,10000,stdin);

send(c,sendBuffer,strlen(sendBuffer)+1,0);
printf("\nMessage sent !\n");
}
}
return 0;
}
