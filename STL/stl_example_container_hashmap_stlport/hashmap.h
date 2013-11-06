#ifndef _STL_HASHMAP_H
#define _STL_HASHMAP_H 1

#include <vector>

#include "default_hash.h"
#include "hash_iterator.h"

using namespace std;

template <typename Key, /// Тип ключа
          typename T,   /// Тип значения
          typename Compare = std::equal_to<Key>, /// Объект сравнения примен. для обнаруж. попыток вставки ключей-дубликатов
          typename Hash = DefaultHash<Key> >
class hashmap
{

public:
    /// Данные три typedef-определения требуеются для ассоциативного контейнера STL
    typedef Key key_type;  /// тип ключа для которого реализуется контейнер
    typedef Compare key_compare; /// класс сравоения
    typedef pair<const Key, T> value_type; /// тип элемента хранимого в контейнере
    typedef T mapped_type; /// тип значения
    typedef pair<const Key, T>& reference; /// ссылка на тип элемента, хранимого в контейнере
    typedef const pair<const Key, T>& const_reference; /// ссылка на const-тип элемента хран в контейнере
    typedef size_t size_type; /// тип позволяющий представить количество эл-тов в контейнере
    typedef ptrdiff_t difference_type; /// тип позволяющий представить разность двух итераторов контейнера
    typedef HashIterator<Key, T, Compare, Hash> iterator;
    typedef HashIterator<Key, T, Compare, Hash> const_iterator;

    /// требуемое определение класса сравнения для ассоциативных контейнеров
    class value_compare : public std::binary_function<value_type, value_type, bool>
    {
        friend class hashmap<Key, T, Compare, Hash>;
    public:
        bool operator()(const value_type& x, const value_type& y) const
        {
            return _comp(x.first, y.first);
        }
    protected:
        Compare _comp;
        value_compare(Compare comp)
            : _comp( comp )
        {
        }
    };

    /// Конструктор
    explicit hashmap(const Compare& comp = Compare(),
                     const Hash& hash = Hash()) throw (invalid_argument);

    /// Конструктор с итераторным диапазоном
    template <class InputIterator>
    hashmap(InputIterator first, InputIterator last,
            const Compare& comp = Compare(),
            const Hash& hash = Hash()) throw (invalid_argument);

    /// Деструктор, конструктор копии, оператор присваивания
    ~hashmap()
    {
        delete _elems;
    }
    hashmap(const hashmap<Key, T, Compare, Hash>& src);
    hashmap<Key, T, Compare, Hash>& operator=(const hashmap<Key, T, Compare, Hash>& rhs);

    friend class HashIterator<Key, T, Compare, Hash>;

    /// STL ИТЕРАТОРНЫЕ МЕТОДЫ ДОСТУПА
    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    /// STL МЕТОДЫ ОПЕРЕДЕЛЕНИЯ РАЗМЕРОВ
    bool empty() const { return ( _size == 0 ); };
    size_type size() const { return ( _size ); };
    /// В худшем случае все элементы попадут в идин список, поэтому возвращаем длину одного списка
    size_type max_size() const { return (*_elems)[0].max_size(); };

    /// МЕТОДЫ ВСТАВКИ ЭЛЕМЕНТОВ
    T& operator[](const key_type& x);
    pair<iterator, bool> insert(const value_type& x);
    iterator insert(iterator position, const value_type& x);
    template <class InputIterator>
    void insert(InputIterator first, InputIterator last);

    /// Метод удаления элемента, если такой существует. По ключу
    void erase(iterator position);
    size_type erase(const key_type& x);
    void erase(iterator first, iterator last);

    /// Другие модифицирующие утилиты
    void swap(hashmap<Key, T, Compare, Hash>& hashIn);
    void clear();

    /// STL МЕТОДЫ ДОСТУПА
    key_compare key_comp() const;
    value_compare value_comp() const;

    /// МЕТОДЫ ПОИСКА
    iterator find(const key_type& x);
    const_iterator find(const key_type& x) const;
    size_type count(const key_type& x) const;

protected:
    typedef list<value_type> ListType;
    vector<ListType>* _elems; /// указатель сужит для того чтобы реализовать метод swap
    size_type _size;
    Compare _comp;
    Hash _hash;

    /// Вспомогательный метод для поиска
    typename ListType::iterator findElement(const key_type& x, int& bucket) const;
};

/// Стандартный конструктор
template <typename Key, typename T, typename Compare, typename Hash >
hashmap<Key, T, Compare, Hash>::hashmap(const Compare& comp, const Hash& hash) throw (invalid_argument)
    : _size( 0 )
    , _comp( comp )
    , _hash( hash )
{
    if ( _hash.getNumBuckets() <= 0 )
    {
        throw( invalid_argument("Segments number must be > 0 ") );
    }
    /// Создать набор сегментов для отображения значений
    _elems = new vector<ListType>(_hash.getNumBuckets());
}

/*
/// Деструктор
template <typename Key, typename T, typename Compare, typename Hash >
hashmap<Key, T, Compare, Hash>::~hashmap<Key, T, Compare, Hash>()
{
    delete _elems;
}
*/

/// Конструктор с итераторным диапазоном
template <typename Key, typename T, typename Compare, typename Hash >
template <class InputIterator>
hashmap<Key, T, Compare, Hash>::hashmap(InputIterator first, InputIterator last,
                                        const Compare& comp, const Hash& hash) throw (invalid_argument)
    : _size( 0 )
    , _comp( comp )
    , _hash( hash )
{
    if ( _hash.getNumBuckets() <= 0 )
    {
        throw( invalid_argument("Segments number must be > 0 ") );
    }
    /// Создать набор сегментов для отображения значений
    _elems = new vector<ListType>(_hash.getNumBuckets());
    insert(first, last);
}



/// Конструктор копирования
template <typename Key, typename T, typename Compare, typename Hash >
hashmap<Key, T, Compare, Hash>::hashmap(const hashmap<Key, T, Compare, Hash>& src)
    : _size( src._size )
    , _comp( src._comp )
    , _hash( src._hash )
{
    /// используем конструктор копирования вектора
    _elems = new vector<ListType>( *(src._elems) );
}

/// Оператор=
template <typename Key, typename T, typename Compare, typename Hash >
hashmap<Key, T, Compare, Hash>&
hashmap<Key, T, Compare, Hash>::operator=(const hashmap<Key, T, Compare, Hash>& rhs)
{
    /// проверяем на самоприсваивание
    if ( this == &rhs )
        return *this;

    _size = rhs._size;
    _comp = rhs._comp;
    _hash = rhs._hash;

    /// копируем вектор данных
    delete _elems;
    _elems = new vector<ListType>( *(rhs._elems) );

    return *this;
}

/// Обмен значениями
template <typename Key, typename T, typename Compare, typename Hash >
void hashmap<Key, T, Compare, Hash>::swap(hashmap<Key, T, Compare, Hash>& hashIn)
{
    //void swap ( T& a, T& b ) { T c(a); a=b; b=c; }
    std::swap(*this, hashIn);
}

/// Вспомогательная функция поиска
template <typename Key, typename T, typename Compare, typename Hash >
typename list<pair<const Key, T> >::iterator
hashmap<Key, T, Compare, Hash>::findElement(const key_type& x, int& bucket) const
{
    /// Хешируем ключ для получения нужного сегмента
    bucket = _hash.hash( x );

    /// Находим элемент по заданному ключу в конкретном сегменте
    for (typename ListType::iterator it = (*_elems)[bucket].begin(); it != (*_elems)[bucket].end(); ++it)
    {
        /// Взяли очередную пару ключ-значение
        pair<const Key, T> pairFound = *it;
        /// Если совпадают -возвращаем
        if ( _comp(pairFound.first, x ))
        {
            return it;
        }
    }
    /// PS можно искать и find_if, но придется писать функтор для сравнения pair.first и x
    /// Возвращаем итератор на конец вектора, если элемент не найден
    return ((*_elems)[bucket].end());
}

/// Функция поиска
template <typename Key, typename T, typename Compare, typename Hash >
typename hashmap<Key, T, Compare, Hash>::iterator hashmap<Key, T, Compare, Hash>::find(const key_type& x)
{
    int bucket;
    /// Используем вспомогательный метод findElement
    typename ListType::iterator it = findElement(x, bucket);
    if (it == (*_elems)[bucket].end())
    {
        return (end());
    }
    return (HashIterator<Key, T, Compare, Hash>(bucket, it, this));
}

template <typename Key, typename T, typename Compare, typename Hash >
typename hashmap<Key, T, Compare, Hash>::const_iterator hashmap<Key, T, Compare, Hash>::find(const key_type& x) const
{
    int bucket;
    /// Используем вспомогательный метод findElement
    typename ListType::iterator it = findElement(x, bucket);
    if (it == (*_elems)[bucket].end())
    {
        return (end());
    }
    return (HashIterator<Key, T, Compare, Hash>(bucket, it, this));
}

template <typename Key, typename T, typename Compare, typename Hash >
typename hashmap<Key, T, Compare, Hash>::size_type hashmap<Key, T, Compare, Hash>::count(const key_type& x) const
{
    if ( find(x) == end() )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/// Оператор индексирования. Если нужный элемент не найден, он добавляется
template <typename Key, typename T, typename Compare, typename Hash >
T& hashmap<Key, T, Compare, Hash>::operator[](const key_type& x)
{
    return (((insert(make_pair(x, T()))).first)->second);
}

/// Вставка элементов
template <typename Key, typename T, typename Compare, typename Hash >
pair<typename hashmap<Key, T, Compare, Hash>::iterator, bool>
hashmap<Key, T, Compare, Hash>::insert(const value_type& x)
{
    int bucket;
    /// Пробуем найти
    typename ListType::iterator it = findElement(x.first, bucket);
    /// Элемент уже существует
    if ( it != (*_elems)[bucket].end() )
    {
        /// преобразуем list-итератор в HashIterator
        HashIterator<Key, T, Compare, Hash> newIt(bucket, it, this);
        pair<HashIterator<Key, T, Compare, Hash>, bool> p(newIt, true);
        return (p);
    }
    else
    {
        _size++;

        typename ListType::iterator endIt = (*_elems)[bucket].insert((*_elems)[bucket].end(), x);
        pair<HashIterator<Key, T, Compare, Hash>, bool>
        p(HashIterator<Key, T, Compare, Hash>(bucket, endIt, this), true);
        return (p);
    }
}

template <typename Key, typename T, typename Compare, typename Hash >
typename hashmap<Key, T, Compare, Hash>::iterator
hashmap<Key, T, Compare, Hash>::insert(typename hashmap<Key, T, Compare, Hash>::iterator position,
                                       const value_type& x)
{
    return (insert(x).first);
}

template <typename Key, typename T, typename Compare, typename Hash >
template <class InputIterator>
void hashmap<Key, T, Compare, Hash>::insert(InputIterator first, InputIterator last)
{
    insert_iterator<hashmap<Key, T, Compare, Hash> > inserter(*this, begin());
    copy(first, last, inserter);
}

/// Удаление элементов
template <typename Key, typename T, typename Compare, typename Hash >
typename hashmap<Key, T, Compare, Hash>::size_type
hashmap<Key, T, Compare, Hash>::erase(const key_type& x)
{
    int bucket;
    /// Пробуем найти
    typename ListType::iterator it = findElement(x, bucket);

    if ( it != (*_elems)[bucket].end() )
    {
        /// Элемент существует, удаляем его
        (*_elems)[bucket].erase(it);
        _size--;
        return (1);
    }
    else
    {
        return (0);
    }
}

template <typename Key, typename T, typename Compare, typename Hash >
void hashmap<Key, T, Compare, Hash>::erase(hashmap<Key, T, Compare, Hash>::iterator first,
                                           hashmap<Key, T, Compare, Hash>::iterator last)
{
    typename hashmap<Key, T, Compare, Hash>::iterator cur, next;
    /// Удаляем все элементы в диапазоне
    for (next=first; next != last;)
    {
        cur = next++;
        erase(cur);
    }
}

template <typename Key, typename T, typename Compare, typename Hash >
void hashmap<Key, T, Compare, Hash>::clear()
{
    for_each(_elems->begin(), _elems->end(), mem_fun_ref(&ListType::clear));
    _size = 0;
}

template <typename Key, typename T, typename Compare, typename Hash >
typename hashmap<Key, T, Compare, Hash>::key_compare
hashmap<Key, T, Compare, Hash>::key_comp() const
{
    return (_comp);
}

template <typename Key, typename T, typename Compare, typename Hash >
typename hashmap<Key, T, Compare, Hash>::value_compare
hashmap<Key, T, Compare, Hash>::value_comp() const
{
    return (value_compare(_comp));
}

template <typename Key, typename T, typename Compare, typename Hash >
void hashmap<Key, T, Compare, Hash>::erase(hashmap<Key, T, Compare, Hash>::iterator position)
{
    (*_elems)[position._bucket].erase(position._it);
}

/// Итераторный метод begin
template <typename Key, typename T, typename Compare, typename Hash >
typename hashmap<Key, T, Compare, Hash>::iterator hashmap<Key, T, Compare, Hash >::begin()
{
    /// Специальный случай -элементы отсутствуют
    if ( _size == 0 )
    {
        return (end());
    }
    /// Находим первый элемент
    for (size_t i=0; i<_elems->size(); ++i)
    {
        if (!((*_elems)[i].empty()))
        {
            return (HashIterator<Key, T, Compare, Hash>(i, (*_elems)[i].begin(), this));
        }
    }
    /// Теоретически, не должны попасть сюда, по возвращаем end
    return (end());
}

/// Итераторный метод end() - создает итератор, ссылающийся на конец последнего сегмента
template <typename Key, typename T, typename Compare, typename Hash >
typename hashmap<Key, T, Compare, Hash>::iterator hashmap<Key, T, Compare, Hash >::end()
{
    /// Конечный итератор -просто конечный итератор списка в последнем сегменте
    return (HashIterator<Key, T, Compare, Hash>(_elems->size()-1, (*_elems)[_elems->size()-1].end(), this));
}

#endif /* _STL_HASHMAP_H */
