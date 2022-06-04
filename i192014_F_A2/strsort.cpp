#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
using namespace std;
int main(int argc, char *argv[], char *env[])
{
    bool check = false;
    cout << "The Sorted string of " << argv[1] << " is ";
    for (int counter = 0; counter < strlen(argv[1]); counter++)
    {
        check = true;
        for (int count = 0; count < strlen(argv[1]) - 1; count++)
        {
            if (argv[1][count] > argv[1][count + 1])
            {
                char temp = argv[1][count];
                argv[1][count] = argv[1][count + 1];
                argv[1][count + 1] = temp;
                check = true;
            }
        }
        if (check == false)
        {
            break;
        }
    }
    cout << argv[1] << endl;
}