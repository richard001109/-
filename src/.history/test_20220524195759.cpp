#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

/*=====================Java���ű���ű���=======================*/
//ö�ٳ�������Ŵ�0��ʼ�������Ϊ���ű�code�롣
//���ű�����д�ķ���(�������Ѿ�����)��
//����:86
//������:87
//=:88
enum TokenCode
{
	//δ����
	W_UNDEFINED, // 0

	//��ʶ��
	W_IDENT, // 1

	//�����
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

	//�߼������
	CW_F,	// 20: !
	CW_A,	// 21: &
	CW_A_A, // 22: &&
	CW_O,	// 23: |
	CW_O_O, // 24: ||
	CW_N,	// 25: ^

	//�ָ���
	W_LEFT_BIG,	   // 26: {
	W_RIGHT_BIG,   // 27: }
	W_LEFT_SMALL,  // 28: (
	W_RIGHT_SMALL, // 29: )
	W_LEFT_MID,	   // 30: [
	W_RIGHT_MID,   // 31: ]
	W_FENHAO,	   // 32: ;
	W_DOUHAO,	   // 33: ,
	W_MAOHAO,	   // 34: :

	//�ؼ���
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

	//����
	W_INT,	  // 86: ����
	W_DOUBLE, // 87: ������

	//©д��
	CW_EQ // 88: =
};

/*===========================ȫ�ֱ���===========================*/
TokenCode code = W_UNDEFINED; // �����ֱ���,Ĭ��Ϊδ����
const int MAX = 48 + 3;		  // �ؼ�������,�����java��3�����ⳣ�������˹ؼ���
int row = 1;				  // ������������
string token = "";			  // �洢����
//�洢48���ؼ���,3�����ⳣ��
char keyWord[][20] = { "public", "protected", "private", "class", "interface", "abstract", "implements",
					  "extends", "new", "import", "package", "short", "char", "boolean", "byte", "int",
					  "long", "float", "double", "void", "if", "else", "while", "for", "switch", "case",
					  "default", "do", "break", "continue", "return", "instanceof", "static", "final",
					  "super", "this", "native", "strictfp", "synchronized", "transient", "volatile",
					  "catch", "try", "finally", "throw", "throws", "enum", "assert", "null", "true", "false" };

//��¼��ʶ���ͳ���������,���40�����20�ַ�
char ident[40][20];
char intOrFloat[40][20];
//��¼ident��intOrFloat������ά������б꣬��Ϊ������������0��ʼ��������δ���ڵı�ʶ��������codeʱ���i2-1��i3-1
int i1 = 0; // ident
int i2 = 0; // intOrFloat
//��¼��ident��intOrFloat���Ѵ��ڵĵ����б꣬����Ѵ��ڵı�ʶ��������codeʱ���i3����
int i3;
//��Ϊ��ӡ�ڴʷ�����֮�������һ��bool���洢�Ƿ��Ѿ����ڵ�״̬
bool alreadyHave;

/*===========================����===============================*/
/**
 * ��ӡ�ʷ����������
 * @param code
 */
void print(TokenCode code)
{
	switch (code)
	{
		//δ����
	case W_UNDEFINED:
		cout<<'('<<code<<','<<token<<')'<<"��ʾ��δʶ��ķ��������У�"<<row<<endl;
		return;
		break;
		//�ؼ���
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
		//�����
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
	//�ָ���
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
		//����
	case W_INT:	   // ����
	case W_DOUBLE: // ������
		// cout << '(' << code << ',' << atoi(token.c_str()) << ")" << endl;
		// cout << '(' << code << ',' << atof(token.c_str()) << ")" << endl;
		if (alreadyHave)
		{
			//�Ѿ����ڣ���ӡi3
			cout << '(' << code << ',' << "intOrFloat[" << i3 << "]"
				<< ")" << endl;
		}
		else
		{
			//��δ���ڣ���ӡi2-1
			cout << '(' << code << ',' << "intOrFloat[" << (i2 - 1) << "]"
				<< ")" << endl;
		}
		return;
		break;
		//��ʶ��
	case W_IDENT:
		if (alreadyHave)
		{
			//�Ѿ����ڣ���ӡi3
			cout << '(' << code << ',' << "ident[" << i3 << "]"
				<< ")" << endl;
		}
		else
		{
			//�����ڣ���ӡi1-1
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
 * �жϱ�ʶ���Ƿ�����������
 * ���Ѵ��ڣ��㷵�ظ������б�
 * �������ڣ�����41
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
	//�����ڷ���41
	return 41;
}

/**
 * �ж�int����float�Ƿ�����������
 * ���Ѵ��ڣ��㷵�ظ������б�
 * �������ڣ�����41
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
	//�����ڷ���41
	return 41;
}

/**
 * �ж��Ƿ�Ϊ�ؼ���
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
 * ���عؼ���codeֵ����ֵ�±� + 35
 * @param token
 * @return int
 */
int getKeyID(string token)
{
	for (int i = 0; i < MAX; i++)
	{
		//�ؼ��ֵ�����ֵΪkeyWord�����ж�Ӧ���±� + 35
		//�����0��ʼ��ö���е�һ���ؼ��ִ�35��ʼ
		if (token.compare(keyWord[i]) == 0)
			return i + 35;
	}
	return -1;
}

/**
 * �ж�һ���ַ��Ƿ�����ĸ
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
 * �ж�һ���ַ��Ƿ�������
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
 * �ʷ�����
 * @param fp �ļ�ָ��
 * ȫ�ֱ�����ident ��¼��ʶ���Ķ�ά����
 * ȫ�ֱ�����intOrFloat ��¼�����Ķ�ά����
 */
void lexicalAnalysis(FILE* fp)
{
	//�����ļ�����
	ofstream os, os2;
	//����������ʶ�����ļ�����
	os.open("H:/java_identTable.txt");
	//��������泣�����ļ�����
	os2.open("H:/java_intorfloatTable.txt");
	//��¼��ʶ���ļ��б�ʶ����code
	int identCode = 0;
	//��¼��ʶ���ļ��б�ʶ����code
	int intOrFloatCode = 0;
	//�洢���ļ��л�ȡ�ĵ����ַ�
	int ch;
	//��δ��ȡ���ļ�β�����ļ��л�ȡһ���ַ�
	while ((ch = fgetc(fp)) != EOF)
	{
		//����ȡ���ַ�����token��
		token = ch;
		// a.���Կո�Tab�ͻس�
		if (ch == ' ' || ch == '\t' || ch == '\n')
		{
			//�������з�����¼������row��1
			if (ch == '\n')
				row++;
			//����ִ��ѭ��
			continue;
		}
		// b.������ĸ��ͷ���ؼ��ֻ��ʶ��
		else if (isLetter(ch))
		{
			// token��ʼ��
			token = "";
			//����ĸ������ʱ�˳��������ʴ洢��token��
			while (isLetter(ch) || isDigit(ch))
			{
				//����ȡ���ַ�ch����token��
				token.push_back(ch);
				//��ȡ��һ���ַ�
				ch = fgetc(fp);
			}
			//�ļ�ָ�����һ���ֽڣ������¶�ȡ�������ʺ�ĵ�һ���ַ�
			fseek(fp, -1L, SEEK_CUR);
			//�ؼ��֣���ʶ��
			if (isKey(token))
			{
				code = TokenCode(getKeyID(token));
			}
			else
			{
				code = W_IDENT;
				//�ж�ident�������Ƿ����иñ�ʶ��
				if (identAlreadyHave(token) == 41)
				{
					//��ʾû�У�token�����ʶ�������У���i1++
					strcpy(ident[i1], token.c_str());
					i1++;
					//����ʶ������ident�ļ�����ֵcode������
					os << identCode << ' ' << token << endl;
					// identCode + 1
					identCode++;
					//ͬʱ��¼״̬��ȫ�ֱ���ֵfalse
					alreadyHave = false;
				}
				else
				{
					//��ʾ�Ѵ���
					//ȫ�ֱ�����¼�Ѵ��ڵ������б�
					i3 = identAlreadyHave(token);
					alreadyHave = true;
				}
			}
		}
		// c.�޷��ų��������ֿ�ͷ
		else if (isDigit(ch))
		{
			//����Ƿ�Ϊ������
			int isdouble = 0;
			// token��ʼ��
			token = "";
			//��ǰ��ȡ�����ַ�Ϊ����
			while (isDigit(ch))
			{
				//��ȡ���֣��������token��
				token.push_back(ch);
				//���ļ��л�ȡ��һ���ַ�
				ch = fgetc(fp);
				//�õ����е�һ�γ���С����
				if (ch == '.' && isdouble == 0)
				{
					//С������һλ������
					if (isDigit(fgetc(fp)))
					{
						isdouble = 1;			  //��Ǹó������Ѿ����ֹ�С����
						fseek(fp, -1L, SEEK_CUR); //����ǰ��ȡ��С�����һλ���¶�ȡ
						token.push_back(ch);	  //��С������token��
						ch = fgetc(fp);			  //��ȡС��������һλ����
					}
				}
			}
			//������or����
			if (isdouble == 1)
			{
				code = W_DOUBLE;
				//�жϸó����Ƿ��Ѿ�����
				if (intOrFloatAlreadyHave(token) == 41)
				{
					// ��ʾ������
					// token�����ʶ�������У�ͬʱi2++
					strcpy(intOrFloat[i2], token.c_str());
					i2++;
					//ͬʱ�����ļ��л���
					os2 << intOrFloatCode << ' ' << token << endl;
					intOrFloatCode++;
					//ͬʱ��¼״̬��ȫ�ֱ���ֵfalse
					alreadyHave = false;
				}
				else
				{
					//��ʾ�Ѵ���
					//ȫ�ֱ�����¼�Ѵ��ڵ������б�
					i3 = intOrFloatAlreadyHave(token);
					alreadyHave = true;
				}
			}
			else
			{
				code = W_INT;
				//�жϸó����Ƿ��Ѿ�����
				if (intOrFloatAlreadyHave(token) == 41)
				{
					// ��ʾ������
					// token�����ʶ�������У�ͬʱi2++
					strcpy(intOrFloat[i2], token.c_str());
					i2++;
					//ͬʱ�����ļ��л���
					os2 << intOrFloatCode << ' ' << token << endl;
					intOrFloatCode++;
					//ͬʱ��¼״̬��ȫ�ֱ���ֵfalse
					alreadyHave = false;
				}
				else
				{
					//��ʾ�Ѵ���
					//ȫ�ֱ�����¼�Ѵ��ڵ������б�
					i3 = intOrFloatAlreadyHave(token);
					alreadyHave = true;
				}
			}
			//�ļ�ָ�����һ���ֽڣ������¶�ȡ������ĵ�һ���ַ�
			fseek(fp, -1L, SEEK_CUR);
		}
		else
			switch (ch)
			{
				//�����
			case '+':
			{
				ch = fgetc(fp); //��ǰ��ȡ'='������ַ�
				if (ch == '=')	//+=���ں�
				{
					token.push_back(ch); //��'+'�����'='����token��
					code = CW_ADD_EQ;	 //����Ϊ"+="
				}
				else
				{							  //+��ֵ�����
					code = CW_ADD;			  //����Ϊ"+"
					fseek(fp, -1L, SEEK_CUR); //����ǰ��ȡ���ַ����¶�ȡ
				}
			}
			break;
			case '-':
			{
				ch = fgetc(fp); //��ǰ��ȡ'='������ַ�
				if (ch == '=')	//-=���ں�
				{
					token.push_back(ch); //��'-'�����'='����token��
					code = CW_SUB_EQ;	 //����Ϊ"-="
				}
				else
				{							  //-��ֵ�����
					code = CW_SUB;			  //����Ϊ"-"
					fseek(fp, -1L, SEEK_CUR); //����ǰ��ȡ���ַ����¶�ȡ
				}
			}
			break;
			case '*':
			{
				ch = fgetc(fp); //��ǰ��ȡ'='������ַ�
				if (ch == '=')	//*=���ں�
				{
					token.push_back(ch); //��'*'�����'='����token��
					code = CW_MUL_EQ;	 //����Ϊ"*="
				}
				else
				{							  //*��ֵ�����
					code = CW_MUL;			  //����Ϊ"-"
					fseek(fp, -1L, SEEK_CUR); //����ǰ��ȡ���ַ����¶�ȡ
				}
			}
			break;
			case '/':
			{
				ch = fgetc(fp); //��ǰ��ȡ'='������ַ�
				if (ch == '=')	///=���ں�
				{
					token.push_back(ch); //��'/'�����'='����token��
					code = CW_DIV_EQ;	 //����Ϊ"/="
				}
				else
				{							  ///��ֵ�����
					code = CW_DIV;			  //����Ϊ"/"
					fseek(fp, -1L, SEEK_CUR); //����ǰ��ȡ���ַ����¶�ȡ
				}
			}
			break;
			case '=':
			{
				ch = fgetc(fp); //��ǰ��ȡ'='������ַ�
				if (ch == '=')	//==���ں�
				{
					token.push_back(ch); //��'='�����'='����token��
					code = CW_EQ_EQ;	 //����Ϊ"=="
				}
				else
				{							  //=��ֵ�����
					code = CW_EQ;			  //����Ϊ"="
					fseek(fp, -1L, SEEK_CUR); //����ǰ��ȡ���ַ����¶�ȡ
				}
			}
			break;
			case '%':
			{
				ch = fgetc(fp); //��ǰ��ȡ'='������ַ�
				if (ch == '=')	//%=���ں�
				{
					token.push_back(ch); //��'%'�����'='����token��
					code = CW_TTR_EQ;	 //����Ϊ"%="
				}
				else
				{							  //%��ֵ�����
					code = CW_TTR;			  //����Ϊ"%"
					fseek(fp, -1L, SEEK_CUR); //����ǰ��ȡ���ַ����¶�ȡ
				}
			}
			break;
			case '<':
			{
				ch = fgetc(fp); //��ǰ��ȡ'<'������ַ�
				if (ch == '=')	//<=С�ڵ��ں�
				{
					token.push_back(ch); //��'<'�����'='����token��
					code = CW_SM_EQ;	 //����Ϊ"<="
				}
				else
				{							  //<С�ں�
					code = CW_SM;			  //����Ϊ"<"
					fseek(fp, -1L, SEEK_CUR); //����ǰ��ȡ���ַ����¶�ȡ
				}
			}
			break;
			case '>':
			{
				ch = fgetc(fp); //��ǰ��ȡ'>'������ַ�
				if (ch == '=')	//>=���ڵ��ں�
				{
					token.push_back(ch); //��'>'�����'='����token��
					code = CW_BG_EQ;	 //����Ϊ">="
				}
				else
				{							  //>���ں�
					code = CW_BI;			  //����Ϊ">"
					fseek(fp, -1L, SEEK_CUR); //����ǰ��ȡ���ַ����¶�ȡ
				}
			}
			break;
			//�ֽ��
			case '(':
				code = W_LEFT_SMALL; //(��Բ����
				break;
			case ')':
				code = W_RIGHT_SMALL; //)��Բ����
				break;
			case '[':
				code = W_LEFT_MID; //[��������
				break;
			case ']':
				code = W_RIGHT_MID; //]��������
				break;
			case '{':
				code = W_LEFT_BIG; //{�������
				break;
			case '}':
				code = W_RIGHT_BIG; //}�Ҵ�����
				break;
			case ';':
				code = W_FENHAO; //;�ֺ�
				break;
			case ',':
				code = W_DOUHAO; //,����
				break;
			case ':':
				code = W_MAOHAO; //:ð��
				break;
				//δʶ�����
			default:
				code = W_UNDEFINED;
			}
		//��ӡ�ʷ��������
		print(code);
	}
	//�ر��ļ�
	os.close();
	os2.close();
}

int main()
{
	string filename; //�ļ�·��
	FILE* fp;		 //�ļ�ָ��
	// cout << "������Դ�ļ�����" << endl;
	while (true)
	{
		//��ȡ�ļ�·��
		// cin >> filename;
		filename = "F:/����ԭ��/lexical analyzer/src/test.txt";
		//���ļ�
		if ((fopen_s(&fp, filename.c_str(), "r")) == 0)
			break;
		else
			cout << "·���������" << endl; //��ȡʧ��
	}
	cout << "/===============================�ʷ��������==============================/" << endl;
	//�ʷ�����
	lexicalAnalysis(fp);
	//�ر��ļ�
	fclose(fp);

	return 0;
}