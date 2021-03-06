cmake_minimum_required(VERSION 3.12)
project(Risk)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR /Library/Frameworks/SDL2.framework/)
set(SDL2_LIBRARY:FILEPATH=/Library/Frameworks/SDL2.framework)
set(SDL2_LIBRARY:FILEPATH=/Library/Frameworks/SDL2_ttf.framework/)

set(SDL_TTF_INCLUDE_DIRS /Library/Frameworks/SDL2_ttf.framework/)
set(SDL_TTF_LIBRARIES /Library/Frameworks/SDL2_ttf.framework)

include_directories(.)
include_directories (${SDL2_INCLUDE_DIR})

find_library(SDL2_LIBRARY SDL2)
find_library(SDL2_IMAGE_LIBRARIES SDL2_IMAGE)
find_library(SDL_TTF_LIBRARIES SDL2_ttf)

include_directories (${SDL2_INCLUDE_DIR})
include_directories (${SDL2_TTF_INCLUDE_DIR})

message(SDL_LIBRARY: ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})

add_executable(Risk main.cpp RiskGame.cpp RiskGame.h RiskPlayer.cpp RiskPlayer.h RiskTerritory.cpp RiskTerritory.h RiskMap.cpp RiskMap.h)

target_link_libraries(Risk ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL_TTF_LIBRARIES})

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})
