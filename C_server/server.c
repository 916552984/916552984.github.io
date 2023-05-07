  1 #include "warp.h"
  2 void sys_err(const char * str)
  3 {
  4     perror(str);
  5     exit(1);
  6 }
  7 
  8 int main(int argc,char *argv[])
  9 {
 10     int lfd = 0,cfd=0;
 11     int ret,i;
 12     char buf[BUFSIZ],client_IP[1024];
 13 
 14     struct sockaddr_in serv_addr,clit_addr;
 15     socklen_t clit_addr_len;
 16 
 17     serv_addr.sin_family=AF_INET;
 18     serv_addr.sin_port=htons(SERV_PORT);
 19     serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
 20 
 21     lfd = Socket(AF_INET,SOCK_STREAM,0);
 22     /*if( lfd ==-1 ){
 23         sys_err("socket error");
 24     }*/
 25     bind(lfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
 26 
 27     listen(lfd,128);
 28 
 29     clit_addr_len=sizeof(clit_addr);
 30 
 31     cfd=accept(lfd,(struct sockaddr *)&clit_addr,&clit_addr_len);
 32     if(cfd==-1)
 33         sys_err("accept error");
 34     printf("client ip:%s port:%d\n",
 35     inet_ntop(AF_INET,&clit_addr.sin_addr.s_addr,client_IP,sizeof(client_IP))
 36     ,ntohs(clit_addr.sin_port));
 37     while(1){
 38         ret=read(cfd,buf,sizeof(buf));
 39         write(STDOUT_FILENO,buf,ret);
 40 
 41         for(i=0;i<ret;i++)
 42             buf[i]=toupper(buf[i]);
 43 
 44         write(cfd,buf,ret);
 45     }
 46     close(lfd);
 47     close(cfd);
 48     return 0;
 49 }

