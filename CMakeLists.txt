CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
PROJECT(JammyChatClient VERSION 1.0 LANGUAGES CXX)


# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置项目资源文件路径
set(RESOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/resource)
message(STATUS "RESOURCE_DIR  = ${RESOURCE_DIR}")
# 项目宏相关
configure_file(Config.h.in Config.h)
include_directories(${CMAKE_BINARY_DIR})

# vs中sln文件分类
if(WIN32)
	source_group("CMake Rules"  REGULAR_EXPRESSION "^$")
    source_group("Generated Files" REGULAR_EXPRESSION "moc_.*|ui_.*|qrc_.*|mocs_.*")
	source_group("Header Files" REGULAR_EXPRESSION ".h$")
	source_group("Source Files" REGULAR_EXPRESSION ".cpp$")
    source_group("Qrc Files"    REGULAR_EXPRESSION ".qrc$")
    source_group("Ui Files"    REGULAR_EXPRESSION ".ui$")
	source_group("zero"			REGULAR_EXPRESSION ".stamp$|.rule$")
endif()

# 设置构建类型
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RELWITHDEBINFO CACHE STRING "Build type" FORCE)
endif()



# 由于生成的C++文件都是放在编译目录里的（在Shadow Building中有别于源码目录），
# 所以还需要将编译目录包含到Include目录，否则编译器会找不到这些头文件：
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 没有添加环境变量时需要加入下面这句
set(Qt5_ROOT "D:/Program Files/Qt5.12.12/5.12.12/msvc2017_64")
find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui Network Charts )

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

MESSAGE(STATUS "=================================================================")
if(DEFINED Qt5_FOUND)
    MESSAGE(STATUS "find Qt5_FOUND: ${Qt5_DIR}")
    MESSAGE(STATUS "find Qt5_FOUND: ${Qt5_FOUND}")
    MESSAGE(STATUS "Qt5Widgets_INCLUDE_DIRS: ${Qt5Widgets_INCLUDE_DIRS}")
    MESSAGE(STATUS "Qt5Gui_INCLUDE_DIRS: ${Qt5Gui_INCLUDE_DIRS}")
    MESSAGE(STATUS "Qt5Core_INCLUDE_DIRS: ${Qt5Core_INCLUDE_DIRS}")
    MESSAGE(STATUS "Qt5Network_INCLUDE_DIRS: ${Qt5Network_INCLUDE_DIRS}")
    MESSAGE(STATUS "Qt5Charts_INCLUDE_DIRS: ${Qt5Charts_INCLUDE_DIRS}")
else()
    MESSAGE(STATUS "not find Qt5_FOUND: ${Qt5_FOUND}")
endif()
MESSAGE(STATUS "=================================================================")


#添加qt包include头文件
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})
include_directories(${Qt5Charts_INCLUDE_DIRS})

# 设置qrc文件路径
set("${PROJECT_NAME}_resource_dir" "${CMAKE_CURRENT_SOURCE_DIR}/resource")
file(GLOB_RECURSE "${PROJECT_NAME}_qrc" "${${PROJECT_NAME}_resource_dir}/*.qrc")
set(Qrc_Files
        ${${PROJECT_NAME}_qrc}
)
MESSAGE(STATUS "Qrc_Files = ${Qrc_Files}")

# 设置ui文件路径
set("${PROJECT_NAME}_ui_dir" "${CMAKE_CURRENT_SOURCE_DIR}/ui")
file(GLOB_RECURSE "${PROJECT_NAME}_ui" "${${PROJECT_NAME}_ui_dir}/*.ui")
set(Ui_Files
        ${${PROJECT_NAME}_ui}
)
MESSAGE(STATUS "Ui_Files: ${Ui_Files}")


set(Boost_NO_SYSTEM_PATHS ON)
# 查找 Boost 库
set(BOOST_ROOT "D:/Program Files/boost_1_80_0/stage/lib/cmake")
find_package(Boost REQUIRED COMPONENTS  system filesystem)
MESSAGE(STATUS "=================================================================")
if(DEFINED Boost_FOUND)
    message(STATUS "Boost version: ${Boost_VERSION}")
    message(STATUS "Boost include dirs: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost library dirs: ${Boost_LIBRARY_DIRS}")
    message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
else ()
    message(STATUS "Boost Not Found!!!")
endif ()
MESSAGE(STATUS "=================================================================")
 # 包含 Boost 头文件
include_directories(${Boost_INCLUDE_DIRS})
message(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")



# 添加项目头文件路径
set("${PROJECT_NAME}_include_dir" "${CMAKE_CURRENT_SOURCE_DIR}/include") 
include_directories(${${PROJECT_NAME}_include_dir})
file(GLOB_RECURSE "${PROJECT_NAME}_include" "${${PROJECT_NAME}_include_dir}/*.h")

# 添加项目源文件路径
set("${PROJECT_NAME}_src_dir" "${CMAKE_CURRENT_SOURCE_DIR}/src") 
file(GLOB_RECURSE "${PROJECT_NAME}_src" "${${PROJECT_NAME}_src_dir}/*.cpp")

# 生成可执行文件
add_executable(     
    ${PROJECT_NAME}
    ${${PROJECT_NAME}_src}
    ${${PROJECT_NAME}_include}
    ${${PROJECT_NAME}_ui}
    ${${PROJECT_NAME}_qrc}
)

# 配置链接库
target_link_libraries(
    ${PROJECT_NAME}
        PUBLIC
        Qt5::Widgets
        Qt5::Core
        Qt5::Gui
        Qt5::Network
        ${Boost_LIBRARIES}
        Boost::filesystem

)
