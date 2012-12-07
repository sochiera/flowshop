#include <instance.h>
#include <individual.h>
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

TEST(Instance, CalculatesIndividualCost){
  Individual ind("210");
  
  double cost[3][3] = {
    {3, 3, 2},
    {1, 4, 4},
    {5, 1, 1}
  };

  const int tasks = 3;
  const int machines = 3;
  const int solution = 16.0;

  FlowshopInstance instance(machines, tasks, solution);
  for(int m = 0; m < machines; m++)
    for(int t = 0; t < tasks; t++)
      instance(m, t) = cost[m][t];

  for(int m = 0; m < machines; m++)
    for(int t = 0; t < tasks; t++)
      ASSERT_EQ(cost[m][t], instance(m, t));
  
  ASSERT_FLOAT_EQ(solution, instance.evaluate(&ind));
}


TEST(Instance, CalculatesIndividualCost2){
  Individual ind("0123");
  
  double cost[4][4] = {
    {2, 3, 2, 1},
    {1, 1, 2, 1},
    {3, 2, 1, 1},
    {1, 1, 3, 1}
  };

  const int tasks = 4;
  const int machines = 4;
  const int solution = 14.0;

  FlowshopInstance instance(machines, tasks, solution);
  for(int m = 0; m < machines; m++)
    for(int t = 0; t < tasks; t++)
      instance(m, t) = cost[m][t];

  for(int m = 0; m < machines; m++)
    for(int t = 0; t < tasks; t++)
      ASSERT_EQ(cost[m][t], instance(m, t));
  
  ASSERT_FLOAT_EQ(solution, instance.evaluate(&ind));
}



TEST(Instance, HandlesBigData){
  Individual ind(10000); 
  ind.randomize();
  FlowshopInstance instance(100, 10000, 10000.0);
  instance.evaluate(&ind);
}

TEST(Instance, AfterInsertionsCostsSmall){
  Individual a("210");
  Individual b("012");
  Individual c("021");
  Individual d("102");
  Individual e("120");
  Individual f("201");
  
  
  double cost[3][3] = {
    {3, 9, 2},
    {1, 4, 14},
    {5, 7, 1}
  };

  const int tasks = 3;
  const int machines = 3;
  const int solution = 16;

  FlowshopInstance instance(machines, tasks, solution);
  for(int m = 0; m < machines; m++)
    for(int t = 0; t < tasks; t++)
      instance(m, t) = cost[m][t];

  for(int m = 0; m < machines; m++)
    for(int t = 0; t < tasks; t++)
      ASSERT_EQ(cost[m][t], instance(m, t));
  
  std::vector<int> M = instance.evaluateAfterInsertions(2, &a);

std::cout << M[0] << " " << M[1] << " " << M[2] << "\n" << 
instance.evaluate(&a) << " " << instance.evaluate(&b) << " " << instance.evaluate(&c) << " " 
<< instance.evaluate(&d) << " " << instance.evaluate(&e) << " " << instance.evaluate(&f);

//  ASSERT_EQ(16, M[1]);
}

TEST(Instance, AfterInsertionsCostsBig){
  const int n = 20;
  Individual a(n);
  a.randomize();
  const char * filename = "tai20_5.txt.in";
  const int instance_index = 0;

  BenchmarkCollection bc;

  bc.load(filename);

  srand(time(0));
  const FlowshopInstance & instance = bc.instance(instance_index);
  
  for(int i = 0; i < n; i++){
    std::vector<int> M = instance.evaluateAfterInsertions(i, &a);
    for(int j = 0; j < n; j++){
      Individual b = a;
      b.insert(i, j);
   //   std::cout << instance.evaluate(&b)- M[j] << "\n";
     // ASSERT_EQ(instance.evaluate(&b), M[j]);
    }
  }
}