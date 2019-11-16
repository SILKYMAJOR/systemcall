#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>

struct user_regs_struct b_regs, regs;

int cmp_regs(){
  if(regs.orig_rax != b_regs.orig_rax) return 1;
  if(regs.rdi != b_regs.rdi) return 1;
  if(regs.rsi != b_regs.rsi) return 1;
  if(regs.rdx != b_regs.rdx) return 1;
  if(regs.r10 != b_regs.r10) return 1;
  if(regs.r8 != b_regs.r8) return 1;
  if(regs.r9 != b_regs.r9) return 1;
  return 0;
}

void print_regs(){
  printf("%03lld, rdi: %018p, rsi: %018p, rdx: %018p, r10: %018p, r8: %018p, r9: %018p \n",
	 regs.orig_rax, regs.rdi, regs.rsi, regs.rdx,
	 regs.r10, regs.r8, regs.r9);
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

