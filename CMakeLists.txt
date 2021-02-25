cmake_minimum_required(VERSION 3.5)

project("Machine Learning CPP")

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  message(WARNING "Clang Detected")
  message(WARNING "12.0.0 Supported")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  message(WARNING "GNU Detected")
  message(WARNING "7.2, 7.5, 8.4, 9.3, 10.2 Supported")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  message(WARNING "Intel Detected")
  message(WARNING "17.0.5 Supported")
  if(${CMAKE_VERSION} VERSION_LESS "3.6")
    message(FATAL_ERROR "Intel requires cmake 3.6 and above")
  endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  message(WARNING "MSVC Detected")
  message(WARNING "2019 Supported")
else()
  message(WARNING "Unknown Compiler Detected")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE on)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)

#add_subdirectory("src")

option(BUILD_EXAMPLES "Build Examples" OFF)
if(BUILD_EXAMPLES)
  add_subdirectory("examples")
endif(BUILD_EXAMPLES)

option(BUILD_TESTS "Build Unit Tests" OFF)

if(BUILD_TESTS)
  if (CMAKE_CXX_COMPILER_ID MATCHES "Cray")
    message(ERROR "Google Test cannot be built using Cray compiler. Try gcc.")
  endif()

  if(EXISTS "${PROJECT_SOURCE_DIR}/extern/googletest/.git")
    #Build GoogleTest 
    option(INSTALL_GTEST "" OFF) #Linking to a local copy is the point of this exercise.
    option(BUILD_GMOCK "" OFF) #We're only using GTest in this example.
    if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
      option(gtest_force_shared_crt "" ON)
    endif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")    
    add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest")
    
    add_library(GTest::GTest IMPORTED INTERFACE)
    set_property(TARGET GTest::GTest PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/extern/googletest/googletest/include")
    set_property(TARGET GTest::GTest PROPERTY INTERFACE_LINK_LIBRARIES "gtest")

    add_library(GTest::Main IMPORTED INTERFACE)
    set_property(TARGET GTest::Main PROPERTY INTERFACE_LINK_LIBRARIES GTest::GTest "gtest_main")
  else(EXISTS "${PROJECT_SOURCE_DIR}/extern/googletest/.git")
    find_package("GTest" REQUIRED)

    if(NOT TARGET GTest::GTest) #doesn't exist until CMake 3.9
      add_library(GTest::GTest IMPORTED INTERFACE)
      set_property(TARGET GTest::GTest PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${GTEST_INCLUDE_DIRS}")
      set_property(TARGET GTest::GTest PROPERTY INTERFACE_LINK_LIBRARIES "${GTEST_LIBRARIES}")
    endif(NOT TARGET GTest::GTest)  
    if(NOT TARGET GTest::Main) #doesn't exist until CMake 3.9
      add_library(GTest::Main IMPORTED INTERFACE)
      set_property(TARGET GTest::Main PROPERTY INTERFACE_LINK_LIBRARIES "${GTEST_MAIN_LIBRARIES}" GTest::GTest)
    endif(NOT TARGET GTest::Main)
  endif(EXISTS "${PROJECT_SOURCE_DIR}/extern/googletest/.git") 
endif(BUILD_TESTS)
if(BUILD_TESTS)
  #add_subdirectory("test")
endif(BUILD_TESTS)
