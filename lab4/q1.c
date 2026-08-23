#include<stdio.h>


typedef struct
{
    int number;
    char colour;
}Item;
int main(){
    int n;
    printf("Enter the size of n: ");
    scanf("%d",&n);
    Item red[n],blue[n],yellow[n];
    int r=0,b=0,y=0;

    Item items[n];

     printf("Enter number and color (R/B/Y):\n");

    for(int i=0;i<n;i++){
        scanf("%d %c",&items[i].number,&items[i].colour);

        if(items[i].colour=='R'){
            red[r++]=items[i];
        }else if(items[i].colour=='B'){
            blue[b++]=items[i];
        }else{
            yellow[y++]=items[i];
        }
    }

    printf("the sorted array is\n");

    for(int i=0;i<r;i++){
        printf("%d %c\n", red[i].number,red[i].colour);
    }
    for(int i=0;i<b;i++){
        printf("%d %c\n", blue[i].number,blue[i].colour);
    }
    for(int i=0;i<y;i++){
        printf("%d %c\n", yellow[i].number,yellow[i].colour);
    }
  return 0;
}