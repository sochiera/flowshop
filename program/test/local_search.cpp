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


TEST(GradialSinglePointOperator, FindsBetterSolutions){

  const char * filename = "tai20_10.txt.in";
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
