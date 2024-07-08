#include<stdio.h>
struct router{
  unsigned cost[20];
  unsigned from[20];
}rt[10];
int main(){
  int routers,costmat[20][20],i,j,k,shortestpath;
  printf("enter the no of routers:");
  scanf("%d",&routers);
  printf("enter the cost matrix:");
  for  (i=0;i<routers;i++){
    for(j=0;j<routers;j++){
      scanf("%d",&costmat[i][j]);
      costmat[i][i]=0;
      rt[i].cost[j]=costmat[i][j];
      rt[i].from[j]=j;
    }
  }
  do{
    for(i=0;i<routers;i++){
      for(j=0;j<routers;j++){
        for(k=0;k<routers;k++){
          if(rt[i].cost[j]>costmat[i][k]+rt[k].cost[j]){
            rt[i].cost[j]=rt[i].cost[k]+rt[k].cost[j];
            shortestpath=1;
            rt[i].from[j]=k;
          }
        }
      }}
  }while(shortestpath!=0);
  for(i=0;i<routers;i++){
    printf("For router %d\n",i+1);
    for(j=0;j<routers;j++){
     printf("Router %d via %d distance %d\n",j+1,rt[i].from[j]+1,rt[i].cost[j]);
    }}
}
