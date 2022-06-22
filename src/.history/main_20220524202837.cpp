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
    "native",       // 28
    "new",          // 29
    "package",      // 30
    "private",      // 31
    "protected",    // 32
    "public",       // 33
    "return",       // 34
    "short",        // 35
    "static",       // 36
    "strictfp",     // 37
    "super",        // 38
    "switch",       // 39
    "synchronized", // 40
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
