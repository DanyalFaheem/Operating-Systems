#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

using namespace std;

string calculate_Grade(double marks)
{
    if (marks >= 90)
    {
        return "A+";
    }
    else if (marks > 85)
    {
        return "A";
    }
    else if (marks > 81)
    {
        return "A-";
    }
    else if (marks > 77)
    {
        return "B+";
    }
    else if (marks > 73)
    {
        return "B";
    }
    else if (marks > 69)
    {
        return "B-";
    }
    else if (marks > 65)
    {
        return "C+";
    }
    else if (marks > 61)
    {
        return "C";
    }
    else if (marks > 57)
    {
        return "C-";
    }
    else if (marks > 53)
    {
        return "D+";
    }
    else if (marks > 49)
    {
        return "D";
    }
    else {
        return "F";
    }
}

int main()
{
    if (mkfifo("PIPE1", 0666) < 0)
    {
        if (errno != EEXIST)
        {
            perror("Error");
            return 0;
        }
    }
    int fd = open("PIPE", O_RDONLY);
    int fd1 = open("PIPE1", O_WRONLY);
    int weight[4] = {40, 15, 15, 30};
    double arr[8];
    read(fd, arr, sizeof(arr));
    double marks = 0;
    for(int counter = 0, index = 0; counter < 7; index++, counter += 2) {
        marks += (weight[index]) * (arr[counter + 1] / arr[counter]);
    }
    cout << "The final total marks of the student out of 100 are: " << marks << "\nThe final grade of the student is: " << calculate_Grade(marks) << endl;
    close(fd);
    close(fd1);
}