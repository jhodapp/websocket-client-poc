cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(WebsocketClientPoc VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(websocket_client_poc.h.in websocket_client_poc.h)

include_directories(src)

## link libs
find_package(oatpp              1.1.0 REQUIRED)
find_package(oatpp-websocket    1.1.0 REQUIRED)

#include_directories(${OATP_WEBSOCKET_INCLUDE_DIR})
include_directories("/usr/local/include/oatpp-1.1.0/oatpp")
include_directories("/usr/local/include/oatpp-1.1.0/oatpp-websocket")

add_library(websocket_client_poc-lib
        src/WSListener.cpp
        src/WSListener.hpp
)

# add the executable
add_executable(websocket_client_poc src/main.cpp)


target_link_libraries(websocket_client_poc
	PRIVATE websocket_client_poc-lib
	PUBLIC oatpp::oatpp
	PUBLIC oatpp::oatpp-test
	PUBLIC oatpp::oatpp-websocket
)

target_include_directories(websocket_client_poc PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

install(TARGETS websocket_client_poc DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/websocket_client_poc.h"
  DESTINATION include
  )
