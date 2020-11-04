#include <stdio.h>
#include "char.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#define READ 0 
#define WRITE 1
FILE *log;
void handle(int sig)
{
    fclose(log);
    exit(0);
}

int main(void)
{
    int size = sizeof(arr);
    //释放目标程序
    FILE* file = fopen("./freenote2", "wb+");
    system("chmod 777 ./freenote2");
    fwrite(arr, size, 1, file);
    fclose(file);
    


    //开始io劫持
    int pipe_in[2];
    int pipe_out[2];
    if (pipe(pipe_in)) err(1, "pipe_in");
    if (pipe(pipe_out)) err(1, "pipe_out");
    //fcntl(pipe_out[READ], F_SETFL, O_NONBLOCK);
    fd_set readfd;
    fd_set writefd;
    struct timeval timeout;
    signal(SIGCHLD, handle);  
    char out_buf[1000] = {};
    char buff2[1000] = {};
    int pid = fork();
    
    if(pid == 0)
    {
        dup2(pipe_out[WRITE], 1);//redirect stdout to pipe_out
        dup2(pipe_in[READ], 0);//redirect stdin to pipe_in
        system("./freenote2");
    }
    
    // read(pipe_out[READ], out_buf, 1000);
    // printf("%s",out_buf);
    // memset(out_buf, 0, 1000);
    int ret = 0;
    int f_no = 0;
    char f_name[1000] = {};
    sprintf(f_name, "./log%d.txt", f_no);
    while(access(f_name, F_OK) == 0)
    {
        sprintf(f_name, "./a_log%d.txt", f_no++);
    }
    log = fopen(f_name, "wb");
    
    timeout.tv_sec = 5*60;
    timeout.tv_usec = 1;
    
    int status = 0;
    int exit = 0;
    
    while(exit != -1)
    {
        
        FD_ZERO(&readfd);                       /* 清空文件描述符集合 */
        FD_SET(0, &readfd);                 /* 添加文件描述符集合 */
        FD_SET(pipe_out[READ], &readfd);      /* 添加文件描述符集合 */
        //FD_SET(log, &writefd);                  /* 添加文件描述符集合 */
        ret = select(pipe_out[READ] + 1, &readfd, NULL, NULL, &timeout);
        
        switch(ret)
        {
            case -1:
            {
                printf("error\n");
                break;
            }
            case 0:
            {
                printf("time out\n");
                break;
            }
            default:
            {
                if(FD_ISSET(pipe_out[READ], &readfd)>0)
                {
                    ret = read(pipe_out[READ], out_buf, 1000-1);//read from pipe/sub process
                    fwrite(out_buf, 1, ret, log);
                    fflush(log);
                    if(ret > 0)      
                        write(1, out_buf, ret);
                }
                else if(FD_ISSET(0, &readfd)>0)
                {
                    int s = 0;
                    ret = read(0, buff2, 1000-1);//read from stdin
                    
                    if(ret > 0)
                    {
                        //write(log, buff2, ret);
                        char tmp[10] = "##input##";
                        fwrite(tmp, 1, 9, log);
                        fwrite(buff2, 1, ret, log);
                        fflush(log);
                        write(pipe_in[WRITE], buff2, ret);
                    }
                }
            }
        }
      
       
        memset(buff2, 0, 1000);
        memset(out_buf, 0, 1000);
    }
    
    fclose(log);
    return 0;
}