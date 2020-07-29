#include<stdio.h>
#include<conio.h>
#include"FormulaCalculator.h"
int Menu();
void normalCal(FormulaCalculator & cal);
void prepareCal(FormulaCalculator& cal);
int main(int argc, char * argv[])
{
	system("title 公式计算器 by Ugex.Savelar");
	//"3*2*2/4+5*(2-4)+6/3+12%10+2^3";//=5 success
	//"((3+5*(4%(3+7))/(2^2))/2/2)^3";//=8  success
	//"((3.14*2-6/(2%10))+(3^1))/(4/2)";//3.14 success
	//"2sqrt4+2log8+1adds5+1muls3";//=26 success
	//"2 rand 4";//随机闭区间值 success
	//"(60radian)sin + (30radian)cos + (30radian)tan +3! +25per +10neg + 180radian";//=1.700994 success
	//"7 and 3 + 1 or 2 + 3 xor 0 +(0 not) and 3"; /=/12 success
	/*
	"7 and 3 + 1 or 2 + 3 xor 0 +(0 not) and 3 +\n\
	(60radian)sin + (30radian)cos + (30radian)tan +3! +25per +10neg + 180radian + \n\
	2 sqrt 4+2 log 8+1 adds 5+1 muls 3 +\n\
	((3.14*2-6/(2%10))+(3^1))/(4/2)+\n\
	((3+5*(4%(3+7))/(2^2))/2/2)^3 +\n\
	3*2*2/4+5*(2-4)+6/3+12%10+2^3\n\
	"; //=55.840994 success
	*/
	FormulaCalculator cal;
	printf("%s\n", FormulaCalculator::getUseHelpStr());
	while(1)
	{
		int sel = Menu();
		if (sel == 0)
			break;

		switch(sel)
		{
		case 1:
			 normalCal(cal);
			break;
		case 2:
			prepareCal(cal);
			break;
		}
	}

	return 0;
}

int Menu()
{
	printf("----------------------------------\n");
	printf("\t公式计算器 (Formula Calculator)\n");
	printf("----------------------------------\n");
	printf("\t1.常规计算\n");
	printf("\t2.预处理计算\n");
	printf("\t0.退出程序\n");
	printf("----------------------------------\n");
	printf("请选择:\n>/ ");
	fflush(stdin);
	char ch = 0;
	while (ch<'0' || ch>'2')
		ch = getch();
	printf("%c\n",ch);
	return ch - '0';
	system("cls");
}
void normalCal(FormulaCalculator & cal)
{
	AlgoString<char, int> fml;
	fml.prepareMemery(1024);
	while (1)
	{
		printf("请输入计算公式：\n>/ ");
		fflush(stdin);
		fml.zeroMemory();
		gets(fml.getData());
		bool isSuccess = false;
		double result = cal.calculate(fml, &isSuccess, 10);
		if (isSuccess == false)
			printf("Err:%s\n", cal.getLastErrStr());
		printf("result:%lf\n", result);
		fflush(stdin);
		printf("-----输入0退出，其他任意键继续---------\n");
		char ch = getch();
		if (ch == '0')
			break;
		system("cls");
	}
	system("cls");
}

void prepareCal(FormulaCalculator& cal)
{
	AlgoString<char, int> preFormala;
	preFormala.prepareMemery(1024);
	AlgoArray<AlgoString<char, int>, int> flags;
	AlgoArray<AlgoString<char, int>, int> values;
	while (1)
	{
		printf("请输入预处理公式,输入#退出：\n>/ ");
		fflush(stdin);
		preFormala.zeroMemory();
		gets(preFormala.getData());
		if (preFormala.equals("#"))
			break;
		printf("请输入公式中的自变量表,#号结束：\n>/ ");
		flags.setSize(0);
		AlgoString<char, int> buf;
		fflush(stdin);
		do
		{
			buf.zeroMemory();
			scanf("%s", buf.getData());
			buf.trim();
			if (buf.equals("#"))
				break;
			if (buf.getLength() != 0)
				flags.push(buf);
		} while (1);
		

		while (1)
		{
			printf("----------------------------------\n");
			fflush(stdin);
			printf("Formula:\t%s\n", preFormala.getData());
			printf("Flags:\t");
			for (int i = 0; i < flags.size(); i++)
			{
				printf("%s\t", flags[i].getData());
			}
			printf("\n");
			fflush(stdin);
			printf("请输入变量列表值：\n>/ ");
			values.setSize(0);
			for (int i = 0; i < flags.size(); i++)
			{
				buf.zeroMemory();
				scanf("%s", buf.getData());
				buf.trim();
				if (buf.getLength() != 0)
					values.push(buf);
				else
					i--;
			}
			AlgoString<char,int> preFormulaStr = cal.buildPrepareFormula(preFormala, flags, values);
			printf("Calcul:%s\n",preFormulaStr.getData());
			bool isSuccess = false;
			double result = cal.calculate(preFormulaStr, &isSuccess, 10);
			if (isSuccess == false)
				printf("Err:%s\n",cal.getLastErrStr());
			printf("\n结果为：%lf\n", result);

			printf("---------输入0退出，其他任意键继续----------------\n");
			fflush(stdin);
			if (getch() == '0')
				break;
			system("cls");

		}
		system("cls");
	}
	system("cls");
}