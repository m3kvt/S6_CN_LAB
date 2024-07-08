#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>

int main(){
  int clisd,n;
  FILE *fp;
  char name[100],fname[100],rcvmsg[100];
  struct sockaddr_in servaddr,clientaddr;
  clisd=socket(AF_INET,SOCK_STREAM,0);
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(8000);
  servaddr.sin_addr.s_addr=INADDR_ANY;
  if(connect(clisd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
    printf("error");
    exit(1);
  }
  printf("connected");
  printf("enter the file to send");
  scanf("%s",name);
  printf("enter the file to write");
  scanf("%s",fname);
  send(clisd,name,sizeof(name),0);
  fp=fopen(fname,"w");
  while(1){
    n=recv(clisd,rcvmsg,sizeof(rcvmsg),0);
    rcvmsg[n]='\0';
    if(strcmp(rcvmsg,"error")==0){
      printf("can't read file");
    }
    else if(strcmp(rcvmsg,"completed")==0){
      printf("completed");
      fclose(fp);
      close(clisd);
      break;
    }
    else{
      fputs(rcvmsg,stdout);
      
      }
      fprintf(fp,"%s",rcvmsg);
      printf("\n");
    
  }

}
