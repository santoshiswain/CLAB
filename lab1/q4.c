#include<stdio.h>
long long moves=0;


void TOH(int n,char first,char aux,char last){
    if(n==1){
        moves++;
        printf("Move disk 1 from %c to %c\n", first, last);
        return;
    }
    else{
        TOH(n-1,first,last,aux);
        moves++;
        printf("Move disk %d from %c to %c\n", n, first, last);
        TOH(n-1,aux,first,last);
    }
}
int main() {
    int n;
    printf("Enter number of disk: ");
    scanf("%d", &n);
    TOH(n, 'A', 'B', 'C');
    printf("Total moves: %lld\n", moves);
    return 0;
}