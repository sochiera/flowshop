#ifndef PERMUTATION_H_
#define PERMUTATION_H_

#include <vector>
#include <istream>

namespace genetic{

class Permutation : public std::vector<int>{
  public:
    Permutation() {}
    Permutation(int size);
    Permutation(const char * str);

    bool operator == (const Permutation & other) const;
    bool valid() const;

    void swap(int i, int j);
    void randomize();
};


std::ostream & operator << (std::ostream & out, const Permutation & p);
};


#endif
