#include <stdio.h>
#include <stdlib.h>
#include "tgc.h"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
struct array { int* array; int length; };
tgc_t gc;
struct WhileTest;
void* WhileTest_test(struct WhileTest* this);
struct WhileTest {
  void* (**vtable)();
};
void* (*WhileTest_vtable[])() = { WhileTest_test };
void* WhileTest_test(struct WhileTest* this) {
  int i;
  i = 0;
  while ((i < 5)) {
    printf("%d\n", i);
    i = (i + 1);
  }
  return (void*)(i);
}
int main(int argc, char *argv[]) {
  tgc_start(&gc, &argc);
  {
    printf("%d\n", ({ struct WhileTest* tmp1 = ({ struct WhileTest* res = tgc_calloc(({ extern tgc_t gc; &gc; }), 1, sizeof(*res)); res->vtable = WhileTest_vtable; res; }); (int) tmp1->vtable[0](tmp1); }));
  }
  tgc_stop(&gc);

  return 0;
}
