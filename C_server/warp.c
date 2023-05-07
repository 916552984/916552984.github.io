  1 #include "warp.h"
  2 
  3 void sys_err(const char *str)
  4 {
  5     perror(str);
  6     exit(1);
  7 }
  8 
  9 int Socket(int domain, int type, int protocol)
 10 {
 11     int n=socket(domain,type,protocol);
 12     if(n==-1)
 13     {
 14         sys_err("socket error");
 15         //return n;
 16     }
 17     return n;
 18 }
    