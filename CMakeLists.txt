## This file is a quick tutorial on writing CMakeLists for targeting the Vita
cmake_minimum_required(VERSION 2.8)

## This includes the Vita toolchain, must go before project definition
# It is a convenience so you do not have to type
# -DCMAKE_TOOLCHAIN_FILE=$VITASDK/share/vita.toolchain.cmake for cmake. It is
# highly recommended that you include this block for all projects.

set(CMAKE_TOOLCHAIN_FILE "/usr/local/vitasdk/share/vita.toolchain.cmake" CACHE PATH "toolchain file")

## Define project parameters here
# Name of the project
project(snakeclone)
# This line adds Vita helper macros, must go after project definition in order
# to build Vita specific artifacts (self/vpk).
include("/usr/local/vitasdk/share/vita.cmake" REQUIRED)

## Configuration options for this app
# Display name (under bubble in LiveArea)
set(VITA_APP_NAME "Snake C++")
# Unique ID must be exactly 9 characters. Recommended: XXXXYYYYY where X =
# unique string of developer and Y = a unique number for this app
set(VITA_TITLEID  "SNAK30000")
# Optional version string to show in LiveArea's more info screen
set(VITA_VERSION  "01.01")

## Flags and includes for building
# Note that we make sure not to overwrite previous flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fpermissive")
# Optional. You can specify more param.sfo flags this way.
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")

# Add any additional include paths here
include_directories(
  CApp
  CSnake
  CSound
  CText
  CContainer
  Headers
)

# Add any additional library paths here
# ${CMAKE_CURRENT_BINARY_DIR} lets you use any library currently being built
link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

## Build and link
# Add all the files needed to compile here
add_executable(${PROJECT_NAME}
  src/main.cpp
  CApp/CApp.cpp
  CSnake/CSnake.cpp
  CSound/CSound.cpp
  CText/CText.cpp
  CContainer/CContainer.cpp
)

# Library to link to (drop the -l prefix). This will mostly be stubs.
target_link_libraries(${PROJECT_NAME}
  SceLibKernel_stub # this line is only for demonstration. It's not needed as
                    # the most common stubs are automatically included.
  stdc++
  pthread
  SDL2
  SDL2_ttf
  SDL2_image
  SDL2_mixer
  freetype
  png
  jpeg
  webp
  pthread
  z
  FLAC
  mikmod
  mpg123
  vorbis
  ogg
  vorbisfile
  opus
  SceDisplay_stub
  SceCtrl_stub
  SceAudio_stub
  SceSysmodule_stub
  SceGxm_stub
  SceCommonDialog_stub
  SceAppMgr_stub
  SceTouch_stub
  SceHid_stub
  SceMotion_stub
  m
)

## Create Vita files
vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
# The FILE directive lets you add additional files to the VPK, the syntax is
# FILE src_path dst_path_in_vpk. In this case, we add the LiveArea paths.
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml


  FILE Resources/App/bg.jpg Resources/App/bg.jpg
  
  FILE Resources/Fonts/LCDPHONE.ttf Resources/Fonts/LCDPHONE.ttf

  FILE Resources/Food/apple.png   Resources/Food/apple.png
  FILE Resources/Food/poison.png  Resources/Food/poison.png

  FILE Resources/Snake/texBody.png Resources/Snake/texBody.png
  FILE Resources/Snake/texHead.png Resources/Snake/texHead.png
  FILE Resources/Snake/texTail.png Resources/Snake/texTail.png

  FILE Resources/Sound/collect.wav Resources/Sound/collect.wav
  FILE Resources/Sound/music.mp3 Resources/Sound/music.mp3
  FILE Resources/Sound/poison.wav Resources/Sound/poison.wav
  FILE Resources/Sound/pause.wav Resources/Sound/pause.wav
  
)
