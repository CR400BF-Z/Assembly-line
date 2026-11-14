#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void initSystem()//初始化，引入srand函数和time函数，以供后续生成随机数，打印系统标题
{
	srand(time(NULL));
	printf("==========智能口算系统==========\n");
}
int evaluateAnswer(int* num1, int* num2, int* op, int userans) {//判断对错的函数
	int rightans;
	switch (*op)
	{
		case 0:
			rightans = *num1 + *num2;
			break;
		case 1:
			rightans = *num1 - *num2;
			break;
		case 2:
			rightans = (*num1) * (*num2);
			break;
		case 3:
			rightans = (*num1) / (*num2);
			break;
	}
	if (userans == rightans)
	{
		printf("√ 正确");
		return 1;
	}
	else
	{
		printf("× 错误，正确答案是%d", rightans);
		return 0;
	}
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
		*num1 = (*num2) * result;//被除数,这样能直接避免0的出现
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
	printf("学生：学生A\n题型：加减乘除各10题\n");
	char operator;
	for (int k = 0; k < 4; k++)
	{
		if (k == 0)
		{
			printf("----第一部分：加法----\n");
		}
		else if (k == 1)
		{
			printf("----第二部分：减法----\n");
		}
		else if (k == 2)
		{
			printf("----第三部分：乘法----\n");
		}
		else if (k == 3)
		{
			printf("----第四部分：除法----\n");
		}
		for (int i = 1; i <= 10; i++)
		{
			generateQuestion(k, num1, num2, op);
			getOpChar(&operator, op);
			printf("第%d题：%d %c %d = ?\n",k * 10 + i, *num1, operator, *num2);
			int userans;
			printf("请输入你的答案\n");
			while (1) // 加个 while(1)，输入非法让他重新输，直到输对为止
			{
				if (scanf("%d", &userans) != 1)
				{
					printf("输入无效，请输入一个数字：");
					while (getchar() != '\n'); // 清空缓冲区
				}
				else
				{
					break; // 输入合法，跳出 while 循环
				}
			}
			int tof = evaluateAnswer(num1, num2, op, userans);//调用evaluateAnswer函数，判断对错，返回1或0，用于统计
			printf("\n");
		}
	}
}
void updateStats()
{

}
void printReport()
{

}
int main()
{
	initSystem();
	int num1, num2, op;
	generate(&num1, &num2, &op);
	printReport();
	return 0;
}