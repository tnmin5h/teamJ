#include <stdio.h>
#include <malloc.h>

int min(int a, int b[], int* P[]);  // 최소 곱셈 알고리즘
void order(int m, int n, int* P[]);     // 최적 순서 출력
int* input(int a);     // dx를 입력 받음
int** make(int a);    // P 행렬 동적 할당

int main()
{
    int* b, ** P;
    int number, result;

    printf("최소 곱셈 행렬\n");
    printf("행렬의 개수를 입력해주세요: ");
    scanf("%d", &number);  // 행렬의 개수 입력 받는다.

    b = input(number); // 알고리즘의 입력이 되는 b 행렬
    P = make(number);     // 최적 순서 출력을 위한 P 행렬

    result = min(number, b, P); // 알고리즘의 결과값을 result에 저장
    printf("\n최소 곱셈의 순서는 ");
    order(1, number, P);
    printf("입니다. \n");// 행렬 곱셈 최적 순서 출력
    printf("\n최소 곱셈의 결과는 %d 입니다.\n", result);

    return 0;
}

int** make(int a) // P 행렬을 동적 메모리 할당으로 만든다.
{
    int m;
    int** P = (int**)malloc(0);
    for (m = 0; m < a; m++)
        P[m] = (int*)malloc(sizeof(int) * a);
    return P;
}

int* input(int a)  // 입력 받은 숫자만큼 bx를 입력 받는다.
{
    int m, * b;
    printf("b0 ~ b%d의 값을 입력해주세요. \n", a);
    b = (int*)malloc(sizeof(int) * a);
    for (m = 0; m <= a; m++) {
        printf("b%d = ", m);
        scanf("%d", &b[m]);
    }
    return b;
}

void order(int m, int n, int* P[])  // 최적의 순서 출력해준다.
{
    int k;
    if (m == n)
        printf("A%d", m);
    else {
        k = P[m][n];
        printf("(");
        order(m, k, P);
        order(k + 1, n, P);
        printf(")");
    }
}

int min(int a, int b[], int* P[])   // 최소 곱셉 알고리즘
{
    int m, n, k, d, min_k = 0;
    int** M, temp = 0;
    M = make(a + 1);
    for (m = 1; m <= a; m++)
        M[m][m] = 0;
    for (d = 1; d <= a - 1; d++)
        for (m = 1; m <= a - d; m++) {
            n = m + d;

            for (k = m; k <= n - 1; k++) {
                M[m][n] = M[m][k] + M[k + 1][n] + b[m - 1] * b[k] * b[n];
                if (m == k) {
                    temp = M[m][n];
                    min_k = k;
                }
                else if (M[m][n] > temp) {
                    M[m][n] = temp;
                }
                else
                    min_k = k;
            }
            P[m][n] = min_k;    // 최소값을 주는 k의 값
        }
    return M[1][a];    // 최소 곱셈 값 리턴
}