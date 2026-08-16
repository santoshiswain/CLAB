#include <stdio.h>

struct Result {
    int min;
    int max;
};

struct Result findMinMax(int arr[], int low, int high) {

    struct Result result, left, right;

    // Only one element
    if (low == high) {
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }

    // Two elements
    if (high == low + 1) {

        if (arr[low] < arr[high]) {
            result.min = arr[low];
            result.max = arr[high];
        } else {
            result.min = arr[high];
            result.max = arr[low];
        }

        return result;
    }

    // Divide
    int mid = low + (high - low) / 2;

    // Conquer
    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high);

    // Combine
    if (left.min < right.min)
        result.min = left.min;
    else
        result.min = right.min;

    if (left.max > right.max)
        result.max = left.max;
    else
        result.max = right.max;

    return result;
}

int main() {

    int n;

    printf("Enter the size of array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    struct Result ans = findMinMax(arr, 0, n - 1);

    printf("\nMinimum element = %d\n", ans.min);
    printf("Maximum element = %d\n", ans.max);

    return 0;
}