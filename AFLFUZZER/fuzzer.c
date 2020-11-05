#include <stdio.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <sys/fcntl.h>   

#include <pthread.h>
#include <stdlib.h>

#include <errno.h>

#include <signal.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <string.h>
#define READ 0 
#define WRITE 1 
int main(int argc, char const *argv[])  
{  
	if (argc != 2)  
   {  
		printf("null args!\n");  
		return -1;  
    }  
	
	/* Get file state */  
    struct stat fstat;  
    if (stat(argv[1], &fstat))  
    {  
        printf("Failed ^_^\n");  
        return -1;  
    }  
	
    /* Open file */  
    int pipe_in[2];
    int pipe_out[2];
    if (pipe(pipe_in)) err(1, "pipe_in");
    if (pipe(pipe_out)) err(1, "pipe_out");
    FILE * fd = NULL;  
    fd = open(argv[1], O_RDONLY);  
    if (fd == -1)  
    {  
        printf("open file failed!\n");  
        return -1;  
    }  

    int pid = fork();
    
    if(pid == 0)
    {
        dup2(pipe_out[WRITE], 1);//redirect stdout to pipe_out
        dup2(pipe_in[READ], 0);//redirect stdin to pipe_in
        system("./level0");
    }

    /* Select */  
    char buf[4096];
    int ret = 0;  
    if ((ret = read(fd, buf, 4096)) == -1)  
    {  
        printf("read failed!");  
        return -1;  
    }  
    // write(1, "hello", ret);
    //write(1, buf, ret);
    write(pipe_in[WRITE], buf, ret);

    return 0;
}
