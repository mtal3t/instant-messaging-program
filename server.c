#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char *argv[]){

int listenfd = 0, connfd = 0;

struct sockaddr_in serv_addr;
memset(&serv_addr, '0', sizeof(serv_addr));
int a=5;
//char sendBuff[10];
//memset(sendBuff, '0', sizeof(sendBuff));

listenfd = socket(AF_INET, SOCK_STREAM, 0);

 
//filing out server info 
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
serv_addr.sin_port = htons(5000); 
//done

bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

listen(listenfd, 10); 

connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
int i=0;
for(i=0;i<6;i++){
//sendBuff[10]="mohammed";
int n=send(connfd,&a,sizeof(a),0);
int c=recv(connfd,&a,sizeof(a),0);
//printf("%d\n",a);

}





}//main
