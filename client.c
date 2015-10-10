#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <poll.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <pthread.h>

char sendbuff[50];
char recvbuff[50];
int sockfd=0;


//sending message "thread" code
void *send_mssg(void *arg)
{
while(1)
{
fgets(sendbuff,sizeof(sendbuff)-1,stdin);
int n=send(sockfd,sendbuff,sizeof(sendbuff),0);
if(n==0)
{
pthread_exit(NULL);
}
//printf("%s",sendbuff);
}
}


//receving message "thread" code
void *recv_mssg(void *arg)
{
while(1)
{
//memset(recvbuff,0,sizeof(recvbuff));
int n=recv(sockfd,recvbuff,sizeof(recvbuff),0);
if(n==0)
{
//close(sockfd);
pthread_exit(NULL);
}
printf(">>%s",recvbuff);
}
}




int main(int argc, char *argv[])
{

struct sockaddr_in serv_addr;
int i;

if(argc != 2)
{
    printf("\n Usage: %s <ip of server> \n",argv[0]);
    return 1;
} 

if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
{
    printf("\n Error : Could not create socket \n");
    return 1;
} 

memset(&serv_addr, '0', sizeof(serv_addr)); 

serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(5000); 

if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
{
    printf("\n inet_pton error occured\n");
    return 1;
} 

if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
{
   printf("\n Error : Connect Failed \n");
   return 1;
}

int send_mssg_id,recv_mssg_id; 


pthread_t send_mssg_thrd,recv_mssg_thrd;


send_mssg_id=pthread_create(&send_mssg_thrd,NULL,send_mssg,NULL);

recv_mssg_id=pthread_create(&recv_mssg_thrd,NULL,recv_mssg,NULL);


pthread_exit(NULL);

} //main
