#ifndef CROSSOVER_H_
#define CROSSOVER_H_

#include <individual.h>
#include <utility>


class Crossover{
  public:
    typedef std::pair<Individual, Individual> Result;

    virtual Result operator() 
      (const Individual & a, const Individual & b) = 0;
};


class OX : public Crossover{
  public:  
    virtual Result operator() 
      (const Individual & a, const Individual & b);

    Individual cross(int a, int b, 
      const Individual & mom, const Individual & dad);
};


class PMX : public Crossover{
  public:  
    PMX(int max_segment = 100000000);

    virtual Result operator() 
      (const Individual & a, const Individual & b);

    Individual cross(int a, int b, 
      const Individual & mom, const Individual & dad);
  
  private:
    int max_seg_;  
};


class UX : public Crossover{
  public: 
    UX(int num_exchanged);
    
    virtual Result operator() 
      (const Individual & a, const Individual & b);
    
    Individual cross(const std::vector<int>  & ind, 
      const Individual & mom, const Individual & dad);
  
  private:
    double num_exchanged_;
};


#endif
