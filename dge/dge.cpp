#include "dge.h"


#include <spdlog/spdlog.h>

void DGE::Engine::Run(){

    for (auto pweakScene : mpweakScenes){
        pweakScene->mfInit();
    }

    while (!glfwWindowShouldClose(mpWindow)){
        glfwSetWindowShouldClose(mpWindow, glfwGetKey(mpWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS);

        for (const auto& pweakScene : mpweakScenes){
            pweakScene->mfUpdate();
            pweakScene->mfInput();
            pweakScene->mfRender();
        }

        glfwSwapBuffers(mpWindow);
        glfwPollEvents();
    }

    for (auto pweakScene : mpweakScenes){
        pweakScene->mfFinish();
    }

}

DGE::Engine::Engine()
{}

void DGE::Engine::PushScene(DGE::Scene* pScene){

    if (std::any_of(mpweakScenes.cbegin(), mpweakScenes.cend(), [&pScene](auto& pweakScene){
        return pweakScene == pScene;
    })){
        spdlog::warn("SceneID: 0x{:x} was already pushed in.", (uint64_t)pScene);
        return;
    }

    mpweakScenes.emplace_back(pScene);
    spdlog::info("SceneID: 0x{:x} is been pushed.", (uint64_t)pScene);


}

void DGE::Engine::Start(){

    auto windowManager = DGE::System::WindowManager::sGetInstance();
    auto windowID = windowManager.CreateWindowHND(1600, 900, "1600x900");
    windowManager.SetWindowActive(windowID);
    mpWindow = reinterpret_cast<GLFWwindow*>(DGE::System::WindowManagerGLFW::sGetGLFWwindow(windowID));


}


void DGE::Engine::ShutDown(){
    auto windowManager = DGE::System::WindowManager::sGetInstance();
    windowManager.ShutDown();
}
