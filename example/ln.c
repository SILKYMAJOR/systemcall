#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
  int s_flag;
  if(
    argc <= 2 || argc >= 5 ||
    (s_flag = (strcmp(argv[1], "-s") == 0), argc == 3 && s_flag) ||
    (argc == 4 && !s_flag)
  ){
    fprintf(stderr, "Usage: %s [-s] source dest\n", argv[0]);
    return 1;
  }

  if(s_flag){
    if(symlink(argv[2], argv[3]) < 0){
      perror("symlink");
      return 1;
    }
  }else{
    if(link(argv[1], argv[2]) < 0){
      perror("link");
      return 1;
    }
  }
}
