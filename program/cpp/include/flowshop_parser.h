#ifndef PARSER_H_
#define PARSER_H_

#include <vector>
#include <instance.h>
#include <algorithm_state.h>


class FlowshopParser{
  public:
    FlowshopInstance Parse(int n);

  private:
    const static int BenchmarkCount = 120;
};

#endif




