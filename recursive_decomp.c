//example to illustrate recursive decomposition in parallel processing, ie using quicksort

#include<stdio.h>
#include<omp.h>
#include<math.h>
#include <stdlib.h>

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int start, int end)
{
    int pivot = arr[end];
    int i = (start - 1);

    // Rearranging the array
    int j;
    for (j = start; j <= end - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[end]);

    return (i + 1);
}

void quicksort(int arr[], int start, int end)
{
    // Declaration
    int index;

    if (start < end) {

        index = partition(arr, start, end);

// Parallel sections
#pragma omp parallel sections
        {
#pragma omp section
            {
                // Evaluating the left half
                quicksort(arr, start, index - 1);
            }
#pragma omp section
            {
                // Evaluating the right half
                quicksort(arr, index + 1, end);
            }
        }
    }
}

int main()
{

    int N;

    printf("Enter the no. of elements: \n");
    scanf("%d",&N);

    int arr[N];
    int i;
    printf("Enter the array: \n");

    for (i = 0; i < N; i++) {
        scanf("%d",&arr[i]);
    }

    quicksort(arr, 0, N - 1);

    // Printing the sorted array
    printf("Final Array after sorting is: \n");

    for (i = 0; i < N; i++) {
        printf("%d ",arr[i]);
    }

    return 0;
}
