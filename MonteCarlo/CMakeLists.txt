# CMakeList.txt : CMake project for MonteCarlo, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (MonteCarlo   "main.cpp"   "MC.h" "MC.cpp" "FDM.h" "SDE.h" "RNG.h" "Pricer.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MonteCarlo PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
