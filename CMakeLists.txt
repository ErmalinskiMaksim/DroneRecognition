# CMakeList.txt : CMake project for DroneRecognition, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("DroneRecognition")

# Add source to this project's executable.
add_executable (DroneRecognition "src/DroneRecognition.cpp" "headers/DroneRecognition.h" "src/ThreeFrameAX.cpp" "headers/ThreeFrameAX.h" "headers/ThreeFrameOO.h" "src/ThreeFrameOO.cpp" "headers/ThreeFrameDetector.h" "src/ThreeFrameDetector.cpp" "headers/ContourFinder.h"  "src/ContourFinder.cpp" "headers/TwoFrameMaskDetector.h"  "src/TwoFrameMaskDetector.cpp" "headers/Deflickerer.h" "src/Deflickerer.cpp")

target_link_libraries(DroneRecognition  ${CMAKE_SOURCE_DIR}/Dependencies/OpenCV/lib/opencv_core490d.lib)
target_link_libraries(DroneRecognition  ${CMAKE_SOURCE_DIR}/Dependencies/OpenCV/lib/opencv_highgui490d.lib)
target_link_libraries(DroneRecognition  ${CMAKE_SOURCE_DIR}/Dependencies/OpenCV/lib/opencv_imgcodecs490d.lib)
target_link_libraries(DroneRecognition  ${CMAKE_SOURCE_DIR}/Dependencies/OpenCV/lib/opencv_videoio490d.lib)
target_link_libraries(DroneRecognition  ${CMAKE_SOURCE_DIR}/Dependencies/OpenCV/lib/opencv_imgproc490d.lib)
target_link_libraries(DroneRecognition  ${CMAKE_SOURCE_DIR}/Dependencies/OpenCV/lib/opencv_tracking490d.lib)
target_link_libraries(DroneRecognition  ${CMAKE_SOURCE_DIR}/Dependencies/OpenCV/lib/opencv_bioinspired490d.lib)
target_link_libraries(DroneRecognition  ${CMAKE_SOURCE_DIR}/Dependencies/OpenCV/lib/opencv_video490d.lib)

include_directories(${CMAKE_SOURCE_DIR}/Dependencies/OpenCV/include)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DroneRecognition PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
