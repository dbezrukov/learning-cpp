#include <iostream>
#include <map>

using namespace std;

class Foo
{
public:
    friend ostream& operator<<(ostream& ostr, const Foo& rhs);
    Foo()
        : _strVar ( "def value" )
    {
        cout << "Foo ctor" << endl;
    }
    ~Foo()
    {
        cout << "Foo dtor" << endl;
    }
protected:
    string _strVar;
};

ostream& operator<<(ostream& ostr, const Foo& rhs)
{
    ostr << rhs._strVar;
    return ostr;
}


int main()
{
    // При использовании оператора [] всегда создается новый элемент
    map<int, Foo> map1;
    cout << "size=" << map1.size() << endl;
    cout << "map1[0]=" << map1[10] << endl;
    cout << "size=" << map1.size() << endl;

// ПОИСК
    // Для поиска без создания объекта можно исользовать метод find
    map<int, Foo>::iterator it = map1.find(10);
    if ( it != map1.end() )
    {
        cout << "Element found, string=" << it->second << endl;
    }
    else
    {
        cout << "There is no such element" << endl;
    }

    // Или count
    if ( map1.count( 10 ) )
    {
        cout << "Element found" << endl;
    }

// ВСТАВКА
    // Оператор [] всегда перезаписывает значение
    // Метод insert наоборот -не перезаписыает.
    // Данный код вернет failed, т.к. значение с таким ключом уже присутствует
    pair<map<int, Foo>::iterator, bool> ret;
    ret = map1.insert( make_pair(10, Foo()) );
    if ( ret.second )
    {
        cout << "Insertion complete" << endl;
    }
    else
    {
        cout << "Insertion failed" << endl;
    }

    // Так же доступны следующие методы вставки:
    // iterator insert(iterator position, const value_type& __x),
    // где position -подсказка куда вставить элемент

    // void insert(_InputIterator first, _InputIterator last)

// УДАЛЕНИЕ
    map<int, string> map2;
    map2[1] = "one";
    map2[2] = "two";
    map2[3] = "three";
    map2[4] = "four";

    // returns void
    map2.erase( map2.begin() );
    cout << "map after begin() erase: ";
    for (map<int, string>::iterator it = map2.begin(); it != map2.end(); ++it)
    {
        cout << it->second << " ";
    }
    cout << endl;

    // returns 1 in case of success and 0 otherwise
    size_t res = map2.erase(2);
    cout << "Res after erase=" << (int)res << endl;

    // returns void
    map2.erase( map2.begin(), map2.end() );
    cout << "map after begin()-end() erase: ";
    for (map<int, string>::iterator it = map2.begin(); it != map2.end(); ++it)
    {
        cout << it->second << " ";
    }
    cout << endl;

    return 0;
}
