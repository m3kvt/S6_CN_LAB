#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<netdb.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(){
  int client;
  socklen_t length;
  char servmsg[1000],climsg[1000];
  struct sockaddr_in servaddr,clientaddr;
  client=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=INADDR_ANY;
  servaddr.sin_port=htons(8000);
  
  printf("enter message to server:");
  fgets(climsg,sizeof(climsg),stdin);
  sendto(client,climsg,sizeof(climsg),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
  printf("Message received from server");
  length=sizeof(servaddr);
  if (recvfrom(client,servmsg,sizeof(servmsg),0,(struct sockaddr *)&servaddr,&length)<0){
    printf("Error");
    exit(1);
  }
  printf("Message from server: %s",servmsg);
  close(client);

}
