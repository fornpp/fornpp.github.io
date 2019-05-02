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
    FILE *fp;
    socklen_t slen=sizeof(sadd);
    sadd.sin_family=AF_INET;
    sadd.sin_addr.s_addr=htonl(INADDR_ANY);
    sadd.sin_port=htons(6969);
    bind(s,(struct sockaddr*)&sadd , slen);
    listen(s,1);
    struct sockaddr_in cadd;
    socklen_t clen=sizeof(cadd);
    int a=accept(s,(struct sockaddr*)&cadd , &clen);
    char buff[10240];
    recv(a,buff,sizeof(buff),0);
    char *command=(char*)malloc(sizeof(buff)+10);
    command[0]='\0';
    strcat(command,buff);
    strcat(command,"> file.txt");
    system(command);
    fp=fopen("file.txt","r");
    char* file;
    fseek(fp,0,SEEK_END);
    long sz=ftell(fp);
    fseek(fp,0,SEEK_SET);
    file=(char*)malloc(sz+1);
    fread(file,1,sz,fp);
    printf("%d\n",(int)send(a,file,sz,0));
    printf("Data sent!\n");
    close(s);
    return 0;
}
