#include <local_search.h>
#include <individual.h>
#include <gtest/gtest.h>
#include <benchmark_collection.h>
#include <parent_selector.h>
#include <crossover.h>
#include <mutation.h>
#include <replacement.h>
#include <adaptation.h>
#include <solver.h>
#include <termination.h>
#include <gtest/gtest.h>
#include <iostream>



TEST(insert, LocalSearch){
  Individual mom("07243165");
  const FlowshopInstance instance(0,0,0);
  GradualSinglePointOperator ls(instance);
  Individual Child1 = ls.insert(&mom, 0, 7);
  Individual Child2 = ls.insert(&mom, 7, 0);
  Individual Child3 = ls.insert(&mom, 2, 5);
  ASSERT_EQ(Individual("72431650"), Child1);
  ASSERT_EQ(Individual("50724316"), Child2);
  ASSERT_EQ(Individual("07431265"), Child3);
}


TEST(localsearch, LocalSearch){

  const char * filename = "tai20_10.txt.in";
  char * test_set_name = strdup(filename);
  int l = strlen(filename);
  test_set_name[l-7] = 0;
  const int instance_index = 0;

  BenchmarkCollection bc;

  bc.load(filename);

  srand(time(0));
  const FlowshopInstance & instance = bc.instance(instance_index);

  GradualSinglePointOperator ls(instance, 0.8);

  Individual randomInd(instance.num_tasks());
  randomInd.randomize();
  randomInd.set_cost(instance.evaluate(&randomInd));

  Crossover::Result r = ls(&randomInd);

  ASSERT_LT(r.first, randomInd);
  ASSERT_LT(r.second, r.first);	
}
