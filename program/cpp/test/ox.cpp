#include <crossover.h>
#include <gtest/gtest.h>

using namespace genetic;

TEST(OX, Crossover){
  Permutation mom("07243165");
  Permutation dad("72403156");

  OX ox;
  
  Permutation child = ox.cross(2, 5, mom, dad);
  ASSERT_EQ(Permutation("24307156"), child);

  child = ox.cross(2, 5, dad, mom);
  ASSERT_EQ(Permutation("04372165"),child);
}



TEST(OX, BigRandom){
  OX ox;
  for(int i = 0; i < 1000; i ++){
    Permutation a(20);
    a.randomize();

    Permutation b(20);
    b.randomize();

    Crossover::Result res = ox(a, b);
    ASSERT_TRUE(res.first.valid());
    ASSERT_TRUE(res.second.valid());
  }
}
