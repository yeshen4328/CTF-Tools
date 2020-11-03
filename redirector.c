#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#define READ 0 
#define WRITE 1
int main(void)
{
    int pipe_in[2];
    int pipe_out[2];
    if (pipe(pipe_in)) err(1, "pipe_in");
    if (pipe(pipe_out)) err(1, "pipe_out");
    //fcntl(pipe_out[READ], F_SETFL, O_NONBLOCK);
    fd_set readfd;
    struct timeval timeout;

    char out_buf[1000] = {};
    char buff2[1000] = {};
    int pid = fork();
    signal(SIGCHLD, SIG_IGN);  
    if(pid == 0)
    {
        dup2(pipe_out[WRITE], 1);//redirect stdout to pipe_out
        dup2(pipe_in[READ], 0);//redirect stdin to pipe_in
        system("./freenote");
    }
    
    // read(pipe_out[READ], out_buf, 1000);
    // printf("%s",out_buf);
    // memset(out_buf, 0, 1000);
    int ret = 0;
    
    timeout.tv_sec = 5*60;
    timeout.tv_usec = 1;

    while(1)
    {
        FD_ZERO(&readfd);                       /* 清空文件描述符集合 */
        FD_SET(0, &readfd);                 /* 添加文件描述符集合 */
        FD_SET(pipe_out[READ], &readfd);      /* 添加文件描述符集合 */
        ret = select(pipe_out[READ] + 1, &readfd, NULL, NULL, &timeout);

        switch(ret)
        {
            case -1:
            {
                //printf("error\n");
                break;
            }
            case 0:
            {
                //printf("time out\n");
                break;
            }
            default:
            {
                if(FD_ISSET(pipe_out[READ], &readfd)>0)
                {
                    ret = read(pipe_out[READ], out_buf, 1000-1);//read from pipe/sub process
                    if(ret > 0)      
                        write(1, out_buf, ret);
                }
                else if(FD_ISSET(0, &readfd)>0)
                {
                    int s = 0;
                    ret = read(0, buff2, 1000-1);//read from stdin
                    if(ret > 0)
                        write(pipe_in[WRITE], buff2, ret);
                }
            }
        }
        
        
        memset(buff2, 0, 1000);
        memset(out_buf, 0, 1000);
    }

    wait(NULL);  
    return 0;
}