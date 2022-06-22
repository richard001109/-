
//char str[MAX][10] = { "int","char","byte","float","boolean","main","double","case", "for","if","else","continue","do","while","void","return","break","try","catch","switch","public","class","static","string" };
/*附录源程序清单：*/

#include<string.h>
#include<stdio.h>
#define   MAX 25            /*分析}表的最大容量*/
#define   RES_MAX   10        /*关键字的最大长度*/
#define   MAXBUF 255         /*缓冲区的大小*/
#define   MAX_IDENTIFIER 255         /*缓冲区的大小*/

char   ch = ' ';             /*存放读入当前的输入字符*/
int identNum=0;         /*标识符表当前长度*/
int Line_NO;                /*纪录行号*/

int fout1 = 1;
int fout2 = 1;

struct keywords    /*关键字*/
{
	char lexptr[MAXBUF];
	int token;
};
struct keywords symtable[MAX];
char str[MAX][10] = { "int","char","byte","float","boolean","main","double","case", "for","if","else","continue","do","while","void","return","break","try","catch","switch","public","class","static","string","package"};

char identifiers[MAX_IDENTIFIER][20];           /*标识符表*/

/*对关键字表进行初始化，div,mod,and,or也作为关键字处理*/
/*最小的token是program：3，最大的token是or：26*/
void init()
{
	int j;
	for (j = 0; j < MAX; j++)
	{
		strcpy(symtable[j].lexptr, str[j]);
		symtable[j].token = j + 3;
	}
}

/***************对关键字进行搜索**************/
int Iskeyword(char* is_res) {
	int i;
	for (i = 0; i < MAX; i++) {
		if ((strcmp(symtable[i].lexptr, is_res)) == 0) break;
	}
	if (i < MAX) return   symtable[i].token;
	else return 0;
}

/***************对标识符进行搜索**************/
int Isidentifier(char* is_res) {
	int i;
	for (i = 0; i < MAX; i++) {
		if ((strcmp(identifiers[i], is_res)) == 0)
			return  i;
	}
	return 0;
}

/*****************判断是否为字母*****************/
int IsLetter(char c)
{
	if (((c <= 'z') && (c >= 'a')) || ((c <= 'Z') && (c >= 'A'))) return 1;
	else return 0;
}

/*************判断是否为数字**************/
int IsDigit(char c) {
	if (c >= '0' && c <= '9') return 1;
	else return 0;
}

/***************分析程序**************/
void analyse(FILE* fpin, FILE* fpout, FILE* fpout1, FILE* fpout2) {
	/* 输入缓冲区，存放一个单词符号 */
	char arr[MAXBUF];
	int j = 0;
	while ((ch = fgetc(fpin)) != EOF) {
		/*碰到空格、tab则跳过*/
		if (ch == ' ' || ch == '\t') {}
		else if (ch == '\n') { Line_NO++; }
		/*********************字符串的处理*************************/
		else if (IsLetter(ch)) {
			while (IsLetter(ch) | IsDigit(ch) | ch == '_') {
				if ((ch <= 'Z') && (ch >= 'A'))
					ch = ch + 32;   /*忽略大小写*/
				arr[j] = ch;
				j++;
				ch = fgetc(fpin);
			}
			/*输入指针回退一个字符*/
			fseek(fpin, -1L, SEEK_CUR);
			arr[j] = '\0';
			j = 0;
			
			if (Iskeyword(arr)) {   /*如果是关键字*/
				fprintf(fpout, "<%s,%d,关键字>\n", arr, Iskeyword(arr));
			}
			else if (Isidentifier(arr) == 0) {
				
				fprintf(fpout, "<%s,%d,identifiers[%d]>\n", arr, 1, identNum); /*普通标识符*/
				fprintf(fpout2, "<%s,%d,标识符>\n", arr, 1); /*普通标识符*/
				for (int j = 0; j < sizeof(arr); j++) {
					identifiers[identNum][j] = arr[j];
				}
				identNum++;
			}
			else {
				int index = Isidentifier(arr);
				fprintf(fpout, "<%s,%d,identifiers[%d]>\n", arr, 1, index); /*普通标识符*/
			}
		}
		/*************************数字的处理****************************/
		else if (IsDigit(ch)) {
			int s = 0;
			while (IsDigit(ch) | IsLetter(ch)) {
				if (IsLetter(ch)) {
					arr[j] = ch;
					j++;
					ch = fgetc(fpin);
					s = 1;
				}
				else if (IsDigit(ch)) {
					arr[j] = ch;
					j++;
					ch = fgetc(fpin);
				}
			}
			fseek(fpin, -1L, SEEK_CUR);
			arr[j] = '\0';
			j = 0;
			if (s == 0)
			{
				fprintf(fpout, "<%s，%d，无符号整数>\n", arr, 2);
				fprintf(fpout1, "<%s，%d，无符号整数>\n", arr, 2);//常数
			}
			else if (s == 1)
				fprintf(fpout, "<%s，%d，错误>\n", arr, 3);
		}
		else switch (ch) {
		case'(':fprintf(fpout, "<%s，%d，分界符>\n", "(", 27); break;
		case')':fprintf(fpout, "<%s，%d，分界符>\n", ")", 28); break;
		case'[':fprintf(fpout, "<%s，%d，分界符>\n", "[", 29); break;
		case']':fprintf(fpout, "<%s，%d，分界符>\n", "]", 30); break;
		case';':fprintf(fpout, "<%s，%d，分界符>\n", ";", 31); break;
		case'.':fprintf(fpout, "<%s，%d，分界符>\n", ".", 32); break;
		case',':fprintf(fpout, "<%s，%d，分界符>\n", ",", 33); break;
		case':':fprintf(fpout, "<%s，%d，分界符>\n", ":", 34); break;
		case'{':fprintf(fpout, "<%s，%d，分界符>\n", "{", 35); break;
		case'}':fprintf(fpout, "<%s，%d，分界符>\n", "}", 36); break;
		case'%':fprintf(fpout, "<%s，%d，分界符>\n", "%", 37); break;
		case'\"':fprintf(fpout, "<%s，%d，分界符>\n", "\"", 38); break;
		case'\\':fprintf(fpout, "<%s，%d，分界符>\n", "\\", 39); break;
		case'#':fprintf(fpout, "<%s，%d，分界符>\n", "#", 40); break;

		case'+':
			ch = fgetc(fpin);
			if (ch == '+') {
				fprintf(fpout, "<%s，%d，自加运算符>\n", "++", 43);
				break;
			}
			else if (ch == '=') {
				fprintf(fpout, "<%s，%d，运算符>\n", "+=", 44);
				break;
			}
			else
				fseek(fpin, -1L, SEEK_CUR);
			fprintf(fpout, "<%s，%d，运算符>\n", "+", 45);
			break;
		case'-':
			ch = fgetc(fpin);
			if (ch == '-') {
				fprintf(fpout, "<%s，%d，自减运算符>\n", "--", 46);
				break;
			}
			else if (ch == '=') {
				fprintf(fpout, "<%s，%d，运算符>\n", "-=", 47);
				break;
			}
			else
				fseek(fpin, -1L, SEEK_CUR);
			fprintf(fpout, "<%s，%d，运算符>\n", "-", 48);
			break;
		case'*':fprintf(fpout, "<%s，%d，运算符>\n", "*", 49); break;

		case'=':fprintf(fpout, "<%s，%d，运算符>\n", "=", 50); break;



		case'>': {
			ch = fgetc(fpin);
			if (ch == '=')
				fprintf(fpout, "<%s，%d，运算符>\n", ">=", 51);
			else {
				fprintf(fpout, "<%s，%d，运算符>\n", ">", 52);
				fseek(fpin, -1L, SEEK_CUR);
			}
		}break;

		case'<': {
			ch = fgetc(fpin);
			if (ch == '=')
				fprintf(fpout, "<%s，%d，运算符>\n", "<=", 53);
			else if (ch == '>')
				fprintf(fpout, "<%s，%d，运算符>\n", "<>", 54);
			else {
				fprintf(fpout, "<%s，%d，运算符>\n", "<", 55);
				fseek(fpin, -1L, SEEK_CUR);
			}
		}break;
			/***************出现在/  /之间的全部作为注释部分处理*******************/
		case'/': {
			ch = fgetc(fpin);
			if (ch == '/') {
				while (ch != '\n') {
					ch = fgetc(fpin);
				}
			}
			else if (ch == '*') {
				while (ch != '/' && ch != EOF) {
					ch = fgetc(fpin);
				}
				if (ch == EOF)
					fprintf(fpout, "缺少一个'/'");
			}
			else {
				fprintf(fpout, "<%s，%d，运算符>\n", "/", 41);
				fseek(fpin, -1L, SEEK_CUR);
			}
			break;
		}
			   /***************非法字符*******************/
		default:fprintf(fpout, "<在第%d行无法识别的字符\t%c>\n", Line_NO, ch);
		}
	}

}
/**********主程序中完成对输入输出文件的读写***********/
int main() {
	char in_fn[25] = "test.txt";
	char out_fn[25] = "F:\\b.txt";
	char out_fn1[25] = "F:\\c.txt";
	char out_fn2[25] = "F:\\d.txt";
	FILE* fpin, * fpout, * fpout1, * fpout2;
	fpin = fopen(in_fn, "r");
	fpout = fopen(out_fn, "w");
	fpout1 = fopen(out_fn1, "w");
	fpout2 = fopen(out_fn2, "w");
	fprintf(fpout, "单词符，种类编码，种类\n");
	init();
	analyse(fpin, fpout,fpout1,fpout2);
	fclose(fpin);
	fclose(fpout);
	return 0;
}

