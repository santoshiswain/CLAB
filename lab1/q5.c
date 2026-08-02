#include<stdio.h>

int main(){
    int n;
    printf("Enter the number of array elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the value of array elements(ONly enter 0 followed by 1):\n");
    for(int i=0;i<n;i++){
        printf("Enter the value of element %d: ", i+1);
        scanf("%d", &arr[i]);
    }
    int i;
    for(i=0;i<n;i++){
        if(arr[i]==1){
            printf("The first occurrence of 1 is at index: %d\n", i);
            printf("The partition index is: %d\n", i);
            break;
        }
    }
    return 0;
}