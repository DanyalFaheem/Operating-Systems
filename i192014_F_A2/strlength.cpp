#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
using namespace std;
int main(int argc, char *argv[], char *env[])
{
    cout << "The length of " << argv[1] << " is ";
    cout << strlen(argv[1]) << endl;
}