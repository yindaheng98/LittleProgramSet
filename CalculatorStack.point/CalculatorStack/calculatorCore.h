#pragma once
#include<stack>
using std::stack;

bool check(CString expr)			//检查表达式
{
	int left = 0;					//左括号计数
	int right = 0;					//右括号计数
	int i = 0;						//循环计数器
	bool prior_ope = 0;				//前一位标识符
	bool prior_brk = 0;				//前一位右括号标识符
	while (wchar_t w = expr[i++])
	{
		switch (w)
		{
		case'+':
		case'-':
		case'*':
		case'/':
			if (prior_ope)return 0;	//如果连续输入两个运算符
			prior_ope = 1;			//前一位标识符设置为运算符
			prior_brk = 0;			//前一位右括号标识符设置为false
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
			if (prior_brk)return 0;	//在右括号后输入数字
			prior_ope = 0;			//前一位标识符设置为数字
			break;

		case'(':
			if (!prior_ope)return 0;//在数字后输入左括号
			left++;					//左括号计数+1
			prior_ope = 1;			//前一位设置为运算符
			break;

		case')':
			if (prior_ope)return 0;	//在运算符后输入右括号
			right++;				//右括号计数+1
			if (left < right)return 0;//右括号多于左括号
			prior_brk = 1;			//前一位右括号标识符设置为true
			prior_ope = 0;			//前一位标识符设置为数字
			break;

		default:
			return 0;				//输入非法字符
			break;
		}
	}
	if (i >= 2)						//判前一位
	{
		switch (expr[i - 2])
		{
		case'+':
		case'-':
		case'*':
		case'/':
			return 0;				//最后一位为运算符
			break;
		}
	}
	if (left - right)return 0;		//左右括号数量不等
	else return 1;
}

void calculate_prior(stack<wchar_t>*ope, stack<float>*num)//运算前一批数据
{
	if (!ope->empty())
	{
		char prior = ope->top();
		ope->pop();									//删前一运算符
		float right = num->top();
		num->pop();
		float left = num->top();
		num->pop();									//删除前两个数
		switch (prior)
		{
		case'+':num->push(left + right); break;
		case'-':num->push(left - right); break;
		case'*':num->push(left * right); break;
		case'/':num->push(left / right); break;		//取出最上面两个数，运算后入栈
		}
	}
}

void calculate_all(stack<wchar_t>*ope, stack<float>*num)//运算所有数据
{
	calculate_prior(ope, num);
	calculate_prior(ope, num);
}

float calculate(CString expr, int&i)				//运算表达式
{
	stack<wchar_t>ope;
	stack<float>num;
	bool prior_ope = 0;
	float tempnum = 0;
	while (expr[i])
	{
		if (expr[i] <= '9' && expr[i] >= '0')		//当输入数字时
		{
			tempnum = tempnum * 10 + expr[i] - 48;
			i++;
			prior_ope = 0;							//前一位标识设置为数字
		}
		else
		{
			num.push(tempnum);						//数入栈
			tempnum = 0;
			if ((expr[i] == '+' || expr[i] == '-') && !prior_ope)//当输入加减时
			{
				calculate_all(&ope, &num);			//运算前面所有项
				ope.push(expr[i]);					//当前运算符入栈
				prior_ope = 1;						//前一位标识设置为运算符
				i++;								//下一位
			}
			else if ((expr[i] == '*' || expr[i] == '/') && !prior_ope)//当输入乘除时
			{

				if (!ope.empty())					//如果不是第一个运算符
				{
					char prior = ope.top();
					switch (prior)					//看前一运算符
					{
					case'*':
					case'/':						//如果前一运算符优先级相等,先运算
						calculate_prior(&ope, &num);//运算前一项
					}
				}
				ope.push(expr[i]);					//当前运算符入栈
				prior_ope = 1;						//前一位标识设置为运算符
				i++;								//下一位

			}
			else if (expr[i] == '('&&prior_ope)		//左括号
			{
				num.pop();							//将判断为非数字时入栈的0删除
				tempnum = calculate(expr, ++i);		//将括号内表达式做递归运算
				prior_ope = 0;						//前一位标识设置为数字
			}
			else if (expr[i] == ')' && !prior_ope)	//右括号
			{
				i++;
				calculate_all(&ope, &num);			//无条件计算表达式
				return num.top();					//返回计算结果
			}
		}
	}
	num.push(tempnum);								//数字入栈
	calculate_all(&ope, &num);						//运算
	return num.top();								//返回值
}
