#include <crossover.h>
#include <gtest/gtest.h>


TEST(PMX, Crossover){
  Individual mom("8473625190");
  Individual dad("0123456789");
  Individual child("0743625189");

  PMX pmx;

  ASSERT_EQ(child, pmx.cross(3, 8, &mom, &dad));
}



TEST(PMX, BigRandom){
  PMX pmx;
  for(int i = 0; i < 1000; i ++){
    Individual a(20);
    a.randomize();

    Individual b(20);
    b.randomize();

    Crossover::Result res = pmx(&a, &b);
    ASSERT_TRUE(res.first.valid());
    ASSERT_TRUE(res.second.valid());
  }
}
