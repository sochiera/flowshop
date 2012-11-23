#include <boost/python.hpp>
#include <cstdio>

using namespace boost::python;

void test_bindings(){
  printf("Bindings work\n");
}

BOOST_PYTHON_MODULE(flowshop){
  def("test_bindings", test_bindings, "");
}
