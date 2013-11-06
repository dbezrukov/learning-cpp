#include <iostream>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

/**
    Цель программы -принять списки избирателей по округам, список заключенных,
    затем удалить из окружных списков нарушитлей: зарегистрированных в разных округах или заключенных
*/

// обязательно const, чтобы не изменять значение!
void printName(const string& name)
{
    cout << " " << name;
}

void printCity(const pair<string, list<string> >& city)
{
    cout << city.first << ": ";
    for_each(city.second.begin(), city.second.end(), printName);
    cout << endl;
}

/// Функци возвращает список дважды зарегистрировавшихся
list<string> getDuplicates(const map<string, list<string> >& voters)
{
    /// Соберем все имена в большой список
    list<string> allNames;
    map<string, list<string> >::const_iterator it;

    for (it = voters.begin(); it != voters.end(); ++it)
    {
        allNames.insert(allNames.end(), it->second.begin(), it->second.end());
    }

    allNames.sort();

    list<string> duplicates;

    /// повторяющиеся имена оказались соседями, найдем их с помощью adjacent_find
    list<string>::iterator lit;
    for (lit = allNames.begin(); lit != allNames.end(); ++lit)
    {
        lit = std::adjacent_find(lit, allNames.end());
        if ( lit == allNames.end() )
        {
            break;
        }
        duplicates.push_back(*lit);
    }

    duplicates.sort();
    duplicates.unique();
    return duplicates;
}

// Функтор для проверки наличия имени в черном списке
class NameInList : public unary_function<string, bool>
{
public:
    NameInList(const list<string> blackList)
        : _blackList( blackList )
    {
    }
    bool operator()(const string& val)
    {
        list<string>::const_iterator it = find( _blackList.begin(), _blackList.end(), val);
        return (it != _blackList.end());
    }
protected:
    const list<string>& _blackList;
};

/// Функтор для удаления в окружном списке фамилий из черного списка
class RemoveNames : public unary_function<pair<string, list<string> >, void>
{
public:
    RemoveNames(const list<string>& blackList)
        : _blackList( blackList )
    {
    }
    void operator() (pair<const string, list<string> >& val)
    {
        list<string>::iterator it = remove_if(val.second.begin(), val.second.end(), NameInList(_blackList));
        val.second.erase(it, val.second.end());
    }
protected:
    const list<string>& _blackList;
};

/// Удаляет зарегистрировавшихся дважды и заключенных
void auditVotersRolls(map<string, list<string> >& voters, const list<string>& convicted)
{
    /// Получаем все имена-дубликаты путем объединения и применения adjacent_find
    list<string> blackList = getDuplicates( voters );

    /// Объединяем со списком заключенных. Первый итератор -позиция куда вставлять
    blackList.insert(blackList.end(), convicted.begin(), convicted.end());

    /// Сортируем и удаляем дубликаты в черном списке
    blackList.sort();
    blackList.unique();

    cout << "blackList:";
    for_each(blackList.begin(), blackList.end(), printName);
    cout << endl;

    /// Удаляем из каждого списка фамилии нарушителей
    /// Функциональный объект RemoveNames будет создан один раз для всех вызовов
    for_each(voters.begin(), voters.end(), RemoveNames(blackList));
}

int main()
{
    /// создаем списки избирателей
    map<string, list<string> > voters;
    list<string> nameList, convicted;

    nameList.push_back("Ivanov");
    nameList.push_back("Sidorov");
    voters.insert( make_pair("SPB", nameList) );

    nameList.clear();
    nameList.push_back("Ivanov");
    nameList.push_back("Petrov");
    nameList.push_back("Smirnov");
    voters.insert( make_pair("MSK", nameList) );

    /// заключенные
    convicted.push_back("Petrov");

    for_each(voters.begin(), voters.end(), &printCity);

    auditVotersRolls(voters, convicted);

    for_each(voters.begin(), voters.end(), &printCity);
    return 0;
}
