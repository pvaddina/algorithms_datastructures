project(Algorithm-Quick-Find)
set(CMAKE_CXX_STANDARD 14)

set(SOURCES test.cpp quick-find.h quick-union.h quick-union-weighted.h quick-union-wt-pcomp.h)

add_executable(dyn-con-test ${SOURCES})

