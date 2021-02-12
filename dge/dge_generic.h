

namespace DGE {

    template <typename T>
    class GenericSingleton {
    public:
        static const T& sGetinstance (){
            static const T t{};
            return t;
        }        
    };

}
