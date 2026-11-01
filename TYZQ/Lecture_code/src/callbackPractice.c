#include <stdio.h>

// 在这里定义 add、subtract 和 multiply
int add(int a, int b) { return (a + b); }

int subtract(int a, int b) { return (a - b); }

int multiply(int a, int b) { return (a * b); }
// 在这里定义 executeOperation

void executeOperation(int (*operation)(int, int), int x, int y) {
  printf("Result: %d\n", operation(x, y));
}

int main(void) {

  int x = 10, y = 5;

  // 依次使用三个不同的回调函数
  executeOperation(add, x, y);
  executeOperation(subtract, x, y);
  executeOperation(multiply, x, y);

  return 0;
}
