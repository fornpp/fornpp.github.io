#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>

#include <netdb.h>
#include <arpa/inet.h>

int main()
{
int s;

struct sockaddr_in sadd;
char sendBuffer[1000],recvBuffer[1000];

pid_t cpid;

bzero(&sadd,sizeof(sadd));

sadd.sin_family=AF_INET;
sadd.sin_addr.s_addr=inet_addr("127.0.0.1");
sadd.sin_port=htons(5501);


s=socket(AF_INET,SOCK_STREAM,0);


connect(s,(struct sockaddr*)&sadd,sizeof(sadd));


cpid=fork();
if(cpid==0)
{
while(1)
{
bzero(&sendBuffer,sizeof(sendBuffer));
printf("\nType a message here ...  ");

fgets(sendBuffer,10000,stdin);

send(s,sendBuffer,strlen(sendBuffer)+1,0);
printf("\nMessage sent !\n");
}
}
else
{
while(1)
{
bzero(&recvBuffer,sizeof(recvBuffer));

recv(s,recvBuffer,sizeof(recvBuffer),0);
printf("\nSERVER : %s\n",recvBuffer);
}
}
return 0;
}
