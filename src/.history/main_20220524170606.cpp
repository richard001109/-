#include<iostream>
#include<fstream>
using namespace std;

int main()
{
  ifstream infile;
  infile.open("qqzl.txt", ios::in);
  if (!infile.is_open()){
  
    cout << "读取文件失败" << endl;
    return 0;
  }
  //第四种读取方法
  char c;
  while ((c = infile.get()) != EOF)
  {
    cout << c;
  }
  return 0;
}
