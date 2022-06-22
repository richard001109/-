#include<iostream>
#include<fstream>
using namespace std;
char buf[1024];//缓冲区大小
int main（）
{
  ifstream infile;
  infile.open("qqzl.txt", ios::in);
  if (!infile.is_open())
  
    cout << "读取文件失败" << endl;
    return;
  }
  //第四种读取方法
  char c;
  while ((c = infile.get()) != EOF)
  {
    cout << c;
  }
}
