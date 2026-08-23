#include<stdio.h>


void merge(int s1[],int s,int e,int mid){
    int i=s;
    int j=mid+1;
    int arr[e-s+1];
    int k=0;

    while(i<=mid && j<=e){
        if(s1[i]<=s1[j]){
            arr[k++]=s1[i];
            i++;
        }else{
            arr[k++]=s1[j];
            j++;
        }
    }

    while(i<=mid){
        arr[k++]=s1[i];
        i++;
    }

    while(j<=e){
        arr[k++]=s1[j];
        j++;
    }

    for(int i=s,k=0;i<=e;i++,k++){
        s1[i]=arr[k];
    }


}

void mergesort(int s1[],int s,int e){
    if(s>=e){
        return;
    }
    int mid=s+(e-s)/2;
    mergesort(s1,s,mid);
    mergesort(s1,mid+1,e);
    merge(s1,s,e,mid);
}

int binarysearch(int s2[],int target,int s,int e){
   while(s<=e){
    int mid=s+(e-s)/2;
    if(s2[mid]==target){
        return 1;
    }else if(s2[mid]<target){
        s=mid+1;
    }else{
        e=mid-1;
    }
   }
   return 0;
}

int main(){
    int n1;
    printf("Enter the size of s1 and s2\n: ");
    scanf("%d",&n1);
    int s1[n1];
    int s2[n1];
    int i;
    printf("Enter the integer for s1\n");
    for(i=0;i<n1;i++){
        scanf("%d",&s1[i]);
    }
   printf("Enter the integer for s2\n");
      for(i=0;i<n1;i++){
        scanf("%d",&s2[i]);
    }
    int x;
    printf("Enter X:\n");
    scanf("%d",&x);

    mergesort(s1,0,n1-1);
    printf("Sorted version\n");
    for(i=0;i<n1;i++){
        printf("%d\n",s1[i]);
    }
    for(i=0;i<n1;i++){
       int target=x-s1[i];
       if(binarysearch(s2,target,0,n1-1)){
          printf("Pair found: %d + %d = %d\n",s1[i], target, x);
          return 0;
       }
    }
    printf("No pair exists whose sum is %d\n", x);
    return 0;
}