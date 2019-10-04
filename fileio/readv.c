#include <sys/uio.h>
#include <stdio.h>

int main(){
  int i;
  ssize_t n;
  char buf1[5], buf2[10], buf3[15];
  struct iovec vector[3];

  vector[0].iov_base = buf1;
  vector[0].iov_len = sizeof buf1;
  
  vector[1].iov_base = buf2;
  vector[1].iov_len = sizeof buf2;

  vector[2].iov_base = buf3;
  vector[2].iov_len = sizeof buf3;

  if((n = readv(0, vector, 3)) < 0){
    perror("readv");
    return 1;
  }
  
  for(i=0;i<3;i++){
    if((size_t)n < vector[i].iov_len){
      vector[i].iov_len = n;
    }
    n -= vector[i].iov_len;
    printf("buf%d[] = %.*s\n", i, (int)vector[i].iov_len, (char *)vector[i].iov_base);
  }
  return 0;
}
