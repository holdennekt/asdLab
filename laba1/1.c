#include <stdio.h>

long double sum = 1;

void calculate(double x, int n, long double prev, int i) {
    long double current = prev * (2 * x / 3 - 1);
    sum += current;
    printf("%d current element = %Lf sum = %Lf\n", i, current, sum);
    if (i <= n) calculate(x, n, current, i + 1);
}

int main() {
    int n, f1 = 1, i = 2;
    double x;
    printf("Input 1 < x < 2 and n > 0\n");
    scanf("%lf %d", &x, &n);
    printf("1 current element = 1 sum = 1\n");
    calculate(x, n, f1, i);
    printf("answer = %Lf right answer = %f\n", sum, 1.5/x);
}