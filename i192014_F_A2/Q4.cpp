#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/wait.h>

using namespace std;

int main()
{
    pid_t pid = fork();
    if (pid > 0)
    {
        wait(NULL);
    }
    else if (pid == 0)
    {
        int i = execl("/bin/sh", "sh", "-c", "ls & echo redirecting output & ls > output1.txt & echo grep starts here & grep -n output1.txt /home/* & export PATH=$PATH:/home" , NULL);
        cout << "Exec failed " << i << endl;
    }
}