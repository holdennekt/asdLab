#include <stdio.h>

double calculate(double x, int n, int i, double prev) {
    long double sum = 0;
    long double current = prev * (2 * x / 3 - 1);
    prev = current;
    printf("%d current element = %Lf\n", i, current);
    if (i < n) sum = calculate(x, n, i + 1, current) + prev;
    else sum += current;
    return sum;
}

int main() {
    int n, f1 = 1;
    double x;
    printf("Input 1 < x < 2 and n > 0\n");
    scanf("%lf %d", &x, &n);
    printf("1 current element = 1\n");
    double result = calculate(x, n, 2, f1) + 1;
    printf("answer = %f right answer = %f\n", result, 1.5/x);
}