#include <stdio.h>

int main()
{
  int a; // allocated on the stack
  a = 5;
  int *b = &a; // created pointer to `a` (also allocated on the stack)
  printf("pointer address value: %p\n", (void *)b);
  printf("pointer dereference value, variable value: %d, %d\n", *b, a);
  *b = 0; // updated underlying value (a also updated)
  printf("pointer dereference value, variable value: %d, %d\n", *b, a);
  b = 0;  // beware, there is no address 0x0, dereferencing would cause SEGFAULT!
  a = *b; // whoops
  return 0;
}