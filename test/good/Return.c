#include <stdio.h>
#include <stdlib.h>
#include "tgc.h"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
struct array { int* array; int length; };
tgc_t gc;
struct TestReturn;
void* TestReturn_fact(struct TestReturn* this, int n);
struct TestReturn {
  void* (**vtable)();
};
void* (*TestReturn_vtable[])() = { TestReturn_fact };
void* TestReturn_fact(struct TestReturn* this, int n) {
  if ((n < 2)) {
    return (void*)(1);
  }
  else {
    return (void*)((n * ({ struct TestReturn* tmp1 = this; (int) tmp1->vtable[0](tmp1, (n - 1)); })));
  }
}
int main(int argc, char *argv[]) {
  tgc_start(&gc, &argc);
  {
    printf("%d\n", ({ struct TestReturn* tmp1 = ({ struct TestReturn* res = tgc_calloc(({ extern tgc_t gc; &gc; }), 1, sizeof(*res)); res->vtable = TestReturn_vtable; res; }); (int) tmp1->vtable[0](tmp1, 5); }));
  }
  tgc_stop(&gc);

  return 0;
}
