#include <stdio.h>

int main() {
    int n, f1 = 1;
    double x;
    long double sum = 1, prev = 1, current;
    printf("Input 1 < x < 2 and n > 0\n");
    scanf("%lf %d", &x, &n);
    printf("1 current element = 1\n");
    for (int i = 2; i <= n; i++) {
        current = prev * (2 * x / 3 - 1);
        sum += current;
        prev = current;
        printf("%d current element = %Lf sum = %Lf\n", i, current, sum);
    }
    printf("answer = %Lf right answer = %f\n", sum, 1.5/x);
}