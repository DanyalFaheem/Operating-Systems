#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

using namespace std;
int main()
{
    int fd[2], fd1[2], fd2[2];
    pipe(fd);
    pipe(fd1);
    pipe(fd2);
    pid_t pid = fork();
    char buff[100];
    if (pid > 0)
    {
        close(fd1[1]);
        wait(NULL);
        pid = fork();
        if (pid > 0)
        {
            close(fd1[0]);
            close(fd[1]);
            wait(NULL);
            pid = fork();
            if (pid > 0)
            {
                close(fd[0]);
                close(fd2[1]);
                wait(NULL);
                pid = fork();
                if (pid > 0)
                {
                    close(fd2[0]);
                    wait(NULL);
                }
                else if (pid == 0)
                {
                    close(fd2[1]);
                    close(fd[0]);
                    close(fd[1]);
                    close(fd1[0]);
                    close(fd1[1]);
                    dup2(fd2[0], 0);
                    execlp("wc", "wc", NULL);
                    close(fd2[0]);
                }
            }
            else if (pid == 0)
            {
                close(fd[1]);
                close(fd1[0]);
                close(fd1[1]);
                close(fd2[0]);
                dup2(fd[0], 0);
                dup2(fd2[1], 1);
                execlp("sort", "sort", NULL);
                close(fd[0]);
                close(fd2[1]);
            }
        }
        else if (pid == 0)
        {
            close(fd[0]);
            close(fd1[1]);
            close(fd2[0]);
            close(fd2[1]);
            dup2(fd1[0], 0);
            dup2(fd[1], 1);
            execlp("sum", "sum", NULL);
            close(fd1[0]);
            close(fd[1]);
        }
    }
    else if (pid == 0)
    {
        close(fd2[0]);
        close(fd2[1]);
        close(fd[0]);
        close(fd[1]);
        close(fd1[0]);
        dup2(fd1[1], 1);
        execlp("grep", "grep", "a", "*.*", NULL);
        close(fd1[1]);
    }
}