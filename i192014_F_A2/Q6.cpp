#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/wait.h>

using namespace std;
char **createarguments(string input)
{
    int no_of_arguments = 1;
    for (int counter = 0; counter < input.length(); counter++)
    {
        if (input[counter] == ' ')
            no_of_arguments++;
    }
    char **arg = new char *[no_of_arguments + 1];
    char arr[100];
    for (int counter = 0, index = 0, index1 = 0; counter <= input.length(); counter++, index1++)
    {
        if (input[counter] == ' ' || input[counter] == 0)
        {
            arg[index] = new char[index1 + 1];
            strcpy(arg[index],arr);
            //cout << "arg: " << arg[0] << "  " << index << endl;
            index++;
            index1 = -1;
            fill(arr, arr + 100, 0);
        }
        else
            arr[index1] = input[counter];
    }
           // cout << arg[0] << endl << arg[1];
            arg[no_of_arguments] = new char[5];
            arg[no_of_arguments] = NULL;
    return arg;
}
int main()
{
    pid_t pid;
    do
    {
        string input;
        cout << "Enter your command: ";
        getline(cin, input);
        cout << endl;
        //char **arr = createarguments(input);
        //cout << arr[0] << endl << arr[1] << endl << arr[2] << endl;
        if (input == "quit" || input == "Quit")
            return 0;
        pid = fork();
        if (pid > 0)
        {
            wait(NULL);
        }
        else if (pid == 0)
        {
            execvp(*createarguments(input), createarguments(input));
            cout << "Exec failed\n";
        }
    } while (true);
}