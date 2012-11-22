project(flowshop)
cmake_minimum_required(VERSION 2.8)

add_definitions(-Wall)

find_package(Boost COMPONENTS python)
include_directories(${Boost_INCLUDE_DIRS})

find_package(PythonLibs)
include_directories(${PYTHON_INCLUDE_DIRS})

find_package(OpenMP)
add_definitions(${OpenMP_CXX_FLAGS})

set(
  SOURCES
)


add_library(flowshop SHARED ${SOURCES})
set_target_properties(flowshop PROPERTIES PREFIX "")
target_link_libraries(flowshop
  ${Boost_LIBRARIES} 
  ${PYTHON_LIBRARIES}
  gomp
  )


