#include <stdio.h>

long double prev = 1;

double calculate(double x, int n, long double sum) {
    if (n > 2) sum = calculate(x, n - 1, sum);
    long double current = prev * (2 * x / 3 - 1);
    prev = current;
    sum += current;
    printf("%d current element = %Lf sum = %Lf\n", n, current, sum);
    return sum;
}

int main() {
    int n, f1 = 1;
    double x;
    printf("Input 1 < x < 2 and n > 0\n");
    scanf("%lf %d", &x, &n);
    printf("1 current element = 1 sum = 1\n");
    double result = calculate(x, n, 1);
    printf("answer = %f right answer = %f\n", result, 1.5/x);
}