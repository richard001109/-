#include<iostream>
#include<fstream>
using namespace std;

#define MAX 22            /*关键字表的最大容量*/
#define RES_MAX 10        /*关键字的最大长度*/
#define MAXBUF[1024];     /*缓冲区大小*/

char ch = ' ';            /*存放读入当前的输入字符*/
int Line_NO;              /*标记行号*/

struct keywords           /*关键字*/
{
  char lexptr[MAXBUF];
  int token;
};

struct keywords symtable[MAX];
char str[MAX][10] = {
    "abstract",   //0
    "assert",     //1
    "boolean",    //2
    "break",      //3
    "byte",       //4
    "case",
    "catch",
    "char",
    "class"
}

int
main()
{
  //逐字符读取文件
  ifstream infile;
  infile.open("test.txt", ios::in);
  if (!infile.is_open()){
  
    cout << "读取文件失败" << endl;
    return 0;
  }

  char c;
  while ((c = infile.get()) != EOF)
  {
    cout << c;
  }
  return 0;
}
