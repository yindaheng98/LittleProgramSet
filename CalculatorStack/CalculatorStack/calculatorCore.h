#pragma once
#include<stack>
using std::stack;

bool check(CString expr)			//�����ʽ
{
	int left = 0;					//�����ż���
	int right = 0;					//�����ż���
	int i = 0;						//ѭ��������
	bool prior_ope = 0;				//ǰһλ��ʶ��
	bool prior_brk = 0;				//ǰһλ�����ű�ʶ��
	while (wchar_t w = expr[i++])
	{
		switch (w)
		{
		case'+':
		case'-':
		case'*':
		case'/':
			if (prior_ope)return 0;	//��������������������
			prior_ope = 1;			//ǰһλ��ʶ������Ϊ�����
			prior_brk = 0;			//ǰһλ�����ű�ʶ������Ϊfalse
			break;

		case'1':
		case'2':
		case'3':
		case'4':
		case'5':
		case'6':
		case'7':
		case'8':
		case'9':
		case'0':
			if (prior_brk)return 0;	//�������ź���������
			prior_ope = 0;			//ǰһλ��ʶ������Ϊ����
			break;

		case'(':
			if (!prior_ope)return 0;//�����ֺ�����������
			left++;					//�����ż���+1
			prior_ope = 1;			//ǰһλ����Ϊ�����
			break;

		case')':
			if (prior_ope)return 0;	//�������������������
			right++;				//�����ż���+1
			if (left < right)return 0;//�����Ŷ���������
			prior_brk = 1;			//ǰһλ�����ű�ʶ������Ϊtrue
			prior_ope = 0;			//ǰһλ��ʶ������Ϊ����
			break;

		default:
			return 0;				//����Ƿ��ַ�
			break;
		}
	}
	if (i >= 2)						//��ǰһλ
	{
		switch (expr[i - 2])
		{
		case'+':
		case'-':
		case'*':
		case'/':
			return 0;				//���һλΪ�����
			break;
		}
	}
	if (left - right)return 0;		//����������������
	else return 1;
}

void calculate_prior(stack<wchar_t>*ope, stack<float>*num)//����ǰһ������
{
	if (!ope->empty())
	{
		char prior = ope->top();
		ope->pop();									//ɾǰһ�����
		float right = num->top();
		num->pop();
		float left = num->top();
		num->pop();									//ɾ��ǰ������
		switch (prior)
		{
		case'+':num->push(left + right); break;
		case'-':num->push(left - right); break;
		case'*':num->push(left * right); break;
		case'/':num->push(left / right); break;		//ȡ�����������������������ջ
		}
	}
}

void calculate_all(stack<wchar_t>*ope, stack<float>*num)//������������
{
	calculate_prior(ope, num);
	calculate_prior(ope, num);
}

float calculate(CString expr, int&i)				//������ʽ
{
	stack<wchar_t>ope;
	stack<float>num;
	bool prior_ope = 0;
	float tempnum = 0;
	while (expr[i])
	{
		if (expr[i] <= '9' && expr[i] >= '0')		//����������ʱ
		{
			tempnum = tempnum * 10 + expr[i] - 48;
			i++;
			prior_ope = 0;							//ǰһλ��ʶ����Ϊ����
		}
		else
		{
			num.push(tempnum);						//����ջ
			tempnum = 0;
			if ((expr[i] == '+' || expr[i] == '-') && !prior_ope)//������Ӽ�ʱ
			{
				calculate_all(&ope, &num);			//����ǰ��������
				ope.push(expr[i]);					//��ǰ�������ջ
				prior_ope = 1;						//ǰһλ��ʶ����Ϊ�����
				i++;								//��һλ
			}
			else if ((expr[i] == '*' || expr[i] == '/') && !prior_ope)//������˳�ʱ
			{

				if (!ope.empty())					//������ǵ�һ�������
				{
					char prior = ope.top();
					switch (prior)					//��ǰһ�����
					{
					case'*':
					case'/':						//���ǰһ��������ȼ����,������
						calculate_prior(&ope, &num);//����ǰһ��
					}
				}
				ope.push(expr[i]);					//��ǰ�������ջ
				prior_ope = 1;						//ǰһλ��ʶ����Ϊ�����
				i++;								//��һλ

			}
			else if (expr[i] == '('&&prior_ope)		//������
			{
				num.pop();							//���ж�Ϊ������ʱ��ջ��0ɾ��
				tempnum = calculate(expr, ++i);		//�������ڱ��ʽ���ݹ�����
				prior_ope = 0;						//ǰһλ��ʶ����Ϊ����
			}
			else if (expr[i] == ')' && !prior_ope)	//������
			{
				i++;
				calculate_all(&ope, &num);			//������������ʽ
				return num.top();					//���ؼ�����
			}
		}
	}
	num.push(tempnum);								//������ջ
	calculate_all(&ope, &num);						//����
	return num.top();								//����ֵ
}
