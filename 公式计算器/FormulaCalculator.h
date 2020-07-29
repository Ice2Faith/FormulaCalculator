#ifndef _FORMULA_CALCULATOR_HPP_
#define _FORMULA_CALCULATOR_HPP_
/*
--------------------------
name:公式计算器
author:Ugex.Savelar
date:2020-7-25
--------------------------
基于双栈（数字栈，符号栈）实现的字符串公式计算器
原理：
扫描整个输入公式，从左向右扫描
如果是数字，直接入栈到数字栈
如果是符号
	如果符号栈为空，或者是左括号，无条件入栈到符号栈
	如果符号栈不为空
		和符号栈栈顶符号，比较优先级
			如果高于栈顶优先级，直接入栈到符号栈
			如果低于栈顶优先级，从数字栈取出两个数字，从符号栈取出一个符号，进行运算，
				将运算结果放入数字栈，将当前符号入栈到符号栈
			如果当前扫描到的符号是右括号）
				不断取出两数字和一符号运算，知道符号栈栈顶符号为左括号（
				弹出栈顶的左括号（
也就是说，数字和左括号（无条件入栈，右括号）始终不入栈，
遇到右括号），就不断弹栈计算，知道消去栈中弹出的第一个左括号（，
其他时候，当前的符号优先级高，直接入栈，优先级低则弹栈计算，再入栈

伪代码流程：
	直到 输入公式扫描结束
		如果 扫描到字符
			获取数字
			入栈-数字栈
			移动下标
		否则
			获取当前符号
			如果 不支持当前符号
				退出循环、直接返回
			如果 符号栈空
				入栈当前符号
			否则
				获取符号栈顶符号
				获得栈顶符号和当前符号的优先级
				如果 优先级获取出错的标志
					退出循环、直接返回
				否则如果 消除括号的优先级标志
					出栈符号栈
				否则如果 当前符号优先级 低于 栈顶符号
					出栈两个数字和一个符号进行计算，并将计算结果重新入栈数字栈--查看注解1
					如果 当前符号 是 右括号
						继续下一轮循环，跳过本轮循环
					入栈 当前符号 到 符号栈
				否则如果 当前符号优先级 高于 栈顶符号
					入栈 当前符号 到 符号栈
			移动下标
	直到 符号栈 为空
		出栈两个数字和一个符号进行计算，并将计算结果重新入栈数字栈--查看注解1
					
	返回 数字栈栈顶，这就是最终的结果

-----注解1：
	出栈数字2 从 数字栈
	出栈数字1 从 数字栈
	出栈运算符号 从 符号栈
	计算 数字1 运算符号 数字2 保存到 结果
	入栈 结果 到 数字栈
----注意，这里是区分了数字1和数字2的，因为除法减法是需要区分的
*/
#include"AlgoContainer.hpp"
#include"AlgoString.hpp"

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

class FormulaCalculator
{
public:
	AlgoString<char, int> buildPrepareFormula(AlgoString<char, int>& preFormula, AlgoArray<AlgoString<char, int>, int> & flags, AlgoArray<AlgoString<char, int>, int> & values)
	{
		AlgoString<char, int> ret(preFormula);
		for (int i = 0; i < flags.size(); i++)
		{
			ret.replace(flags[i], values[i],-1);
		}
		return ret;
	}

	/////////////////////////////////////////////
public:
	static const char * getUseHelpStr()
	{
		static char help[] = {"公式计算器使用简介：\tUgex.Savelar\n\
\t常规双目运算符号：+ - * / % ^ ( )\n\
\t\t加、减、乘、除、取模、求幂\n\
\t\t用法：3+2*5-(2^3)%5\n\
\t拓展双目运算符号：sqrt log adds muls and or xor\n\
\t\tN次根、对数、累加、累乘、位与、位或、位异或\n\
\t\t用法：2 sqrt 4 + 1adds5+ 7 and 3\n\
\t\t说明：2sqrt4表示4开2次根，1adds5表示1+...+5\n\
\t\t\t2log8表示求以2为底8的对数,7and3表示7位与3\n\
\t拓展单目运算符：\n\
\t\t! neg per abs radian angle sin cos tan arcsin arccos arctan\n\
\t\t阶乘 负号 百分号 绝对值 转弧度 转角度 三角函数族\n\
\t\t用法：3!+5neg+50per+(60radian)sin\n\
\t\t说明：3!表示求3的阶乘，5neg表示负5,50per表示百分之50\n\
\t\t\t60radian表示将60转换为弧度制，(60radian)sin表示求sin60角度\n\
\t\t[注意]:三角函数族计算需要使用弧度制，拥有运算符转换\n\
\t注意事项：\n\
\t\t运算符不区分大小写\n\
\t\t空格空白符号可以任意添加，只要不中断运算符\n\
\t\t空白符号指：ASCII字符：空格 回车 换行 制表符\n\
\t\t计算结果请检查isSuccess标志位，如果为false，计算失败，错误发生\n\
\t\t你可以使用getLastErrStr()获取错误描述\n\
\t\t使用getLastResult()获取计算结果，如果发生错误就是中间计算结果\n\
\t\t\t如果未发生错误，就是正确结果\n\
\t综合使用案例：\n\
\t\t7 and 3 + 1 or 2 + 3 xor 0 + (0 not) and 3 + \n\
\t\t(60radian)sin + (30radian)cos + (30radian)tan + 3!+ 25per + 10neg + 180radian + \n\
\t\t2 sqrt 4 + 2 log 8 + 1 adds 5 + 1 muls 3 + \n\
\t\t((3.14 * 2 - 6 / (2 % 10)) + (3 ^ 1)) / (4 / 2) + \n\
\t\t((3 + 5 * (4 % (3 + 7)) / (2 ^ 2)) / 2 / 2) ^ 3 + \n\
\t\t3 * 2 * 2 / 4 + 5 * (2 - 4) + 6 / 3 + 12 % 10 + 2 ^ 3\n\
\t\t计算结果为：55.840994\n\
"};
		return help; 
	}
	FormulaCalculator()
	{
		cleanAll();

		m_flags.setSize(0);
		m_flags.push(AlgoString<char, int>("+"));	//写法参考：3+2-5*4/3
		m_flags.push(AlgoString<char, int>("-"));
		m_flags.push(AlgoString<char, int>("*"));
		m_flags.push(AlgoString<char, int>("/"));
		m_flags.push(AlgoString<char, int>("%"));
		m_flags.push(AlgoString<char, int>("^"));
		m_flags.push(AlgoString<char, int>("("));
		m_flags.push(AlgoString<char, int>(")"));

		m_flags.push(AlgoString<char, int>("sqrt"));	// 对m开n次根: n sqrt m //写法参考：2 sqrt 4 + 2 log 8 adds 3 ，其实和传统运算符一样，操作数在两边
		m_flags.push(AlgoString<char, int>("log"));    // 计算log以a为底b的对数： a log b //log(num2)/log(num1)//换底公式
		m_flags.push(AlgoString<char, int>("adds"));	//计算a累加到b: a adds b
		m_flags.push(AlgoString<char, int>("muls"));	//计算a累乘到b: a muls b

		m_flags.push(AlgoString<char, int>("and"));	//二进制运算
		m_flags.push(AlgoString<char, int>("or"));
		m_flags.push(AlgoString<char, int>("xor"));

		m_indexOfSingleNumberOperatorBegin = m_flags.size(); //单目双目运算符分割记录

		m_flags.push(AlgoString<char, int>("not"));

		m_flags.push(AlgoString<char, int>("!"));		//阶乘		//写法参考：2! + (6 neg) abs ，其实和阶乘写法一样，操作数在前
		m_flags.push(AlgoString<char, int>("neg"));	//取负数	//负号
		m_flags.push(AlgoString<char, int>("per"));	//取百分值	//百分号
		m_flags.push(AlgoString<char, int>("abs"));	//取绝对值
		m_flags.push(AlgoString<char, int>("radian"));	//取弧度制
		m_flags.push(AlgoString<char, int>("angle"));		//取角度制
		m_flags.push(AlgoString<char, int>("sin"));		//三角函数族，默认使用弧度进行计算，特别说明
		m_flags.push(AlgoString<char, int>("cos"));
		m_flags.push(AlgoString<char, int>("tan"));
		m_flags.push(AlgoString<char, int>("arcsin"));
		m_flags.push(AlgoString<char, int>("arcsos"));
		m_flags.push(AlgoString<char, int>("arctan"));

		int len = m_flags.size();
		m_ruleTable = new char[len*len];

		char tpTable[50][50] = 
		{
		   //+	-	*	/	%	^	(		)		sqrt	log	adds	muls		and	or	xor	not		!	neg	per	abs	radian	angle	sin	cos	tan	arcsin	arccos	arctan
			{0,	0,	0,	0,	0,	0,	1,		-1,		0,		0,	0,		0,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// +
			{0,	0,	0,	0,	0,	0,	1,		-1,		0,		0,	0,		0,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// -
			{1,	1,	0,	0,	0,	0,	1,		-1,		0,		0,	0,		0,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// *
			{1,	1,	0,	0,	0,	0,	1,		-1,		0,		0,	0,		0,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// /
			{1,	1,	1,	1,	1,	1,	1,		-1,		0,		0,	0,		0,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// %
			{1,	1,	1,	1,	1,	0,	1,		-1,		0,		0,	0,		0,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// ^
			{1,	1,	1,	1,	1,	1,	1,		-1,		1,		1,	1,		1,			1,	1,	1,	1,		1,	1,	1,	1,	1,		1,		1,	1,	1,	1,		1,		1},			// (
			{0,	0,	0,	0,	0,	0,	9,		-1,		0,		0,	0,		0,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// )
			//,{双,目,运算,符,	,	,		-1,		,		,	,		,			,	,	,	,		,	,	,	,	,		,		,	,	,	,		,		} ,			// 
			{1,	1,	1,	1,	1,	0,	1,		-1,		0,		0,	0,		0,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// sqrt
			{1,	1,	1,	1,	1,	0,	1,		-1,		0,		0,	0,		0,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// log
			{1,	1,	1,	1,	1,	0,	1,		-1,		0,		0,	0,		0,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// adds
			{1,	1,	1,	1,	1,	0,	1,		-1,		0,		0,	0,		0,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// muls
			//{,	,	,	,	,	,	,	-1		,	,		,	,		,			,	,,	,		,	,	,	,	,		,		,	,	,	,		,		 },			// 
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// and
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// or
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// xor
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// not
			//,{单,目,运算,符,	,	,		-1,		,		,	,		,			,	,	,	,		,	,	,	,	,		,		,	,	,	,		,		} ,			// 
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// !
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// neg
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// per
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// abs
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// radian
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// angle
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// sin
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// cos
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// tan
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// arcsin
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// arccos
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// arctan
																																		 
		};

		for (int i = 0; i < len; i++)
		{
			for (int j = 0; j < len; j++)
			{
				At(i, j) = tpTable[i][j];
			}
		}
		
	}
	~FormulaCalculator()
	{
		delete[] m_ruleTable;
		cleanAll();
	}
	/*
	给定算术表达式，即可进行计算，返回计算结果，
	并且你需要接受计算是否成功的标志，
	一旦发生错误，返回值为0，成功标志为false
	但是你可以通过getLastErrStr()获取错误描述
	可能过程中，是存在一定步骤之前的正确结果的，
	你可以通过getLastResult()获取计算结果，此方法如果之前计算标志成功，那么就是最终的计算结果
	base参数用于指定运算使用的进制，默认十进制，这将会决定整个计算的数字部分的解析
	*/
	double calculate(AlgoString<char, int> formula, bool * isSuccess, int base = 10)
	{
		return calculate(formula.getData(), isSuccess, base);
	}
	double calculate(char * formula,bool * isSuccess,int base=10)
	{
		m_flagStack.clear();
		m_numberStack.clear();

		if (AlgoString<char,int>(formula).trim().getLength() == 0)
		{
			sprintf(lastErr, "输入串长度被截断或是无意义空串，请重试\0");
			*isSuccess = false;
			return 0;
		}
		lastErr[0] = 0;

		int i = 0;
		while (formula[i])
		{
			int addCount = 0;
			if (isNumberChar(formula[i], base))
			{
				double num = getNumber(&formula[i], &addCount, base);
				m_numberStack.push(num);
				i += addCount;
			}
			else
			{
				AlgoString<char, int> flg = getFlag(&formula[i], &addCount, base);
				flg.trim();
				if (flg.getLength() > 0)
				{
					if (isLegalOperator(flg) == false)
					{
						sprintf(lastErr, "未识别的运算符：%s\0", flg.getData());
						*isSuccess = false;
						return 0;
					}

					if (m_flagStack.size() == 0)
						m_flagStack.push(flg);
					else
					{
						AlgoString<char, int> top = m_flagStack.top();
						int priority = getPriortyTag(flg, top);
						if (priority == -1)
						{
							sprintf(lastErr, "表达式错误：index:%d,value:%s\0", i, flg.getData());
							*isSuccess = false;
							return 0;
						}
						else if (priority == 9)
						{
							m_flagStack.pop();
						}
						else if (priority == 0)
						{
							if (calculateOnceStack() == false)
							{
								sprintf(lastErr, "公式错误，不匹配的操作数,操作数个数异常：index:%d,value:%s\0", i, flg.getData());
								*isSuccess = false;
								return 0;
							}
							//注意，这个continue至关重要，主要作用是处理最里层的括号内的运算
							//由于后面的下标移动是统一的，如果这里不判断进行continue
							//将会导致下标持续向前走，导致计算括号出现错误
							if (flg.equalsIgnoreCase(")"))
								continue;
							m_flagStack.push(flg);
						}
						else if (priority == 1)
						{
							m_flagStack.push(flg);
						}
					}
					
				}
				i += addCount;	
			}
		}
		//处理最后栈中剩余的数据
		//特别注意：此时栈中的符号依然存在优先级关系，如果直接不断取出栈顶计算，那么就算没有优先级，也会应为不遵循从左到右的计算规则而导致计算出错
		//常见的：2*2-4*1+2 sqrt 4，将会导致计算流程变为：((2*2)-((4*1)+(2 sqrt 4)))=-2,而不是正确的结果2=(((2*2)-(4*1))+(2 sqrt 4))
		//这种错误将是致命的，因此，正确的善后计算过程是：
		/*
		如果 符号栈内数量大于等于2， 那就需要比较优先级，下面的描述中：真栈顶==真实的栈顶部元素，次栈顶==除了栈顶的栈顶元素
			如果 真栈顶的优先级 大于 次栈顶的优先级
				那么 直接弹出数字栈两个数字和符号栈一个符号进行计算，将计算结果入栈【符号不在入栈了，需要注意】
			否则
				那么 先保存符号栈顶和数字栈的栈顶，在去正常的弹栈计算，将计算结果入栈【再把先前保存的符号和数字入栈】
		否则
			直接弹栈计算，得出最终结果
				
		*/
		while (m_flagStack.size() > 0)
		{
			bool isCalSec = false;
			if (m_flagStack.size() >= 2)//如果符号栈还有两个以上的运算符，那就需要优先级比较
			{
				//先弹栈比较优先级
				AlgoString<char, int> endTop = m_flagStack.pop();
				AlgoString<char, int> preTop = m_flagStack.pop();
				int priority = getPriortyTag(endTop, preTop);
				if (priority == 1)
				{
					//真栈顶的优先级高，则恢复栈
					m_flagStack.push(preTop);
					m_flagStack.push(endTop);

					//弹栈计算,入栈结果
					isCalSec = calculateOnceStack();
				}
				else if (priority == 0)
				{
					//真栈顶的优先级低，则保存两栈的栈顶，因为我这里实现的时候，是弹栈比较的优先级，因此需要回复次栈顶成为临时栈顶
					double topNum = m_numberStack.pop();
					m_flagStack.push(preTop);

					//弹栈计算，入栈结果
					isCalSec = calculateOnceStack();

					//恢复保存的两真栈顶
					m_numberStack.push(topNum);
					m_flagStack.push(endTop);
				}
				else
				{
					//由于最后收尾的时候，符号栈不存在左括号了，但是如果还是存在，那就是出错了
					sprintf(lastErr, "堆栈异常或者符号栈异常\0");
					*isSuccess = false;
					return 0;
				}
			}
			else
			{
				//如果符号栈只有一个符号了，没得商量，直接计算，得到最终结果
				isCalSec = calculateOnceStack();
			}

			if (isCalSec == false)
			{
				sprintf(lastErr, "公式错误，不匹配的操作数,操作数个数异常：index:end,value:end\0");
				*isSuccess = false;
				return 0;
			}
		}

		if (m_numberStack.size() ==0)
		{
			sprintf(lastErr, "不能识别的公式，无运算结果\0");
			*isSuccess = false;
			return 0;
		}
		if (m_numberStack.size() !=1)
		{
			sprintf(lastErr, "公式存在错误或不完整，但是依然满足计算需求规则\0");
			*isSuccess = false;
			return 0;
		}
		*isSuccess = true;
		return m_numberStack.top();
	}
	double getLastResult()
	{
		if (m_numberStack.size() == 0)
			return 0;
		return m_numberStack.top();
	}
	const char * getLastErrStr()
	{
		return lastErr;
	}
private:
	static AlgoString<char, int> getFlag(char * str, int * addCount, int base = 10)
	{
		AlgoString<char, int> ret;
		ret[0] = 0;
		if (isNumberChar(*str, base) == true)
		{
			*addCount = 0;
			return ret;
		}
		int i = 0;
		if (!ret.isA2Z(str[i]) && !ret.isa2z(str[i]))
		{
			ret[i] = str[i];
			ret[i + 1] = 0;
			*addCount = 1;
			return ret;
		}
		while (str[i]!=0 && isNumberChar(str[i], base)==false)
		{
			if (!ret.isA2Z(str[i]) && !ret.isa2z(str[i]))
			{
				break;
			}
			ret[i] = str[i];
			i++;
		}
		*addCount = i;
		ret[i] = 0;
		return ret;
	}
	static double getNumber(char * str, int * addCount,int base=10)
	{
		double ret=0;
		if (isNumberChar(*str,base) == false)
		{
			*addCount = 0;
			return 0;
		}
		int i = 0;
		while (isNumberChar(str[i],base))
		{
			ret *= base;
			ret += getNumCharValue(str[i],base);
			i++;
		}
		if (str[i] == '.')
		{
			i++;
			double lbit = 1;
			while (isNumberChar(str[i],base))
			{
				lbit *= base;
				ret += getNumCharValue(str[i], base) / lbit;
				i++;
			}
		}
		*addCount = i;
		return ret;
	}
	static int getNumCharValue(char ch, int base=10)
	{
		static char map[] = { "0123456789ABCDEF" };
		if (ch >= 'a'&&ch <= 'z')
			ch &= ~32;
		int i = 0;
		while (map[i] && i<base)
		{
			if (ch == map[i])
				return i;
			i++;
		}
		return -1;
	}
	static bool isNumberChar(char ch,int base=10)
	{
		static char map[] = {"0123456789ABCDEF"};
		if (ch >= 'a'&&ch <= 'z')
			ch &= ~32;
		int i = 0;
		while (map[i]&&i<base)
		{
			if (ch == map[i])
				return true;
			i++;
		}
		return false;
	}
private:
	bool isLegalOperator(AlgoString<char, int>& ope)
	{
		for (int i = 0; i < m_flags.size(); i++)
		{
			if (ope.equalsIgnoreCase(m_flags[i]))
				return true;
		}
		return false;
	}
	bool calculateOnceStack()
	{
		AlgoString<char, int> top = m_flagStack.top();
		if (isSingleNumberOperator(top))//单目运算符号，只取出一个操作数计算即可
		{
			if (m_numberStack.size() < 1)
			{
				return false;
			}
			double num2 = 0;
			double num1 = m_numberStack.pop();
			AlgoString<char, int> ope = m_flagStack.pop();

			double result = calculateOperator(num1, num2, ope);
			m_numberStack.push(result);
			
		}
		else
		{
			if (m_numberStack.size() < 2)
			{
				return false;
			}
			double num2 = m_numberStack.pop();
			double num1 = m_numberStack.pop();
			AlgoString<char, int> ope = m_flagStack.pop();

			double result = calculateOperator(num1, num2, ope);
			m_numberStack.push(result);
		}

		return true;
	}
	bool isSingleNumberOperator(AlgoString<char, int>& ope)
	{
		for (int i = m_indexOfSingleNumberOperatorBegin; i < m_flags.size(); i++)
		{
			if (ope.equalsIgnoreCase(m_flags[i]))
				return true;
		}
		return false;
	}
	double calculateOperator(double num1, double num2, AlgoString<char, int>& ope)
	{
		//+	-	*	/	%	^	(	)		sqrt	log	adds	muls		and	or	not	xor		!	neg	per	abs	radian	angle	sin	cos	tan	arcsin	arccos	arctan
		if (ope.equalsIgnoreCase("+"))
		{
			return num1 + num2;
		}
		else if (ope.equalsIgnoreCase("-"))
		{
			return num1 - num2;
		}
		else if (ope.equalsIgnoreCase("*"))
		{
			return num1 * num2;
		}
		else if (ope.equalsIgnoreCase("/"))
		{
			return num1 / num2;
		}
		else if (ope.equalsIgnoreCase("%"))
		{
			return ((long)num1) % ((long)num2);
		}
		else if (ope.equalsIgnoreCase("^"))
		{
			return pow(num1, num2);
		}
		else if (ope.equalsIgnoreCase("sqrt"))//n次根号m==m的1/n次幂
		{
			return pow(num2, 1.0 / num1);
		}
		else if (ope.equalsIgnoreCase("log"))
		{
			return log(num2) / log(num1);
		}
		else if (ope.equalsIgnoreCase("adds"))
		{
			double ret = 0;
			int step = num1 < num2 ? 1 : -1;
			long beg = (long)num1;
			long end = (long)num2;
			for (int i = beg; i <= end; i += step)
				ret += i;
			return ret;
		}
		else if (ope.equalsIgnoreCase("muls"))
		{
			double ret = 1;
			int step = num1 < num2 ? 1 : -1;
			long beg = (long)num1;
			long end = (long)num2;
			for (int i = beg; i <= end; i += step)
				ret *= i;
			return ret;
		}
		else if (ope.equalsIgnoreCase("and"))
		{
			return ((long)num1)&((long)num2);
		}
		else if (ope.equalsIgnoreCase("or"))
		{
			return ((long)num1) | ((long)num2);
		}
		else if (ope.equalsIgnoreCase("xor"))
		{
			return ((long)num1) ^ ((long)num2);
		}
		else if (ope.equalsIgnoreCase("not"))
		{
			return ~((long)num1);
		}
		else if (ope.equalsIgnoreCase("!")) //!	neg	per	abs	radian	angle	sin	cos	tan	arcsin	arccos	arctan
		{
			double ret = 1;
			long beg = 1;
			long end = (long)num1;
			for (int i = beg; i <= end; i++)
				ret *= i;
			return ret;
		}
		else if (ope.equalsIgnoreCase("neg"))
		{
			return 0 - num1;
		}
		else if (ope.equalsIgnoreCase("per"))
		{
			return num1 / 100.0;
		}
		else if (ope.equalsIgnoreCase("abs"))
		{
			return abs(num1);
		}
		else if (ope.equalsIgnoreCase("radian"))
		{
			return num1 / 180.0*3.141592653549;
		}
		else if (ope.equalsIgnoreCase("angle"))
		{
			return num1 / 3.141562653549*180.0;;
		}
		else if (ope.equalsIgnoreCase("sin"))
		{
			return sin(num1);
		}
		else if (ope.equalsIgnoreCase("cos"))
		{
			return cos(num1);
		}
		else if (ope.equalsIgnoreCase("tan"))
		{
			return tan(num1);
		}
		else if (ope.equalsIgnoreCase("arcsin"))
		{
			return asin(num1);
		}
		else if (ope.equalsIgnoreCase("arccos"))
		{
			return acos(num1);
		}
		else if (ope.equalsIgnoreCase("arctan"))
		{
			return atan(num1);
		}
		return 0;
	}
	int getPriortyTag(AlgoString<char, int>& cur, AlgoString<char, int> & top)
	{
		int curI = getFlagIndex(cur);
		int topI = getFlagIndex(top);
		if (curI == -1 || topI == -1)
			return -1;
		return At(curI, topI);
	}
	int getFlagIndex(AlgoString<char, int> & flg)
	{
		int ret = -1;
		for (int i = 0; i < m_flags.size(); i++)
		{
			if (flg.equalsIgnoreCase(m_flags[i]))
			{
				ret = i;
				break;
			}
		}
		return ret;
	}

	void cleanAll()
	{
		m_flags.setSize(0);
		lastErr[0] = 0;
		m_ruleTable = NULL;
		m_flagStack.clear();
		m_numberStack.clear();
		m_indexOfSingleNumberOperatorBegin = 0;
	}
private:

	char lastErr[1024];
	//cur line ,top row
	char & At(int cur, int top)
	{
		return m_ruleTable[cur*m_flags.size()+top];
	}
	int m_indexOfSingleNumberOperatorBegin;
	char * m_ruleTable;
	AlgoArray<AlgoString<char, int>, int> m_flags;
	AlgoList<double, int> m_numberStack;
	AlgoList<AlgoString<char, int>, int> m_flagStack;
};

#endif // _FORMULA_CALCULATOR_HPP_