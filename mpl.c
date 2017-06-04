
#include<stdio.h>


int result[] = { 0 };
int MX_double(int x[], int xMax, int y[], int yMax)
{
	int i = 0, k = 0;

	int resultMax = 0;
	resultMax = xMax + yMax;
	memset(result, 0, (1 + resultMax) * sizeof(double));

	for (i = 0; i <= xMax; i++)
	{
		for (k = 0; k <= yMax; k++)
		{
			result[i + k] += x[i] * y[k];
		}
	}

	return 0;
}
int main()
{
	int xMax,yMax;
	int n,m;
	int* x;
	int* y;
	printf("请输入第一个多项式的个数: ");
	while (1)
	{
		scanf("%d", &n);
		if (n > 1)
			break;
		else
			printf("重输入多项式个数:");
	}
	x = malloc(n * sizeof(int));
	printf("输入这%d个多项式的系数:", n);
	for (int i = 0; i < n;i++) {
		scanf("%d", &x[i]);
	}
	xMax = n - 1;

	printf("请输入第二个多项式的个数: ");
	while (1)
	{
		scanf("%d", &m);
		if (m > 1)
			break;
		else
			printf("重输入多项式个数:");
	}
	y = malloc(m * sizeof(int));
	printf("输入这%d个多项式的系数:", m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &y[i]);
	}
	yMax = m - 1;

	MX_double(x, xMax, y, yMax);
	printf("这两个多项式相乘的结果为:\n");
	for (int i = 0; i <= xMax+yMax; i++) {
		if (i == xMax+yMax) {
			printf("%d*x^%d", result[i], i);
			printf("\n");
		}
		else if(i==0){
			printf("%d+", result[0]);
		}
		else {
			printf("%d*x^%d+", result[i], i);
		}
	}


	return 0;
}
