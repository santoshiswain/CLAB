#include<stdio.h>
int  search_defective_coin(int arr[],int s,int e){
if(s>e){
    return -1;
}
if(s==e){
return s;        
}
int mid=(s+e)/2;
int leftend=mid;
int right=mid+1;
int leftsum=0;
int rightsum=0;

for(int i=s;i<=leftend;i++){
leftsum+=arr[i];
}
for(int i=right;i<=e;i++){
    rightsum+=arr[i];
}
if(leftsum<rightsum){
  return   search_defective_coin(arr,s,leftend);
}else if(rightsum<leftsum){
   return  search_defective_coin(arr,right,e);
}else if(leftsum==rightsum){
    return -1;
}

}
int main(){
    //suppose each element of array represent size of coin
    //in array all coin have same size except one(may or may not be)
    //we have to give this small element
    //process is accending order searching and return small element

    //time com-log(n)
    int n;
    printf("Enter the size of array");
    scanf("%d",&n);

    int arr[n];
    int i;
    printf("Enter the element in sorted order: ");
    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    int s=0;
    int e=n-1;

    int k=search_defective_coin(arr,s,e);
    printf("the answer is : %d",k);

    return 0;
}