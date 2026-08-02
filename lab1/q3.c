#include<stdio.h>

void bubbleSortbefore(int arr[], int n) {
    int i,j,temp,step=0;
     for(i=0;i<n-1;i++){
        int swapped=0;
        for(j=0;j<n-1-i;j++){
            
            if(arr[j]>arr[j+1]){
                step++;
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
                swapped=1;
            }
           
        }
        if(swapped==0)
            break;
     }
     printf("Number of steps before optimization: %d\n", step);
}
void bubbleSortafter(int arr[], int n) {
    int i,j,temp,step=0;
     for(i=0;i<n-1;i++){
        for(j=0;j<n-1-i;j++){
          if(arr[j]>arr[j+1]){
               step++;
                 temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
          }  
        }
     }
     printf("Number of steps after optimization: %d\n", step);
}

int main() {
    int arr1[10]={6,7,3,5,9,1,4,8,10,11};


    bubbleSortbefore(arr1, 10);
    int arr2[10]={6,7,3,5,9,1,4,8,10,11};
    bubbleSortafter(arr2, 10);
    return 0;
}