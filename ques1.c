#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int get_random(int max, int min) { return rand() % (max - min + 1) + min; }

int comparisions = 0;

int randomized_partition(int *arr, int left, int right) {
  int random_i = get_random(right, left);
  swap(&arr[right], &arr[random_i]);
  int x = arr[right];
  int i = left - 1;
  for (int j = left; j < right; j++) {
    if (arr[j] <= x) {
      comparisions++;
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[right]);
  return i + 1;
}

void quick_sort(int *arr, int left, int right) {
  if (left < right) {
    int q = randomized_partition(arr, left, right);
    quick_sort(arr, left, q - 1);
    quick_sort(arr, q + 1, right);
  }
}

int main(void) {
  int arr[] = {3, 2, 3, 2, 1, 43, 0, -1, 7};
  quick_sort(arr, 0, 8);
  for (int i = 0; i < 9; i++) {
    printf("%d ", arr[i]);
  }
  printf("\nNo. of comparisions is %d\n", comparisions);
}
