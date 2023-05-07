  1 #include<stdio.h>
  2 #include<ctype.h>
  3 #include<sys/socket.h>
  4 #include<arpa/inet.h>
  5 #include<stdlib.h>
  6 #include<string.h>
  7 #include<unistd.h>
  8 #include<errno.h>
  9 #include<pthread.h>
 10 
 11 #define SERV_PORT 9527
 12 
 13 void sys_err(const char * str)
 14 {
 15     perror(str);
 16     exit(1);
 17 }
 18 
 19 int main(int argc,char *argv[])
 20 {
 21     int cfd;
 22     int conter=10;
 23     char buf[BUFSIZ];
 24 
 25     struct sockaddr_in serv_addr;
 26     serv_addr.sin_family=AF_INET;
 27     serv_addr.sin_port=htons(SERV_PORT);
 28     inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr.s_addr);
 29     cfd=socket(AF_INET,SOCK_STREAM,0);
 30     if(cfd==-1)
 31         sys_err("socket error");
 32     int ret=connect(cfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
 33     if(ret!=0)
 34         sys_err("connect error");
 35     while(--conter){
 36         write(cfd,"hello\n",6);
 37         ret=read(cfd,buf,sizeof(buf));
 38         write(STDOUT_FILENO,buf,ret);
 39         sleep(1);
 40     }
 41     close(cfd);
 42 
 43     return 0;
 44 }
