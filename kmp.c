#include <stdio.h>  
#include <string.h>  

int next[32] = { -999 };

/* 返回模式串T在母串S中第pos个字符的位置 */
/* 调试小技巧 print x = value 或 set var x = value 可以改变gdb运行时变量的值 */
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
			i = i - j + 1;/*这里要理解一下*/
			j = 0;
		}
	}

	/* 注意strlen(T)意味着j的取值范围为0 ~ (strlen(T) - 1) */
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
		if ((k == -1) || (T[j] == T[k])) //注意等号是==，而不是=  
		{
			++k; // 注意是先加后使用  
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
		/* j = -1 表示next[0], 说明失配处在模式串T的第0个字符。所以这里特殊处理，然后令i+1和j+1。*/
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