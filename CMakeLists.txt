cmake_minimum_required(VERSION 3.28)
project(TestEmODP)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DEM_64_BIT -DENV_64_BIT)

#link_directories(-L/root/em-odp/installation/em-odp_install/lib)

find_package(PkgConfig REQUIRED)

#pkg_check_modules(YOUR_LIBRARY1 REQUIRED libemodp)
#pkg_check_modules(YOUR_LIBRARY2 REQUIRED libodp-linux)
#pkg_check_modules(YOUR_LIBRARY3 REQUIRED libodphelper)

add_executable(TestEmODP
        hello.cpp common/cm_error_handler.c common/cm_pktio.c common/cm_setup.c)

target_link_libraries(TestEmODP libemodp libodp-linux libodphelper)

#target_link_libraries(TestEmODP ${YOUR_LIBRARY1_LIBRARIES} ${YOUR_LIBRARY2_LIBRARIES} ${YOUR_LIBRARY3_LIBRARIES})
#
#target_include_directories(TestEmODP PUBLIC ${YOUR_LIBRARY1_INCLUDE_DIRS} ${YOUR_LIBRARY2_INCLUDE_DIRS} ${YOUR_LIBRARY3_INCLUDE_DIRS})

include_directories(/root/em-odp/installation/em-odp_install/include)
include_directories(/root/em-odp/installation/odp_install/include)
link_directories(-L/root/em-odp/installation/em-odp_install/lib)
link_directories(-L/root/em-odp/installation/odp_install/lib)

#message(PROJECT_SOURCE_DIR="${YOUR_LIBRARY1_LIBRARIES}")
#message(PROJECT_SOURCE_DIR="${YOUR_LIBRARY2_LIBRARIES}")
#message(PROJECT_SOURCE_DIR="${YOUR_LIBRARY3_LIBRARIES}")
#
#message(PROJECT_SOURCE_DIR="${YOUR_LIBRARY1_INCLUDE_DIRS}")
#message(PROJECT_SOURCE_DIR="${YOUR_LIBRARY2_INCLUDE_DIRS}")
#message(PROJECT_SOURCE_DIR="${YOUR_LIBRARY3_INCLUDE_DIRS}")

#target_link_libraries(TestEmODP ${YOUR_LIBRARY1_LIBRARIES} ${YOUR_LIBRARY2_LIBRARIES} ${YOUR_LIBRARY3_LIBRARIES} emodp odp-linux odp-linux odphelper)
#target_link_libraries(TestEmODP ${YOUR_LIBRARY1_LIBRARIES} ${YOUR_LIBRARY2_LIBRARIES} ${YOUR_LIBRARY3_LIBRARIES})
#target_link_libraries(TestEmODP emodp)
