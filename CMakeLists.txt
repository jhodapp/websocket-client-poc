cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(WebsocketClientPoc VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(websocket_client_poc.h.in websocket_client_poc.h)

# add the executable
add_executable(WebsocketClientPoc main.cpp)

target_link_libraries(WebsocketClientPoc PUBLIC /usr/local/lib/oatpp-1.1.0/liboatpp.a)

target_include_directories(WebsocketClientPoc PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

install(TARGETS WebsocketClientPoc DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/websocket_client_poc.h"
  DESTINATION include
  )
