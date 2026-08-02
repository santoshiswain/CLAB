#include<stdio.h>
void bubbleSortbefore(int arr[], int n) {
    int i,j,temp;
     for(i=0;i<n-1;i++){
        int swapped=0;
        for(j=0;j<n-1-i;j++){
            
            if(arr[j]>arr[j+1]){
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
                swapped=1;
            }
           
        }
        if(swapped==0)
            break;
     }
    
}
int main(){
      int n;
    printf("Enter the number of array elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the value of array elements:\n");
    for(int i=0;i<n;i++){
        printf("Enter the value of element %d: ", i+1);
        scanf("%d", &arr[i]);
    }
   bubbleSortbefore(arr, n);
   for(int i=1;i<n;i++){
       if(arr[i-1]==arr[i]){
        printf("The duplicate element is: %d\n", arr[i]);
       return 0;
       } 
    }
    printf("No duplicate element found.\n");
}