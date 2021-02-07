#include <functional>
#include <dge/dge_system/dge_system.h>

namespace DGE {

  class Scene {
    GLFWwindow* mpweakWindow{nullptr};

  protected:

  public:
    std::function<void()> mfInit {[&](){ return; }};
    std::function<void()> mfFinish {[&](){ return; }};
    std::function<void()> mfUpdate {[&](){ return; }};
    std::function<void()> mfInput {[&](){ return; }};
    std::function<void()> mfRender{[&](){ return; }};
    Scene();

  };







}



