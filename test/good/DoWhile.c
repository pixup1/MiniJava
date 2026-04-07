#include <stdio.h>
#include <stdlib.h>
#include "tgc.h"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
struct array { int* array; int length; };
tgc_t gc;
struct DoWhileTest;
void* DoWhileTest_test(struct DoWhileTest* this);
struct DoWhileTest {
  void* (**vtable)();
};
void* (*DoWhileTest_vtable[])() = { DoWhileTest_test };
void* DoWhileTest_test(struct DoWhileTest* this) {
  int i;
  i = 0;
  do {
    printf("%d\n", i);
    i = (i + 1);
  } while ((i < 5));
  return (void*)(i);
}
int main(int argc, char *argv[]) {
  tgc_start(&gc, &argc);
  {
    printf("%d\n", ({ struct DoWhileTest* tmp1 = ({ struct DoWhileTest* res = tgc_calloc(({ extern tgc_t gc; &gc; }), 1, sizeof(*res)); res->vtable = DoWhileTest_vtable; res; }); (int) tmp1->vtable[0](tmp1); }));
  }
  tgc_stop(&gc);

  return 0;
}
