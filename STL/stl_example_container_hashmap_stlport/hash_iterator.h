#ifndef HASH_ITERATOR_H
#define HASH_ITERATOR_H 1

#include <list>

using namespace std;

template <typename Key, typename T, typename Compare, typename Hash>
class hashmap;

/// Определение класса HashIterator
template <typename Key, typename T, typename Compare, typename Hash>
class HashIterator : public std::iterator<std::bidirectional_iterator_tag, pair<const Key, T> >
{
public:
    HashIterator(); /// Двумаправленные итераторы должны содержать конструкторы по умолчанию
    HashIterator(int bucket,
                 typename list<pair<const Key, T> >::iterator listIt,
                 const hashmap<Key, T, Compare, Hash>* inHashmap);
    pair<const Key, T>& operator*() const;

    /// Тип значения возвращаемого итератором должен позволять повторное применение оператора ->
    pair<const Key, T>* operator->() const;
    /// Инкремент обычный. Инкрементирует значение и возвращает ссылку на измененный объект
    HashIterator<Key, T, Compare, Hash>& operator++();
    /// Инкремент постфиксный. Инкрементирует значение, но возвращает копию старого объекта
    const HashIterator<Key, T, Compare, Hash> operator++(int);
    /// Декремент обычный
    HashIterator<Key, T, Compare, Hash>& operator--();
    /// Декремент постфиксный
    const HashIterator<Key, T, Compare, Hash> operator--(int);

    /// Конструктор копии - по умолчанию
    /// Оператор = - по умолчанию
    /// Деструктор - по умолчанию

    /// == и != - по умолчнию
    bool operator==(const HashIterator& rhs) const;
    bool operator!=(const HashIterator& rhs) const;
 protected:
     int _bucket;
     typename list<pair<const Key, T> >::iterator _it;
     const hashmap<Key, T, Compare, Hash>* _hashmap;

     /// Вспомогательные методы для операторов ++ и --
     void increment();
     void decrement();
};

/// Разыменование итератора, созданного конструктором по умолчанию даёт неопред. результат
/// Стандартный конструктор
template <typename Key, typename T, typename Compare, typename Hash>
HashIterator<Key, T, Compare, Hash>::HashIterator()
    : _bucket( -1)
    , _it ( list<pair<const Key, T> >::iterator())
    , _hashmap( NULL )
{
}

/// Конструктор с параметрами
template <typename Key, typename T, typename Compare, typename Hash>
HashIterator<Key, T, Compare, Hash>::HashIterator(int bucket,
                                                  typename list<pair<const Key, T> >::iterator listIt,
                                                  const hashmap<Key, T, Compare, Hash>* inHashmap)
    : _bucket( bucket)
    , _it( listIt )
    ,_hashmap( inHashmap )
{
}

/// Оператор * - возвращает значение, на которое ссылается итератор
template <typename Key, typename T, typename Compare, typename Hash>
pair<const Key, T>& HashIterator<Key, T, Compare, Hash>::operator*() const
{
    return (*_it);
}

/// Оператор -> возвращает указатель на значение, компилятор сам применит к нему оператор ->
template <typename Key, typename T, typename Compare, typename Hash>
pair<const Key, T>* HashIterator<Key, T, Compare, Hash>::operator->() const
{
    return (&(*_it));
}

/// Оператор инкремента
template <typename Key, typename T, typename Compare, typename Hash>
HashIterator<Key, T, Compare, Hash>& HashIterator<Key, T, Compare, Hash>::operator++()
{
    increment();
    return (*this);
}

/// Оператор инкремента постфиксный
template <typename Key, typename T, typename Compare, typename Hash>
const HashIterator<Key, T, Compare, Hash> HashIterator<Key, T, Compare, Hash>::operator++(int)
{
    HashIterator<Key, T, Compare, Hash> oldIt = *this;
    increment();
    return (oldIt);
}

/// Оператор декремента
template <typename Key, typename T, typename Compare, typename Hash>
HashIterator<Key, T, Compare, Hash>& HashIterator<Key, T, Compare, Hash>::operator--()
{
    decrement();
    return (*this);
}

/// Оператор декремента постфиксный
template <typename Key, typename T, typename Compare, typename Hash>
const HashIterator<Key, T, Compare, Hash> HashIterator<Key, T, Compare, Hash>::operator--(int)
{
    HashIterator<Key, T, Compare, Hash> oldIt = *this;
    decrement();
    return (oldIt);
}

/// Если _it уже ссылкается на элемент, расположенный за последним элементов в таблице,
/// поведение этого кода не определено
template<typename Key, typename T, typename Compare, typename Hash>
void HashIterator<Key, T, Compare, Hash>::increment()
{
    /// _it действителен в одном сегменте, инкрементируем его
    ++_it;
    /// Если в конце сегмента, переходим к следующему непустому
    if (_it == (*_hashmap->_elems)[_bucket].end())
    {
        for (int i = _bucket + 1; i < (*_hashmap->_elems).size(); i++)
        {
            if (!((*_hashmap->_elems)[i].empty()))
            {
                /// Нашли непустой сегмент, указываем на первый элемент
                _it = (*_hashmap->_elems)[i].begin();
                _bucket = i;
                return;
            }
        }
        // Больше нет пустых сегментов, указываем на end последнего списка
        _bucket = (*_hashmap->_elems).size() - 1;
        _it = (*_hashmap->_elems)[_bucket].end();
    }
}

/// Если _it ссылается на первый элемент таблицы, поведение данного кода не определено
template<typename Key, typename T, typename Compare, typename Hash>
void HashIterator<Key, T, Compare, Hash>::decrement()
{
    /// Итератор действителен в одном сегменте. Если он ссылается на начало текущего сегмента,
    /// пытаемся найти непустой сегмент перед текущим
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
        /// Мы не в начале сегмента, просто спускаемся
        --_it;
    }
}

/// Оператор ==
template<typename Key, typename T, typename Compare, typename Hash>
bool HashIterator<Key, T, Compare, Hash>::operator==(const HashIterator& rhs) const
{
    return (_hashmap == rhs._hashmap && _bucket == rhs._bucket && _it == rhs._it );
}

/// Оператор !=
template<typename Key, typename T, typename Compare, typename Hash>
bool HashIterator<Key, T, Compare, Hash>::operator!=(const HashIterator& rhs) const
{
    return (!operator==(rhs));
}

#endif /* HASH_ITERATOR_H */
