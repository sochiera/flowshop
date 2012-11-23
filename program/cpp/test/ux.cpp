#include <crossover.h>
#include <gtest/gtest.h>


TEST(UX, Crossover){
  Individual mom("02134");
  Individual dad("41302");

  std::vector<int> indices;
  indices.push_back(1);
  indices.push_back(3);

  UX ux(2);
  
  ASSERT_EQ(Individual("31204"), ux.cross(indices, dad, mom));
}

TEST(UX, BigRandom){
  UX ux(10);
  for(int i = 0; i < 1000; i ++){
    Individual a(20);
    a.randomize();

    Individual b(20);
    b.randomize();

    Crossover::Result res = ux(a, b);
    ASSERT_TRUE(res.first.valid());
    ASSERT_TRUE(res.second.valid());
  }
}
