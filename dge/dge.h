#pragma once
#include <vector>
#include <dge/dge_scene/dge_scene.h>
#include <dge/dge_system/dge_system.h>

namespace DGE {
    class Engine : public GenericSingleton<Engine>{
        friend class GenericSingleton;
        GLFWwindow* mpWindow;
        std::vector<DGE::Scene*> mpweakScenes;
        Engine();
    public:
        void Start();
        void Run();
        void Pause();
        void PushScene(DGE::Scene*);
        void ShutDown();
    };

}