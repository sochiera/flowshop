#ifndef CROSSOVER_H_
#define CROSSOVER_H_

#include <permutation.h>
#include <utility>

namespace genetic{


class Crossover{
  public:
    typedef std::pair<Permutation, Permutation> Result;

    virtual Result operator() 
      (const Permutation & a, const Permutation & b) = 0;
};


class OX : public Crossover{
  public:  
    virtual Result operator() 
      (const Permutation & a, const Permutation & b);

    Permutation cross(int a, int b, 
      const Permutation & mom, const Permutation & dad);
};


class PMX : public Crossover{
  public:  
    PMX(int max_segment = 100000000);

    virtual Result operator() 
      (const Permutation & a, const Permutation & b);

    Permutation cross(int a, int b, 
      const Permutation & mom, const Permutation & dad);
  
  private:
    int max_seg_;  
};


class UX : public Crossover{
  public: 
    UX(int num_exchanged);
    
    virtual Result operator() 
      (const Permutation & a, const Permutation & b);
    
    Permutation cross(const std::vector<int>  & ind, 
      const Permutation & mom, const Permutation & dad);
  
  private:
    double num_exchanged_;
};


};

#endif
