#include<iostream>
#include<fstream>
using namespace std;
//char buf[1024];//缓冲区大小
int main()
{
  ifstream infile;
  infile.open("qqzl.txt", ios::in);
  if (!infile.is_open())
  {
    cout << "文件不存在，读取文件失败" << endl;
    return 0;
  }
  while (infile.getline(buf, sizeof(buf)))
  {
    cout << buf << endl;
  }
}
