#include <cstdio>
#include <boost/python.hpp>


using namespace boost::python;

void say_something()
{
  printf("foo\n");
}


int add_huge(){
  int a[10];
  int b[10];
  int c[10];

  #pragma omp parallel for shared(a, b)
  for(int i = 0; i < 10; i++){
    c[i] = a[i] + b[i];
  }

  int sum = 0;
  for(int i = 0; i < 10; i++)
    sum += c[i];

  return sum;
}

void print_dict(const dict & dict){
  
}



BOOST_PYTHON_MODULE(experiment){
  def("say_something", say_something, "says something");
  def("add", add_huge , "adds something");
}
