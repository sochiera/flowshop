#include <permutation.h>
#include <gtest/gtest.h>

TEST(Permutation, ReadsItselfFromString){
  genetic::Permutation p("0123");

  ASSERT_EQ(4, p.size());
  for(int i = 0; i < 4; i++){
    ASSERT_EQ(i, p[i]);  
  }
}


TEST(Permutation, ChecksValidity){
  genetic::Permutation p(3);
  ASSERT_FALSE(p.valid());

  p[0] = 2;
  p[1] = 1;
  p[2] = 0;
  ASSERT_TRUE(p.valid());
}
