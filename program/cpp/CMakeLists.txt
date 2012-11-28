project(flowshop)
cmake_minimum_required(VERSION 2.8)

add_definitions(-Wall)

find_package(Boost COMPONENTS python)
include_directories(${Boost_INCLUDE_DIRS})

find_package(PythonLibs)
include_directories(${PYTHON_INCLUDE_DIRS})

find_package(OpenMP)
add_definitions(${OpenMP_CXX_FLAGS})

find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(include)


set(SOURCES
  src/random.cpp 
  src/individual.cpp
  src/ox.cpp
  src/ux.cpp
  src/pmx.cpp
  src/mutation.cpp
  src/population.cpp
  src/algorithm_state.cpp
  src/instance.cpp
  src/termination.cpp
  src/solver.cpp
  bindings.cpp
)


set(TESTS
  test/random.cpp
  test/individual.cpp
  test/ux.cpp
  test/ox.cpp
  test/pmx.cpp
  test/instance.cpp
)


add_library(flowshop SHARED ${SOURCES})
set_target_properties(flowshop PROPERTIES PREFIX "")
target_link_libraries(flowshop
  ${Boost_LIBRARIES} 
  ${PYTHON_LIBRARIES}
  gomp
  )

add_executable(ut ${TESTS})
target_link_libraries(ut flowshop ${GTEST_BOTH_LIBRARIES})


find_package(PythonInterp)
add_custom_target( 
  copy_bindings_test ALL
  COMMAND cp  ${CMAKE_CURRENT_SOURCE_DIR}/binding_test.py ${CMAKE_CURRENT_BINARY_DIR}/binding_test.py)


enable_testing()
add_test(UnitTests ${CMAKE_CURRENT_BINARY_DIR}/ut)
add_test(Bindings ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/binding_test.py)

