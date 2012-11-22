#include <permutation.h>
#include <cstring>
#include <algorithm>


genetic::Permutation::Permutation(int size)
  : std::vector<int>(size) 
{}


genetic::Permutation::Permutation(const char * code)
  : std::vector<int>(strlen(code))
{
  int n = strlen(code);
  for(int i = 0; i < n; i++){
    at(i) = code[i] - '0'; 
  }
}


bool genetic::Permutation::operator == (const Permutation & other) const{
  for(int i = 0; i < size(); i++){
    if(at(i) != other[i])
      return false;
  }
  return true;
}


bool genetic::Permutation::valid() const{
  bool was[size()];
  std::fill(was, was + size(), false);
  for(int i = 0; i < size(); i++){
    if(was[at(i)])
      return false;
    was[at(i)] = true;
  }

  return true;
}



std::ostream & genetic::operator << 
  (std::ostream & out, const Permutation & p)
{
  for(int i = 0; i < p.size(); i ++)
    out << p[i] << " ";
  out << std::endl;
  return out;
}


void genetic::Permutation::swap(int i, int j){
  std::swap(at(i), at(j));
}


void  genetic::Permutation::randomize(){
  for(int i = 0; i < size(); i++)
    at(i) = i;
  std::random_shuffle(begin(), end());
}
