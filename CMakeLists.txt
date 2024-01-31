cmake_minimum_required(VERSION 3.26)
project(DataAnalyseSystem)

set(CMAKE_CXX_STANDARD 17)
include_directories(./EasyX/include)
link_directories(./EasyX/lib64)
link_libraries(libeasyx.a)
add_executable(DataAnalyseSystem src/main.cpp
        src/PolyFitUtils/polyop.cpp
        src/PolyFitUtils/polyfit.cpp
        src/GuiComponents/GuiButton.cpp
        src/Screens/WelcomeScreen.cpp
        src/GuiComponents/GuiScreen.cpp
        src/Processors/UserAuthentication.cpp
        src/Processors/LifecycleProcessor.cpp
        src/UserInputHandler.cpp
        src/GuiComponents/GuiInputBox.cpp
        src/GuiComponents/GuiInputBox.cpp
        src/GuiComponents/GuiInputBox.cpp
        src/Screens/RegisterScreen.cpp
        src/GuiComponents/GuiControllers.cpp
        src/Screens/LoginScreen.cpp
        src/Screens/MainScreen.cpp
        src/Screens/DataAnalyseScreen.cpp
        src/Processors/DataAnalyseSystem.cpp
        src/Screens/DataResScreen.cpp
        src/Entities/FileEntity.cpp
        src/GuiComponents/GuiLineChart.cpp
        src/GuiComponents/GuiHistogram.cpp
        src/Processors/DataManageSystem.cpp
        src/GuiComponents/GuiLabel.cpp
        src/Screens/DataManageScreen.cpp
        src/Entities/SavedDataEntity.cpp)
