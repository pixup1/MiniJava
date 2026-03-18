#include <stdio.h>
#include <stdlib.h>
#include "tgc.h"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
struct array { int* array; int length; };
tgc_t gc;
struct ContinueTest;
void* ContinueTest_test(struct ContinueTest* this, int n);
struct ContinueTest {
  void* (**vtable)();
};
void* (*ContinueTest_vtable[])() = { ContinueTest_test };
void* ContinueTest_test(struct ContinueTest* this, int n) {
  int i;
  i = 0;
  while ((i < n)) {
    i = (i + 1);
    if ((i == 5)) {
      continue;
    }
    else {
      
    }
  }
  return (void*)(i);
}
int main(int argc, char *argv[]) {
  tgc_start(&gc, &argc);
  {
    printf("%d\n", ({ struct ContinueTest* tmp1 = ({ struct ContinueTest* res = tgc_calloc(({ extern tgc_t gc; &gc; }), 1, sizeof(*res)); res->vtable = ContinueTest_vtable; res; }); (int) tmp1->vtable[0](tmp1, 10); }));
  }
  tgc_stop(&gc);

  return 0;
}
