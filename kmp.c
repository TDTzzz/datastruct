#include <stdio.h>  
#include <string.h>  

int next[32] = { -999 };

/* ����ģʽ��T��ĸ��S�е�pos���ַ���λ�� */
/* ����С���� print x = value �� set var x = value ���Ըı�gdb����ʱ������ֵ */
int index_BM(char *S, char *T, int pos)
{
	int i;
	int j;

	i = pos;
	j = 0;

	while ((i < strlen(S)) && (j < strlen(T)))
	{
		if (S[i] == T[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;/*����Ҫ���һ��*/
			j = 0;
		}
	}

	/* ע��strlen(T)��ζ��j��ȡֵ��ΧΪ0 ~ (strlen(T) - 1) */
	if (strlen(T) == j)
	{
		return i - strlen(T);
	}
	else
	{
		return -1;
	}
}

void get_next(char *T, int *next)
{
	int k = -1;
	int j = 0;

	next[j] = k;

	while (j < strlen(T))
	{
		if ((k == -1) || (T[j] == T[k])) //ע��Ⱥ���==��������=  
		{
			++k; // ע�����ȼӺ�ʹ��  
			++j;
			next[j] = k;
		}
		else
		{
			k = next[k];
		}
	}
}

int index_KMP(char *S, char *T, int pos)
{
	int i;
	int j;

	i = pos;
	j = 0;

	while ((i < strlen(S)) && (j < strlen(T)))
	{
		/* j = -1 ��ʾnext[0], ˵��ʧ�䴦��ģʽ��T�ĵ�0���ַ��������������⴦��Ȼ����i+1��j+1��*/
		if ((j == -1) || S[i] == T[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}

	if (strlen(T) == j)
	{
		return i - strlen(T);
	}
	else
	{
		return -1;
	}
}

void print_next(int next[], int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		printf("next[%d] = %d\n", i, next[i]);
	}
}

int main(void)
{

	char *s = "abaabcabcacbabcac";
	char *t = "abcacb";
	/*char *s = "ababbaabbabbcde";
	char *t = "ababcaabc";*/
	int pos = 0;
	int index;

	printf("================ BM ==============\n");
	index = index_BM(s, t, pos);
	printf("index = %d\n", index);

	printf("================ KMP ==============\n");
	get_next(t, next);
	print_next(next, strlen(t));
	
	index = index_KMP(s, t, pos);
	printf("index = %d\n", index);
}