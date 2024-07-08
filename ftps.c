#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>

int main(){
  FILE *fp;
  int sockfd,clisd,clilen,n;
  char rcv[100],fileread[100];
  struct sockaddr_in servaddr,clientaddr;
  
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  if (sockfd<0){
    printf("error creating socket");
  }
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(8000);
  servaddr.sin_addr.s_addr=INADDR_ANY;
  if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
    printf("error binding");
    exit(1);
  }
  listen(sockfd,5);
  clilen=sizeof(clientaddr);
  clisd=accept(sockfd,(struct sockaddr*)&clientaddr,&clilen);
  n=recv(clisd,rcv,sizeof(rcv),0);
  rcv[n]='\0';
  fp=fopen(rcv,"r");
  if(fp==NULL){
    send(clisd,"error",5,0);
    close(clisd);
  }
  else{
    while(fgets(fileread,sizeof(fileread),fp)){
      if(send(clisd,fileread,sizeof(fileread),0)<0){
        printf("error sending");
        sleep(1);
        
      }
      
    }
    if (!fgets(fileread,sizeof(fileread),fp)){
      send(clisd,"completed",9,0);
      exit(0);
    }
    
  }

}
