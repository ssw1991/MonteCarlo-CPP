# CMakeList.txt : CMake project for MonteCarlo, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (MonteCarlo "MonteCarlo.cpp" "MonteCarlo.h" "main.cpp" "Model.h" "Model.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MonteCarlo PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
