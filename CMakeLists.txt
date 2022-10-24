cmake_minimum_required(VERSION 3.0)
project(DS_EVAL)
include(ExternalProject)

option(BUILD_DBoW2          "Build DBoW2"                   ON)
option(BUILD_DEMO_MAIN     "Build DEMO_MAIN application"  ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(HDRS
  libs/DBoW2/include/DBoW2/BowVector.h           
  libs/DBoW2/include/DBoW2/FBrief.h
  libs/DBoW2/include/DBoW2/QueryResults.h        
  libs/DBoW2/include/DBoW2/TemplatedDatabase.h   
  libs/DBoW2/include/DBoW2/FORB.h
  libs/DBoW2/include/DBoW2/DBoW2.h               
  libs/DBoW2/include/DBoW2/FClass.h              
  libs/DBoW2/include/DBoW2/FeatureVector.h
  libs/DBoW2/include/DBoW2/ScoringObject.h       
  libs/DBoW2/include/DBoW2/TemplatedVocabulary.h 
  libs/dirent/dirent.h
  libs/indicators/indicators.hpp

  include/DBow2_handler.h   
  include/includes.h    
  include/defs.h    
  include/Sequence.h    
  include/Dataset.h   
  include/Utils.h   
  include/System.h
  include/pyhelper.hpp      
  include/Contrast_handler.h              
  include/Brightness_handler.h              
  include/Stats_Utils.h
  include/Calculus_Utils.h
  include/Inertial_Diff_handler.h
  include/Inertial_DR_handler.h
  include/Features_handler.h
  include/Visualization_Utils.h
  include/Reports_Utils.h
  include/Scoreboard.h
  include/Sequence_Scoreboard.h
  include/Dataset_Scoreboard.h
  include/Blur_Scoreboard.h
  include/Brightness_Scoreboard.h
  include/Inertial_data.h
  include/Visual_data.h
  include/Sensor_Data.h
  include/Processing_Element.h
  include/Export_Utils.h
  include/UI_Utils.h
  include/Blur_handler.h
  include/Exposure_handler.h
  include/Disparity_handler.h
  include/General_Metrics_handler.h
  include/Contrast_Scoreboard.h
  include/DBoW2_Scoreboard.h
  include/Visual_Feature_Scoreboard.h
  include/Features_Scoreboard.h
  include/Inertial_Diff_Scoreboard.h
  include/Inertial_DR_Scoreboard.h
  include/Inertial_Axis_Diff_Scorebaord.h
  include/Inertial_Axis_DR_Scorebaord.h
  include/General_Char_Scoreboard.h
  include/Disparity_Scoreboard.h
  include/Exposure_Scoreboard.h
  include/Disparity_Method_Scoreboard.h
  include/Rotation_only_handler.h
  include/Rotation_only_Scoreboard.h)


set(SRCS 
  libs/DBoW2/src/BowVector.cpp     
  libs/DBoW2/src/FBrief.cpp        
  libs/DBoW2/src/FORB.cpp
  libs/DBoW2/src/FeatureVector.cpp 
  libs/DBoW2/src/QueryResults.cpp   
  libs/DBoW2/src/ScoringObject.cpp 
  src/DBow2_handler.cpp     
  src/Dataset.cpp       
  src/Sequence.cpp  
  src/Utils.cpp   
  src/System.cpp  
  src/defs.cpp
  src/Contrast_handler.cpp  
  src/Brightness_handler.cpp              
  src/Stats_Utils.cpp             
  src/Calculus_Utils.cpp
  src/Inertial_Diff_handler.cpp
  src/Inertial_DR_handler.cpp
  src/Features_handler.cpp
  src/Visualization_Utils.cpp
  src/Reports_Utils.cpp
  src/Scoreboard.cpp
  src/Sequence_Scoreboard.cpp
  src/Dataset_Scoreboard.cpp
  src/Blur_Scoreboard.cpp
  src/Brightness_Scoreboard.cpp
  src/Inertial_data.cpp
  src/Visual_data.cpp
  src/Sensor_Data.cpp
  src/Processing_Element.cpp
  src/Export_Utils.cpp
  src/UI_Utils.cpp
  src/Blur_handler.cpp
  src/Exposure_handler.cpp
  src/Disparity_handler.cpp
  src/General_Metrics_handler.cpp
  src/Contrast_Scoreboard.cpp
  src/DBoW2_Scoreboard.cpp
  src/Visual_Feature_Scoreboard.cpp
  src/Features_Scoreboard.cpp
  src/Inertial_Diff_Scoreboard.cpp
  src/Inertial_DR_Scoreboard.cpp
  src/Inertial_Axis_Diff_Scorebaord.cpp
  src/Inertial_Axis_DR_Scorebaord.cpp
  src/General_Char_Scoreboard.cpp
  src/Disparity_Scoreboard.cpp
  src/Exposure_Scoreboard.cpp
  src/Disparity_Method_Scoreboard.cpp
  src/Rotation_only_handler.cpp
  src/Rotation_only_Scoreboard.cpp)  


set(DEPENDENCY_DIR ${CMAKE_CURRENT_BINARY_DIR}/dependencies)
set(DEPENDENCY_INSTALL_DIR ${DEPENDENCY_DIR}/install)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(PythonLibs REQUIRED)
# include_directories(/usr/include/python3.8)


if(BUILD_DBoW2)
  set(LIB_SHARED "SHARED")
  if(WIN32)
    set(LIB_SHARED "STATIC")
  endif(WIN32)
  add_library(${PROJECT_NAME} ${LIB_SHARED} ${SRCS})
  target_include_directories(${PROJECT_NAME} PUBLIC libs/DBoW2/include/DBoW2/ libs/DBoW2/include/ libs/dirent/inlcude/ include/ /usr/include/python3.8 libs/indicators/)
  set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11 COMPILE_FLAGS -O0)
endif(BUILD_DBoW2)

if(BUILD_DEMO_MAIN)
  add_executable(demo_main Examples/demo_main.cpp)
  target_link_libraries(demo_main ${PROJECT_NAME} ${OpenCV_LIBS} ${PYTHON_LIBRARIES})
  set_target_properties(demo_main PROPERTIES CXX_STANDARD 11 COMPILE_FLAGS -O0)

  add_executable(demo_test Examples/demo_test.cpp)
  target_link_libraries(demo_test ${PROJECT_NAME} ${OpenCV_LIBS} ${PYTHON_LIBRARIES})
  set_target_properties(demo_test PROPERTIES CXX_STANDARD 11 COMPILE_FLAGS -O0)
  
  target_include_directories(${PROJECT_NAME} PUBLIC include/)
  #file(COPY py_lib DESTINATION ${CMAKE_BINARY_DIR}/)
  file(COPY resources/ORBvoc.txt DESTINATION ${CMAKE_BINARY_DIR}/)
endif(BUILD_DEMO_MAIN)

configure_file(libs/DBoW2/src/DBoW2.cmake.in
  "${PROJECT_BINARY_DIR}/DBoW2Config.cmake" @ONLY)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
if(BUILD_DBoW2)
  install(DIRECTORY include/DBoW2 DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
endif()
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/DBoW2Config.cmake"
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})
install(FILES "${PROJECT_BINARY_DIR}/DBoW2Config.cmake" 
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/DBoW2/)
install(DIRECTORY ${DEPENDENCY_INSTALL_DIR}/ DESTINATION ${CMAKE_INSTALL_PREFIX} OPTIONAL)

