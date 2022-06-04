#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <sys/wait.h>
using namespace std;
int main(int argc, char *argv[], char *env[])
{
    cout << "The uppercase version of \"" << argv[1] << "\" is ";
    char* arr = argv[1];
    for (int i = 0; i < strlen(arr); i++)
        arr[i] = putchar(toupper(arr[i]));

    cout << endl;
}