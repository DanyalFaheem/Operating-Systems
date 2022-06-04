#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
using namespace std;
int main(int argc, char *argv[], char *env[])
{
    cout << "The string " << argv[1] << " after adding 2 in ascii is ";
    for (int counter = strlen(argv[1]) - 1; counter >= 0; counter--)
    {
        argv[1][counter] += 2;
    }
    cout << argv[1] << endl;
}