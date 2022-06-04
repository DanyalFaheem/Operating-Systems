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
    if (mkfifo("PIPE", 0666) < 0)
    {
        if (errno != EEXIST)
        {
            perror("Error");
            return 0;
        }
    }
    int fd = open("PIPE", O_WRONLY);
    int fd1 = open("PIPE1", O_RDONLY);
    double arr[8];
    cout << "Enter total lab tasks marks: \n";
    cin >> arr[0];
    cout << "Enter obtained lab tasks marks out of " << arr[0] << endl;
    cin >> arr[1];
    cout << "Enter total assignments marks: \n";
    cin >> arr[2];
    cout << "Enter obtained assignments marks out of " << arr[2] << endl;
    cin >> arr[3];
    cout << "Enter total project marks: \n";
    cin >> arr[4];
    cout << "Enter obtained project marks out of " << arr[4] << endl;
    cin >> arr[5];
    cout << "Enter total final exam marks: \n";
    cin >> arr[6];
    cout << "Enter obtained final exam marks out of " << arr[6] << endl;
    cin >> arr[7];
    write(fd, arr, 64);
    close(fd);
    unlink("PIPE");
    unlink("PIPE1");
}