#include <iostream>

using namespace std;

/** Отличие c_str() от data()
    const char* c_str ( ) const - автоматически добавляется завершающий ноль
    const char* data ( ) const - terminating null character не добавляется!

    size_t find ( const string& str, size_t pos = 0 ) const;
    size_t find ( const char* s, size_t pos, size_t n ) const;
    size_t find ( const char* s, size_t pos = 0 ) const;
    size_t find ( char c, size_t pos = 0 ) const;

    string& replace ( size_t pos1, size_t n1,   const char* s );

    string substr ( size_t pos = 0, size_t n = npos ) const;
*/

int main()
{
/// const char* c_str - добавляет NULL terminating
    string s("1234567890");
    cout << "c_str() result: " << s.c_str() << endl;
/// const char* data - получает данные строки в буфер, без завершающего нуля
    s[7] = 0;
    s[8] = 111;
    const char* p = s.data();
    cout << "data result, p=" << int(p[8]) << endl;

/// size_t find ( const string& str, size_t pos = 0 ) const;
/// где pos - начальная позиция для поиска
    string str ("There are two needles in this haystack with needles.");
    string str2 ("needle");
    size_t found;
    // different member versions of find in the same order as above:
    found=str.find(str2);
    if (found!=string::npos)
        cout << "first 'needle' found at: " << int(found) << endl;

/// size_t find ( const char* s, size_t pos, size_t n ) const;
/// где n - количество символов из второй строки!
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
/// где n - количество символов в строке 1 которые нужно заменить
/// если n==0, то needled не будет удалено
    // let's replace the first needle:
    str.replace(str.find(str2),str2.length(),"apples");
    cout << str << endl;

/// string substr ( size_t pos = 0, size_t n = npos ) const;
/// генерирует подстроку
    /// There are two apples in this haystack with needles.
    string apple = str.substr(14,6); /// apples
    cout << "after substr(14,6): " << apple << endl;

    size_t pos = str.find("haystack");
    string theend = str.substr(pos); /// от pos до конца: haystack with needles.
    cout << "after substr(pos): " << theend << endl;

    return 0;
}
