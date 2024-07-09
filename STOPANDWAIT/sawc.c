#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

void main() {
    int k=4,m=1,p,clisd,n,y;
    char  buffer[10];
    struct sockaddr_in servaddr,clientaddr;
    clisd=socket(AF_INET,SOCK_STREAM,0);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(8000);
    y=connect(clisd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    if(y==-1){
      printf("error connecting\n");
      exit(1);
    }
    while(k!=0){
      if (m<5){
        printf("SENDING %d ..\n",m);
      }
      if(m%2==0){
        strcpy(buffer,"frame");
      }
      else{
      printf("Packet loss\n");
        for(p=1;p<=3;p++){
          printf("Waiting for %d seconds..\n",p);
          sleep(1);
          
        }
        strcpy(buffer,"frame");
        printf("retransmitting\n");
      }
      int z=send(clisd,buffer,sizeof(buffer),0);
      if(z==-1){
        printf("error sending\n");
        exit(1);
      }
      int x=recv(clisd,buffer,sizeof(buffer),0);
      if(x==-1){
        printf("error in receiving ack\n");
        exit(1);
      }
      if (strcmp(buffer,"ack")==0){
        printf("acknowledgement received for %d\n",m);
        
      }
      else{
        printf("ack not received\n");
      }
      k--;
      m++;
      
      
    }
    
}
