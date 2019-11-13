#include <sys/utsname.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv){
  int c;
  int s, n, r, v, m;

  struct utsname buf;
  char *sp;
  
  s = n = r = v = m = 0;

  while((c = getopt(argc, argv, "snrvma")) != -1){
    if(c == '?'){
      optind = 0;
      break;
    }
    switch (c){
      case 's':
        s = 1;
        break;
      case 'n':
        n = 1;
        break;
      case 'r':
        r = 1;
        break;
      case 'v':
        v = 1;
        break;
      case 'm':
        m = 1;
        break;
      case 'a':
        s = n = r = v = m = 1;
        break;
    }
  }
  if(optind != argc){
    fprintf(stderr, "Usage: %s [-snrvma]\n", argv[0]);
    return 1;
  }

  s |= !(n|r|v|m);

  if(uname(&buf) < 0){
    perror("uname error");
    return 1;
  }
  
  sp = "";

  if(s){printf("%s", buf.sysname); sp= " ";}
  if(n){printf("%s%s", sp, buf.nodename); sp = " ";}
  if(r){printf("%s%s", sp, buf.release); sp = " ";}
  if(v){printf("%s%s", sp, buf.version); sp = " ";}
  if(m){printf("%s%s", sp, buf.machine);}
  putchar('\n');
  return 0;
}

