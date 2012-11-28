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

  FlowshopInstance instance(machines, tasks);
  for(int m = 0; m < machines; m++)
    for(int t = 0; t < tasks; t++)
      instance(m, t) = cost[m][t];

  for(int m = 0; m < machines; m++)
    for(int t = 0; t < tasks; t++)
      ASSERT_EQ(cost[m][t], instance(m, t));
  
  ASSERT_FLOAT_EQ(16.0, instance.evaluate(&ind));
}


TEST(Instance, HandlesBigData){
  Individual ind(10000); 
  ind.randomize();
  FlowshopInstance instance(100, 10000);
  instance.evaluate(&ind);
}
