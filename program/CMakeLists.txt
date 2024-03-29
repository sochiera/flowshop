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
  src/parent_selector.cpp
  src/crossover.cpp
  src/local_search.cpp
  src/replacement.cpp
  src/benchmark_collection.cpp
  src/immigration.cpp
)


set(TESTS
  test/random.cpp
  test/individual.cpp
  test/ux.cpp
  test/ox.cpp
  test/pmx.cpp
  test/instance.cpp
  test/parent_selector.cpp
  test/composition.cpp
  test/population.cpp
  test/adaptation.cpp
  test/best_of_replacement.cpp
  test/benchmark_collection.cpp
  test/local_search.cpp
  test/crossover.cpp
  test/replacement.cpp
)


add_library(flowshoplib ${SOURCES})
target_link_libraries(flowshoplib gomp)

add_executable(ut ${TESTS})
target_link_libraries(ut flowshoplib ${GTEST_BOTH_LIBRARIES})

add_executable(flowshop flowshop.cpp)
target_link_libraries(flowshop flowshoplib)

add_custom_target(
  copy_bindings_test ALL
  COMMAND cp  ${CMAKE_CURRENT_SOURCE_DIR}/../benchmark/* ${CMAKE_CURRENT_BINARY_DIR}/)

add_executable(random random.cpp)
target_link_libraries(random flowshoplib)

add_executable(smart_random smart_random.cpp)
target_link_libraries(smart_random flowshoplib)

add_executable(taboo_search taboo_search.cpp)
target_link_libraries(taboo_search flowshoplib)
