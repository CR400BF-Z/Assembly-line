#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void updateStats(int tof, int qNo, int num1, int num2, int op, int userans, int rightans, float* score, int* correctcount, int* wrongcount, int wrongQNo[], int wrongN1[], int wrongN2[], int wrongop[], int wronguserAns[], int wrongRightAns[],int k,int* wrong_total,int* add_correct,int* sub_correct,int* mul_correct,int* div_correct);//声明函数
void printReport(float score, int correctcount, int wrongcount, int wrongQNo[], int wrongN1[], int wrongN2[], int wrongop[], int wronguserAns[], int wrongRightAns[], int wrong_total, int add_correct, int sub_correct, int mul_correct, int div_correct);//声明函数
void initSystem()//初始化，引入srand函数和time函数，以供后续生成随机数，打印系统标题
{
	srand(time(NULL));
	printf("==========智能口算系统==========\n");
}
int evaluateAnswer(int* num1, int* num2, int* op, int userans) {//判断对错的函数
	int rightans;
	switch (*op)//根据op的值，判定运算类型，计算正确答案
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
	if (userans == rightans)//输出正确和错误
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
void generate(int* num1, int* num2, int* op)//流水线生成题目函数
{
	int tof;
	int correctcount = 0;//正确数
	int wrongcount = 0;//错误数
	float score = 0;//总分
	int wrong_total = 0;//错误总计数
	int add_correct = 0;//加法区正确计数
	int sub_correct = 0;//减法区正确计数
	int mul_correct = 0;//乘法区正确计数
	int div_correct = 0;//除法区正确计数
	int wrongQNo[40], wrongN1[40], wrongN2[40], wrongop[40], wronguserAns[40], wrongRightAns[40];//用数组存储后续统计要用的数字和符号
	printf("学生：学生A\n题型：加减乘除各10题\n");
	char operator;
	for (int k = 0; k < 4; k++)//用k判断运算符，外循环
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
		for (int i = 1; i <= 10; i++)//外循环完毕后的内循环
		{
			generateQuestion(k, num1, num2, op);//核心出题模块
			getOpChar(&operator, op);//根据op转换为运算符
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
			tof = evaluateAnswer(num1, num2, op, userans);//调用evaluateAnswer函数，判断对错，返回1或0，用于统计
			int rightans = 0;
			if (*op == 0)
			{
				rightans = *num1 + *num2;
			}
			else if (*op == 1)
			{
				rightans = *num1 - *num2;
			}
			else if (*op == 2)
			{
				rightans = (*num1) * (*num2);
			}
			else if (*op == 3)
			{
				rightans = (*num1) / (*num2);
			}
			//引入统计
			updateStats(tof, k * 10 + i, *num1, *num2, *op, userans,rightans ,&score, &correctcount, &wrongcount,wrongQNo,wrongN1,wrongN2,wrongop,wronguserAns,wrongRightAns,k,&wrong_total,&add_correct,&sub_correct,&mul_correct,&div_correct);
			printf("\n");
		}
	}
	//引入打印报告
	printReport(score, correctcount, wrongcount,wrongQNo, wrongN1, wrongN2, wrongop, wronguserAns, wrongRightAns, wrong_total, add_correct, sub_correct, mul_correct, div_correct);
}
void updateStats(int tof, int qNo, int num1, int num2, int op, int userans,int rightans, float* score, int* correctcount, int* wrongcount, int wrongQNo[], int wrongN1[], int wrongN2[], int wrongop[], int wronguserAns[], int wrongRightAns[],int k,int* wrong_total,int* add_correct,int* sub_correct,int* mul_correct,int* div_correct)
{
	if (tof == 1)
	{
		*correctcount = *correctcount + 1; // 答对了，正确数 +1
		*score = *score + 2.5;             // 答对了，总分 +2.5
		//根据不同的运算符来实现分运算符区统计
		if (k == 0)
		{
			*add_correct = *add_correct + 1;
		}
		else if (k == 1)
		{
			*sub_correct = *sub_correct + 1;
		}
		else if (k == 2)
		{
			*mul_correct = *mul_correct + 1;
		}
		else if (k == 3)
		{
			*div_correct = *div_correct + 1;
		}
	}
	else
	{
		*wrongcount = *wrongcount + 1;     // 答错了，错误数 +1
	}
	//错题统计部分
	if (tof == 0)
	{
		wrongQNo[*wrong_total] = qNo;//题号
		wrongN1[*wrong_total] = num1;//num1的值
		wrongN2[*wrong_total] = num2;//num2的值
		wrongop[*wrong_total] = op;//运算符
		wronguserAns[*wrong_total] = userans;//用户的答案
		wrongRightAns[*wrong_total] = rightans;//正确答案
		*wrong_total = *wrong_total + 1;//每过一次，内标加一
	}
}
//打印报告函数
void printReport(float score, int correctcount, int wrongcount,int wrongQNo[], int wrongN1[], int wrongN2[], int wrongop[], int wronguserAns[], int wrongRightAns[], int wrong_total, int add_correct, int sub_correct, int mul_correct, int div_correct)
{
	float correct_percent = ((float)correctcount / 40) * 100; // 计算正确率
	printf("\n========== 训练成绩报告 ==========\n");
	printf("总题数：40\n");
	printf("正确题数：%d\n", correctcount);
	printf("错误题数：%d\n", wrongcount);
	printf("正确率：%.2f%%\n", correct_percent);
	printf("得分：%.2f\n", score);
	printf("\n--- 分题型分布 ---\n");
	printf("加法：10题，正确 %d 题\n", add_correct);
	printf("减法：10题，正确 %d 题\n", sub_correct);
	printf("乘法：10题，正确 %d 题\n", mul_correct);
	printf("除法：10题，正确 %d 题\n", div_correct);
	printf("\n--- 错误信息 ---\n");
	if (wrong_total == 0)
	{
		printf("太棒了，全对！\n");
	}
	else
	{
		char opChar;
		for (int i = 0; i < wrong_total; i++)
		{
			getOpChar(&opChar, &wrongop[i]);// 调用之前的转换函数，把数字变符号
			printf("%d. 第%d题：%d %c %d = ? 你的答案：%d，正确答案：%d\n",i + 1, wrongQNo[i], wrongN1[i], opChar, wrongN2[i], wronguserAns[i], wrongRightAns[i]);

		}
	}
	printf("==================================\n");

}
int main()
{
	initSystem();
	int num1, num2, op;
	generate(&num1, &num2, &op);
	return 0;
}