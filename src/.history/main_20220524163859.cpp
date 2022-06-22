#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#define MAX 10000
char ch;
char token[MAX][100];
int ptoken = 0; //指针
const char *pkeyword[] = {"if", "else", "begin", "void", "int", "char", "main", "scanf", "printf", "while", "for",
                          "return", "end", "switch", "case"};

int isletter()
{
  if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
    return 1;
  else
  {
    return 0;
  }
}

int isdigit()
{
  if (ch >= '0' && ch <= '9')
    return 1;
  else
    return 0;
}

int iskeyword()
{
  for (int i = 0; i < 15; i++)
  {
    if (strcmp(token[ptoken], pkeyword[i]) == 0)
      return i;
  }
  return 15;
}

void scanning(ifstream *file)
{
  ofstream out_file("C://Users//23649//Desktop//Code//VSCode//file//out.txt");
  out_file << setw(20) << setiosflags(ios::left) << "单词值"
           << "种别编码" << endl;
  file->get(ch); // ifstream &get(char &ch);功能是从流中读取一个字符，结果保存在ch
  while (1)
  {
    if (isletter())
    {
      int i = 0;
      token[ptoken][i] = ch; //判断关键词
      file->get(ch);
      while (isletter())
      {
        i++;
        token[ptoken][i] = ch;
        file->get(ch);
      }
      int check = iskeyword();
      if (check < 15)
        out_file << setw(20) << setiosflags(ios::left) << pkeyword[check] << check + 1 << endl;
      else
      {
        out_file << setw(20) << setiosflags(ios::left) << token[ptoken] << "30" << endl;
      }
      ptoken++;
    }
    else if (isdigit())
    {
      int i = 0;
      token[ptoken][i] = ch;
      while (file->get(ch) && isdigit())
      {
        i++;
        token[ptoken][i] = ch;
      }
      int flag = 0;
      while (ch != ' ' && ch != '\n' && ch != ';' && ch != '=' && ch != '\'')
      {
        i++;
        token[ptoken][i] = ch;
        file->get(ch);
        flag = 1;
      }
      if (flag == 0)
        out_file << setw(20) << setiosflags(ios::left) << token[ptoken] << "31" << endl;
      else
      {
        out_file << setw(20) << setiosflags(ios::left) << token[ptoken] << "非法字符" << endl;
      }
      ptoken++;
    }
    else if (ch == ' ' || ch == '\n')
      file->get(ch);
    else if (ch == '#')
      break;
    else
    {
      switch (ch)
      {
      case '+':
        token[ptoken][0] = ch;
        out_file << setw(20) << setiosflags(ios::left) << token[ptoken]
                 << "16" << endl;
        ptoken++;
        file->get(ch);
        break;
      case '-':
        token[ptoken][0] = ch;
        out_file << setw(20) << setiosflags(ios::left) << token[ptoken]
                 << "17" << endl;
        ptoken++;
        file->get(ch);
        break;
      case '*':
        token[ptoken][0] = ch;
        out_file << setw(20) << setiosflags(ios::left) << token[ptoken]
                 << "18" << endl;
        ptoken++;
        file->get(ch);
        break;
      case '=':
        token[ptoken][0] = ch;
        out_file << setw(20) << setiosflags(ios::left) << token[ptoken]
                 << "19" << endl;
        ptoken++;
        file->get(ch);
        break;
      case '(':
        token[ptoken][0] = ch;
        out_file << setw(20) << setiosflags(ios::left) << token[ptoken]
                 << "20" << endl;
        ptoken++;
        file->get(ch);
        break;
      case ')':
        token[ptoken][0] = ch;
        out_file << setw(20) << setiosflags(ios::left) << token[ptoken]
                 << "21" << endl;
        ptoken++;
        file->get(ch);
        break;
      case '{':
        token[ptoken][0] = ch;
        out_file << setw(20) << setiosflags(ios::left) << token[ptoken]
                 << "22" << endl;
        ptoken++;
        file->get(ch);
        break;
      case '}':
        token[ptoken][0] = ch;
        out_file << setw(20) << setiosflags(ios::left) << token[ptoken]
                 << "23" << endl;
        ptoken++;
        file->get(ch);
        break;
      case ';':
        token[ptoken][0] = ch;
        out_file << setw(20) << setiosflags(ios::left) << token[ptoken]
                 << "24" << endl;
        ptoken++;
        file->get(ch);
        break;
      case '<':
        token[ptoken][0] = ch;
        file->get(ch);
        if (ch == '=')
        {
          token[ptoken][1] = ch;
          out_file << setw(20) << setiosflags(ios::left) << token[ptoken]
                   << "27" << endl;
          file->get(ch);
        }
        else
          out_file << setw(20) << setiosflags(ios::left) << token[ptoken]
                   << "25" << endl;
        ptoken++;
        break;
      case '>':
        token[ptoken][0] = ch;
        file->get(ch);
        if (ch == '=')
        {
          token[ptoken][1] = ch;
          out_file << setw(20) << setiosflags(ios::left) << token[ptoken]
                   << "28" << endl;
          file->get(ch);
        }
        else
          out_file << setw(20) << setiosflags(ios::left) << token[ptoken]
                   << "26" << endl;
        ptoken++;
        break;
      case '"':
        token[ptoken][0] = ch;
        out_file << setw(20) << setiosflags(ios::left) << token[ptoken]
                 << "29" << endl;
        ptoken++;
        file->get(ch);
        break;
      case '\\':
        token[ptoken][0] = ch;
        file->get(ch);
        if (ch == 'n')
        {
          token[ptoken][1] = ch;
          out_file << setw(20) << setiosflags(ios::left) << token[ptoken]
                   << "33" << endl;
          file->get(ch);
        }
        else
          out_file << setw(20) << setiosflags(ios::left) << token[ptoken]
                   << "32" << endl;
        ptoken++;
        break;
      default:
        out_file << "无法识别:"
                 << "\t" << ch << endl;
        file->get(ch);
        break;
      }
    }
  }
}
int main()
{
  ifstream in_file(".//in.txt");   //输入文件，把你的文件地址加进去
  ofstream out_file("..//out.txt"); //输出文件，同上
  if (!in_file)
  {
    out_file << "file does not exist!" << endl;
    return 0;
  }
  scanning(&in_file);
  cout << "lexical analysis done!" << endl;
  in_file.close();
  out_file.close();
  system("pause");
  return 0;
}
