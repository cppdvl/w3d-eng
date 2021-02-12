#pragma once

#include <array>
#include <sstream>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>



namespace DGE::Primitive {

    template <int T>
    class Mesh : public std::array<float, T*9> {
    public:
        void LogInfo(){
            spdlog::info("Generating a mesh with the following triangles:");
            auto arr = static_cast<std::array<float, T*9>>(*this);
            for (auto index = 0; index < T*9; index += 3){
                auto& arrayref = *this;
                auto vidx = index / 3;                
                if (vidx % 9 == 0) spdlog::info("TRNG [{:02d}]: VTXs [{:02d} - {:02d}]  ", index / 9, vidx, vidx + 2 );
                spdlog::info("    VTX [{:02d}] {:0.3f}, {:0.3f}, {:0.3f}", vidx, arrayref[index + 0], arrayref[index + 1], arrayref[index + 2]);//  {  }", vidx / 3, );
            }
        }        
    };
    using Triangle = Mesh<1>;

    /*class Triangle : public Mesh<1> {
        
    }; 

    class Rectangle : public Mesh<2> {

    };*/

}


