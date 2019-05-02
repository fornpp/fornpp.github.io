#include <stdio.h>
#include "netinet/in.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/socket.h"
int main(int argc, char const *argv[]) {
  int s=socket(AF_INET,SOCK_DGRAM,0);
  struct sockaddr_in saddr;
  saddr.sin_family=AF_INET;
  saddr.sin_addr.s_addr=htonl(INADDR_ANY);
  saddr.sin_port=htons(6565);
  socklen_t slen=sizeof(saddr);
  bind(s,(struct sockaddr*)&saddr,slen);
  listen(s,1);
  while(1){
    char b[1024];
    recvfrom(s,b,sizeof(b),0,(struct sockaddr*)&saddr,&slen);
    printf("Message received:%s\n",b);
  }
  close(s);
  return 0;
}
