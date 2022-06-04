#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <cmath>
#include <thread>
#include <fstream>
using namespace std;
pthread_t tid[26];
string filename;
ifstream file;

int countchar(string s, char c)
{
    int count = 0;
    for (int counter = 0; counter < s.length(); counter++)
    {
        if (s[counter] == c || s[counter] == (c - 32))
            count++;
    }
    return count;
}

void *charcount(void *arg)
{
    char *ch = (char *)arg;
    int* count = new int;
    *count = 0;
    string s = "";
    while (!file.eof())
    {
        getline(file, s);
        *count += countchar(s, *ch);
    }
    file.clear();
    file.seekg(0, ios::beg);
    cout << "Count of character " << *ch << ", " << (char)((*ch) - 32) << ": " << *count << endl;
    pthread_exit((void *) count);
}

int main()
{
    int c_count = 0;
    cout << "Enter filename: " << endl;
    cin >> filename;
    file.open(filename);
    while (!file)
    {
        cout << "File does not exist in current directory.\nPlease enter filename of existing file" << endl;
        cin >> filename;
        file.open(filename);
    }
    char c = 'a';
    void* status;
    for(int counter = 0; counter < 26; counter++, c++) {
        pthread_create(&tid[counter], NULL, charcount, (void*) (&c));
        pthread_join(tid[counter], &status);
        c_count += *((int *) status);
    }
    cout << "Total Characters: " << c_count << endl;
    file.close();
    pthread_exit(NULL);
}