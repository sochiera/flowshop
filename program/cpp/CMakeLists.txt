project(flowshop)
cmake_minimum_required(VERSION 2.8)

add_definitions(-Wall)

find_package(OpenMP)
add_definitions(${OpenMP_CXX_FLAGS})

find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(include)


set(SOURCES
  src/random.cpp 
  src/individual.cpp
  src/composition.cpp
  src/ox.cpp
  src/ux.cpp
  src/pmx.cpp
  src/mutation.cpp
  src/population.cpp
  src/algorithm_state.cpp
  src/instance.cpp
  src/termination.cpp
  src/solver.cpp
  src/adaptation.cpp
  src/stat_utils.cpp
)


set(TESTS
  test/random.cpp
  test/individual.cpp
  test/ux.cpp
  test/ox.cpp
  test/pmx.cpp
  test/instance.cpp
  test/composition.cpp
)


add_library(flowshop ${SOURCES})
target_link_libraries(flowshop gomp)

add_executable(ut ${TESTS})
target_link_libraries(ut flowshop ${GTEST_BOTH_LIBRARIES})
