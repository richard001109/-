#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

/*=====================Java符号表符号编码=======================*/
//枚举常量的序号从0开始，序号作为符号表code码。
//符号表里忘写的符号(代码里已经加上)：
//整数:86
//浮点数:87
//=:88
enum TokenCode
{
	//未定义
	W_UNDEFINED, // 0

	//标识符
	W_IDENT, // 1

	//运算符
	CW_ADD,		// 2: +
	CW_SUB,		// 3: -
	CW_MUL,		// 4: *
	CW_DIV,		// 5: /
	CW_TTR,		// 6: %
	CW_EQ_EQ,	// 7: ==
	CW_F_EQ,	// 8: !=
	CW_BI,		// 9: >
	CW_SM,		// 10: <
	CW_BG_EQ,	// 11: >=
	CW_SM_EQ,	// 12: <=
	CW_ADD_ADD, // 13: ++
	CW_SUB_SUB, // 14: --
	CW_ADD_EQ,	// 15: +=
	CW_SUB_EQ,	// 16: -=
	CW_MUL_EQ,	// 17: *=
	CW_DIV_EQ,	// 18: /=
	CW_TTR_EQ,	// 19: %=

	//逻辑运算符
	CW_F,	// 20: !
	CW_A,	// 21: &
	CW_A_A, // 22: &&
	CW_O,	// 23: |
	CW_O_O, // 24: ||
	CW_N,	// 25: ^

	//分隔符
	W_LEFT_BIG,	   // 26: {
	W_RIGHT_BIG,   // 27: }
	W_LEFT_SMALL,  // 28: (
	W_RIGHT_SMALL, // 29: )
	W_LEFT_MID,	   // 30: [
	W_RIGHT_MID,   // 31: ]
	W_FENHAO,	   // 32: ;
	W_DOUHAO,	   // 33: ,
	W_MAOHAO,	   // 34: :

	//关键字
	KW_PUBLIC,		 // 35
	KW_PROTECTED,	 // 36
	KW_PRIVATE,		 // 37
	KW_CLASS,		 // 38
	KW_INTERFACE,	 // 39
	KW_ABSTRACT,	 // 40
	KW_IMPLEMENTS,	 // 41
	KW_EXTENDS,		 // 42
	KW_NEW,			 // 43
	KW_IMPORT,		 // 44
	KW_PACKAGE,		 // 45
	KW_SHORT,		 // 46
	KW_CHAR,		 // 47
	KW_BOOLEAN,		 // 48
	KW_BYTE,		 // 49
	KW_INT,			 // 50
	KW_LONG,		 // 51
	KW_FLOAT,		 // 52
	KW_DOUBLE,		 // 53
	KW_VOID,		 // 54
	KW_IF,			 // 55
	KW_ELSE,		 // 56
	KW_WHILE,		 // 57
	KW_FOR,			 // 58
	KW_SWITCH,		 // 59
	KW_CASE,		 // 60
	KW_DEFAULT,		 // 61
	KW_DO,			 // 62
	KW_BREAK,		 // 63
	KW_CONTINUE,	 // 64
	KW_RETURN,		 // 65
	KW_INSTANCEOF,	 // 66
	KW_STATIC,		 // 67
	KW_FINAL,		 // 68
	KW_SUPER,		 // 69
	KW_THIS,		 // 70
	KW_NATIVE,		 // 71
	KW_STRICTFP,	 // 72
	KW_SYNCHRONIZED, // 73
	KW_TRANSIENT,	 // 74
	KW_VOLATILE,	 // 75
	KW_CATCH,		 // 76
	KW_TRY,			 // 77
	KW_FINALLY,		 // 78
	KW_THROW,		 // 79
	KW_THROWS,		 // 80
	KW_ENUM,		 // 81
	KW_ASSERT,		 // 82
	KW_NULL,		 // 83
	KW_TRUE,		 // 84
	KW_FALSE,		 // 85

	//常量
	W_INT,	  // 86: 整数
	W_DOUBLE, // 87: 浮点数

	//漏写的
	CW_EQ // 88: =
};

/*===========================全局变量===========================*/
TokenCode code = W_UNDEFINED; // 单词种别码,默认为未定义
const int MAX = 48 + 3;		  // 关键字数量,这里把java的3个特殊常量算作了关键字
int row = 1;				  // 单词所在行数
string token = "";			  // 存储单词
//存储48个关键字,3个特殊常量
char keyWord[][20] = {"public", "protected", "private", "class", "interface", "abstract", "implements",
					  "extends", "new", "import", "package", "short", "char", "boolean", "byte", "int",
					  "long", "float", "double", "void", "if", "else", "while", "for", "switch", "case",
					  "default", "do", "break", "continue", "return", "instanceof", "static", "final",
					  "super", "this", "native", "strictfp", "synchronized", "transient", "volatile",
					  "catch", "try", "finally", "throw", "throws", "enum", "assert", "null", "true", "false"};

//记录标识符和常数的数组,最多40个，最长20字符
char ident[40][20];
char intOrFloat[40][20];
//记录ident和intOrFloat两个二维数组的行标，因为这两个索引从0开始，因此输出未存在的标识符或常数的code时输出i2-1或i3-1
int i1 = 0; // ident
int i2 = 0; // intOrFloat
//记录在ident或intOrFloat中已存在的单词行标，输出已存在的标识符或常数的code时输出i3即可
int i3;
//因为打印在词法分析之后，因此用一个bool来存储是否已经存在的状态
bool alreadyHave;

/*===========================函数===============================*/
/**
 * 打印词法分析器结果
 * @param code
 */
void print(TokenCode code)
{
	switch (code)
	{
	//未定义
	case W_UNDEFINED:
		cout << '(' << code << ',' << token << ')' << "提示！未识别的符号所在行：" << row << endl;
		return;
		break;
	//关键字
	case KW_PUBLIC:
	case KW_PROTECTED:
	case KW_PRIVATE:
	case KW_CLASS:
	case KW_INTERFACE:
	case KW_ABSTRACT:
	case KW_IMPLEMENTS:
	case KW_EXTENDS:
	case KW_NEW:
	case KW_IMPORT:
	case KW_PACKAGE:
	case KW_SHORT:
	case KW_CHAR:
	case KW_BOOLEAN:
	case KW_BYTE:
	case KW_INT:
	case KW_LONG:
	case KW_FLOAT:
	case KW_DOUBLE:
	case KW_VOID:
	case KW_IF:
	case KW_ELSE:
	case KW_WHILE:
	case KW_FOR:
	case KW_SWITCH:
	case KW_CASE:
	case KW_DEFAULT:
	case KW_DO:
	case KW_BREAK:
	case KW_CONTINUE:
	case KW_RETURN:
	case KW_INSTANCEOF:
	case KW_STATIC:
	case KW_FINAL:
	case KW_SUPER:
	case KW_THIS:
	case KW_NATIVE:
	case KW_STRICTFP:
	case KW_SYNCHRONIZED:
	case KW_TRANSIENT:
	case KW_VOLATILE:
	case KW_CATCH:
	case KW_TRY:
	case KW_FINALLY:
	case KW_THROW:
	case KW_THROWS:
	case KW_ENUM:
	case KW_ASSERT:
		break;
	//运算符
	case CW_ADD:   // +
	case CW_SUB:   // -
	case CW_MUL:   // *
	case CW_DIV:   // /
	case CW_TTR:   // %
	case CW_EQ:	   // =
	case CW_EQ_EQ: // ==
	case CW_SM:	   // <
	case CW_BI:	   // >
	case CW_SM_EQ: // <=
	case CW_BG_EQ: // >=
	//分隔符
	case W_LEFT_BIG:	// {
	case W_RIGHT_BIG:	// }
	case W_LEFT_MID:	// [
	case W_RIGHT_MID:	// ]
	case W_LEFT_SMALL:	// (
	case W_RIGHT_SMALL: // )
	case W_DOUHAO:		// ,
	case W_FENHAO:		// ;
	case W_MAOHAO:		// :
		break;
	//常量
	case W_INT:	   // 整数
	case W_DOUBLE: // 浮点数
		// cout << '(' << code << ',' << atoi(token.c_str()) << ")" << endl;
		// cout << '(' << code << ',' << atof(token.c_str()) << ")" << endl;
		if (alreadyHave)
		{
			//已经存在，打印i3
			cout << '(' << code << ',' << "intOrFloat[" << i3 << "]"
				 << ")" << endl;
		}
		else
		{
			//还未存在，打印i2-1
			cout << '(' << code << ',' << "intOrFloat[" << (i2 - 1) << "]"
				 << ")" << endl;
		}
		return;
		break;
	//标识符
	case W_IDENT:
		if (alreadyHave)
		{
			//已经存在，打印i3
			cout << '(' << code << ',' << "ident[" << i3 << "]"
				 << ")" << endl;
		}
		else
		{
			//不存在，打印i1-1
			cout << '(' << code << ',' << "ident[" << (i1 - 1) << "]"
				 << ")" << endl;
		}
		return;
		break;
	default:
		break;
	}
	cout << '(' << code << ',' << token << ')' << endl;
}

/**
 * 判断标识符是否已在数组中
 * 若已存在，便返回该数组行标
 * 若不存在，返回41
 * @param token
 * @return int
 */
int identAlreadyHave(string token)
{
	for (int i = 0; i < 40; i++)
	{
		if (ident[i] == token)
			return i;
	}
	//不存在返回41
	return 41;
}

/**
 * 判断int或是float是否已在数组中
 * 若已存在，便返回该数组行标
 * 若不存在，返回41
 * @param token
 * @return int
 */
int intOrFloatAlreadyHave(string token)
{
	for (int i = 0; i < 40; i++)
	{
		if (intOrFloat[i] == token)
			return i;
	}
	//不存在返回41
	return 41;
}

/**
 * 判断是否为关键字
 * @param token
 * @return true
 * @return false
 */
bool isKey(string token)
{
	for (int i = 0; i < MAX; i++)
	{
		if (token.compare(keyWord[i]) == 0)
			return true;
	}
	return false;
}

/**
 * 返回关键字code值：数值下标 + 35
 * @param token
 * @return int
 */
int getKeyID(string token)
{
	for (int i = 0; i < MAX; i++)
	{
		//关键字的内码值为keyWord数组中对应的下标 + 35
		//数组从0开始，枚举中第一个关键字从35开始
		if (token.compare(keyWord[i]) == 0)
			return i + 35;
	}
	return -1;
}

/**
 * 判断一个字符是否是字母
 * @param letter
 * @return true
 * @return false
 */
bool isLetter(char letter)
{
	if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
		return true;
	return false;
}

/**
 * 判断一个字符是否是数字
 * @param digit
 * @return true
 * @return false
 */
bool isDigit(char digit)
{
	if (digit >= '0' && digit <= '9')
		return true;
	return false;
}

/**
 * 词法分析
 * @param fp 文件指针
 * 全局变量：ident 记录标识符的二维数组
 * 全局变量：intOrFloat 记录常数的二维数组
 */
void lexicalAnalysis(FILE *fp)
{
	//创建文件对象
	ofstream os, os2;
	//将对象与存标识符的文件关联
	os.open("H:/java_identTable.txt");
	//将对象与存常数的文件关联
	os2.open("H:/java_intorfloatTable.txt");
	//记录标识符文件中标识符的code
	int identCode = 0;
	//记录标识符文件中标识符的code
	int intOrFloatCode = 0;
	//存储从文件中获取的单个字符
	int ch;
	//若未读取到文件尾，从文件中获取一个字符
	while ((ch = fgetc(fp)) != EOF)
	{
		//将获取的字符存入token中
		token = ch;
		// a.忽略空格、Tab和回车
		if (ch == ' ' || ch == '\t' || ch == '\n')
		{
			//遇到换行符，记录行数的row加1
			if (ch == '\n')
				row++;
			//继续执行循环
			continue;
		}
		// b.若以字母开头，关键字或标识符
		else if (isLetter(ch))
		{
			// token初始化
			token = "";
			//非字母或数字时退出，将单词存储在token中
			while (isLetter(ch) || isDigit(ch))
			{
				//将读取的字符ch存入token中
				token.push_back(ch);
				//获取下一个字符
				ch = fgetc(fp);
			}
			//文件指针后退一个字节，即重新读取上述单词后的第一个字符
			fseek(fp, -1L, SEEK_CUR);
			//关键字，标识符
			if (isKey(token))
			{
				code = TokenCode(getKeyID(token));
			}
			else
			{
				code = W_IDENT;
				//判断ident数组中是否已有该标识符
				if (identAlreadyHave(token) == 41)
				{
					//表示没有，token存入标识符数组中，且i1++
					strcpy(ident[i1], token.c_str());
					i1++;
					//将标识符存入ident文件并赋值code并换行
					os << identCode << ' ' << token << endl;
					// identCode + 1
					identCode++;
					//同时记录状态的全局变量值false
					alreadyHave = false;
				}
				else
				{
					//表示已存在
					//全局变量记录已存在的数组行标
					i3 = identAlreadyHave(token);
					alreadyHave = true;
				}
			}
		}
		// c.无符号常数以数字开头
		else if (isDigit(ch))
		{
			//标记是否为浮点数
			int isdouble = 0;
			// token初始化
			token = "";
			//当前获取到的字符为数字
			while (isDigit(ch))
			{
				//读取数字，将其存入token中
				token.push_back(ch);
				//从文件中获取下一个字符
				ch = fgetc(fp);
				//该单词中第一次出现小数点
				if (ch == '.' && isdouble == 0)
				{
					//小数点下一位是数字
					if (isDigit(fgetc(fp)))
					{
						isdouble = 1;			  //标记该常数中已经出现过小数点
						fseek(fp, -1L, SEEK_CUR); //将超前读取的小数点后一位重新读取
						token.push_back(ch);	  //将小数点入token中
						ch = fgetc(fp);			  //读取小数点后的下一位数字
					}
				}
			}
			//浮点型or整型
			if (isdouble == 1)
			{
				code = W_DOUBLE;
				//判断该常数是否已经存在
				if (intOrFloatAlreadyHave(token) == 41)
				{
					// 表示不存在
					// token存入标识符数组中，同时i2++
					strcpy(intOrFloat[i2], token.c_str());
					i2++;
					//同时存入文件切换行
					os2 << intOrFloatCode << ' ' << token << endl;
					intOrFloatCode++;
					//同时记录状态的全局变量值false
					alreadyHave = false;
				}
				else
				{
					//表示已存在
					//全局变量记录已存在的数组行标
					i3 = intOrFloatAlreadyHave(token);
					alreadyHave = true;
				}
			}
			else
			{
				code = W_INT;
				//判断该常数是否已经存在
				if (intOrFloatAlreadyHave(token) == 41)
				{
					// 表示不存在
					// token存入标识符数组中，同时i2++
					strcpy(intOrFloat[i2], token.c_str());
					i2++;
					//同时存入文件切换行
					os2 << intOrFloatCode << ' ' << token << endl;
					intOrFloatCode++;
					//同时记录状态的全局变量值false
					alreadyHave = false;
				}
				else
				{
					//表示已存在
					//全局变量记录已存在的数组行标
					i3 = intOrFloatAlreadyHave(token);
					alreadyHave = true;
				}
			}
			//文件指针后退一个字节，即重新读取常数后的第一个字符
			fseek(fp, -1L, SEEK_CUR);
		}
		else
			switch (ch)
			{
			//运算符
			case '+':
			{
				ch = fgetc(fp); //超前读取'='后面的字符
				if (ch == '=')	//+=等于号
				{
					token.push_back(ch); //将'+'后面的'='存入token中
					code = CW_ADD_EQ;	 //单词为"+="
				}
				else
				{							  //+赋值运算符
					code = CW_ADD;			  //单词为"+"
					fseek(fp, -1L, SEEK_CUR); //将超前读取的字符重新读取
				}
			}
			break;
			case '-':
			{
				ch = fgetc(fp); //超前读取'='后面的字符
				if (ch == '=')	//-=等于号
				{
					token.push_back(ch); //将'-'后面的'='存入token中
					code = CW_SUB_EQ;	 //单词为"-="
				}
				else
				{							  //-赋值运算符
					code = CW_SUB;			  //单词为"-"
					fseek(fp, -1L, SEEK_CUR); //将超前读取的字符重新读取
				}
			}
			break;
			case '*':
			{
				ch = fgetc(fp); //超前读取'='后面的字符
				if (ch == '=')	//*=等于号
				{
					token.push_back(ch); //将'*'后面的'='存入token中
					code = CW_MUL_EQ;	 //单词为"*="
				}
				else
				{							  //*赋值运算符
					code = CW_MUL;			  //单词为"-"
					fseek(fp, -1L, SEEK_CUR); //将超前读取的字符重新读取
				}
			}
			break;
			case '/':
			{
				ch = fgetc(fp); //超前读取'='后面的字符
				if (ch == '=')	///=等于号
				{
					token.push_back(ch); //将'/'后面的'='存入token中
					code = CW_DIV_EQ;	 //单词为"/="
				}
				else
				{							  ///赋值运算符
					code = CW_DIV;			  //单词为"/"
					fseek(fp, -1L, SEEK_CUR); //将超前读取的字符重新读取
				}
			}
			break;
			case '=':
			{
				ch = fgetc(fp); //超前读取'='后面的字符
				if (ch == '=')	//==等于号
				{
					token.push_back(ch); //将'='后面的'='存入token中
					code = CW_EQ_EQ;	 //单词为"=="
				}
				else
				{							  //=赋值运算符
					code = CW_EQ;			  //单词为"="
					fseek(fp, -1L, SEEK_CUR); //将超前读取的字符重新读取
				}
			}
			break;
			case '%':
			{
				ch = fgetc(fp); //超前读取'='后面的字符
				if (ch == '=')	//%=等于号
				{
					token.push_back(ch); //将'%'后面的'='存入token中
					code = CW_TTR_EQ;	 //单词为"%="
				}
				else
				{							  //%赋值运算符
					code = CW_TTR;			  //单词为"%"
					fseek(fp, -1L, SEEK_CUR); //将超前读取的字符重新读取
				}
			}
			break;
			case '<':
			{
				ch = fgetc(fp); //超前读取'<'后面的字符
				if (ch == '=')	//<=小于等于号
				{
					token.push_back(ch); //将'<'后面的'='存入token中
					code = CW_SM_EQ;	 //单词为"<="
				}
				else
				{							  //<小于号
					code = CW_SM;			  //单词为"<"
					fseek(fp, -1L, SEEK_CUR); //将超前读取的字符重新读取
				}
			}
			break;
			case '>':
			{
				ch = fgetc(fp); //超前读取'>'后面的字符
				if (ch == '=')	//>=大于等于号
				{
					token.push_back(ch); //将'>'后面的'='存入token中
					code = CW_BG_EQ;	 //单词为">="
				}
				else
				{							  //>大于号
					code = CW_BI;			  //单词为">"
					fseek(fp, -1L, SEEK_CUR); //将超前读取的字符重新读取
				}
			}
			break;
			//分界符
			case '(':
				code = W_LEFT_SMALL; //(左圆括号
				break;
			case ')':
				code = W_RIGHT_SMALL; //)右圆括号
				break;
			case '[':
				code = W_LEFT_MID; //[左中括号
				break;
			case ']':
				code = W_RIGHT_MID; //]右中括号
				break;
			case '{':
				code = W_LEFT_BIG; //{左大括号
				break;
			case '}':
				code = W_RIGHT_BIG; //}右大括号
				break;
			case ';':
				code = W_FENHAO; //;分号
				break;
			case ',':
				code = W_DOUHAO; //,逗号
				break;
			case ':':
				code = W_MAOHAO; //:冒号
				break;
			//未识别符号
			default:
				code = W_UNDEFINED;
			}
		//打印词法分析结果
		print(code);
	}
	//关闭文件
	os.close();
	os2.close();
}

int main()
{
	string filename; //文件路径
	FILE *fp;		 //文件指针
	// cout << "请输入源文件名：" << endl;
	while (true)
	{
		//读取文件路径
		// cin >> filename;
		filename = "F:/.编译原理\lexical analyzer\src\test.txt";
		//打开文件
		if ((fopen_s(&fp, filename.c_str(), "r")) == 0)
			break;
		else
			cout << "路径输入错误！" << endl; //读取失败
	}
	cout << "/===============================词法分析结果==============================/" << endl;
	//词法分析
	lexicalAnalysis(fp);
	//关闭文件
	fclose(fp);

	return 0;
}