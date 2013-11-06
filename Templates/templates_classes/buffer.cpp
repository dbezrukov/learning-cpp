#include "buffer.h"

template <typename T, int size>
T* Buffer<T, size>::GetBuffer()
{
    return buffer;
}

template <typename T, int size>
T& Buffer<T, size>::operator[](int index)
{
    return buffer[index];
}
