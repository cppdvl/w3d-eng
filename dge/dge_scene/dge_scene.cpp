
#include "dge_scene.h"

static GLFWwindow* mpweakWindow{nullptr};
void default_init(){
    return;
}
void default_finish(){
    return;
}
void default_update(){
    return;
}
void default_input(){
    return;
}
void default_render(){

    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    return;
}
DGE::Scene::Scene()  {

    mfInit = default_init;
    mfFinish = default_finish;
    mfUpdate = default_update;
    mfInput = default_input;
    mfRender = default_render;

}