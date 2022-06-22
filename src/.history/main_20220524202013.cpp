#include<iostream>
#include<fstream>
using namespace std;

#define MAX 53            /*关键字表的最大容量*/
#define RES_MAX 10        /*关键字的最大长度*/
#define MAXBUF[1024];     /*缓冲区大小*/

char ch = ' ';            /*存放读入当前的输入字符*/
int Line_NO;              /*标记行号*/

struct keywords           /*关键字*/
{
  char lexptr[MAXBUF];
  int token;
};
//此处将
struct keywords symtable[MAX];
char str[MAX][20] = {
    "abstract",   // 0
    "assert",     // 1
    "boolean",    // 2
    "break",      // 3
    "byte",       // 4
    "case",       // 5
    "catch",      // 6
    "char",       // 7
    "class",      // 8
    "continue",   // 9
    "default",    // 10
    "do",         // 11
    "double",     // 12
    "else",       // 13
    "enum",       // 14
    "extends",    // 15
    "final",      // 16
    "finally",    // 17
    "float",      // 18
    "for",        // 19
    "if",         // 20
    "implements", // 21
    "import",     // 22
    "int",        // 23
    "interface",  // 24
    "instanceof", // 25
    "long",       // 27
    "native",     // 28
    "new",        // 29
    "package",    // 30
    "",           // 31
    "",           // 32
    "",           // 33
    "",           // 34
    "",           // 35
    "",           // 36
    "",           // 37
    "",           // 38
    "",           // 39
    "",           // 40
    "",           // 41
    "",           // 42
    "",           // 43
    "",           // 44
    "",           // 45
    "",           // 46
    "",           // 47
    "",           // 48
    "",           // 49
    "",           // 50
    "",           // 51

}

int
main()
{
}
