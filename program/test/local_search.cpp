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

  LocalSearch::Result r = ls(&randomInd);

  ASSERT_LT(r.first, randomInd);
  ASSERT_LT(r.second, r.first);	
}


TEST(TabooSearch, Taboo_vs_SinglePiontOperator){

  const char * filename = "tai20_10.txt.in";
  const int instance_index = 0;

  BenchmarkCollection bc;

  bc.load(filename);

  srand(time(0));
  const FlowshopInstance & instance = bc.instance(instance_index);

  GradualSinglePointOperator ls1(instance, 0.0);
  TabooSearch ls2(instance, 1, 1);

  Individual randomInd(instance.num_tasks());
  randomInd.randomize();
  randomInd.set_cost(instance.evaluate(&randomInd));

  LocalSearch::Result r1 = ls1(&randomInd);
  LocalSearch::Result r2 = ls2(&randomInd);

  ASSERT_EQ(instance.evaluate(&r1.first), instance.evaluate(&r2.first));
  ASSERT_EQ(instance.evaluate(&r1.second), instance.evaluate(&r2.second)); 
}



TEST(TabooSearch, FourIterations){

  const char * filename = "tai20_10.txt.in";
  const int instance_index = 0;

  BenchmarkCollection bc;

  bc.load(filename);

  srand(time(0));
  const FlowshopInstance & instance = bc.instance(instance_index);

  GradualSinglePointOperator ls1(instance, 0.0);
  TabooSearch ls2(instance, 4, 0);

  Individual randomInd(instance.num_tasks());
  randomInd.randomize();
  randomInd.set_cost(instance.evaluate(&randomInd));

  LocalSearch::Result r1 = ls1(&randomInd);
  LocalSearch::Result r2 = ls1(&r1.second);
  LocalSearch::Result r3 = ls1(&r2.second);
  LocalSearch::Result r4 = ls1(&r3.second);
  LocalSearch::Result r5 = ls2(&randomInd);

  ASSERT_EQ(instance.evaluate(&r5.second), instance.evaluate(&r5.second)); 
}

