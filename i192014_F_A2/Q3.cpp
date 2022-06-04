#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/wait.h>

using namespace std;

int main()
{
    int sum = 0;
    int *sumptr = &sum;
    int status = 0;
    pid_t pid = fork();
    //wait(&status);
    if (pid > 0)
    {
        wait(&status);
        pid = fork();
        if (pid > 0)
        {
            wait(&status);
            sum += status / 256;
            //cout << sum << endl;
            cout << "Node D. PID: " << getpid() << ". PPID: " << getppid() << " and ASCII: " << int('D') << ". My children are A and N" << endl
                 << "Sum of all ASCII: " << int('D' + 'A' + 'N' + 'Y' + 'A' + 'L' + 'F' + 'A' + 'H' + 'E' + 'E' + 'M') << endl;
            //pid = fork();
        }
        else if (pid == 0)
        {
            //wait(&status);
            pid = fork();
            if (pid > 0)
            {
                wait(&status);
                sum += status / 256;
                pid = fork();
                if (pid > 0)
                {
                    wait(&status);
                    sum += status / 256;
                    cout << "Node N. PID: " << getpid() << ". PPID: " << getppid() << " and ASCII: " << int('N') << ". My children are L and Y" << endl;
                    exit('N');
                }
                else if (pid == 0)
                {
                    //wait(&status);
                    pid = fork();
                    if (pid > 0)
                    {
                        wait(&status);
                        sum += status / 256;
                        pid = fork();
                        if (pid > 0)
                        {
                            wait(&status);
                            sum += status / 256;
                            cout << "Node L. PID: " << getpid() << ". PPID: " << getppid() << " and ASCII: " << int('L') << ". My children are F and M" << endl;
                            exit('L');
                        }
                        else if (pid == 0)
                        {
                            //wait(&status);
                            pid = fork();
                            if (pid > 0)
                            {
                                wait(&status);
                                sum += status / 256;
                                pid = fork();
                                if (pid > 0)
                                {
                                    wait(&status);
                                    sum += status / 256;
                                    cout << "Node F. PID: " << getpid() << ". PPID: " << getppid() << " and ASCII: " << int('F') << ". My children are H and E" << endl;
                                    exit('F');
                                }
                                else if (pid == 0)
                                {
                                    pid = fork();
                                    if (pid > 0)
                                    {
                                        wait(&status);
                                        sum += status / 256;
                                        cout << "Node E. PID: " << getpid() << ". PPID: " << getppid() << " and ASCII: " << int('E') << ". My child is E." << endl;
                                        exit('E');
                                    }
                                    else if (pid == 0)
                                    {
                                        cout << "Node E. PID: " << getpid() << ". PPID: " << getppid() << " and ASCII: " << int('E') << "." << endl;
                                        exit('E');
                                    }
                                }
                            }
                            else if (pid == 0)
                            {
                                cout << "Node H. PID: " << getpid() << ". PPID: " << getppid() << " and ASCII: " << int('H') << "." << endl;
                                exit('H');
                            }
                        }
                    }
                    else if (pid == 0)
                    {
                        cout << "Node M. PID: " << getpid() << ". PPID: " << getppid() << " and ASCII: " << int('M') << "." << endl;
                        exit('M');
                    }
                }
            }
            else if (pid == 0)
            {
                cout << "Node Y. PID: " << getpid() << ". PPID: " << getppid() << " and ASCII: " << int('Y') << "." << endl;
                exit('Y');
            }
        }
    }
    else if (pid == 0)
    {
        pid = fork();
        if (pid > 0)
        {
            wait(&status);
            sum += status / 256;
            cout << "Node A. PID: " << getpid() << ". PPID: " << getppid() << " and ASCII: " << int('A') << ". My child is A" << endl;
            exit('A');
        }
        else if (pid == 0)
        {
            pid = fork();
            if (pid > 0)
            {
                wait(&status);
                sum += status / 256;
                cout << "Node A. PID: " << getpid() << ". PPID: " << getppid() << " and ASCII: " << int('A') << ". My child is A" << endl;
                exit('A');
            }
            else if (pid == 0)
            {
                cout << "Node A. PID: " << getpid() << ". PPID: " << getppid() << " and ASCII: " << int('A') << endl;
                exit('A');
            }
        }
    }
}