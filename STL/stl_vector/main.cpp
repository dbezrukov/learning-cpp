#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

template < class T, class Allocator = allocator<T> >
class Vector
{
// construction
    explicit Vector ( const Allocator& = Allocator() );
    explicit Vector ( size_t n, const T& value= T(), const Allocator& = Allocator() );
    template <class InputIterator>
    Vector ( InputIterator first, InputIterator last, const Allocator& = Allocator() );
    Vector ( const vector<T,Allocator>& x );
};

void print(int elem)
{
    cout << elem << " ";
}

template <typename T>
void printVector(const vector<T>& vec, const string& name)
{
    cout << name << ": " ;
    for_each(vec.begin(), vec.end(), &print);
    cout << endl;
}

template <typename T>
void printVectorReverse(const vector<T>& vec, const string& name)
{
    cout << name << ": " ;
    for_each(vec.rbegin(), vec.rend(), &print);
    cout << endl;
}

int main()
{
// Construction
    vector<int> first;                                  // empty vector of ints
    vector<int> second (4,100);                         // four ints with value 100
    vector<int> third (second.begin(),second.end()-1);  // iterating through second
    vector<int> fourth (third);                         // a copy of third
    // the iterator constructor can also be used to construct from arrays:
    // массив как stl-контейнер:
    int myints[] = {16,2,77,29};
    vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

// Iterators
    cout << "Iterators:" << endl;

    printVector(first,  "first");
    printVector(second, "second");
    printVector(third,  "third");
    printVector(fourth, "fourth");
    printVector(fifth,  "fifth");

    // try reverse
    printVectorReverse(fifth,  "fifth-reverse");

    cout << "try reverse once more: ";
    vector<int>::reverse_iterator rit;

    fifth.clear();
    for ( rit=fifth.rbegin() ; rit != fifth.rend(); ++rit )
    {
        cout << " " << *rit;
    }

    // Создается массив для двух zero-initialized элементов
    vector<int> intVec(2);
    cout << endl << "Create new array:" << endl;
    printVector(intVec, "intVec");

// Capacity
// size	    - Return size (public member function)
// max_size	- Return maximum size (public member function)
// resize	- Change size (public member function)
// capacity	- Return size of allocated storage capacity (public member function)
// empty	- Test whether vector is empty (public member function)
// reserve	- Request a change in capacity (public member function)

    cout << "Capacity:" << endl;

    intVec.clear();
    for (int i=0; i<100; i++)
    {
        intVec.push_back(i);
    }

    cout << "Number of elements, intVec.size() = " << (int)(intVec.size()) << endl;
    cout << "Number of elements that can be inserted without mem reallocation = " << (int)(intVec.capacity() - intVec.size()) << endl;

    // При очищении вектора перераспределения памяти не происходит
    intVec.clear();
    cout << "Number of elements that can be inserted without mem reallocation = " << (int)(intVec.capacity() - intVec.size()) << endl;

    // Метод resize - уменьшает или увеличивает количество элементов в векторе
    intVec.resize(2);
    intVec.resize(4, 777); // - при увеличении количества элементов можно задать им значения
    printVector(intVec, "intVec");

    // Недействительные казатели
    first.push_back(111);
    cout << "Number of elements that can be inserted without mem reallocation = " << (int)(first.capacity() - first.size()) << endl;
    vector<int>::iterator it = first.begin();
    cout << "First element = " << *it << endl;
    first.push_back(222);
    // Iterator invalidation! A reallocation invalidates all iterators referring to elements in the vector!
    // если бы перед вызовами была вызван метод reserve, было бы корректное значение, а так 0.
    cout << "First element = " << *it << endl;

// Element access
    intVec.assign(3, 1);
    try
    {
        int val = intVec.at(10);
    }
    catch (std::out_of_range& e)
    {
        cout << e.what() << endl;
    }

// Modifiers
// assign	 - Assign vector content (public member function)
// push_back - Add element at the end (public member function)
// pop_back	 - Delete last element (public member function)
// insert	 - Insert elements (public member function)
// erase	 - Erase elements (public member function)
// swap	     - Swap content (public member function)
// clear	 - Clear content (public member function)

    // assign удаляет содержимое вектора, не меняет capacity. Имеет две формы:
    // void assign ( size_type n, const T& u );
    intVec.assign(3, 333);
    printVector(intVec, "intVec");
    // void assign ( InputIterator first, InputIterator last );
    intVec.assign(fifth.rbegin(), fifth.rend());
    printVector(intVec, "intVec");

    // iterator insert ( iterator position, const T& x );
    // void insert ( iterator position, size_type n, const T& x );
    // void insert ( iterator position, InputIterator first, InputIterator last );
    // Если новый размер больше capacity, происходит перераспределение памяти.
    intVec.clear();
    intVec.push_back(1);
    intVec.push_back(3);

    // Функция вставки возвращает итератор на вставленный объект
    it = intVec.insert( intVec.begin() + 1, 2 );
    cout << "Value at iterator after insert function = " << *it << endl;

    // erase
    // iterator erase ( iterator position );
    // iterator erase ( iterator first, iterator last );
    // This invalidates all iterator and references to elements after position or first.
    // Returns iterator pointing to the new location of the element
    // that followed the last element erased by the function call,
    // which is the vector end if the operation erased the last element in the sequence.

    intVec.clear();
    intVec.push_back(1);
    intVec.push_back(2);
    intVec.push_back(3);

    // Функция удаления возвращает итератор на элемент после удаленного
    vector<int>::iterator itNew = intVec.erase( intVec.begin() + 1 );
    cout << "The element after deleted is " << *itNew << endl;

// Operators
    int ints1[] = { 1,2,3,5,7 };
    vector<int> vec1(ints1, ints1 + sizeof(ints1)/sizeof(int));

    int ints2[] = { 1,2,3,5 };
    vector<int> vec2(ints2, ints2 + sizeof(ints2)/sizeof(int));

    // сравнение векторов оного размера
    vec1 == vec2 ? (cout << "vec1==vec2" << endl) : (cout << "vec1!=vec2" << endl);

    // сравнение разного. здесь vec > vec2 т.к. в первом больше значащих символов
    vec1 > vec2 ? (cout << "vec1>vec2" << endl) : (cout << "vec1<vec2" << endl);

    return 0;
}
