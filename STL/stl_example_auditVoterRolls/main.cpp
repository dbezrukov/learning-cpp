#include <iostream>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

/**
    ���� ��������� -������� ������ ����������� �� �������, ������ �����������,
    ����� ������� �� �������� ������� ����������: ������������������ � ������ ������� ��� �����������
*/

// ����������� const, ����� �� �������� ��������!
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

/// ������ ���������� ������ ������ ��������������������
list<string> getDuplicates(const map<string, list<string> >& voters)
{
    /// ������� ��� ����� � ������� ������
    list<string> allNames;
    map<string, list<string> >::const_iterator it;

    for (it = voters.begin(); it != voters.end(); ++it)
    {
        allNames.insert(allNames.end(), it->second.begin(), it->second.end());
    }

    allNames.sort();

    list<string> duplicates;

    /// ������������� ����� ��������� ��������, ������ �� � ������� adjacent_find
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

// ������� ��� �������� ������� ����� � ������ ������
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

/// ������� ��� �������� � �������� ������ ������� �� ������� ������
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

/// ������� �������������������� ������ � �����������
void auditVotersRolls(map<string, list<string> >& voters, const list<string>& convicted)
{
    /// �������� ��� �����-��������� ����� ����������� � ���������� adjacent_find
    list<string> blackList = getDuplicates( voters );

    /// ���������� �� ������� �����������. ������ �������� -������� ���� ���������
    blackList.insert(blackList.end(), convicted.begin(), convicted.end());

    /// ��������� � ������� ��������� � ������ ������
    blackList.sort();
    blackList.unique();

    cout << "blackList:";
    for_each(blackList.begin(), blackList.end(), printName);
    cout << endl;

    /// ������� �� ������� ������ ������� �����������
    /// �������������� ������ RemoveNames ����� ������ ���� ��� ��� ���� �������
    for_each(voters.begin(), voters.end(), RemoveNames(blackList));
}

int main()
{
    /// ������� ������ �����������
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

    /// �����������
    convicted.push_back("Petrov");

    for_each(voters.begin(), voters.end(), &printCity);

    auditVotersRolls(voters, convicted);

    for_each(voters.begin(), voters.end(), &printCity);
    return 0;
}
