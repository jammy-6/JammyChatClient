CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(JammyChatClient VERSION 1.0 LANGUAGES CXX)

# qt相关配置
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# 设置c++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#windows系统动态库生成lib文件命令
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# 配置find_package的相关路径
list(APPEND  
    CMAKE_PREFIX_PATH 
    "D:/Qt/6.5.3/msvc2019_64/lib/cmake"
    "D:/Program Files/boost_1_86_0/stage/lib/cmake/Boost-1.86.0"
    "D:/repos/spdlog/build/install"
)

# 设置项目资源文件路径
set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/resource)

# 项目宏相关
configure_file(Config.h.in "${CMAKE_SOURCE_DIR}/include/Config.h")

# vs中sln文件分类
if(WIN32)
	source_group("CMake Rules"  REGULAR_EXPRESSION "^$")
    source_group("Generated Files" REGULAR_EXPRESSION "moc_.*|ui_.*|qrc_.*|mocs_.*")
	source_group("Header Files" REGULAR_EXPRESSION ".h$")
	source_group("Source Files" REGULAR_EXPRESSION ".cpp$")
    source_group("Qrc Files"    REGULAR_EXPRESSION ".qrc$")
	source_group("QML Files" 	REGULAR_EXPRESSION ".qml$")
	source_group("QSS Files" 	REGULAR_EXPRESSION ".qss$")
    source_group("Ui Files"    REGULAR_EXPRESSION ".ui$")
	source_group("zero"			REGULAR_EXPRESSION ".stamp$|.rule$")
endif()


# 设置构建类型
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RELWITHDEBINFO CACHE STRING "Build type" FORCE)
endif()


find_package(Qt6 CONFIG REQUIRED COMPONENTS Widgets Core Gui Network Quick)
find_package(Boost CONFIG REQUIRED COMPONENTS  system filesystem)
find_package(spdlog CONFIG REQUIRED)

# 设置qrc文件路径
set("${PROJECT_NAME}_resource_dir" "${CMAKE_CURRENT_SOURCE_DIR}/resource")
file(GLOB_RECURSE "${PROJECT_NAME}_qrc" "${CMAKE_SOURCE_DIR}/resource/*.qrc")

# 添加项目头文件路径
set("${PROJECT_NAME}_header_dir" "${CMAKE_CURRENT_SOURCE_DIR}/include") 
include_directories(${${PROJECT_NAME}_header_dir})

file(GLOB_RECURSE "${PROJECT_NAME}_header" "${${PROJECT_NAME}_header_dir}/*.h")

# 添加项目源文件路径
set("${PROJECT_NAME}_src_dir" "${CMAKE_CURRENT_SOURCE_DIR}/src") 
file(GLOB_RECURSE "${PROJECT_NAME}_src" "${${PROJECT_NAME}_src_dir}/*.cpp")

# 添加qml资源文件路径
file(GLOB_RECURSE "${PROJECT_NAME}_qml" "${CMAKE_SOURCE_DIR}/resource/*.qml")
message(STATUS "QML资源文件： ${${PROJECT_NAME}_qml}")

# 添加qss资源文件路径
file(GLOB_RECURSE "${PROJECT_NAME}_qss" "${CMAKE_SOURCE_DIR}/resource/*.qss")
message(STATUS "QSS资源文件： ${${PROJECT_NAME}_qss}")

# 配置各登录、注册相关窗口
add_library(
    chat_window
    SHARED
    ${${PROJECT_NAME}_qrc}
	${${PROJECT_NAME}_qml}
	${${PROJECT_NAME}_qss}
    ${CMAKE_SOURCE_DIR}/include/MoveableWidget.h
    ${CMAKE_SOURCE_DIR}/include/CustomerWidget.h
    ${CMAKE_SOURCE_DIR}/include/CustomTimerBtn.h
    ${CMAKE_SOURCE_DIR}/include/LoginWindow.h
    ${CMAKE_SOURCE_DIR}/include/RegisterSuccessHintWindow.h
    ${CMAKE_SOURCE_DIR}/include/RegisterWindow.h
    ${CMAKE_SOURCE_DIR}/include/ResetPasswordWindow.h

    ${CMAKE_SOURCE_DIR}/src/MoveableWidget.cpp
    ${CMAKE_SOURCE_DIR}/src/CustomerWidget.cpp
    ${CMAKE_SOURCE_DIR}/src/CustomTimerBtn.cpp
    ${CMAKE_SOURCE_DIR}/src/LoginWindow.cpp
    ${CMAKE_SOURCE_DIR}/src/RegisterSuccessHintWindow.cpp
    ${CMAKE_SOURCE_DIR}/src/RegisterWindow.cpp
    ${CMAKE_SOURCE_DIR}/src/ResetPasswordWindow.cpp
)
target_link_libraries(
    chat_window
    PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    spdlog::spdlog
)
target_compile_definitions(
    chat_window
    PRIVATE
    CHAT_WINDOW_LIBRARY
)

add_library(
    chat_mgr
    SHARED
    ${CMAKE_SOURCE_DIR}/include/ConfigMgr.h
    ${CMAKE_SOURCE_DIR}/include/HttpManager.h
    ${CMAKE_SOURCE_DIR}/include/TcpMgr.h

    ${CMAKE_SOURCE_DIR}/src/ConfigMgr.cpp
    ${CMAKE_SOURCE_DIR}/src/HttpManager.cpp
    ${CMAKE_SOURCE_DIR}/src/TcpMgr.cpp

)

target_link_libraries(
    chat_mgr
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Network
        Boost::filesystem
        spdlog::spdlog
)

target_compile_definitions(
    chat_mgr
    PRIVATE
    CHAT_MGR_LIBRARY
)
# 生成可执行文件
add_executable(     
    ${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/include/Controller.h
    ${CMAKE_SOURCE_DIR}/include/FriendListModel.h
    ${CMAKE_SOURCE_DIR}/include/UserManagement.h

    ${CMAKE_SOURCE_DIR}/src/GlobalTool.cpp
    ${CMAKE_SOURCE_DIR}/src/Controller.cpp
    ${CMAKE_SOURCE_DIR}/src/FriendListModel.cpp
    ${CMAKE_SOURCE_DIR}/src/UserManagement.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

# 配置链接库
target_link_libraries(
    ${PROJECT_NAME}
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        chat_window
        chat_mgr
		Qt${QT_VERSION_MAJOR}::Quick
        spdlog::spdlog
)




if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(${PROJECT_NAME})
    qt_finalize_executable(${PROJECT_NAME})
endif()
