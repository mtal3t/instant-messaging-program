#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
//#include <time.h> 
#include <pthread.h>
#include <poll.h>
char sendbuff[50];
char recvbuff[50];
int  connfd=0;

//sending message "thread" code
void *send_mssg(void *arg)
{
while(1)
{
fgets(sendbuff,sizeof(sendbuff)-1,stdin);

int n=send(connfd,sendbuff,sizeof(sendbuff),0);
if(n==0)
{
pthread_exit(NULL);
}
}
}

//receving message "thread" code
void *recv_mssg(void *arg)
{
while(1)
{

int n=recv(connfd,recvbuff,sizeof(recvbuff),0);

if(n==0)
{
//close(connfd);
pthread_exit(NULL);
}
printf(">> %s",recvbuff);
}
}


int listenfd = 0;
int main(int argc, char *argv[]){



struct sockaddr_in serv_addr; 
memset(&serv_addr, '0', sizeof(serv_addr));

listenfd = socket(AF_INET, SOCK_STREAM, 0);

 
//filing out server info 
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
serv_addr.sin_port = htons(5000); 
//done

bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

listen(listenfd, 10); 

connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);//this waits for a connection and then and then accept and control goes on 


int send_mssg_id,recv_mssg_id;


pthread_t send_mssg_thrd,recv_mssg_thrd;

// creating threads
send_mssg_id=pthread_create(&send_mssg_thrd,NULL,send_mssg,NULL);

recv_mssg_id=pthread_create(&recv_mssg_thrd,NULL,recv_mssg,NULL);

//dont let main exit before before threads do 
pthread_exit(NULL);


}//main
