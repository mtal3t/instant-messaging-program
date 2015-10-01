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

int main(int argc, char *argv[])
{
int sockfd = 0;
//char sendBuff[10];
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
for(i=0;i<6;i++){
int a=0;
int n=recv(sockfd,&a,sizeof(a),0);

printf("%d \n",a);

a++;

printf("%d \n",a);

int c =send(sockfd,&a,sizeof(a),0);

}

} //main
