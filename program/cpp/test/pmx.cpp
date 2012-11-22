#include <crossover.h>
#include <gtest/gtest.h>

using namespace genetic;

TEST(PMX, Crossover){
  Permutation mom("8473625190");
  Permutation dad("0123456789");
  Permutation child("0743625189");

  PMX pmx;

  ASSERT_EQ(child, pmx.cross(3, 8, mom, dad));
}



TEST(PMX, BigRandom){
  PMX pmx;
  for(int i = 0; i < 1000; i ++){
    Permutation a(20);
    a.randomize();

    Permutation b(20);
    b.randomize();

    Crossover::Result res = pmx(a, b);
    ASSERT_TRUE(res.first.valid());
    ASSERT_TRUE(res.second.valid());
  }
}
