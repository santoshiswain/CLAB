#include<stdio.h>




void binarySearch(int arr[],int n,int key){
    int s=0;
    int e=n-1;
   while(s<=e){
    int mid=(e+s)/2;
    if(arr[mid]==key){
       printf("The searched element : %d \n",arr[mid]);
       break;  
    }else if(arr[mid]<key){
        s=mid+1;
    }else{
        e=mid-1;
    }
   }
   if(s>e){
    printf("The searched element not found\n");
   }
   
}
void ternarysearch(int arr[],int n,int key){
    int s=0;
    int l=n-1;
    int i;

    while(s<=l){
        int mid1=s+(s+l)/3;
        int mid2=l-(s+l)/3;
       if(arr[mid1]==key){
        printf("The sorted elment: %d \n",arr[mid1]);
        break;
       }
       if(arr[mid2]==key){
        printf("The searched element is : %d \n",arr[mid2]);
        break;
       }
       else if(key<arr[mid1]){
        l=mid1-1;
       }else if(key>arr[mid2]){
        s=mid2+1;
       }else if(arr[mid1]<key && arr[mid2]>key){
        s=mid1+1;
        l=mid2-1;
       }
    }
    if(s>l){
        printf("The searched element not found\n");
    }
}
int main(){
    int n,i;
    printf("Enter the size of array: ");
    scanf("%d",&n);
    int arr[n];
    printf("Enter the elment of array(Enter sorted form of array): ");
    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    binarySearch(arr,n,5);
    ternarysearch(arr,n,5);
    return 0;
}