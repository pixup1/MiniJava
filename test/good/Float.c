#include <stdio.h>
#include <stdlib.h>
#include "tgc.h"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
struct array { int* array; int length; };
tgc_t gc;
struct TestFloat;
void* TestFloat_test(struct TestFloat* this);
struct TestFloat {
  void* (**vtable)();
};
void* (*TestFloat_vtable[])() = { TestFloat_test };
void* TestFloat_test(struct TestFloat* this) {
  float x;
  x = (1.000000 + 2.500000);
  return (void*)(*(int*)&x);
}
int main(int argc, char *argv[]) {
  tgc_start(&gc, &argc);
  {
    printf("%.7g\n", ({ struct TestFloat* tmp1 = ({ struct TestFloat* res = tgc_calloc(({ extern tgc_t gc; &gc; }), 1, sizeof(*res)); res->vtable = TestFloat_vtable; res; }); void* tmp2 = (void*) tmp1->vtable[0](tmp1); (float)(*(float*)&tmp2); }));
  }
  tgc_stop(&gc);

  return 0;
}
