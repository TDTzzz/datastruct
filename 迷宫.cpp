/*ע��������̽���Թ�������˳�� = >  1 - �¡�2 - �ҡ�3 - �ϡ�4 - �� <= �������ƣ����ң���ʱ�뷽����Ϊ���ھ����ұ��·�*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define stack_init_size 200
#define stack_increment 10
#define OVERFLOW 0
#define OK 1
#define ERROE 0
#define TRUE 1
#define FALSE 0
typedef int Status;

typedef struct {
	int x;
	int y;
}PosType;

typedef struct {
	int ord;	//	ͨ������·���ϵġ���š�
	PosType seat;	//ͨ�������Թ��еġ�����λ�á�
	int di;			//�Ӵ�ͨ����������һͨ����ġ�����
}SElemType;

typedef struct {
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

int mg[20][20];

/*��������Թ��ĺ���
/*Ϊ���ܹ��þ�����ͨ��������ͨ���Ŀ�Ͳ���ͨ���Ŀ������ȴ���Ϊ2:1*/
void Random() {
	int i, j, k;
	srand(time(NULL));
	mg[1][0] = mg[1][1] = mg[18][19] = 0;	//����ڡ���������Ϊ��0������ͨ��
	for (j = 0; j<20; j++)
		mg[0][j] = mg[19][j] = 1;		/*�����Թ���Χ�������ߡ�����ֻ֤��һ�����ں����*/
	for (i = 2; i<19; i++)
		mg[i][0] = mg[i - 1][19] = 1;		/*�����Թ���Χ�������ߡ�����ֻ֤��һ�����ں����*/
	for (i = 1; i<19; i++)
		for (j = 1; j<19; j++) {
			k = rand() % 3;	//�������0��1��2������
			if (k)
				mg[i][j] = 0;
			else {
				if ((i == 1 && j == 1) || (i == 18 && j == 18))	/*��Ϊ����ڻ����һ����·�Ǳؾ�֮·�������ͨ����Ϊ��0���Ӵ��Թ���ͨ�еĸ���*/
					mg[i][j] = 0;
				else
					mg[i][j] = 1;
			}
		}
}
//����һ����ջ
Status InitStack(SqStack &s) {
	s.base = (SElemType *)malloc(stack_init_size * sizeof(SElemType));
	if (!s.base) return OVERFLOW;
	s.top = s.base;
	s.stacksize = stack_init_size;
	return OK;
}

//��ǰ��ɷ�ͨ��
Status Pass(PosType e) {
	if (mg[e.x][e.y] == 0)  //0ʱ����ͨ��  
		return OK;		// �����ǰλ���ǿ���ͨ��������1
	return OVERFLOW;	// �����������0
}

//����ͨ�����㼣
Status FootPrint(PosType e) {
	mg[e.x][e.y] = 7;
	return OK;
}

//ѹ��ջ
Status Push(SqStack &s, SElemType e) {
	if (s.top - s.base >= s.stacksize) {
		s.base = (SElemType *)realloc(s.base, (s.stacksize + stack_increment) * sizeof(SElemType));
		if (!s.base)exit(OVERFLOW);
		s.top = s.base + s.stacksize;
		s.stacksize += stack_increment;
	}
	*s.top++ = e;
	return OK;
}

//��ջ
Status Pop(SqStack &s, SElemType &e) {
	if (s.top == s.base)
		return ERROE;
	e = *--s.top;
	return OK;
}

//��һ��
PosType NextPos(PosType &e, int dir) {
	PosType E;
	switch (dir) {
	case 1:E.x = e.x;		//����
		E.y = e.y + 1;
		break;
	case 2:E.x = e.x + 1;	//����
		E.y = e.y;
		break;
	case 3:E.x = e.x;		//����
		E.y = e.y - 1;
		break;
	case 4:E.x = e.x - 1;	//����
		E.y = e.y;
		break;
	}
	return E;
}

//�Ƿ��ջ
Status StackEmpty(SqStack s) {
	if (s.top == s.base)
		return OK;
	return OVERFLOW;
}

//���²���ͨ�����㼣
Status MarkPrint(PosType e) {
	mg[e.x][e.y] = 3;
	return OK;
}

//�Թ�����
// ���Թ�maze�д���� start������ end��ͨ���������һ�������ջ��
// ����ջ�׵�ջ������������TRUE�����򷵻�FALSE
Status MazePath(int mg, PosType start, PosType end, SqStack &s) {
	PosType curpos;
	InitStack(s);
	SElemType e;
	int curstep;
	curpos = start;	// �趨"��ǰλ��"Ϊ"���λ��"
	curstep = 1;		// ̽����һ��
	do {
		if (Pass(curpos)) {	// ��ǰλ�ÿ�ͨ��������δ���ߵ�����ͨ����
			FootPrint(curpos);	// �����㼣
			e.di = 1;
			e.ord = curstep;
			e.seat = curpos;
			Push(s, e);	// ����·��
			if (curpos.x == end.x&&curpos.y == end.y) {
				printf("\n\n0��_��0 �ܵ����յ�!");
				return TRUE;
			}
			curpos = NextPos(curpos, 1);	// ��һλ���ǵ�ǰλ�õĶ���
			curstep++;	 // ̽����һ��
		}
		else {	// ��ǰλ�ò���ͨ��
			if (!StackEmpty(s)) {
				Pop(s, e);
				while (e.di == 4 && !StackEmpty(s)) {
					MarkPrint(e.seat);
					Pop(s, e);
				}
				if (e.di<4) {
					e.di++;
					Push(s, e);	// ���²���ͨ���ı�ǣ����˻�һ��
					curpos = NextPos(e.seat, e.di);	/* ��ǰλ����Ϊ�·�������ڿ�*/
				}//if
			}//if
		}//else
	} while (!StackEmpty(s));
	printf("\n\n�� ! ���ܵ����յ�!");
	return FALSE;
}

//��ӡ�Թ�
void PrintMaze() {
	int i, j;
	printf("����·��:\n\n");
	for (i = 0; i<20; i++) {
		for (j = 0; j<20; j++) {
			if (mg[i][j] == 0)printf("  ");
			else if (mg[i][j] == 1) printf("��");		//�Թ��ġ�ǽ��
			else if (mg[i][j] == 3) printf("��");      //��ͨ��·
			else if (mg[i][j] == 7)printf("��");		//ͨ����·��
		}
		printf("\n");
	}
	printf("\n");
}

void main() {
	SqStack S;
	PosType start, end;
	start.x = 1; start.y = 0;	//�������	
	end.x = 18; end.y = 19;	//�յ�����
	printf("\n==================�Թ���Ϸ==================");
	printf("\n˵��:�������ߵ�����\t���߲�ͨ������");
	printf("\n    ���ո񡱴���δ����������");
	printf("\n     �������ͨ����·����ָ���յ�");
	printf("\n============================================");
	Random();
	printf("\n\nTest 1:");
	MazePath(mg[20][20], start, end, S);
	PrintMaze();
	system("pause");
	Random();
	printf("\nTest 2:");
	MazePath(mg[20][20], start, end, S);
	PrintMaze();
	system("pause");
	Random();
	printf("\nTest 3:");
	MazePath(mg[20][20], start, end, S);
	PrintMaze();
	printf("\n==========�����˳�����лʹ��!==========\n");
}