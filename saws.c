#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

void main() {
    int k=4,m=1,p,sockfd,clisd,n;
    char  buffer[10];
    struct sockaddr_in servaddr,clientaddr;
    socklen_t clilen;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(8000);
    
    bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    listen(sockfd,5);
    clilen=sizeof(clientaddr);
    clisd=accept(sockfd,(struct sockaddr*)&clientaddr,&clilen);
    while(k!=0){
      n=recv(clisd,buffer,sizeof(buffer),0);
      if (n==-1){
        printf("error receiving data\n");
      }
      if(strcmp(buffer,"frame")==0){
        printf("frame received successfully\n");
      }
      else
        printf("frame not received\n");
      
      if(m%2==0){
        strcpy(buffer,"ack");
        
      }
      else{
        printf("ack lost\n");
        for(p=1;p<=3;p++){
          printf("waiting for %d seconds\n",p);
          sleep(1);
        }
        strcpy(buffer,"ack");
      }
      int z=send(clisd,buffer,sizeof(buffer),0);
      if (z==-1){
      printf("error sending ack");
      exit(1);
      
      }
      else{
        printf("sending ack %d ...",m);
      }
      k--;
      m++;
    }
    close(clisd);
    
}
