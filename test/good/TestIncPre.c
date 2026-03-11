#include <stdio.h>
#include <stdlib.h>
#include "tgc.h"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
struct array { int* array; int length; };
tgc_t gc;
struct TestIncPre;
void* TestIncPre_test(struct TestIncPre* this);
struct TestIncPre {
  void* (**vtable)();
};
void* (*TestIncPre_vtable[])() = { TestIncPre_test };
void* TestIncPre_test(struct TestIncPre* this) {
  int x;
  x = 5;
  (x = x + 1);

  return (void*)(intptr_t)(x);
}
int main(int argc, char *argv[]) {
  tgc_start(&gc, &argc);
  {
    printf("%d\n", ({ struct TestIncPre* tmp1 = ({ struct TestIncPre* res = tgc_calloc(({ extern tgc_t gc; &gc; }), 1, sizeof(*res)); res->vtable = TestIncPre_vtable; res; }); (int) tmp1->vtable[0](tmp1); }));
  }
  tgc_stop(&gc);

  return 0;
}
