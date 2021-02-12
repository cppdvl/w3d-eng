#include <dge/dge.h>

namespace DGE::Render {

    using ArrayOfVBOs = std::vector<unsigned int>

    class ObjectArrayTree : public std::vector<ArrayOfVBOs> /*vector of VBOs */ {

        unsigned int mVao{0};

    }; 

    class ShaderTree : public std::vector<ObjectArrayTree>{
    
    };
    
    class Camera{

    };
    
    class ViewPort : public std::vector<ShaderTree>{
    
    };
    
    class RenderTree : public std::vector<ViewPort>{

    };



    class Manager : public DGE::GenericSingleton<Manager> {



    };

}