#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
int main(int argc, char const *argv[]) {
  int s=socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in sadd;
  sadd.sin_family = AF_INET;
  sadd.sin_addr.s_addr = htonl(INADDR_ANY);
  sadd.sin_port = htons(8080);
  socklen_t slen=sizeof(sadd);
  bind(s,(struct sockaddr*) &sadd , slen);
  printf("Server connected!\n");
  listen(s,1);
  struct sockaddr_in cadd;
  socklen_t clen=sizeof(cadd);
  int a=accept(s,(struct sockaddr*) &cadd,&clen);
  printf("Client Connected!\n");
  while(1){
      char b[1024];
      recv(a,b,sizeof(b),0);
      printf("%s",b);
      fgets(b,sizeof(b),stdin);
      send(a,b,sizeof(b),0);
  }
  close(s);
  return 0;
}
