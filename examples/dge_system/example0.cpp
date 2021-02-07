/*#include <dge/dge_system/dge_system.h>
#include <dge/dge_scene/dge_scene.h>*/
#include <dge/dge.h>
/*
extern "C"{
#include <glad/glad.h>
}
#include <GLFW/glfw3.h>
void processInput(GLFWwindow* pW){

}
*/
int main(){
    
    auto e = DGE::Engine::sGetInstance();
    e.Start();

    auto s = DGE::Scene{};
    e.PushScene(&s);
    e.Run();


    e.ShutDown();
    return 0;

}
