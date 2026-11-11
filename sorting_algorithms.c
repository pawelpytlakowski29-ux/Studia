#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE 100

void bubble_sort(int lst[], int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (lst[j] > lst[j + 1])
            {
                int val = lst[j];
                lst[j] = lst[j + 1];
                lst[j + 1] = val;
            }
        }
    }
}    

void bubble_sort_opt(int lst[], int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int swap = 0;
        for (int j = 0; j < i; j++)
        {
            if (lst[j] > lst[j + 1])
            {
                int val = lst[j];
                lst[j] = lst[j + 1];
                lst[j + 1] = val;
                swap++;
            }
        }

        if (swap == 0)
        {
            break;
        }
    }
}

void insertion_sort(int lst[], int n)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (lst[j] < lst[j - 1])
            {
                int value = lst[j];
                lst[j] = lst[j - 1];
                lst[j - 1] = value;
            }
            else
            {
                break;
            }
        }
    }
}

void insertion_sort_opt(int lst[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int value = lst[i];
        int j = i - 1;

        while (j >= 0 && lst[j] > value)
        {
            lst[j + 1] = lst[j];
            j--;
        }

        lst[j + 1] = value;
    }
}

void selection_sort(int lst[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (lst[j] < lst[min])
            {
                min = j;
            }
        }

        if (min != i)
        {
            int val = lst[i];
            lst[i] = lst[min];
            lst[min] = val;
        }
    }
}

void my_merge_sort(int lst[], int start, int end)
{
    if (start == end)
    {
        return;
    }

    int mid = (start + end) / 2;
    my_merge_sort(lst, start, mid);
    my_merge_sort(lst, mid + 1, end);

    int draft[end - start + 1];
    int i1 = start;
    int i2 = mid + 1;
    int i3 = 0;

    while (i1 <= mid)
    {
        while (i2 <= end)
        {
            if (lst[i2] < lst[i1])
            {
                draft[i3] = lst[i2];
                i3++;
                i2++;
            }
            else
            {
                break;
            }
        }

        draft[i3] = lst[i1];
        i3++;
        i1++;
    }

    for (int i = 0; i < i3; i++)
    {
        lst[start + i] = draft[i];
    }
}

void merge_sort(int lst[], int start, int end)
{
    if (start >= end)
    {
        return;
    }

    int mid = (start + end) / 2;
    merge_sort(lst, start, mid);
    merge_sort(lst, mid + 1, end);

    int draft[end - start + 1];
    int i1 = start;
    int i2 = mid + 1;
    int i3 = 0;

    while (i1 <= mid && i2 <= end)
    {
        if (lst[i1] <= lst[i2])
        {
            draft[i3] = lst[i1];
            i1++;
        }
        else
        {
            draft[i3] = lst[i2];
            i2++;
        }
        i3++;
    }

    while (i1 <= mid)
    {
        draft[i3] = lst[i1];
        i1++;
        i3++;
    }

    for (int i = 0; i < i3; i++)
    {
        lst[start + i] = draft[i];
    }
}

int partition(int lst[], int start, int end)
{
    int j = start;
    int val;

    for (int i = start; i < end; i++)
    {
        if (lst[i] < lst[end])
        {
            if (i != j)
            {
                val = lst[i];
                lst[i] = lst[j];
                lst[j] = val;
            }
            
            j++;
        }
    }

    val = lst[j];
    lst[j] = lst[end];
    lst[end] = val;

    return j;
}

void quick_sort(int lst[], int start, int end)
{
    if (start >= end)
    {
        return;
    }

    int i1 = partition(lst, start, end);
    quick_sort(lst, start, i1 - 1);
    quick_sort(lst, i1 + 1, end);
}

void DownHeap(int T[], int n, int i)
{
    int v = T[i];
    int k = 2*i;

    while (k <= n)
    {
        if (k + 1 <= n && T[k+1] > T[k]) k++;
        if (v >= T[k]) break;
        
        T[i] = T[k];
        i = k;
        k = 2*i;
    }

    T[i] = v;
}

void CreateHeap(int T[], int n)
{
    for(int i = n/2; i>=1; i--)
    {
        DownHeap(T, n, i);
    }
}

void HeapSort(int T[], int n)
{
    CreateHeap(T, n);
    for(int i = n; i > 1; i--)
    {
        int max = T[1];
        T[1] = T[i];
        T[i] = max;
        DownHeap(T, i-1, 1);
    }
}

void print(int lst[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", lst[i]);
    }
    printf("\n\n");
}

void inject_random(int lst[], int n)
{
    time_t t = time(NULL);
    srand(t);

    for (int i = 0; i < n; i++)
    {
        lst[i] = rand() % RANGE;
    }
}

int main(int argc, char* argv[])
{
    long int N = 100;
    if (argc > 1)
    {
        N = atol(argv[1]); 
    }
    
    int numbers[N];
    inject_random(numbers, N);
    // print(numbers, N);
    
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    // Testowany algorytm
    merge_sort(numbers, 0, N-1);
    // Koniec testowanego algorytmu
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    double time_taken = 
    (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    
    // print(numbers, N);
    printf("Czas wykonywania: %f sekund\n", time_taken);   
    return 0;
}