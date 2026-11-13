#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void initSystem()//初始化，引入srand函数和time函数，以供后续生成随机数，打印系统标题
{
	srand(time(NULL));
	printf("==========智能口算系统==========\n");
}
void generateQuestion(int type, int* num1, int* num2, int* op)//传进num，让函数生成随机数并赋值给num1和num2，传进op，让函数生成运算符类型并赋值给op
{
	*op = type;
	if (type == 0)//加法
	{
		*num1 = rand() % 90 + 10;
		*num2 = rand() % 90 + 10;
	}
	else if (type == 1)//减法
	{
		*num1 = rand() % 90 + 10;
		*num2 = rand() % 90 + 10;
		if (*num1 < *num2)//保证被减数大于减数，否则交换两个数
		{
			int tmp;
			tmp = *num1;
			*num1 = *num2;
			*num2 = tmp;
		}
	}
	else if (type == 2)//乘法
	{
		*num1 = rand() % 9 + 1;
		*num2 = rand() % 9 + 1;
	}
	else if (type == 3)//除法
	{
		*num2 = rand() % 9 + 1;//除数
		int result = rand() % 9 + 1;//商
		*num1 = (*num2) * result;//被除数
	}
}
void random(int* type)//用0-3表示四种运算类型，0为加法，1为减法，2为乘法，3为除法
{
	*type = rand() % 4 + 0;
}
void getOpChar(char* operator,int* op)//根据op的值，给operator赋值为对应的运算符，用于输出运算符号
{
	if (*op == 0)
	{
		*operator = '+';
	}
	else if (*op == 1)
	{
		*operator = '-';
	}
	else if (*op == 2)
	{
		*operator = '*';
	}
	else if (*op == 3)
	{
		*operator = '/';
	}
}
void generate(int* num1, int* num2, int* op)
{
	char operator;
	for (int k = 0; k < 4; k++)
	{
		for (int i = 1; i <= 10; i++)
		{
			generateQuestion(k, num1, num2, op);
			getOpChar(&operator, op);
			printf("本次题目：%d %c %d = ?\n", *num1, operator, *num2);
		}
	}
}void evaluateAnswer()
{
	
}
void updateStats()
{
	printf("学生：学生A\n题型：加减乘除各10题\n----第一部分：加法----");
}
void printReport()
{

}
int main()
{
	initSystem();
	int num1, num2, op;
	generate(&num1, &num2, &op);
	evaluateAnswer();
	updateStats();
	printReport();
	return 0;
}