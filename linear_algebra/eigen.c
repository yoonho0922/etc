#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX 5

//������������ ��� �迭 ����ü ���� 
typedef struct matrix {
	double a[MAX][MAX];
}matrix;

//�������� ������ ���� �����ϴ� ����ü ����
typedef struct eigenvalue {
	int cnt;	//�������� ����
	int e[MAX];	//�������� ������ �迭
}eigenvalue;

int error;

eigenvalue eigen(matrix a, int n);	//������ ��� �Լ�
matrix eigensub(matrix a, int n, int e);	//�������� �޾Ƽ� ��Ŀ��� �������� �� ����� ��ȯ�ϴ� �Լ�
void printout(matrix a, int n);	//���� ��� ��� �Լ�
void gauss(matrix a, int n);		//���콺 �ҰŹ� ��� �Լ�
void backsub(matrix a, int n);	//�����Թ� ����Լ�

//������ ���
eigenvalue eigen(matrix a, int n) {
	int i = -50;
	int det = 0;
	eigenvalue e;
	e.cnt = 0;

	//2*2����� ������ ���ϱ�
	if (n == 2) {

		while (i < 50 && e.cnt < 2) {
			det = (a.a[0][0] - i) * (a.a[1][1] - i) - a.a[0][1] * a.a[1][0];
			//printf(" %d, %d, %d |", i, det, e.cnt);
			if (det == 0) {
				e.e[e.cnt] = i;
				e.cnt++;
			}
			i++;
		}
	}//3*3����� ������ ���ϱ�
	else if (n == 3) {

		while (i < 50 && e.cnt < 3) {
			det = (a.a[0][0] - i) * ((a.a[1][1] - i) * (a.a[2][2] - i) - a.a[1][2] * a.a[2][1])
				- (a.a[0][1]) * (a.a[1][0] * (a.a[2][2] - i) - a.a[1][2] * a.a[2][0])
				+ (a.a[0][2]) * (a.a[1][0] * a.a[2][1] - (a.a[1][1] - i) * a.a[2][0]);
			if (det == 0) {
				e.e[e.cnt] = i;
				e.cnt++;
			}
			i++;
		}
	}
	if (e.cnt == 0) {
		printf("�������� �������� �ʽ��ϴ�!!\n\n");
		return e;
	}
	printf(" ������ : ");
	for (int j = 0; j < e.cnt; j++)
		printf("%d%s ", e.e[j], j + 1 == e.cnt ? "" : ",");
	printf("\n\n");
	return e;
}

//�������� �� ��� ��ȯ
matrix eigensub(matrix a, int n, int e) {
	matrix b;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				b.a[i][j] = a.a[i][j] - e;
			else
				b.a[i][j] = a.a[i][j];
		}
	}
	return b;
}



//�� ���� ���콺-���� �ҰŹ��� ����

//�������� ���
void printout(matrix a, int n) {
	int i = 0, j = 0;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {

			printf(" %.3lf\t", a.a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

// �Է¹��� ���� �������� ���콺 �ҰŹ����� ���
void gauss(matrix a, int n) {
	int i = 0, j = 0, k = 0, l = 0;
	double multi = 0, temp = 0;

	error = 0;
	k = 0;

	while (k < n && error != 1) {
		l = k;
		for (j = k + 1; j < n; j++) {

			if (fabs(a.a[j][k]) > fabs(a.a[l][k]))
				l = j;

			//j������ ���밪�� �� ū�� ���� �ø�
			for (j = k; j < n; j++) {	//swap (a.a[k][j], a.a[l][j]) 
				temp = a.a[k][j];
				a.a[k][j] = a.a[l][j];
				a.a[l][j] = temp;
			}

			if (a.a[k][k] != 0) {

				for (j = k + 1; j < n; j++) {
					multi = -1 * (a.a[j][k]) / a.a[k][k];	//�ҰŸ� ���� multi ���
					//�� �踦 ���Ұ��� ����

					for (i = k; i < n; i++) {

						if (multi != 0)
							a.a[j][i] = a.a[j][i] + multi * a.a[k][i];
					}
					//printout(a, n);
				}
			}
			else {
				error = 1;
			}
		}
		k = k + 1;
	}

	if (error == 1) {
		printf("Trap condition..... \n");
	}

	//printout(a, n);

	backsub(a, n);
}

// �����Թ� ��� �Լ�
void backsub(matrix a, int n) {

	int i = 0, j = 0, k = 0;
	float sum;



	//������ n���� ���� n-1 ��
	if (a.a[n - 1][n - 1] < 0.1) {
		//������ 3�� ��Ŀ� ���� ���
		if (n == 3) {
			//x1, x2�� x3������ ������ ǥ���ϱ�
			float x1, x2, x3;
			x3 = -7;
			x2 = ((-1) * a.a[1][2] / a.a[1][1]);
			x1 = (-1) * ((a.a[0][1] * x2 + a.a[0][2])) / a.a[0][0];
			x2 *= x3;
			x1 *= x3;

			printf(" | %.1lf |\n", x1);
			printf(" | %.1lf |\n", x2);
			printf(" | %.1lf |\n\n\n", x3);
		}
		//������ 2�� ��Ŀ� ���� ���
		else if (n == 2) {
			if (a.a[n - 1][n - 1] < 0.1) {
				float x1 = a.a[0][0], x2 = a.a[0][1];
				printf(" | %.1lf |\n", x2);
				printf(" | %.1lf |\n", -x1);

			}
		}
	}
}

int main(void) {
	int i = 0, j = 0;
	int n;

	matrix a;

	printf(" ***********************************************************\n");
	printf(" **                                                       **\n");
	printf(" **        ����� �������� �������� ��� ���α׷�         **\n");
	printf(" **                                                       **\n");
	printf(" ***********************************************************\n");


	printf(" ����� �ִ� ����: ");
	scanf("%d", &n);

	printf("\n");

	// ��� �Է�
	printf(" ��� �Է� \n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf(" %d �� %d �� : ", i + 1, j + 1);
			scanf("%lf", &a.a[i][j]);
		}
	}

	printf("\n");

	eigenvalue e = eigen(a, n);	//������ ���ϱ�

	if (e.cnt == 0)	//�������� �������� ���� ��
		return 0;
	matrix b;
	for (i = 0; i < e.cnt; i++) {
		b = eigensub(a, n, e.e[i]);	//��Ŀ��� ������ ����
		printf(" ������ %d \n", e.e[i]);
		printf(" �������� \n");
		gauss(b, n);
	}

	return 0;
}