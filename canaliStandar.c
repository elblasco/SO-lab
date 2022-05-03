#include <stdio.h>
#include <unistd.h>

int main(){
    printf("stdin: stdin->flags = %hd, STDIN_FILENO = %d\n",stdin->_flags,STDIN_FILENO);
    printf("stdout: stdout->flags = %hd, STDIN_FILENO = %d\n",stdout->_flags,STDOUT_FILENO);
    printf("stderr: stderr->flags = %hd, STDERR_FILENO = %d\n",stderr->_flags,STDERR_FILENO);
    return 0;
}