

/*附录源程序清单：*/
#include<iostream>
#include <string.h>
#include <stdio.h>
#define MAX 53     /*分析}表的最大容量*/
#define RES_MAX 10 /*关键字的最大长度*/
#define MAXBUF 255 /*缓冲区的大小*/

char ch = ' '; /*存放读入当前的输入字符*/
int Line_NO;   /*纪录行号*/
//char identifierArr[200][20];

struct keywords /*关键字*/
{
  char lexptr[MAXBUF];
  int token;
};
struct keywords symtable[MAX];
char str[MAX][20] = {
    "abstract",     // 3
    "assert",       // 4
    "boolean",      // 5
    "break",        // 6
    "byte",         // 7
    "case",         // 8
    "catch",        // 9
    "char",         // 10
    "class",        // 11
    "continue",     // 12
    "default",      // 13
    "do",           // 14
    "double",       // 15
    "else",         // 16
    "enum",         // 17
    "extends",      // 18
    "final",        // 19
    "finally",      // 20
    "float",        // 21
    "for",          // 22
    "if",           // 23
    "implements",   // 24
    "import",       // 25
    "int",          // 26
    "interface",    // 27
    "instanceof",   // 28
    "long",         // 29
    "native",       // 30
    "new",          // 31
    "package",      // 32
    "private",      // 33
    "protected",    // 34
    "public",       // 35
    "return",       // 36
    "short",        // 37
    "static",       // 38
    "strictfp",     // 39
    "super",        // 40
    "switch",       // 41
    "synchronized", // 42
    "this",         // 43
    "throw",        // 44
    "throws",       // 45
    "transient",    // 46
    "try",          // 47
    "void",         // 48
    "volatile",     // 49
    "while",        // 50
    "goto",         // 51
    "const",        // 52
    "true",         // 53
    "false",        // 54
    "null",         // 55
};


/*对关键字表进行初始化，div,mod,and,or也作为关键字处理*/
/*最小的token是program：3，最大的token是or：24*/
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
int Iskeyword(char *is_res)
{
  int i;
  for (i = 0; i < MAX; i++)
  {
    if ((strcmp(symtable[i].lexptr, is_res)) == 0)
      break;
  }
  if (i < MAX)
    return symtable[i].token;
  else
    return 0;
}

/*****************判断是否为字母*****************/
int IsLetter(char c)
{
  if (((c <= 'z') && (c >= 'a')) || ((c <= 'Z') && (c >= 'A')))
    return 1;
  else
    return 0;
}

/*************判断是否为数字**************/
int IsDigit(char c)
{
  if (c >= '0' && c <= '9')
    return 1;
  else
    return 0;
}

/***************分析程序**************/
void analyse(FILE *fpin, FILE *fpout)
{
  /* 输入缓冲区，存放一个单词符号 */
  char arr[MAXBUF];
  int j = 0;
  while ((ch = fgetc(fpin)) != EOF)
  {
    /*碰到空格、tab则跳过*/
    if (ch == ' ' || ch == '\t')
    {
    }
    else if (ch == '\n')
    {
      Line_NO++;
    }
    /*********************字符串的处理*************************/
    else if (IsLetter(ch))
    {
      while (IsLetter(ch) | IsDigit(ch) | ch == '_')
      {
        if ((ch <= 'Z') && (ch >= 'A'))
          ch = ch + 32; /*忽略大小写*/
        arr[j] = ch;
        j++;
        ch = fgetc(fpin);
      }
      /*输入指针回退一个字符*/
      fseek(fpin, -1L, SEEK_CUR);
      arr[j] = '\0';
      j = 0;
      if (Iskeyword(arr))
      { /*如果是关键字*/
        fprintf(fpout, "%s\t\t%d\t\t关键字\n", arr, Iskeyword(arr));
      }

                                                        /*************************数字的处理****************************/
    }
    else if (IsDigit(ch))
    {
      int s = 0;
      while (IsDigit(ch) | IsLetter(ch))
      {
        if (IsLetter(ch))
        {
          arr[j] = ch;
          j++;
          ch = fgetc(fpin);
          s = 1;
        }
        else if (IsDigit(ch))
        {
          arr[j] = ch;
          j++;
          ch = fgetc(fpin);
        }
      }
      fseek(fpin, -1L, SEEK_CUR);
      arr[j] = '\0';
      j = 0;
      if (s == 0)
        fprintf(fpout, "%s\t\t%d\t\t无符号整数\n", arr, 2);
        std::cout<<
      else if (s == 1)
        fprintf(fpout, "%s\t\t%d\t\t错误\n", arr, 3);
    }
    else
      switch (ch)
      {
      case '+':
        ch = fgetc(fpin);
        if (ch == '+')
        {
          std::cout<<"<"<<72<<" , "<<"++"<<">"<<std::endl;
          break;
        }
        else if (ch == '=')
        {
          fprintf(fpout, "%s\t\t%d\t\t运算符\n", "+=", 73);
          break;
        }
        else
          fseek(fpin, -1L, SEEK_CUR);
        fprintf(fpout, "%s\t\t%d\t\t运算符\n", "+", 74);
        break;
      case '-':
        ch = fgetc(fpin);
        if (ch == '-')
        {
          fprintf(fpout, "%s\t\t%d\t\t自减运算符\n", "--", 75);
          break;
        }
        else if (ch == '=')
        {
          fprintf(fpout, "%s\t\t%d\t\t运算符\n", "-=", 76);
          break;
        }
        else
          fseek(fpin, -1L, SEEK_CUR);
        fprintf(fpout, "%s\t\t%d\t\t运算符\n", "-", 77);
        break;
      case '*':
        fprintf(fpout, "%s\t\t%d\t\t运算符\n", "*", 78);
        break;
      case '(':
        fprintf(fpout, "%s\t\t%d\t\t分界符\n", "(", 56);
        break;
      case ')':
        fprintf(fpout, "%s\t\t%d\t\t分界符\n", ")", 57);
        break;
      case '[':
        fprintf(fpout, "%s\t\t%d\t\t分界符\n", "[", 58);
        break;
      case ']':
        fprintf(fpout, "%s\t\t%d\t\t分界符\n", "]", 59);
        break;
      case ';':
        fprintf(fpout, "%s\t\t%d\t\t分界符\n", ";", 60);
        break;
      case '=':
        fprintf(fpout, "%s\t\t%d\t\t运算符\n", "=", 79);
        break;
      case '.':
        fprintf(fpout, "%s\t\t%d\t\t分界符\n", ".", 61);
        break;
      case ',':
        fprintf(fpout, "%s\t\t%d\t\t分界符\n", ",", 62);
        break;
      case ':':
        fprintf(fpout, "%s\t\t%d\t\t分界符\n", ":", 63);
        break;
      case '{':
        fprintf(fpout, "%s\t\t%d\t\t分界符\n", "{", 64);
        break;
      case '}':
        fprintf(fpout, "%s\t\t%d\t\t分界符\n", "}", 65);
        break;
      case '%':
        fprintf(fpout, "%s\t\t%d\t\t分界符\n", "%", 66);
        break;
      case '\"':
        fprintf(fpout, "%s\t\t%d\t\t分界符\n", "\"", 67);
        break;
      case '\\':
        fprintf(fpout, "%s\t\t%d\t\t分界符\n", "\\", 68);
        break;
      case '#':
        fprintf(fpout, "%s\t\t%d\t\t分界符\n", "#", 69);
        break;
      case '>':
      {
        ch = fgetc(fpin);
        if (ch == '=')
          fprintf(fpout, "%s\t\t%d\t\t运算符\n", ">=", 80);
        else
        {
          fprintf(fpout, "%s\t\t%d\t\t运算符\n", ">", 81);
          fseek(fpin, -1L, SEEK_CUR);
        }
      }
      break;

      case '<':
      {
        ch = fgetc(fpin);
        if (ch == '=')
          fprintf(fpout, "%s\t\t%d\t\t运算符\n", "<=", 82);
        else if (ch == '>')
          fprintf(fpout, "%s\t\t%d\n", "<>", 52);
        else
        {
          fprintf(fpout, "%s\t\t%d\t\t运算符\n", "<", 84);
          fseek(fpin, -1L, SEEK_CUR);
        }
      }
      break;
        /***************出现在/  /之间的全部作为注释部分处理*******************/
      case '/':
      {
        ch = fgetc(fpin);
        if (ch == '/')
        {
          while (ch != '\n')
          {
            ch = fgetc(fpin);
          }
        }
        else if (ch == '*')
        {
          while (ch != '/' && ch != EOF)
          {
            ch = fgetc(fpin);
          }
          if (ch == EOF)
            fprintf(fpout, "缺少一个'/'");
        }
        else
        {
          fprintf(fpout, "%s\t\t%d\t\t运算符\n", "/", 70);
          fseek(fpin, -1L, SEEK_CUR);
        }
        break;
      }
        /***************非法字符*******************/
      default:
        fprintf(fpout, "在第%d行无法识别的字符\t%c\n", Line_NO, ch);
      }
  }
}
/**********主程序中完成对输入输出文件的读写***********/
int main()
{
  char in_fn[25] = "test1.txt";
  char out_fn[25] = "b.txt";
  FILE *fpin, *fpout;
  fpin = fopen(in_fn, "r");
  fpout = fopen(out_fn, "w");
  fprintf(fpout, "单词符\t\t种类编码\t\t种类\n");
  init();
  analyse(fpin, fpout);
  fclose(fpin);
  fclose(fpout);
  return 0;
}
