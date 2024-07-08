#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>

int main(){
  int server,client,len;
  char buffer[1024];
  struct sockaddr_in servaddr,clientaddr;
  server=socket(AF_INET,SOCK_STREAM,0);
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
  servaddr.sin_port=htons(8000);
  bind(server,(struct sockaddr*)&servaddr,sizeof(servaddr));
  if (listen(server,5)==0)
    printf("Listening\n");
  else
    printf("error");
    len=sizeof(clientaddr);
  client=accept(server,(struct sockaddr*)&clientaddr,&len);
  recv(client,buffer,sizeof(buffer),0);
  printf("Message from client: %s",buffer);
  strcpy(buffer,"MESSAGE RECEIVED");
  send(client,buffer,16,0);
  close(client);
  close(server);
}




