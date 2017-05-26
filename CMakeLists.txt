#MakeLists.txt for event package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(NKFADC500DECODER)

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS Core RIO Net Hist Graf Graf3d Gpad Tree Rint Postscript Matrix Physics MathCore Thread Spectrum Minuit Gui)

include(${ROOT_USE_FILE})

include_directories(
${ROOT_INCLUDE_DIRS}
${CMAKE_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/src
)

add_definitions(${ROOT_CXX_FLAGS})

ROOT_GENERATE_DICTIONARY(NoticeFADC500DECODERDict
${CMAKE_SOURCE_DIR}/include/FADC500Gui.h
${CMAKE_SOURCE_DIR}/include/FADC500Decoder.h
)

#---Create a shared library with geneated dictionary
add_library(NKFADC500DECODER SHARED
${CMAKE_SOURCE_DIR}/src/FADC500Gui.cc
${CMAKE_SOURCE_DIR}/src/FADC500Decoder.cc
NoticeFADC500DECODERDict.cxx
)

target_link_libraries(NKFADC500DECODER ${ROOT_LIBRARIES})
