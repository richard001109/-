#include <iostream>
#include <stack>
#include <cstring>
#include <stdlib.h>
using namespace std;

struct FuZhi
{
	int num;
	string code;
};

//预测分析表非终结符序列
string fei[21] = {"G'", "G", "H", "M", "S'", "S", "A", "Q", "L", "L'", "X", "R", "E", "E'", "T", "T'", "F", "B", "C", "D", "P"};
//终结符表
FuZhi teminator[37] = {1, "id", 36, ";", 33, "{", 34, "}", 53, "class", 58, "static", 69, "import", 70, "package", 50, "public",
					   48, "private", 49, "protected", 2, "num", 29, "(", 30, ")", 8, "=", 13, ">", 15, ">=", 14, "<", 16, "<=", 11, "==", 12, "!=",
					   3, "+", 4, "-", 5, "*", 6, "/", 62, "else", 65, "if", 68, "while", 40, "char", 45, "short", 43, "int", 44, "long", 42, "float", 47, "void", 35, ",", 31, "[", 32, "]"};
//预测分析表
int predict[21][37] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
					   0, 0, 0, 0, 0, 0, 2, 2, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 52,
					   0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   6, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0,
					   9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 12, 8, 8, 8, 8, 8, 8, 0, 0, 0,
					   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 15, 16, 17, 18, 19, 0, 0, 0,
					   21, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 21, 21, 21, 21, 21, 21, 21, 21, 0, 0, 0,
					   22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 53, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23,
					   25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25, 25, 0, 0, 0, 0, 0, 0, 0, 0, 25, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 26, 27, 28, 29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   34, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 34, 34, 0, 0, 0, 0, 0, 0, 0, 0, 32, 33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 37, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 37, 0, 37, 37, 37, 37, 37, 37, 35, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   38, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 38, 38, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 41, 0, 41, 41, 41, 41, 41, 41, 41, 41, 39, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 43, 44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 0, 0, 0, 0, 0, 0, 0, 45, 46, 47, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 0, 0, 0, 0, 0, 48, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 0, 0, 0, 50, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

stack<string> code_stack; //符号栈，保存非终结符或终结符的种别码
int input_str[100];		  //输入串
int input_id;			  //输入串下标
int input_len;			  //输入串符号数量

//读取输入串
void scan_input()
{
	string filename; //文件路径
	FILE *fp;
	if ((fp = fopen("input.txt", "r")) == 0)
	{ //打开文件失败
		cout << "打开文件失败！";
		exit(0);
	}
	char ch;
	int i = 0;
	int num = 0;
	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch == '<')
		{
			while ((ch = fgetc(fp)) != EOF)
			{
				if (ch == ',')
				{
					break;
				}
				num = num * 10 + (ch - '0');
			}
			input_str[i] = num;
			num = 0;
			i++;
		}
	}

	input_str[i] = -1;
	input_len = i;
}

void print_file(char *filename)
{
	FILE *fp;
	if ((fp = fopen(filename, "r")) == 0)
	{ //打开文件失败
		cout << "打开文件失败！";
		exit(0);
	}
	char ch;
	while ((ch = fgetc(fp)) != EOF)
	{
		cout << ch;
	}
}

//入栈
void put_stack(int n)
{ //编号为n的产生式右端入栈
	if (n == 1)
	{
		code_stack.push("H");
		code_stack.push("G");
	}
	else if (n == 2)
	{
		code_stack.push("G");
		code_stack.push("36");
		code_stack.push("1");
		code_stack.push("C");
	}
	else if (n == 4)
	{
		code_stack.push("34");
		code_stack.push("M");
		code_stack.push("33");
		code_stack.push("1");
		code_stack.push("D");
		code_stack.push("B");
	}
	else if (n == 5)
	{
		code_stack.push("34");
		code_stack.push("S'");
		code_stack.push("33");
		code_stack.push("30");
		code_stack.push("1");
		code_stack.push("32");
		code_stack.push("31");
		code_stack.push("1");
		code_stack.push("29");
		code_stack.push("1");
		code_stack.push("A");
		code_stack.push("D");
		code_stack.push("B");
	}
	else if (n == 6)
	{
		code_stack.push("S'");
		code_stack.push("S");
	}
	else if (n == 8)
	{
		code_stack.push("36");
		code_stack.push("L");
		code_stack.push("A");
	}
	else if (n == 9)
	{
		code_stack.push("P");
		code_stack.push("1");
	}
	else if (n == 10)
	{
		code_stack.push("36");
		code_stack.push("E");
		code_stack.push("8");
	}
	else if (n == 11)
	{
		code_stack.push("Q");
		code_stack.push("34");
		code_stack.push("S");
		code_stack.push("33");
		code_stack.push("30");
		code_stack.push("X");
		code_stack.push("29");
		code_stack.push("65");
	}
	else if (n == 12)
	{
		code_stack.push("34");
		code_stack.push("S");
		code_stack.push("33");
		code_stack.push("30");
		code_stack.push("X");
		code_stack.push("29");
		code_stack.push("68");
	}
	else if (n == 13)
	{
		code_stack.push("36");
		code_stack.push("30");
		code_stack.push("L");
		code_stack.push("29");
	}
	else if (n == 14)
	{
		code_stack.push("40");
	}
	else if (n == 15)
	{
		code_stack.push("45");
	}
	else if (n == 16)
	{
		code_stack.push("43");
	}
	else if (n == 17)
	{
		code_stack.push("44");
	}
	else if (n == 18)
	{
		code_stack.push("42");
	}
	else if (n == 19)
	{
		code_stack.push("47");
	}
	else if (n == 20)
	{
		code_stack.push("34");
		code_stack.push("S");
		code_stack.push("33");
		code_stack.push("62");
	}
	else if (n == 22)
	{
		code_stack.push("L'");
		code_stack.push("1");
	}
	else if (n == 23)
	{
		code_stack.push("L'");
		code_stack.push("1");
		code_stack.push("35");
	}
	else if (n == 25)
	{
		code_stack.push("E");
		code_stack.push("R");
		code_stack.push("E");
	}
	else if (n == 26)
	{
		code_stack.push("13");
	}
	else if (n == 27)
	{
		code_stack.push("15");
	}
	else if (n == 28)
	{
		code_stack.push("14");
	}
	else if (n == 29)
	{
		code_stack.push("16");
	}
	else if (n == 30)
	{
		code_stack.push("11");
	}
	else if (n == 31)
	{
		code_stack.push("12");
	}
	else if (n == 32)
	{
		code_stack.push("E'");
		code_stack.push("T");
		code_stack.push("3");
	}
	else if (n == 33)
	{
		code_stack.push("E'");
		code_stack.push("T");
		code_stack.push("4");
	}
	else if (n == 34)
	{
		code_stack.push("E'");
		code_stack.push("T");
	}
	else if (n == 35)
	{
		code_stack.push("E'");
		code_stack.push("T");
		code_stack.push("3");
	}
	else if (n == 36)
	{
		code_stack.push("E'");
		code_stack.push("T");
		code_stack.push("4");
	}
	else if (n == 38)
	{
		code_stack.push("T'");
		code_stack.push("F");
	}
	else if (n == 39)
	{
		code_stack.push("T'");
		code_stack.push("F");
		code_stack.push("5");
	}
	else if (n == 40)
	{
		code_stack.push("T'");
		code_stack.push("F");
		code_stack.push("6");
	}
	else if (n == 42)
	{
		code_stack.push("1");
	}
	else if (n == 43)
	{
		code_stack.push("2");
	}
	else if (n == 44)
	{
		code_stack.push("30");
		code_stack.push("E");
		code_stack.push("29");
	}
	else if (n == 45)
	{
		code_stack.push("50");
	}
	else if (n == 46)
	{
		code_stack.push("48");
	}
	else if (n == 47)
	{
		code_stack.push("49");
	}
	else if (n == 48)
	{
		code_stack.push("69");
	}
	else if (n == 49)
	{
		code_stack.push("70");
	}
	else if (n == 50)
	{
		code_stack.push("53");
	}
	else if (n == 51)
	{
		code_stack.push("58");
	}
	else if (n == 53)
	{
		code_stack.push("2");
		code_stack.push("8");
	}
}

void LL1()
{
	cout << "符号栈模拟：" << endl;
	stack<string> s; //中间栈
	while (!code_stack.empty())
	{
		s.push(code_stack.top());
		code_stack.pop();
	}
	while (s.size() >= 1 && input_str[input_id] != -1)
	{
		while (!s.empty())
		{
			code_stack.push(s.top());
			int i;
			for (i = 0; i < 37; i++)
			{
				int num = atoi(s.top().c_str());
				if (num == teminator[i].num)
				{
					cout << teminator[i].code;
					break;
				}
			}
			if (i == 37)
			{
				cout << s.top();
			}
			s.pop();
		}
		cout << endl;
		string top_code = code_stack.top(); //获取栈顶符号
		code_stack.pop();
		int i, f = 0;
		for (i = 0; i < 21; i++)
		{
			if (top_code == fei[i])
			{ //栈顶为非终结符
				int j;
				for (j = 0; j < 35; j++)
				{
					int p = 0;
					if (teminator[j].num == input_str[input_id])
					{ //获取输入串目前讨论到的符号种别码
						if (predict[i][j] != 0)
						{
							put_stack(predict[i][j]);
						}
						else
						{
							//							cout<<"第"<<input_id+1<<"个符号无法识别,语法分析失败！"<<endl;
							f = 1;
						}
						p = 1;
					}
					if (p == 1)
					{
						break;
					}
				}
				if (j == 35)
				{
					//					cout<<"第"<<input_id+1<<"个符号无法识别,语法分析失败！"<<endl;
					f = 1;
				}
				break;
			}
		}
		if (f == 1)
		{
			break;
		}
		if (i == 21)
		{	//栈顶为终结符
			//		    if(top_code=="#"){
			//
			//			}
			// cout<<top_code<<endl;
			int num = atoi(top_code.c_str());
			if (num == input_str[input_id])
			{
				input_id++;
				// cout<<top_code<<" "<<input_id<<endl;
			}
			else
			{
				//				cout<<"第"<<input_id+1<<"个符号无法识别,语法分析失败！"<<endl;
				break;
			}
		}
		while (!code_stack.empty())
		{
			s.push(code_stack.top());
			code_stack.pop();
		}
	}
	while (!s.empty())
	{
		int i;
		for (i = 0; i < 37; i++)
		{
			if (atoi(s.top().c_str()) == teminator[i].num)
			{
				cout << teminator[i].code;
				break;
			}
		}
		if (i == 37)
		{
			cout << s.top();
		}
		code_stack.push(s.top());
		s.pop();
	}
	cout << endl;
	if (code_stack.top() == "#" && input_str[input_id] == -1)
	{
		cout << "语法分析成功！" << endl;
		code_stack.pop();
	}
	else
	{
		cout << "第" << input_id + 1 << "个符号无法识别,语法分析失败！" << endl;
	}
}

int main()
{
	int n;
	while (1)
	{
		cout << "------------------------语法分析器-----------------------" << endl;
		cout << "---------------------1、文法产生式-----------------------" << endl;
		cout << "---------------------2、First，Follow集------------------" << endl;
		cout << "---------------------3、预测分析表-----------------------" << endl;
		cout << "---------------------4、测试代码-------------------------" << endl;
		cout << "---------------------4、语法分析-------------------------" << endl;
		cout << "---------------------0、退出-----------------------------" << endl;
		cout << "请选择操作序号：" << endl;
		cin >> n;
		switch (n)
		{
		case 1:
			print_file("result.txt");
			break;
		case 2:
			print_file("ff.txt");
			break;
		case 3:
			print_file("yu.txt");
			break;
		case 4:
			scan_input();
			code_stack.push("#"); //栈底符号
			code_stack.push("G'");
			LL1();
			memset(input_str, 0, sizeof(input_str));
			input_id = 0;
			input_len = 0;
			break;
		case 0:
			break;
		}
		if (n == 0)
		{
			break;
		}
		cout << endl;
	}
	return 0;
}
