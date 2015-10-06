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
#include <pthread.h>
int listenfd = 0, connfd = 0;
char sendbuff[50];
char recvbuff[50];


void *send_mssg(void *arg)
{
while(1)
{
fgets(sendbuff,sizeof(sendbuff)-1,stdin);
int n=send(connfd,sendbuff,sizeof(sendbuff),0);

//printf("%s",sendbuff);
}
}



void *recv_mssg(void *arg)
{
while(1)
{
int n=recv(connfd,recvbuff,sizeof(recvbuff),0);
if(n==0)
{
pthread_exit(NULL);
}
printf("%s",recvbuff);

}
}




int main(int argc, char *argv[]){



struct sockaddr_in serv_addr;
memset(&serv_addr, '0', sizeof(serv_addr));
//int a=5;


listenfd = socket(AF_INET, SOCK_STREAM, 0);

 
//filing out server info 
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
serv_addr.sin_port = htons(5000); 
//done

bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

listen(listenfd, 10); 

connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
//fflush(stdin);
int thrd1_id,thrd2_id;

pthread_t thrd1,thrd2;


thrd1_id=pthread_create(&thrd1,NULL,send_mssg,NULL);

thrd2_id=pthread_create(&thrd2,NULL,recv_mssg,NULL);



pthread_exit(NULL);
}//main
