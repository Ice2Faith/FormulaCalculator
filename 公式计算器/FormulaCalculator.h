#ifndef _FORMULA_CALCULATOR_HPP_
#define _FORMULA_CALCULATOR_HPP_
/*
--------------------------
name:��ʽ������
author:Ugex.Savelar
date:2020-7-25
--------------------------
����˫ջ������ջ������ջ��ʵ�ֵ��ַ�����ʽ������
ԭ��
ɨ���������빫ʽ����������ɨ��
��������֣�ֱ����ջ������ջ
����Ƿ���
	�������ջΪ�գ������������ţ���������ջ������ջ
	�������ջ��Ϊ��
		�ͷ���ջջ�����ţ��Ƚ����ȼ�
			�������ջ�����ȼ���ֱ����ջ������ջ
			�������ջ�����ȼ���������ջȡ���������֣��ӷ���ջȡ��һ�����ţ��������㣬
				����������������ջ������ǰ������ջ������ջ
			�����ǰɨ�赽�ķ����������ţ�
				����ȡ�������ֺ�һ�������㣬֪������ջջ������Ϊ�����ţ�
				����ջ���������ţ�
Ҳ����˵�����ֺ������ţ���������ջ�������ţ�ʼ�ղ���ջ��
���������ţ����Ͳ��ϵ�ջ���㣬֪����ȥջ�е����ĵ�һ�������ţ���
����ʱ�򣬵�ǰ�ķ������ȼ��ߣ�ֱ����ջ�����ȼ�����ջ���㣬����ջ

α�������̣�
	ֱ�� ���빫ʽɨ�����
		��� ɨ�赽�ַ�
			��ȡ����
			��ջ-����ջ
			�ƶ��±�
		����
			��ȡ��ǰ����
			��� ��֧�ֵ�ǰ����
				�˳�ѭ����ֱ�ӷ���
			��� ����ջ��
				��ջ��ǰ����
			����
				��ȡ����ջ������
				���ջ�����ź͵�ǰ���ŵ����ȼ�
				��� ���ȼ���ȡ����ı�־
					�˳�ѭ����ֱ�ӷ���
				������� �������ŵ����ȼ���־
					��ջ����ջ
				������� ��ǰ�������ȼ� ���� ջ������
					��ջ�������ֺ�һ�����Ž��м��㣬����������������ջ����ջ--�鿴ע��1
					��� ��ǰ���� �� ������
						������һ��ѭ������������ѭ��
					��ջ ��ǰ���� �� ����ջ
				������� ��ǰ�������ȼ� ���� ջ������
					��ջ ��ǰ���� �� ����ջ
			�ƶ��±�
	ֱ�� ����ջ Ϊ��
		��ջ�������ֺ�һ�����Ž��м��㣬����������������ջ����ջ--�鿴ע��1
					
	���� ����ջջ������������յĽ��

-----ע��1��
	��ջ����2 �� ����ջ
	��ջ����1 �� ����ջ
	��ջ������� �� ����ջ
	���� ����1 ������� ����2 ���浽 ���
	��ջ ��� �� ����ջ
----ע�⣬����������������1������2�ģ���Ϊ������������Ҫ���ֵ�
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
		static char help[] = {"��ʽ������ʹ�ü�飺\tUgex.Savelar\n\
\t����˫Ŀ������ţ�+ - * / % ^ ( )\n\
\t\t�ӡ������ˡ�����ȡģ������\n\
\t\t�÷���3+2*5-(2^3)%5\n\
\t��չ˫Ŀ������ţ�sqrt log adds muls and or xor\n\
\t\tN�θ����������ۼӡ��۳ˡ�λ�롢λ��λ���\n\
\t\t�÷���2 sqrt 4 + 1adds5+ 7 and 3\n\
\t\t˵����2sqrt4��ʾ4��2�θ���1adds5��ʾ1+...+5\n\
\t\t\t2log8��ʾ����2Ϊ��8�Ķ���,7and3��ʾ7λ��3\n\
\t��չ��Ŀ�������\n\
\t\t! neg per abs radian angle sin cos tan arcsin arccos arctan\n\
\t\t�׳� ���� �ٷֺ� ����ֵ ת���� ת�Ƕ� ���Ǻ�����\n\
\t\t�÷���3!+5neg+50per+(60radian)sin\n\
\t\t˵����3!��ʾ��3�Ľ׳ˣ�5neg��ʾ��5,50per��ʾ�ٷ�֮50\n\
\t\t\t60radian��ʾ��60ת��Ϊ�����ƣ�(60radian)sin��ʾ��sin60�Ƕ�\n\
\t\t[ע��]:���Ǻ����������Ҫʹ�û����ƣ�ӵ�������ת��\n\
\tע�����\n\
\t\t����������ִ�Сд\n\
\t\t�ո�հ׷��ſ���������ӣ�ֻҪ���ж������\n\
\t\t�հ׷���ָ��ASCII�ַ����ո� �س� ���� �Ʊ��\n\
\t\t����������isSuccess��־λ�����Ϊfalse������ʧ�ܣ�������\n\
\t\t�����ʹ��getLastErrStr()��ȡ��������\n\
\t\tʹ��getLastResult()��ȡ�����������������������м������\n\
\t\t\t���δ�������󣬾�����ȷ���\n\
\t�ۺ�ʹ�ð�����\n\
\t\t7 and 3 + 1 or 2 + 3 xor 0 + (0 not) and 3 + \n\
\t\t(60radian)sin + (30radian)cos + (30radian)tan + 3!+ 25per + 10neg + 180radian + \n\
\t\t2 sqrt 4 + 2 log 8 + 1 adds 5 + 1 muls 3 + \n\
\t\t((3.14 * 2 - 6 / (2 % 10)) + (3 ^ 1)) / (4 / 2) + \n\
\t\t((3 + 5 * (4 % (3 + 7)) / (2 ^ 2)) / 2 / 2) ^ 3 + \n\
\t\t3 * 2 * 2 / 4 + 5 * (2 - 4) + 6 / 3 + 12 % 10 + 2 ^ 3\n\
\t\t������Ϊ��55.840994\n\
"};
		return help; 
	}
	FormulaCalculator()
	{
		cleanAll();

		m_flags.setSize(0);
		m_flags.push(AlgoString<char, int>("+"));	//д���ο���3+2-5*4/3
		m_flags.push(AlgoString<char, int>("-"));
		m_flags.push(AlgoString<char, int>("*"));
		m_flags.push(AlgoString<char, int>("/"));
		m_flags.push(AlgoString<char, int>("%"));
		m_flags.push(AlgoString<char, int>("^"));
		m_flags.push(AlgoString<char, int>("("));
		m_flags.push(AlgoString<char, int>(")"));

		m_flags.push(AlgoString<char, int>("sqrt"));	// ��m��n�θ�: n sqrt m //д���ο���2 sqrt 4 + 2 log 8 adds 3 ����ʵ�ʹ�ͳ�����һ����������������
		m_flags.push(AlgoString<char, int>("log"));    // ����log��aΪ��b�Ķ����� a log b //log(num2)/log(num1)//���׹�ʽ
		m_flags.push(AlgoString<char, int>("adds"));	//����a�ۼӵ�b: a adds b
		m_flags.push(AlgoString<char, int>("muls"));	//����a�۳˵�b: a muls b

		m_flags.push(AlgoString<char, int>("and"));	//����������
		m_flags.push(AlgoString<char, int>("or"));
		m_flags.push(AlgoString<char, int>("xor"));

		m_indexOfSingleNumberOperatorBegin = m_flags.size(); //��Ŀ˫Ŀ������ָ��¼

		m_flags.push(AlgoString<char, int>("not"));

		m_flags.push(AlgoString<char, int>("!"));		//�׳�		//д���ο���2! + (6 neg) abs ����ʵ�ͽ׳�д��һ������������ǰ
		m_flags.push(AlgoString<char, int>("neg"));	//ȡ����	//����
		m_flags.push(AlgoString<char, int>("per"));	//ȡ�ٷ�ֵ	//�ٷֺ�
		m_flags.push(AlgoString<char, int>("abs"));	//ȡ����ֵ
		m_flags.push(AlgoString<char, int>("radian"));	//ȡ������
		m_flags.push(AlgoString<char, int>("angle"));		//ȡ�Ƕ���
		m_flags.push(AlgoString<char, int>("sin"));		//���Ǻ����壬Ĭ��ʹ�û��Ƚ��м��㣬�ر�˵��
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
			//,{˫,Ŀ,����,��,	,	,		-1,		,		,	,		,			,	,	,	,		,	,	,	,	,		,		,	,	,	,		,		} ,			// 
			{1,	1,	1,	1,	1,	0,	1,		-1,		0,		0,	0,		0,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// sqrt
			{1,	1,	1,	1,	1,	0,	1,		-1,		0,		0,	0,		0,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// log
			{1,	1,	1,	1,	1,	0,	1,		-1,		0,		0,	0,		0,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// adds
			{1,	1,	1,	1,	1,	0,	1,		-1,		0,		0,	0,		0,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// muls
			//{,	,	,	,	,	,	,	-1		,	,		,	,		,			,	,,	,		,	,	,	,	,		,		,	,	,	,		,		 },			// 
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// and
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// or
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// xor
			{1,	1,	1,	1,	1,	0,	1,		-1,		1,		1,	1,		1,			0,	0,	0,	0,		0,	0,	0,	0,	0,		0,		0,	0,	0,	0,		0,		0},			// not
			//,{��,Ŀ,����,��,	,	,		-1,		,		,	,		,			,	,	,	,		,	,	,	,	,		,		,	,	,	,		,		} ,			// 
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
	�����������ʽ�����ɽ��м��㣬���ؼ�������
	��������Ҫ���ܼ����Ƿ�ɹ��ı�־��
	һ���������󣬷���ֵΪ0���ɹ���־Ϊfalse
	���������ͨ��getLastErrStr()��ȡ��������
	���ܹ����У��Ǵ���һ������֮ǰ����ȷ����ģ�
	�����ͨ��getLastResult()��ȡ���������˷������֮ǰ�����־�ɹ�����ô�������յļ�����
	base��������ָ������ʹ�õĽ��ƣ�Ĭ��ʮ���ƣ��⽫�����������������ֲ��ֵĽ���
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
			sprintf(lastErr, "���봮���ȱ��ضϻ���������մ���������\0");
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
						sprintf(lastErr, "δʶ����������%s\0", flg.getData());
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
							sprintf(lastErr, "���ʽ����index:%d,value:%s\0", i, flg.getData());
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
								sprintf(lastErr, "��ʽ���󣬲�ƥ��Ĳ�����,�����������쳣��index:%d,value:%s\0", i, flg.getData());
								*isSuccess = false;
								return 0;
							}
							//ע�⣬���continue������Ҫ����Ҫ�����Ǵ��������������ڵ�����
							//���ں�����±��ƶ���ͳһ�ģ�������ﲻ�жϽ���continue
							//���ᵼ���±������ǰ�ߣ����¼������ų��ִ���
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
		//�������ջ��ʣ�������
		//�ر�ע�⣺��ʱջ�еķ�����Ȼ�������ȼ���ϵ�����ֱ�Ӳ���ȡ��ջ�����㣬��ô����û�����ȼ���Ҳ��ӦΪ����ѭ�����ҵļ����������¼������
		//�����ģ�2*2-4*1+2 sqrt 4�����ᵼ�¼������̱�Ϊ��((2*2)-((4*1)+(2 sqrt 4)))=-2,��������ȷ�Ľ��2=(((2*2)-(4*1))+(2 sqrt 4))
		//���ִ����������ģ���ˣ���ȷ���ƺ��������ǣ�
		/*
		��� ����ջ���������ڵ���2�� �Ǿ���Ҫ�Ƚ����ȼ�������������У���ջ��==��ʵ��ջ����Ԫ�أ���ջ��==����ջ����ջ��Ԫ��
			��� ��ջ�������ȼ� ���� ��ջ�������ȼ�
				��ô ֱ�ӵ�������ջ�������ֺͷ���ջһ�����Ž��м��㣬����������ջ�����Ų�����ջ�ˣ���Ҫע�⡿
			����
				��ô �ȱ������ջ��������ջ��ջ������ȥ�����ĵ�ջ���㣬����������ջ���ٰ���ǰ����ķ��ź�������ջ��
		����
			ֱ�ӵ�ջ���㣬�ó����ս��
				
		*/
		while (m_flagStack.size() > 0)
		{
			bool isCalSec = false;
			if (m_flagStack.size() >= 2)//�������ջ�����������ϵ���������Ǿ���Ҫ���ȼ��Ƚ�
			{
				//�ȵ�ջ�Ƚ����ȼ�
				AlgoString<char, int> endTop = m_flagStack.pop();
				AlgoString<char, int> preTop = m_flagStack.pop();
				int priority = getPriortyTag(endTop, preTop);
				if (priority == 1)
				{
					//��ջ�������ȼ��ߣ���ָ�ջ
					m_flagStack.push(preTop);
					m_flagStack.push(endTop);

					//��ջ����,��ջ���
					isCalSec = calculateOnceStack();
				}
				else if (priority == 0)
				{
					//��ջ�������ȼ��ͣ��򱣴���ջ��ջ������Ϊ������ʵ�ֵ�ʱ���ǵ�ջ�Ƚϵ����ȼ��������Ҫ�ظ���ջ����Ϊ��ʱջ��
					double topNum = m_numberStack.pop();
					m_flagStack.push(preTop);

					//��ջ���㣬��ջ���
					isCalSec = calculateOnceStack();

					//�ָ����������ջ��
					m_numberStack.push(topNum);
					m_flagStack.push(endTop);
				}
				else
				{
					//���������β��ʱ�򣬷���ջ�������������ˣ�����������Ǵ��ڣ��Ǿ��ǳ�����
					sprintf(lastErr, "��ջ�쳣���߷���ջ�쳣\0");
					*isSuccess = false;
					return 0;
				}
			}
			else
			{
				//�������ջֻ��һ�������ˣ�û��������ֱ�Ӽ��㣬�õ����ս��
				isCalSec = calculateOnceStack();
			}

			if (isCalSec == false)
			{
				sprintf(lastErr, "��ʽ���󣬲�ƥ��Ĳ�����,�����������쳣��index:end,value:end\0");
				*isSuccess = false;
				return 0;
			}
		}

		if (m_numberStack.size() ==0)
		{
			sprintf(lastErr, "����ʶ��Ĺ�ʽ����������\0");
			*isSuccess = false;
			return 0;
		}
		if (m_numberStack.size() !=1)
		{
			sprintf(lastErr, "��ʽ���ڴ����������������Ȼ��������������\0");
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
		if (isSingleNumberOperator(top))//��Ŀ������ţ�ֻȡ��һ�����������㼴��
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
		else if (ope.equalsIgnoreCase("sqrt"))//n�θ���m==m��1/n����
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