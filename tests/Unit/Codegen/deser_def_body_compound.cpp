// RUN: %amp_device -D__GPU__=1 %s -c -o %t.device.o
// RUN: %gtest_amp %s %t.device.o -o %t && %t
#include <stdlib.h>
#ifndef __GPU__ //gtest requires rtti, but amp_device forbids rtti
#include <gtest/gtest.h>
#endif
class Member {
 public:
  // Compiler-generated constructor
  __attribute__((annotate("deserialize"))) Member(float*, int) restrict(amp);
  float* bzzt;
  int zzz;
};

class baz {
 public:
  baz(void): m(NULL, 3), foo(1234) {}
  // Compiler-generated constructor
  __attribute__((annotate("deserialize"))) baz(float *m1, int m2,
    int foo_, float bar_) restrict(amp);

  Member m;
  int foo;
  float bar;
};
int fake_use(void) restrict(amp) {
  baz bll(NULL, 0,  1, 2.0);
  return bll.foo;
}
#ifndef __GPU__
TEST(GPUCodeGen, ConstructorCompound) {
  float local_float = 2.78f;
  baz bll(&local_float, 2, 1, 2.0);
  EXPECT_EQ(bll.foo, 1);
  EXPECT_EQ(bll.m.bzzt, &local_float);
  EXPECT_EQ(bll.m.zzz, 2);
}
#endif
