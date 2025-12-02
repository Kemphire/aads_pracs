#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int get_random(int max, int min)
{
    return rand() % (max - min + 1) + min;
}

int randomized_partition(int *arr, int left, int right)
{
    int random_i = get_random(right, left);
    swap(&arr[right], &arr[random_i]);
    int x = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++)
    {
        if (arr[j] <= x)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[right]);
    return i + 1;
}

int randomized_select(int *arr, int left, int right, int i)
{
    if (left == right)
    {
        return arr[left];
    }

    int q = randomized_partition(arr, left, right);

    int k = q - left + 1;

    if (i == k)
    {
        return arr[q];
    }
    else if (i < k)
    {
        return randomized_select(arr, left, q - 1, i);
    }
    else
    {
        return randomized_select(arr, q + 1, right, i - k);
    }
}

int main()
{
    int arr[] = {7, 1, 4, 3, -1};
    int ele = randomized_select(arr, 0, 4, 3);

    printf("The %d'rd largest element is %d\n", 3, ele);
};
