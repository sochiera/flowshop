#include <instance.h>
#include <gtest/gtest.h>

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
