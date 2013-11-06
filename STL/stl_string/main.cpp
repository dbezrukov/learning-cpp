#include <iostream>

using namespace std;

/** ������� c_str() �� data()
    const char* c_str ( ) const - ������������� ����������� ����������� ����
    const char* data ( ) const - terminating null character �� �����������!

    size_t find ( const string& str, size_t pos = 0 ) const;
    size_t find ( const char* s, size_t pos, size_t n ) const;
    size_t find ( const char* s, size_t pos = 0 ) const;
    size_t find ( char c, size_t pos = 0 ) const;

    string& replace ( size_t pos1, size_t n1,   const char* s );

    string substr ( size_t pos = 0, size_t n = npos ) const;
*/

int main()
{
/// const char* c_str - ��������� NULL terminating
    string s("1234567890");
    cout << "c_str() result: " << s.c_str() << endl;
/// const char* data - �������� ������ ������ � �����, ��� ������������ ����
    s[7] = 0;
    s[8] = 111;
    const char* p = s.data();
    cout << "data result, p=" << int(p[8]) << endl;

/// size_t find ( const string& str, size_t pos = 0 ) const;
/// ��� pos - ��������� ������� ��� ������
    string str ("There are two needles in this haystack with needles.");
    string str2 ("needle");
    size_t found;
    // different member versions of find in the same order as above:
    found=str.find(str2);
    if (found!=string::npos)
        cout << "first 'needle' found at: " << int(found) << endl;

/// size_t find ( const char* s, size_t pos, size_t n ) const;
/// ��� n - ���������� �������� �� ������ ������!
    found=str.find("needles are small", found+1, 6);
    if (found!=string::npos)
        cout << "second 'needle' found at: " << int(found) << endl;

///size_t find ( const char* s, size_t pos = 0 ) const;
    found=str.find("haystack");
    if (found!=string::npos)
        cout << "'haystack' also found at: " << int(found) << endl;

/// size_t find ( char c, size_t pos = 0 ) const;
    found=str.find('.');
    if (found!=string::npos)
        cout << "Period found at: " << int(found) << endl;

/// string& replace ( size_t pos1, size_t n1, const char* s );
/// ��� n - ���������� �������� � ������ 1 ������� ����� ��������
/// ���� n==0, �� needled �� ����� �������
    // let's replace the first needle:
    str.replace(str.find(str2),str2.length(),"apples");
    cout << str << endl;

/// string substr ( size_t pos = 0, size_t n = npos ) const;
/// ���������� ���������
    /// There are two apples in this haystack with needles.
    string apple = str.substr(14,6); /// apples
    cout << "after substr(14,6): " << apple << endl;

    size_t pos = str.find("haystack");
    string theend = str.substr(pos); /// �� pos �� �����: haystack with needles.
    cout << "after substr(pos): " << theend << endl;

    return 0;
}
