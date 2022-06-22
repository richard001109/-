#include<string.h>
#include<stdio.h>

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
//51+2个保留字=53个关键字
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
    "this",         // 41
    "throw",        // 42
    "throws",       // 43
    "transient",    // 44
    "try",          // 45
    "void",         // 46
    "volatile",     // 47
    "while",        // 48
    "goto",         // 49
    "const",        // 50
    "true",         // 51
    "false",        // 52
    "null",        // 53
}

int
main()
{
}
