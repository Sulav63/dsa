/*Write a program in C to get 2 numbers and display the max and min.*/
#include <stdio.h>

int main() {
    double num1, num2;

    printf("Enter the first number: ");
    scanf("%lf", &num1);

    printf("Enter the second number: ");
    scanf("%lf", &num2);

    if (num1 > num2) {
        printf("Maximum: %.2lf\n", num1);
        printf("Minimum: %.2lf\n", num2);
    } else if (num2 > num1) {
        printf("Maximum: %.2lf\n", num2);
        printf("Minimum: %.2lf\n", num1);
    } else {
        printf("Both numbers are equal.\n");
    }

    return 0;
}
