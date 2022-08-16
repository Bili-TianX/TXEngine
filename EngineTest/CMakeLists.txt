project(EngineTest)

set(SRC_ROOT ./src)
set(SRC ${SRC_ROOT}/main.cpp)

include_directories(../TXEngine/include)

link_directories(./lib)
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} TXEngine.lib)