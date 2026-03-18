#include <stdio.h>
#include <stdlib.h>
#include "tgc.h"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
struct array { int* array; int length; };
tgc_t gc;
struct BreakTest;
void* BreakTest_test(struct BreakTest* this, int n);
struct BreakTest {
  void* (**vtable)();
};
void* (*BreakTest_vtable[])() = { BreakTest_test };
void* BreakTest_test(struct BreakTest* this, int n) {
  int i;
  i = 0;
  while ((i < n)) {
    if ((i == 5)) {
      break;
    }
    else {
      
    }
    i = (i + 1);
  }
  return (void*)(i);
}
int main(int argc, char *argv[]) {
  tgc_start(&gc, &argc);
  {
    printf("%d\n", ({ struct BreakTest* tmp1 = ({ struct BreakTest* res = tgc_calloc(({ extern tgc_t gc; &gc; }), 1, sizeof(*res)); res->vtable = BreakTest_vtable; res; }); (int) tmp1->vtable[0](tmp1, 10); }));
  }
  tgc_stop(&gc);

  return 0;
}
