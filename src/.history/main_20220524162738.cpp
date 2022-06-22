#include<iostream>
#include<
using namespace std;

void show()
{
  int i;
  char ch;
  printf("分析程序：\n");
  rewind(in);
  while (!feof(in))
  {
    printf("%c", getc(in));
  }
  printf("\n 二元式 :\n");
  rewind(out);
  while (!feof(out))
  {
    printf("%c", getc(out));
  }
  printf("\n 标志符表 \n");
  for (i = 0; i < NUM; i++)
  {
    if (Word[i][0] != NULL)
      printf("%d,%s\n", i, Word[i]);
  }
  printf("\n 常数表 \n");
  for (i = 0; i < NUM; i++)
  {
    if (consts[i][0] != NULL)
      printf("%d,%s\n", i, consts[i]);
  }
}

int main(){

}

