#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/wait.h>

using namespace std;

int main()
{
    char input[100];
    cout << "Enter string: ";
    cin.getline(input, 100);
    pid_t pid = fork();
    if (pid > 0)
    {
        wait(NULL);
    }
    else if (pid == 0)
    {
        pid = fork();
        if (pid > 0)
        {
            wait(NULL);
            execlp("./strcapitalize", "./strcapitalize", input, NULL);
        }
        else if (pid == 0)
        {
            pid = fork();
            if (pid > 0)
            {
                wait(NULL);
                execlp("./strsort", "./strsort", input, NULL);
            }
            else if (pid == 0)
            {
                pid = fork();
                if (pid > 0)
                {
                    wait(NULL);
                    execlp("./stradd2", "./stradd2", input, NULL);
                }
                else if (pid == 0)
                {
                    pid = fork();
                    if (pid > 0)
                    {
                        wait(NULL);
                        execlp("./strlength", "./strlength", input, NULL);
                    }
                    else if (pid == 0)
                    {
                        execlp("./strrev", "./strrev", input, NULL);
                    }
                }
            }
        }
    }
}