#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/wait.h>
#include <cmath>
using namespace std;
int matA[3][3], matB[3][3], resultmat[3][3];
pthread_t tid[9];
void *matmultiply(void *arg)
{
    int* arr = (int *) arg;
    resultmat[arr[0]][arr[1]] = (matA[arr[0]][0] * matB[0][arr[1]]) + (matA[arr[0]][1] * matB[1][arr[1]]) + (matA[arr[0]][2] * matB[2][arr[1]]);
    pthread_exit(NULL);
}
int main()
{
    cout << "_____Matrix A_____" << endl;
    for (int counter = 0; counter < 3; counter++)
    {
        for (int count = 0; count < 3; count++)
        {
            cout << "Enter value for row " << counter + 1 << " and column " << count + 1 << " :" << endl;
            cin >> matA[counter][count];
            matA[counter][count] = count;
        }
    }
    cout << "\n_____Matrix B____" << endl;
    for (int counter = 0; counter < 3; counter++)
    {
        for (int count = 0; count < 3; count++)
        {
            cout << "Enter value for row " << counter + 1 << " and column " << count + 1 << " :" << endl;
            cin >> matB[counter][count];
        }
    }
    int index[2] = {0,0};
    for (int counter = 0, ind = 0; counter < 3; counter++)
    {
        for(int count = 0; count < 3; count++, ind++){
            index[0] = counter;
            index[1] = count;
            pthread_create(&tid[ind], NULL, matmultiply, (void *) index);
            pthread_join(tid[ind], NULL);
        }
    }
    cout << "Final resultant matrix is as follows" << endl;
    for (int counter = 0; counter < 3; counter++)
    {
        cout << "| ";
        for (int count = 0; count < 3; count++)
        {
            cout << resultmat[counter][count] << " ";
        }
        cout << "|" << endl;
    }
    pthread_exit(NULL);
}