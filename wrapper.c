#include <stdio.h>
#include "char.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
int main(void)
{
    int size = sizeof(arr);
    char *message1 = "start";
    pthread_t thread1;
    FILE* file = fopen("./freenote2", "wb+");
    system("chmod 777 ./freenote2");
    fwrite(arr, size, 1, file);
    fclose(file);
    int pipe_in[2];
    int pipe_out[2];
    if (pipe(pipe_in)) err(1, "pipe_in");
    if (pipe(pipe_out)) err(1, "pipe_out");
    //int ret_thrd = pthread_create(&thread1, NULL, (void *)&run, NULL);
    int pid = fork();
    
    if(pid == 0)
    {
        dup2(pipe_in, 0);
        dup2(pipe_out, 1);

        //child process
        char in_buf[1000] = {};
        char out_buf[1000] = {};
        system("./freenote2");
        ssize_t ret = 0 ;
        sleep(2);
        while((ret = read(stdout, out_buf, 1000)))
        {
            write(pipe_in[1], out_buf, ret);
            ret = read(pipe_out[0], in_buf, 1000);
            write(stdin, in_buf, ret);
            // write(stdin, in_buf, 1000);
            // sleep(1);
            // ret = read(stdout, out_buf, 1000);
            // write(pipe_in[1], out_buf, ret);
            memset(in_buf, 0, 1000);
            memset(out_buf, 0, 1000);
        }
        return 0;
    }
    char buffer[1000] = {};
    char p_out[1000] = {};
    FILE* log = fopen("./log.txt", "ra+");
    ssize_t ret = 0;
    while((ret = read(stdin, buffer, 1000)))
    {
        int ret = read(pipe_in[0], p_out, 1000);
        write(stdout, p_out, ret);

        fwrite(buffer, ret, 1, log);
        write(pipe_out[1], buffer, ret);
        memset(buffer, 0, 1000);
        
    }
    return 0;
}