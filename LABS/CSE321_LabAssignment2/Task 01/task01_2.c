#include <stdio.h>

int is_perfect(int n) {
    int sum = 0;

    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }

    return sum == n;
}

int main() {
    int start, end;

    scanf("%d", &start);
    scanf("%d", &end);

    for (int num = start; num <= end; num++) {
        if (is_perfect(num)) {
            printf("%d\n", num);
        }
    }
}
