#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <fcntl.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sys/wait.h>

using namespace std;

//This function divides the string according to comma and returns value after "count" commas from passed string
string divide_str(string s, int count)
{
    string str = "";
    for (int count2 = 0, counter = 0; count2 < count; count2++)
    {
        str = "";
        for (; s[counter] != 0 && s[counter] != ','; counter++)
            str += s[counter];
        counter += 2;
    }
    return str;
}

int countcommas(string s)
{
    int count = 0;
    for (int counter = 0; counter < s.length(); counter++)
    {
        if (s[counter] == ',')
            count++;
    }
    return count;
}

//This function divides the string according to comma and returns value after "count" commas from passed string
string divide_str2(string s, int count)
{
    string str = "";
    for (int count2 = 0, counter = 0; count2 < count; count2++)
    {
        str = "";
        for (; s[counter] != 0 && s[counter] != '|'; counter++)
            str += s[counter];
        counter += 1;
    }
    //cout << s << " " << count << " " << str << endl;
    return str;
}

string *read1(string arg);

int main(int argc, char *argv[], char *env[])
{
    int fd3[2], fd1[2], fd2[2];
    pipe(fd3);
    pipe(fd1);
    pipe(fd2);
    pid_t pid = fork();
    if (pid > 0) //Parent
    {
        close(fd3[0]);
        close(fd3[1]);
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[0]);
        string *arr = read1(argv[1]);
        int count = stoi(arr[1]);
        int arrsize = 0;
        for (int counter = 0; counter < count; counter++)
        {
            arrsize += arr[counter].length() + 1;
            //cout << arr[counter] << endl;
        }
        char ch1[arrsize];
        write(fd2[1], ch1, strlen(ch1));
        close(fd2[1]);
        wait(NULL);
    }
    else if (pid == 0)
    {
        pid = fork();
        if (pid > 0) //child1
        {
            close(fd3[0]);
            close(fd3[1]);
            close(fd1[0]);
            close(fd2[1]);
            char *ch;
            read(fd2[0], ch, sizeof(ch));
            string *arr = read1(argv[1]);
            int frequency = 0;
            vector<int> freq;
            vector<string> v;
            for (int counter = 2; counter < stoi(arr[1]); counter++)
            {
                for (int count = 1; count < countcommas(arr[counter]) + 1; count++)
                {
                    frequency = 0;
                    if (find(v.begin(), v.end(), divide_str(arr[counter], count)) == v.end())
                    {
                        v.push_back(divide_str(arr[counter], count));
                        for (int count2 = 2; count2 < stoi(arr[1]); count2++)
                        {
                            for (int count3 = 1; count3 < countcommas(arr[counter]) + 1; count3++)
                            {
                                if (divide_str(arr[counter], count) == divide_str(arr[count2], count3))
                                {
                                    frequency++;
                                }
                            }
                        }
                        freq.push_back(frequency);
                    }
                }
            }
            cout << "Table without threshold frequency applied\nProduct\tFrequency\n";
            for (int counter = 0; counter < v.size(); counter++)
            {
                cout << v[counter] << "\t" << freq[counter] << endl;
            }
            cout << "Table with threshold frequency applied\nProduct\tFrequency\n";
            for (int counter = 0; counter < v.size(); counter++)
            {
                if (freq[counter] >= stoi(arr[0]))
                    cout << v[counter] << "\t" << freq[counter] << endl;
            }
            int count = stoi(arr[1]);
            int arrsize = 0;
            for (int counter = 0; counter < count; counter++)
            {
                arrsize += arr[counter].length() + 1;
            }
            char ch1[arrsize];
            write(fd1[1], ch, strlen(ch));
            cout << "Forwarding message to child 2\n";
            close(fd1[1]);
            close(fd2[0]);
        }
        else if (pid == 0)
        {
            pid = fork();
            if (pid > 0) //Child 2
            {
                close(fd3[0]);
                close(fd2[0]);
                close(fd1[1]);
                close(fd2[1]);
                char *ch;
                read(fd1[0], ch, sizeof(ch));
                string *arr = read1(argv[1]);
                vector<int> freq;
                vector<string> v;
                for (int counter = 2; counter < stoi(arr[1]); counter++)
                {
                    for (int count = 1; count <= countcommas(arr[counter]) + 1; count++)
                    {
                        for (int count2 = count + 1; count2 <= countcommas(arr[counter]) + 1; count2++)
                        {
                            if ((find(v.begin(), v.end(), divide_str(arr[counter], count) + ',' + divide_str(arr[counter], count2)) == v.end() && find(v.begin(), v.end(), divide_str(arr[counter], count2) + ',' + divide_str(arr[counter], count)) == v.end()) && (divide_str(arr[counter], count) != divide_str(arr[counter], count2)))
                            {
                                v.push_back(divide_str(arr[counter], count) + ',' + divide_str(arr[counter], count2));
                                freq.push_back(1);
                            }
                            else if (find(v.begin(), v.end(), divide_str(arr[counter], count) + ',' + divide_str(arr[counter], count2)) != v.end())
                            {
                                freq[distance(v.begin(), find(v.begin(), v.end(), divide_str(arr[counter], count) + ',' + divide_str(arr[counter], count2)))] += 1;
                            }
                            else if (find(v.begin(), v.end(), divide_str(arr[counter], count2) + ',' + divide_str(arr[counter], count)) != v.end())
                            {
                                freq[distance(v.begin(), find(v.begin(), v.end(), divide_str(arr[counter], count2) + ',' + divide_str(arr[counter], count)))] += 1;
                            }
                        }
                    }
                }
                cout << "Table without threshold frequency applied\nProduct\tFrequency\n";
                for (int counter = 0; counter < v.size(); counter++)
                {
                    cout << v[counter] << "\t" << freq[counter] << endl;
                }
                cout << "Table with threshold frequency applied\nProduct\tFrequency\n";
                for (int counter = 0; counter < v.size(); counter++)
                {
                    if (freq[counter] >= stoi(arr[0]))
                        cout << v[counter] << "\t" << freq[counter] << endl;
                }
                int count = stoi(arr[1]);
                int arrsize = 0;
                for (int counter = 0; counter < count; counter++)
                {
                    arrsize += arr[counter].length() + 1;
                }
                char ch1[arrsize];
                //write(fd3[1], ch1, strlen(ch1));
                write(fd3[1], ch, sizeof(ch));
                close(fd1[0]);
                close(fd3[1]);
                wait(NULL);
            }
            else if (pid == 0) //Child 3
            {
                close(fd3[1]);
                close(fd2[0]);
                close(fd1[0]);
                close(fd1[1]);
                close(fd2[1]);
                char *ch;
                read(fd3[0], ch, sizeof(ch));
                string *arr = read1(argv[1]);
                int frequency = 0;
                vector<int> freq;
                vector<string> v;
                for (int counter = 2; counter < stoi(arr[1]); counter++)
                {
                    for (int count = 1; count <= countcommas(arr[counter]) + 1; count++)
                    {
                        for (int count2 = count + 1; count2 <= countcommas(arr[counter]) + 1; count2++)
                        {
                            for (int count3 = count2 + 1; count3 <= countcommas(arr[counter]) + 1; count3++)
                            {
                                if ((find(v.begin(), v.end(), divide_str(arr[counter], count) + ',' + divide_str(arr[counter], count2) + ',' + divide_str(arr[counter], count3)) == v.end() &&
                                     find(v.begin(), v.end(), divide_str(arr[counter], count) + ',' + divide_str(arr[counter], count3) + ',' + divide_str(arr[counter], count2)) == v.end() &&
                                     find(v.begin(), v.end(), divide_str(arr[counter], count2) + ',' + divide_str(arr[counter], count) + ',' + divide_str(arr[counter], count3)) == v.end() &&
                                     find(v.begin(), v.end(), divide_str(arr[counter], count3) + ',' + divide_str(arr[counter], count2) + ',' + divide_str(arr[counter], count)) == v.end() &&
                                     find(v.begin(), v.end(), divide_str(arr[counter], count2) + ',' + divide_str(arr[counter], count3) + ',' + divide_str(arr[counter], count)) == v.end() &&
                                     find(v.begin(), v.end(), divide_str(arr[counter], count3) + ',' + divide_str(arr[counter], count) + ',' + divide_str(arr[counter], count2)) == v.end() &&
                                     (divide_str(arr[counter], count) != divide_str(arr[counter], count2) && divide_str(arr[counter], count2) != divide_str(arr[counter], count3) && divide_str(arr[counter], count) != divide_str(arr[counter], count3))))
                                {
                                    v.push_back(divide_str(arr[counter], count) + ',' + divide_str(arr[counter], count2) + ',' + divide_str(arr[counter], count3));
                                    freq.push_back(1);
                                }
                                else
                                {
                                    freq[distance(v.begin(), find(v.begin(), v.end(), divide_str(arr[counter], count) + ',' + divide_str(arr[counter], count2) + ',' + divide_str(arr[counter], count3)))] += 1;
                                }
                            }
                        }
                    }
                }
                cout << "Table without threshold frequency applied\nProduct\tFrequency\n";
                for (int counter = 0; counter < v.size(); counter++)
                {
                    cout << v[counter] << "\t" << freq[counter] << endl;
                }
                cout << "Table with threshold frequency applied\nProduct\tFrequency\n";
                for (int counter = 0; counter < v.size(); counter++)
                {
                    if (freq[counter] > stoi(arr[0]))
                        cout << v[counter] << "\t" << freq[counter] << endl;
                }
                int file_desc = open("output.txt", O_WRONLY);
                dup2(file_desc, 1);
                for (int counter = 0; counter < v.size(); counter++)
                {
                    if (freq[counter] >= stoi(arr[0]))
                        cout << v[counter] << "\t" << freq[counter] << endl;
                }
                close(fd3[0]);
            }
        }
    }
}

string *read1(string arg)
{
    fstream file;
    file.open(arg);
    int count = 0;
    string s = "";
    while (!file.eof())
    {
        getline(file, s);
        count++;
    }
    file.clear();
    file.seekg(0, ios::beg);
    string *arr = new string[count];
    for (int counter = 0; !file.eof(); counter++)
    {
        getline(file, s);
        arr[counter] = s;
    }
    arr[0] = to_string(stod(arr[0]) * stod(arr[1]));
    arr[1] = to_string(count);
    return arr;
}