#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
int client,server;
char buffer[1024];
struct sockaddr_in servaddr,clientaddr;
client=socket(AF_INET,SOCK_STREAM,0);
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=htons(8000);
connect(client,(struct sockaddr*)&servaddr,sizeof(servaddr));
printf("enter data:");
fgets(buffer,sizeof(buffer),stdin);
send(client,buffer,sizeof(buffer),0);
recv(client,buffer,sizeof(buffer),0);
printf("Data received:%s",buffer);
close(client);

}

