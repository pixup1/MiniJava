#include <stdio.h>
#include <stdlib.h>
#include "tgc.h"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
struct array { int* array; int length; };
tgc_t gc;
struct TestAddAssign;
void* TestAddAssign_test(struct TestAddAssign* this);
struct TestAddAssign {
  void* (**vtable)();
};
void* (*TestAddAssign_vtable[])() = { TestAddAssign_test };
void* TestAddAssign_test(struct TestAddAssign* this) {
  int x;
  int r;
  x = 5;
  x = x + 3;

  if ((x == 8)) {
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
    printf("%d\n", ({ struct TestAddAssign* tmp1 = ({ struct TestAddAssign* res = tgc_calloc(({ extern tgc_t gc; &gc; }), 1, sizeof(*res)); res->vtable = TestAddAssign_vtable; res; }); (int) tmp1->vtable[0](tmp1); }));
  }
  tgc_stop(&gc);

  return 0;
}
