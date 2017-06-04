#include<stdio.h>
#define Max 100

void arymul(int a[2][3], int b[3][4], int c[2][4])
{
	int i, j, k;
	int temp;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 4; j++) {
			temp = 0;
			for (k = 0; k < 3; k++) {
				temp += a[i][k] * b[k][j];
			}
			c[i][j] = temp;
			printf("%d\t", c[i][j]);
		}
		printf("\n");
	}
}
int main()
{
	/*int a[2][3] = { 1,2,3,4,5,6 },
		b[3][4] = { 1,2,3,4,5,6,7,8,9,10,11,12 },
		c[2][4] = { 0 };*/
	int a[Max][Max],b[Max][Max],c[Max][Max];
	int x, y, z;
	printf("请输入第一个矩阵的行数:");
	scanf("%d", &x);
	printf("请输入第一个矩阵的列数(也是第二个矩阵的行数):");
	scanf("%d", &y);
	printf("请输入第二个矩阵的列数:");
	scanf("%d", &y);
	printf("--------------------/n");

	arymul(a, b, c);
	return 0;
}