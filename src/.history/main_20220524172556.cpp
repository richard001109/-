#include<iostream>
#include<fstream>
using namespace std;

#define MAX 22 
char buf[1024];//缓冲区大小


int main()
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
