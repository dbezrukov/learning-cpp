#ifndef DEFAULT_HASH_H
#define DEFAULT_HASH_H 1

#include <stdexcept>

using namespace std;

/// Класс хеширования
template <typename T> /// Шаблонизируем по типу ключа который он хеширует, H(key)=bucket
class DefaultHash
{
public:
    DefaultHash(int numBuckets = 101) throw (invalid_argument);
    int hash(const T& key) const; /// Хеш функция
    int getNumBuckets() const
    {
        return _numBuckets;
    }
protected:
    int _numBuckets;
};

//#include "default_hash.cpp"

template <typename T>
DefaultHash<T>::DefaultHash(int numBuckets) throw (invalid_argument)
{
    if ( numBuckets <= 0 )
    {
        throw( invalid_argument("numBuckets must be > 0") );
    }
    _numBuckets = numBuckets;
}

/// Ключ -последовательность байтов, ASCII зачения суммируются, потом делятся по модулю
template <typename T>
int DefaultHash<T>::hash(const T& key) const
{
    int bytes = sizeof(key);
    unsigned long res = 0;
    for (int i=0; i<bytes; ++i)
    {
        res += *( (char*)&key + i );
    }
    return ( res % _numBuckets );
}


#endif /* DEFAULT_HASH_H */

