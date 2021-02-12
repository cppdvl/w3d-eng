#pragma once
#include <cstdint>
    
extern "C"{
#include <glad/glad.h>
}
#include <GLFW/glfw3.h>

#include <dge/dge.h>


namespace DGE::System{

    using WindowID = uint64_t;
    class WindowManager : public DGE::GenericSingleton<WindowManager>{
        friend class GenericSingleton;
        public:
            //static const WindowManager& sGetInstance();
            const WindowID CreateWindowHND(int width, int height, const char* windowTitle);
            bool SetWindowActive(const WindowID&);
            void CloseWindow(const WindowID&);
            void CloseAllWindows();
            void ShutDown();
        private:
            WindowManager(){}

    };
    class WindowManagerGLFW : public WindowManager {
    public:
        static void* sGetGLFWwindow(const WindowID&);
    };


}
