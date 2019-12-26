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

void print_regs(){
  char *syscall_name;
  if(regs.orig_rax == 0){
    syscall_name = "read";
    printf("%s (%d, %018p, %d) = %d\n", syscall_name, regs.rdi, regs.rsi, regs.rdx, regs.rax);
  }
  else if(regs.orig_rax == 1){
    syscall_name = "write";
    printf("%s (%d, %018p, %d) = %d\n", syscall_name, regs.rdi, regs.rsi, regs.rdx, regs.rax);
  }
  else if(regs.orig_rax == 2){
    syscall_name = "open";
    printf("%s (%d, %08p, %04x) = %d\n", syscall_name, regs.rdi, regs.rsi, regs.rdx, regs.rax);
  }
  else if(regs.orig_rax == 3){
    syscall_name = "close";
    printf("%s (%d) = %d \n", syscall_name, regs.rdi, regs.rax);
  }
  else if(regs.orig_rax == 9){
    syscall_name = "mmap";
    printf("%s (%p, %d, %d, %d, %d, %p) = %p\n",
  	 syscall_name, regs.rdi, regs.rsi, regs.rdx, regs.r10, regs.r8, regs.r9, regs.rax);
  }
  else if(regs.orig_rax == 10){
    syscall_name = "mprotect";
    printf("%s (%p, %d, %d) = %d\n", syscall_name, regs.rdi, regs.rsi, regs.rdx, regs.rax);
  }
  else if(regs.orig_rax == 12){
    syscall_name = "brk";
    printf("%s (%p) = %p\n", syscall_name, regs.rdi, regs.rax);
  }
  else{
  printf("%03lld, rdi: %018p, rsi: %018p, rdx: %018p, r10: %018p, r8: %018p, r9: %018p \n",
	 regs.orig_rax, regs.rdi, regs.rsi, regs.rdx, regs.r10, regs.r8, regs.r9);
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

