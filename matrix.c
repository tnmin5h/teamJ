#include <stdio.h>
#include <malloc.h>

int min(int a, int b[], int* P[]);  // �ּ� ���� �˰���
void order(int m, int n, int* P[]);     // ���� ���� ���
int* input(int a);     // dx�� �Է� ����
int** make(int a);    // P ��� ���� �Ҵ�

int main()
{
    int* b, ** P;
    int number, result;

    printf("�ּ� ���� ���\n");
    printf("����� ������ �Է����ּ���: ");
    scanf("%d", &number);  // ����� ���� �Է� �޴´�.

    b = input(number); // �˰����� �Է��� �Ǵ� b ���
    P = make(number);     // ���� ���� ����� ���� P ���

    result = min(number, b, P); // �˰����� ������� result�� ����
    printf("\n�ּ� ������ ������ ");
    order(1, number, P);
    printf("�Դϴ�. \n");// ��� ���� ���� ���� ���
    printf("\n�ּ� ������ ����� %d �Դϴ�.\n", result);

    return 0;
}

int** make(int a) // P ����� ���� �޸� �Ҵ����� �����.
{
    int m;
    int** P = (int**)malloc(0);
    for (m = 0; m < a; m++)
        P[m] = (int*)malloc(sizeof(int) * a);
    return P;
}

int* input(int a)  // �Է� ���� ���ڸ�ŭ bx�� �Է� �޴´�.
{
    int m, * b;
    printf("b0 ~ b%d�� ���� �Է����ּ���. \n", a);
    b = (int*)malloc(sizeof(int) * a);
    for (m = 0; m <= a; m++) {
        printf("b%d = ", m);
        scanf("%d", &b[m]);
    }
    return b;
}

void order(int m, int n, int* P[])  // ������ ���� ������ش�.
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

int min(int a, int b[], int* P[])   // �ּ� ���� �˰���
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
            P[m][n] = min_k;    // �ּҰ��� �ִ� k�� ��
        }
    return M[1][a];    // �ּ� ���� �� ����
}