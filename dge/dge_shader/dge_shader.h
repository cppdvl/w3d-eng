#pragma once
#include <vector>
namespace DGE::Asset {

    class Shader {
        std::string mVtx{}, mFrg{};
    public:
        Shader(const std::string& vertexShader, const std::string& fragmentShader) : mVtx(vertexShader), mFrg(fragmentShader){
        }
        auto GetVertexShader() -> const char* { return mVtx.data(); }
        auto GetFragmentShader() -> const char* { return mFrg.data(); }
    };

}




