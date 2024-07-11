#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<netdb.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(){
  int server;
  struct sockaddr_in servaddr,clientaddr;
  socklen_t length;
  char servmsg[1000],climsg[1000];
  server=socket(AF_INET,SOCK_DGRAM,0);
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=INADDR_ANY;
  servaddr.sin_port=htons(8000);
  if(bind(server,(struct sockaddr *)&servaddr,sizeof(servaddr))<0){
    printf("Error");
    exit(1);
  }
  printf("Binding");
  printf("Listening");
  length=sizeof(clientaddr);
  if (recvfrom(server,climsg,sizeof(climsg),0,(struct sockaddr *)&clientaddr,&length)<0){
    printf("ERROR");
    exit(1);
  }
  printf("Message from client: %s",climsg);
  printf("Enter message to client:");
  fgets(servmsg,sizeof(servmsg),stdin);
  sendto(server,servmsg,sizeof(servmsg),0,(struct sockaddr *)&clientaddr,sizeof(clientaddr));
  printf("Message sent to client");
  
   close(server);
}
