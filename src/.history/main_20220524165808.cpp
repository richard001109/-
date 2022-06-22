#include<iostream>
#include<fstream>
using namespace std;

int main()
{
  ifstream infile;
  infile.open("01.txt", ios::in);
  if (!infile.is_open())
  {
    cout << "读取文件失败" << endl;
    return 0;
  }
  //第二种读取方法
  char buf[1024];
  while (infile.getline(buf, sizeof(buf)))
  {
    cout << buf << endl;
  }
}
