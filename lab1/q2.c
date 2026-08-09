#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n;
    int fairHeads = 0;
    int biasedHeads = 0;

    
    double biasedProbability = 0.7;

    printf("Enter number of tosses: ");
    scanf("%d", &n);

    
    srand(time(NULL));

   
    for (int i = 0; i < n; i++) {

        
        if (rand() % 2 == 0) {
            fairHeads++;
        }

        
        double r = (double)rand() / RAND_MAX;

        if (r < biasedProbability) {
            biasedHeads++;
        
    }
    double fairProbability = (double)fairHeads / n;
    double biasedExperimentalProbability =
        (double)biasedHeads / n;


    printf("Number of tosses: %d\n", n);

    printf("\nFair Coin:\n");
    printf("Number of HEADS: %d\n", fairHeads);
    printf("Experimental P(HEAD) = %.4f\n", fairProbability);

    printf("\nBiased Coin:\n");
    printf("Number of HEADS: %d\n", biasedHeads);
    printf("Experimental P(HEAD) = %.4f\n",
           biasedExperimentalProbability);

    return 0;
}