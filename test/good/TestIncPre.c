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
  int i;
  x = 5;
  i = 