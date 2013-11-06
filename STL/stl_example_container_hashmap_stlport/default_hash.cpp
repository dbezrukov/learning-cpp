#include "default_hash.h"

/// частичная специализация метода hash для типа string
template<>
int DefaultHash<string>::hash(const string& key) const
{
    int sum = 0; /// Суммируем значения всех символов в строке
    for (size_t i = 0; i < key.size(); ++i)
    {
        sum += key[i];
    }
    return ( sum % _numBuckets );
}
