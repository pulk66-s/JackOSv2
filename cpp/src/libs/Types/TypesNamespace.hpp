#ifndef __JACKOS_LIBS_TYPES_TYPESNAMESPACE_HPP__
    #define __JACKOS_LIBS_TYPES_TYPESNAMESPACE_HPP__

namespace JO::Libs::Types
{
    namespace String
    {
        class AString;
        class HeapString;
    }

    namespace Array
    {
        template <typename T>
        class AArray;

        template <typename T>
        class HeapArray;
    }
}

#endif