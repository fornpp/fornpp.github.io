#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
int main(int argc, char const *argv[]) {
    int s=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in sadd;
    socklen_t slen=sizeof(sadd);
    sadd.sin_family=AF_INET;
    sadd.sin_addr.s_addr=inet_addr("127.0.0.1");
    sadd.sin_port=htons(6969);
    connect(s,(struct sockaddr*)&sadd,slen);
    char buff[1024];
    printf("Enter cmd line:\n");
    scanf("%[^\n]s",buff);
    send(s,buff,sizeof(buff),0);
    char file[10240];
    recv(s,file,sizeof(file),0);
    printf("%s\n",file);
    close(s);
  return 0;
}