#ifndef HASH_ITERATOR_H
#define HASH_ITERATOR_H 1

#include <list>

using namespace std;

template <typename Key, typename T, typename Compare, typename Hash>
class hashmap;

/// ����������� ������ HashIterator
template <typename Key, typename T, typename Compare, typename Hash>
class HashIterator : public std::iterator<std::bidirectional_iterator_tag, pair<const Key, T> >
{
public:
    HashIterator(); /// ��������������� ��������� ������ ��������� ������������ �� ���������
    HashIterator(int bucket,
                 typename list<pair<const Key, T> >::iterator listIt,
                 const hashmap<Key, T, Compare, Hash>* inHashmap);
    pair<const Key, T>& operator*() const;

    /// ��� �������� ������������� ���������� ������ ��������� ��������� ���������� ��������� ->
    pair<const Key, T>* operator->() const;
    /// ��������� �������. �������������� �������� � ���������� ������ �� ���������� ������
    HashIterator<Key, T, Compare, Hash>& operator++();
    /// ��������� �����������. �������������� ��������, �� ���������� ����� ������� �������
    const HashIterator<Key, T, Compare, Hash> operator++(int);
    /// ��������� �������
    HashIterator<Key, T, Compare, Hash>& operator--();
    /// ��������� �����������
    const HashIterator<Key, T, Compare, Hash> operator--(int);

    /// ����������� ����� - �� ���������
    /// �������� = - �� ���������
    /// ���������� - �� ���������

    /// == � != - �� ��������
    bool operator==(const HashIterator& rhs) const;
    bool operator!=(const HashIterator& rhs) const;
 protected:
     int _bucket;
     typename list<pair<const Key, T> >::iterator _it;
     const hashmap<Key, T, Compare, Hash>* _hashmap;

     /// ��������������� ������ ��� ���������� ++ � --
     void increment();
     void decrement();
};

/// ������������� ���������, ���������� ������������� �� ��������� ��� �������. ���������
/// ����������� �����������
template <typename Key, typename T, typename Compare, typename Hash>
HashIterator<Key, T, Compare, Hash>::HashIterator()
    : _bucket( -1)
    , _it ( list<pair<const Key, T> >::iterator())
    , _hashmap( NULL )
{
}

/// ����������� � �����������
template <typename Key, typename T, typename Compare, typename Hash>
HashIterator<Key, T, Compare, Hash>::HashIterator(int bucket,
                                                  typename list<pair<const Key, T> >::iterator listIt,
                                                  const hashmap<Key, T, Compare, Hash>* inHashmap)
    : _bucket( bucket)
    , _it( listIt )
    ,_hashmap( inHashmap )
{
}

/// �������� * - ���������� ��������, �� ������� ��������� ��������
template <typename Key, typename T, typename Compare, typename Hash>
pair<const Key, T>& HashIterator<Key, T, Compare, Hash>::operator*() const
{
    return (*_it);
}

/// �������� -> ���������� ��������� �� ��������, ���������� ��� �������� � ���� �������� ->
template <typename Key, typename T, typename Compare, typename Hash>
pair<const Key, T>* HashIterator<Key, T, Compare, Hash>::operator->() const
{
    return (&(*_it));
}

/// �������� ����������
template <typename Key, typename T, typename Compare, typename Hash>
HashIterator<Key, T, Compare, Hash>& HashIterator<Key, T, Compare, Hash>::operator++()
{
    increment();
    return (*this);
}

/// �������� ���������� �����������
template <typename Key, typename T, typename Compare, typename Hash>
const HashIterator<Key, T, Compare, Hash> HashIterator<Key, T, Compare, Hash>::operator++(int)
{
    HashIterator<Key, T, Compare, Hash> oldIt = *this;
    increment();
    return (oldIt);
}

/// �������� ����������
template <typename Key, typename T, typename Compare, typename Hash>
HashIterator<Key, T, Compare, Hash>& HashIterator<Key, T, Compare, Hash>::operator--()
{
    decrement();
    return (*this);
}

/// �������� ���������� �����������
template <typename Key, typename T, typename Compare, typename Hash>
const HashIterator<Key, T, Compare, Hash> HashIterator<Key, T, Compare, Hash>::operator--(int)
{
    HashIterator<Key, T, Compare, Hash> oldIt = *this;
    decrement();
    return (oldIt);
}

/// ���� _it ��� ���������� �� �������, ������������� �� ��������� ��������� � �������,
/// ��������� ����� ���� �� ����������
template<typename Key, typename T, typename Compare, typename Hash>
void HashIterator<Key, T, Compare, Hash>::increment()
{
    /// _it ������������ � ����� ��������, �������������� ���
    ++_it;
    /// ���� � ����� ��������, ��������� � ���������� ���������
    if (_it == (*_hashmap->_elems)[_bucket].end())
    {
        for (int i = _bucket + 1; i < (*_hashmap->_elems).size(); i++)
        {
            if (!((*_hashmap->_elems)[i].empty()))
            {
                /// ����� �������� �������, ��������� �� ������ �������
                _it = (*_hashmap->_elems)[i].begin();
                _bucket = i;
                return;
            }
        }
        // ������ ��� ������ ���������, ��������� �� end ���������� ������
        _bucket = (*_hashmap->_elems).size() - 1;
        _it = (*_hashmap->_elems)[_bucket].end();
    }
}

/// ���� _it ��������� �� ������ ������� �������, ��������� ������� ���� �� ����������
template<typename Key, typename T, typename Compare, typename Hash>
void HashIterator<Key, T, Compare, Hash>::decrement()
{
    /// �������� ������������ � ����� ��������. ���� �� ��������� �� ������ �������� ��������,
    /// �������� ����� �������� ������� ����� �������
    if (_it == (*_hashmap->_elems)[_bucket].begin())
    {
        for (int i = _bucket - 1; i >= 0; --i)
        {
            if (!((*_hashmap->_elems)[i].empty()))
            {
                _it = (*_hashmap->_elems)[i].end();
                --_it;
                _bucket = i;
                return;
            }
        }
        _it = (*_hashmap->_elems)[0].begin();
        --_it;
        _bucket = 0;
    }
    else
    {
        /// �� �� � ������ ��������, ������ ����������
        --_it;
    }
}

/// �������� ==
template<typename Key, typename T, typename Compare, typename Hash>
bool HashIterator<Key, T, Compare, Hash>::operator==(const HashIterator& rhs) const
{
    return (_hashmap == rhs._hashmap && _bucket == rhs._bucket && _it == rhs._it );
}

/// �������� !=
template<typename Key, typename T, typename Compare, typename Hash>
bool HashIterator<Key, T, Compare, Hash>::operator!=(const HashIterator& rhs) const
{
    return (!operator==(rhs));
}

#endif /* HASH_ITERATOR_H */
