#include <stdio.h>
#include <stdlib.h>
#include "tgc.h"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
struct array { int* array; int length; };
tgc_t gc;
struct TestAffec;
void* TestAffec_test(struct TestAffec* this);
struct TestAffec {
  void* (**vtable)();
};
void* (*TestAffec_vtable[])() = { TestAffec_test };
void* TestAffec_test(struct TestAffec* this) {
  int x;
  int r;
  x = 5;
  if ((x == 5)) {
    r = 1;
  }
  else {
    r = 0;
  }
  return (void*)(r);
}
int main(int argc, char *argv[]) {
  tgc_start(&gc, &argc);
  {
    printf("%d\n", ({ struct TestAffec* tmp1 = ({ struct TestAffec* res = tgc_calloc(({ extern tgc_t gc; &gc; }), 1, sizeof(*res)); res->vtable = TestAffec_vtable; res; }); (int) tmp1->vtable[0](tmp1); }));
  }
  tgc_stop(&gc);

  return 0;
}
