#include <stdio.h>
#include<omp.h>
int getMax(int array[], int n)
{
    int max = array[0];
    for (int i = 1; i < n; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}
void countSort(int array[], int size, int place)
{
    int output[size + 1];
    int max = (array[0] / place) % 10;
    for (int i = 1; i < size; i++)
    {
        if (((array[i] / place) % 10) > max)
            max = array[i];
    }
    int count[max + 1];
    for (int i = 0; i < max; ++i)
        count[i] = 0;
    for (int i = 0; i < size; i++)
        count[(array[i] / place) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    #pragma omp parallel for
    for (int i = size - 1; i >= 0; i--)
    {
        output[count[(array[i] / place) % 10] - 1] = array[i];
        count[(array[i] / place) % 10]--;
    }
    for (int i = 0; i < size; i++)
        array[i] = output[i];
}
void radixsort(int array[], int size)
{
    int max,tid;
    omp_set_num_threads(2);
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            tid=omp_get_thread_num();
            max = getMax(array, size);
        }
        #pragma omp section
        {
            tid=omp_get_thread_num();
            for (int place = 1; max / place > 0; place *= 10)
                countSort(array, size, place);
        }
    }
}
void printArray(int array[], int size)
{
    printf("\nSorted array: ");
    printf("\n");
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
int main()
{
    int arr[] = {55, 89, 90, 34, 56, 11, 3};
    printf("Original array: ");
    printf("\n");
    int length = sizeof(arr) / sizeof(arr[0]);
     for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    radixsort(arr, length);
    printArray(arr, length);
}
