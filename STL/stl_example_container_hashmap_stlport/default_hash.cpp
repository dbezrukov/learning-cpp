#include "default_hash.h"

/// ��������� ������������� ������ hash ��� ���� string
template<>
int DefaultHash<string>::hash(const string& key) const
{
    int sum = 0; /// ��������� �������� ���� �������� � ������
    for (size_t i = 0; i < key.size(); ++i)
    {
        sum += key[i];
    }
    return ( sum % _numBuckets );
}
