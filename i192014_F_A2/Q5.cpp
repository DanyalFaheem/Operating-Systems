#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[], char *env[])
{
    pid_t pid = fork();
    if (pid > 0)
    {
        wait(NULL);
        pid = fork();
        if (pid > 0)
        {
            wait(NULL);
        }
        else if (pid == 0)
        {
            execlp("wc", "wc", argv[1], NULL);
        }
    }
    else if (pid == 0)
    {
        execlp("cat", "cat", "-n", argv[1], NULL);
    }
}