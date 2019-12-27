#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>

struct user_regs_struct b_regs, regs;

int cmp_regs(){
  if(regs.orig_rax != b_regs.orig_rax) return 0;
  if(regs.rdi != b_regs.rdi) return 0;
  if(regs.rsi != b_regs.rsi) return 0;
  if(regs.rdx != b_regs.rdx) return 0;
  if(regs.r10 != b_regs.r10) return 0;
  if(regs.r8 != b_regs.r8) return 0;
  if(regs.r9 != b_regs.r9) return 0;
  return 1;
}

void print_syscall_name(char *syscall_name){
  char *syscall_color = "\x1b[36m";
  char *default_color = "\x1b[0m";
  printf("%s%s%s ", syscall_color, syscall_name, default_color);
}

void print_return(int flag){
  char *return_color = "\x1b[33m";
  char *default_color = "\x1b[0m";
  if(flag==0){
    printf(" = %s%d%s\n", return_color, regs.rax, default_color);
  }
  else if(flag==1){
    printf(" = %s%p%s\n", return_color, regs.rax, default_color); 
  }
}

void print_regs(){
  char *syscall_name;

  if(regs.orig_rax == 0){
    syscall_name = "read";
    print_syscall_name(syscall_name);
    printf("(%d, %018p, %d)", regs.rdi, regs.rsi, regs.rdx);
    print_return(0);
  }
  else if(regs.orig_rax == 1){
    syscall_name = "write";
    print_syscall_name(syscall_name);
    printf("(%d, %018p, %d)", regs.rdi, regs.rsi, regs.rdx);
    print_return(0);
  }
  else if(regs.orig_rax == 2){
    syscall_name = "open";
    print_syscall_name(syscall_name);
    printf("(%08p, %d, %04x)", regs.rdi, regs.rsi, regs.rdx);
    print_return(0);
  }
  else if(regs.orig_rax == 3){
    syscall_name = "close";
    print_syscall_name(syscall_name);
    printf("(%d)", regs.rdi);
    print_return(0);
  }
  else if(regs.orig_rax == 5){
    syscall_name = "fstat";
    print_syscall_name(syscall_name);
    printf("(%d, %p)", regs.rdi, regs.rsi);
    print_return(0);
  }
  else if(regs.orig_rax == 9){
    syscall_name = "mmap";
    print_syscall_name(syscall_name);
    printf("(%p, %d, %d, %d, %d, %p)",
  	 regs.rdi, regs.rsi, regs.rdx, regs.r10, regs.r8, regs.r9);
    print_return(1);
  }
  else if(regs.orig_rax == 10){
    syscall_name = "mprotect"; 
    print_syscall_name(syscall_name);
    printf("(%p, %d, %d)", regs.rdi, regs.rsi, regs.rdx);
    print_return(0);
  }
  else if(regs.orig_rax == 12){
    syscall_name = "brk"; 
    print_syscall_name(syscall_name);
    printf("(%p)", regs.rdi);
    print_return(1);
  }
  else if(regs.orig_rax == 21){
    syscall_name = "access";
    print_syscall_name(syscall_name);
    printf("(%08p, %04x)", regs.rdi, regs.rsi);
    print_return(0);
  }
  else if(regs.orig_rax == 257){
    syscall_name = "openat";
    print_syscall_name(syscall_name);
    printf("(%d, %08p, %d, %04x)", regs.rdi, regs.rsi, regs.rdx, regs.r10);
    print_return(0);
  }
  else{
  printf("\x1b[31m");
  printf("%03lld, rdi: %018p, rsi: %018p, rdx: %018p, r10: %018p, r8: %018p, r9: %018p",
	 regs.orig_rax, regs.rdi, regs.rsi, regs.rdx, regs.r10, regs.r8, regs.r9);
  printf("\x1b[0m\n");
  }
}

int main(int argc, char *argv[], char *envp[]){
  int pid, status, count = 0;
  pid = fork();

  if(!pid){
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    execve(argv[1], argv + 1, envp);
  }

  while(1){
    waitpid(pid, &status, 0);
    if(WIFEXITED(status)){
      break;
    }else if(WIFSTOPPED(status)) {
      ptrace(PTRACE_GETREGS, pid, NULL, &regs);
      if(cmp_regs(&regs, &b_regs)){
        print_regs(&regs);
      }
    }
    ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
    b_regs = regs;
  }
  return 0;
}

