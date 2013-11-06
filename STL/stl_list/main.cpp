#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

template <typename T>
void print(T& elem)
{
    cout << elem << " ";
}

template <typename T>
void printList(string name, list<T>& lst)
{
    cout << name << ": ";
    for_each(lst.begin(), lst.end(), &print<T>);
    cout << endl;
}

// Функция получает список групп и список отчисленных студентов
// возвращает список учащихся студprintList("dict", dict);
list<string> getStudents(vector< list<string> >& classes, list<string>& dropped)
{
    list<string> students;
    for (int i=0; i<classes.size(); i++)
    {
        students.insert(students.begin(), classes[i].begin(), classes[i].end());
    }
    printList("students, mixed", students);
    students.sort();
    printList("students, sorted", students);
    students.unique();
    printList("students, unique", students);

    for (list<string>::iterator it = dropped.begin(); it != dropped.end(); ++it)
    {
        students.remove(*it);
    }
    return students;
}

int main()
{
    // Функция splice - вклеивает один список в другой
    // void splice ( iterator position, list& srcList );
    // void splice ( iterator position, list& srcList, InputIterator position );
    // void splice ( iterator position, list& srcList, InputIterator first, InputIterator last );

    list<string> dict;
    dict.push_back("ace");
    dict.push_back("apple");
    dict.push_back("cat");
    dict.push_back("car");

    list<string> bwords;
    bwords.push_back("bank");
    bwords.push_back("bush");

    int i;
    list<string>::iterator it;
    for (it = dict.begin(), i=0; i<2; ++it, ++i);

    // Вклеим первое слово на 'b' в словарь
    dict.splice(it, bwords, bwords.begin());

    printList("dict", dict);
    printList("bwords", bwords);

    // пример списка студенов
    list<string> class1;
    class1.push_back("kolya");
    class1.push_back("dima");

    list<string> class2;
    class2.push_back("ivan");
    class2.push_back("kolya");

    vector< list<string> > classes;
    classes.push_back( class1 );
    classes.push_back( class2 );

    list<string> dropped;
    dropped.push_back("ivan");

    list<string> students = getStudents(classes, dropped);
    printList("students, total", students);

    return 0;
}
