#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

void print(int x)
{
    cout << x << " ";
}

int main()
{
    /** Input iterator

    Служит для чтения данных, может быть сравнен с другими на предмет равенства или неравенства,
    содержимое объекта на который указывает итератор может быть получено с помощью оператора *,
    перемещение к следующему элементу происходит благодаря оператору ++.
    Итератор возвращается шаблонным классом istream_iterator.

    template<class InputIterator, class Function>
    Function for_each (InputIterator first, InputIterator last, Function f)
    {
        while (first != last)
            f(*first++); // чтение из first
        return f;
    }
    */


    int ints[] = { 1, 2, 3, 4, 5 };
    cout << "Print initial array using for_each & input iterator: ";
    for_each(ints, ints+5, &print);

    /** Output iterator

    Служит для указания на область памяти, куда выводятся данные. Для итератора опеределяются
    операторы =, *, ++. Первые два в смысле записи данных в область, куда итератор указывает.
    Итератор возвращается классом потокового итератора ostream_iterator и итераторами вставки
    inserter, font_inserter, back_inserter

    template<class InputIterator, class OutputIterator>
    OutputIterator copy ( InputIterator first, InputIterator last, OutputIterator result )
    {
        while (first!=last)
            *result++ = *first++; // запись в result
        return result;
    }
    */

    cout << endl << "Print initial array using copy & output iterator: ";
    copy(ints, ints+5, ostream_iterator<int>(cout, " "));

    /** Forward iterator

    Объединяет свойства итератора ввода и вывода. Позволяет читать и писать данные, смещаясь по цепочке
    при помощи оператора ++. Кроме того, итератор поддерживает операторы сравнения == и !=,
    а также разыменовывания * и присвоения =.

    алгоритм replace меняет в диапазоне одно указанное значение на другое:

    template <class ForwardIterator, class T>
    void replace (ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value)
    {
        while (first != last)
        {
            if (*first == old_value) // чтение из first
                *first = new_value;  // запись в first
            ++first;
        }
    }
    */

    replace(ints, ints+5, 3, 333);
    cout << endl << "Modify array using replace & forward iterator: ";
    copy(ints, ints+5, ostream_iterator<int>(cout, " ")); /// 1 2 333 4 5

    /** Bidirectional iterator

    Дополняет ForwardIterator возможность перемещаться назад благодаря оператору --.

    алгоритм reverse выполняет реверсию элементов диапазона

    template<typename BidirectionalIterator>
    void reverse(BidirectionalIterator first, BidirectionalIterator last)
    {
        while (true)
        {
            if (first == last || first == --last)
            {
                return;
            }
            else
            {
                std::iter_swap(first, last);
                ++first;
            }
        }
    }
    */

    reverse(ints, ints+5);
    cout << endl << "Modify array using reverse & bidirectional iterator: ";
    copy(ints, ints+5, ostream_iterator<int>(cout, " ")); /// 5 4 333 2 1

    /** RandomAccessIterator

    Дополнительно поддерживаю арифметические оператции, полноценное сравнение, индексирование

    */

    ints = { 1, 2, 3, 4, 5 }; /// c++0x feature!
    vector<int> intVec(5);
    vector<int>::iterator it = intVec.begin();
    copy(ints, ints + 5, it);
    cout << endl << "New vector, counting to begin: ";
    cout << *(   it  + 4      ) << ""; /// 5
    cout << *(   it += 3      ) << ""; /// 4
    cout << *(   it -= 1      ) << ""; /// 3
    cout << *(   it  = it - 1 ) << ""; /// 2
    cout << *( --it )           << ""; /// 1

    cout << endl << "Print vector from begin+1 using []: ";
    it++; /// !!!
    for(int i = 0; i < intVec.end()-intVec.begin()-1; i++)
    {
        cout << it[i] << ""; /// 2 3 4 5 - индексирование с позиции в которой сейчас итератор!
    }

    /** reverse_iterator - адаптер */

    cout << endl << "Reverse print using reverse_iterator: ";
    copy(intVec.rbegin(), intVec.rend(), ostream_iterator<int>(cout, " "));

    /** stream_iterator - адаптер

    Пример запрашивает ввод чисел, пока не встретит 555. Каждое введенное число комментирует текстом

    */

    cout << endl << "Request digits until 555" << endl;
    istream_iterator<int> is(cin);
    ostream_iterator<int> os(cout, " - last entered value\n");

    while( *is != 555)
    {
        *os++ = *is;
        is++ ;
    }

    /** Итераторы вставки
    inserter - вставляет элементы в любой контейнер
    front_inserter - не работает с set, map и vector. Последовательноть должна передаваться в обратном порядке
    back_inserver - не работает с set и map, нужно использовать inserter

    Создадим список с двумя значениями равными нулю.
    Добавим в начало и конец значения {1,2,3}
    Потом в середину между двумя нулями добавим 1,1,1
    */

    int ints0[] = { 0, 0 };
    int intsFront[] = { 3, 2, 1 };
    int intsBack[] = { 1, 2, 3 };
    int intsCenter[] = { 1, 1, 1 };

    list<int> intList(ints0, ints0+2);
    cout << endl << "List initial: ";
    copy(intList.begin(), intList.end(), ostream_iterator<int>(cout, " ")); /// 0 0

    copy(intsFront, intsFront+3, front_inserter(intList));
    cout << endl << "List after front inserter: ";
    copy(intList.begin(), intList.end(), ostream_iterator<int>(cout, " ")); /// 1 2 3 0 0

    copy(intsBack, intsBack+3, back_inserter(intList));
    cout << endl << "List after back inserter: ";
    copy(intList.begin(), intList.end(), ostream_iterator<int>(cout, " ")); /// 1 2 3 0 0 1 2 3

    list<int>::iterator list_it = intList.begin();
    advance(list_it, 4); /// вместо it = it + 4, если итератор не произвольного доступа!

    copy(intsCenter, intsCenter+3, inserter(intList, list_it));
    cout << endl << "List after inserter: ";
    copy(intList.begin(), intList.end(), ostream_iterator<int>(cout, " ")); /// 1 2 3 0 1 1 1 0 1 2 3


    /** Операции с итераторами

    void advance (InputIterator& iter, Distance& n);
    - это просто удобная форма инкрементирования итератора iter на определенное число n:
    реализация: while (n--) ++i;

    void distance(InputIterator& first, InputIterator& second, Distance& n);
    - измеряет расстояние между итераторами first и second, возвращая полученное число через ссылку n:
    реализация: return last - first

    */

    return 0;
}
