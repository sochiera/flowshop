#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <vector>
#include <istream>


class Individual : public std::vector<int>{
  public:
    Individual() {}
    Individual(int size);
    Individual(const char * str);

    bool operator == (const Individual & other) const;
    bool operator < (const Individual & other) const;
    bool valid() const;

    void swap(int i, int j);
    void randomize();

    double cost() const;
    void set_cost(double cost);

  private:
    double cost_;
};


std::ostream & operator << (std::ostream & out, const Individual & p);


#endif
