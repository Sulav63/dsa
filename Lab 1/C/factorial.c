/*Write a program in C to find out the factorial of a user entered number using
iterative method.*/
#include <stdio.h>

// Function to calculate the factorial iteratively
unsigned long long factorial(int n) {
    unsigned long long result = 1;

    // Calculate factorial using a loop
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }

    return result;
}

int main() {
    // Declare a variable to store user-entered number
    int number;

    printf("Enter a number: ");
    scanf("%d", &number);

    // Check for negative input
    if (number < 0) {
        printf("Factorial is not defined for negative numbers.\n");
    } else {
        // Calculate and display the factorial
        printf("Factorial of %d is: %llu\n", number, factorial(number));
    }

    return 0;
}
