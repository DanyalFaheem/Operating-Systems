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
#include <stdlib.h>
using namespace std;
int *arr;
// Code taken from: https://www.geeksforgeeks.org/merge-sort/ and https://www.geeksforgeeks.org/merge-sort-using-multi-threading/
void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]

    // Initial index of first subarray
    int i = 0;

    // Initial index of second subarray
    int j = 0;

    // Initial index of merged subarray
    int k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l >= r)
    {
        return; //returns recursively
    }
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

void printarr(int *arr, int size)
{
    cout << "The array is as follows:  " << endl;
    for (int counter = 0; counter < size; counter++)
    {
        cout << arr[counter] << " ";
    }
    cout << endl;
}

int highestfactor(int num, int div)
{
    int divisor = 0;
    for (int counter = div + 1; counter < num; counter++)
    {
        counter % div == 0 ? divisor = counter : divisor = divisor;
    }
    return divisor;
}

void *sortarr(void *arg)
{
    int *arr1 = (int *)arg;
    int *arr2 = new int[arr1[1] - arr1[0]];
    //cout << "arr[0]: " << arr1[0] << "   " << "arr[1]:" << arr1[1] << endl;
    for (int counter = arr1[0], index1 = 0; counter < arr1[1]; counter++, index1++)
    {
        arr2[index1] = arr[counter];
    }
    int arr_size1 = arr1[1] - arr1[0];
    //cout << "Arr_size1: " << arr_size1 << endl;
    //printarr(arr2, arr_size1);
    mergeSort(arr2, 0, arr_size1 - 1);
    //printarr(arr2, arr_size1);
    for (int counter = arr1[0], index1 = 0; counter < arr1[1]; counter++, index1++)
    {
        arr[counter] = arr2[index1];
    }
    pthread_exit(NULL);
}

void merge(int low, int mid, int high)
{
    int *left = new int[mid - low + 1];
    int *right = new int[high - mid];

    // n1 is size of left part and n2 is size
    // of right part
    int n1 = mid - low + 1, n2 = high - mid, i, j;

    // storing values in left part
    for (i = 0; i < n1; i++)
        left[i] = arr[i + low];

    // storing values in right part
    for (i = 0; i < n2; i++)
        right[i] = arr[i + mid + 1];

    int k = low;
    i = j = 0;

    // merge left and right in ascending order
    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    // insert remaining values from left
    while (i < n1)
    {
        arr[k++] = left[i++];
    }

    // insert remaining values from right
    while (j < n2)
    {
        arr[k++] = right[j++];
    }
}

int main()
{
    srand(time(NULL));
    int arr_size = 0, processor_count = 4;
    //const auto processor_count = thread::hardware_concurrency();
    cout << "Number of cores: " << processor_count << endl;
    cout << "LAN1 MAC: 8C-C6-81-6C-DB-CC\nLAN2 MAC: 8E-C6-81-6C-DB-CB\nWIFI MAC: 0A-85-14-5E-6E-90" << endl;
    cout << "Enter size of array: " << endl;
    cin >> arr_size;
    arr = new int[arr_size];
    for (int counter = 0; counter < arr_size; counter++)
    {
        cout << "Enter value(integer) for index: " << counter + 1 << endl;
        //arr[counter] = rand() % (10);
        cin >> arr[counter];
    }
    printarr(arr, arr_size);
    cout << endl;
    pthread_t tid[processor_count];
    if (arr_size % processor_count == 0)
    {
        cout << "The array is divided into chunks of: " << ((arr_size / processor_count)) << endl;
        int index[2] = {0, arr_size / processor_count};
        for (int counter = 0; counter < processor_count; counter++)
        {
            pthread_create(&tid[counter], NULL, sortarr, (void *)index);
            pthread_join(tid[counter], NULL);
            index[0] += arr_size / processor_count;
            index[1] += arr_size / processor_count;
        }
    }
    else
    {
        int index[2] = {0, (arr_size / processor_count) + 1};
        for (int counter = 0; counter < processor_count - 1; counter++)
        {
            pthread_create(&tid[counter], NULL, sortarr, (void *)index);
            pthread_join(tid[counter], NULL);
            index[0] += (arr_size / processor_count) + 1;
            index[1] += (arr_size / processor_count) + 1;
            if (index[0] >= highestfactor(arr_size, processor_count) || index[1] > (highestfactor(arr_size, processor_count) + 1))
            {
                break;
            }
        }
        index[0] = highestfactor(arr_size, processor_count) + 1;
        index[1] = arr_size;
        pthread_create(&tid[processor_count - 1], NULL, sortarr, (void *)index);
        pthread_join(tid[processor_count - 1], NULL);
    }
    printarr(arr, arr_size);
}