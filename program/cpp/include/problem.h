#ifndef PROBLEM_H_
#define PROBLEM_H_

namespace genetic{

template<class I>
class Problem{
  pubilc:
    virtual double evaluate(const I & individual) const = 0;
};

};


#endif
