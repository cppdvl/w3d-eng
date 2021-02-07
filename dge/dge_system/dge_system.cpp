#include <map>
#include <mutex>
#include <vector>
#include <utility>
#include <functional>
#include <spdlog/spdlog.h>

#include "dge_system.h"
#include <iostream>


using namespace DGE::System;
std::map<WindowID, GLFWwindow*> id_window{
    std::make_pair(0, nullptr)
};

std::map<WindowID, std::function<void(GLFWwindow*)>> id_processInput {
    std::make_pair(0, [](GLFWwindow*){})
};

/*const WindowManager& WindowManager::sGetInstance(){
    static WindowManager sWindowManager;
    return sWindowManager;
}*/
std::once_flag uniqueGLFWInitialization;
void sWindowResizeCallback(GLFWwindow* ptrWindow, int width, int height){
    glViewport(0, 0, width>>1, height>>1);
    std::cout << width << " x " << height << std::endl;
}
static WindowID __wid;
const DGE::System::WindowID DGE::System::WindowManager::CreateWindowHND(int width, int height, const char* windowTitle){

    std::call_once(uniqueGLFWInitialization, []()->void {
        spdlog::info("Unique Intialization of GLFW.");
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        spdlog::info("Finished GLFW Initialization.");
    });

    auto ptrWindow = glfwCreateWindow(width, height, windowTitle, nullptr, nullptr);
    if (!ptrWindow){
        spdlog::critical("glfwCreateWindow {:s}:{:d}", __FILE__, __LINE__);
        __wid = 0;
        return 0;
    }

    auto id_window_bind = std::make_pair((WindowID)ptrWindow, ptrWindow);
    id_window.insert(id_window_bind);
    spdlog::info("WindowID => '{:s}' : {:d} [@0x{:x}]", windowTitle, id_window_bind.first, (WindowID)id_window_bind.second);
    glfwSetFramebufferSizeCallback(ptrWindow, sWindowResizeCallback);
    __wid = (WindowID)ptrWindow;
    return __wid;
}
std::once_flag uniqueGladInitialization;
bool WindowManager::SetWindowActive(const WindowID& windowID){
    if(id_window.find(windowID) == id_window.cend()){
        spdlog::critical("Window ID is not registered!!! {:d}", windowID);
        return false;
    }

    auto ptrWindow = id_window[windowID];
    glfwMakeContextCurrent(ptrWindow);
    bool gladInitResult {true};
    std::call_once(uniqueGladInitialization, [&](){
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            spdlog::critical("Glad opengl function pointers lib, {:s}:{:d} it's fucked.", __FILE__, __LINE__);
            gladInitResult = false;
        }
        else {
            gladInitResult = true;
            glEnable(GL_CULL_FACE);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
    });
    return gladInitResult;
}
void WindowManager::CloseWindow(const WindowID& windowID){
    auto idFound = id_window.find(windowID) != id_window.cend();
    if (idFound){
        auto windowPtr = id_window[windowID];
        id_window.erase(windowID);
        glfwDestroyWindow(windowPtr);
    }
}
void WindowManager::CloseAllWindows(){
    for (auto k_v : id_window){
        auto ptrWindow = k_v.second;
        glfwDestroyWindow(ptrWindow);
    }
    id_window.clear();
}
void WindowManager::ShutDown(){
    glfwTerminate();
}




void* WindowManagerGLFW::sGetGLFWwindow(const WindowID& wid){
    if (id_window.find(wid) != id_window.end())  return id_window[wid];
    return nullptr;
}