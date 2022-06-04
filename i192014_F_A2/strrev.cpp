#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
using namespace std;
int main(int argc, char *argv[], char *env[])
{
    cout << "The reverse of " << argv[1] << " is ";
    char *arr = new char[strlen(argv[1]) + 1];
    strcpy(arr, argv[1]);
    for (int counter = strlen(argv[1]) - 1, index = 0; counter >= 0; index++, counter--)
    {
        arr[index] = argv[1][counter];
    }
    cout << arr << endl;
}