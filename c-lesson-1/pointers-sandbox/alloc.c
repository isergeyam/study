#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main()
{
  int num = 100;
  int *fstBuff = calloc(num, sizeof(int)); // allocated array on the heap
  int sndBuff[100];                        // allocated array on the stack,
                                           // the type of the sndBuff is int[100], not int*
  printf("Size of heap-allocated and stack-allocated variables: %lu, %lu\n",
         sizeof(fstBuff), sizeof(sndBuff));
  printf("Pointers to the first entry of the array: %p, %p\n",
         (void *)fstBuff, (void *)sndBuff);
  memset(fstBuff, 0, sizeof(sndBuff));
  memset(sndBuff, 0, sizeof(sndBuff));
  for (int i = 0; i < num; ++i)
  {
    assert(fstBuff[i] == 0 && sndBuff[i] == 0);
  }
  return 0;
}
