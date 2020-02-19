#include <Graphyte/Hash/FNV.hxx>

namespace Graphyte::Hash
{
    static_assert(HashFnv1A32::FromString("") == 0x811c9dc5);
    static_assert(HashFnv1A32::FromString("graphyte") == 0x800b92dd);
    static_assert(HashFnv1A32::FromString("engine") == 0xee05d83b);


    static_assert(HashFnv1A64::FromString("") == 0xcbf29ce484222325);
    static_assert(HashFnv1A64::FromString("graphyte") == 0xa2f92f8a595d627d);
    static_assert(HashFnv1A64::FromString("engine") == 0x3dacd07fc0cad3db);
}
