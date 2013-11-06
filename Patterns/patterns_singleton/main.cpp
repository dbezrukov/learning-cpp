#include <iostream>
#include <stdlib.h>
#include <auto_ptr.h>

using namespace std;

/// �������� �������. ��� ������������ ����������
class MayersSingleton
{
public:
    static MayersSingleton& instance()
    {
        // � ����� ������� � ����������� ���� ������ ��� �������� � ����������� �����������
        static MayersSingleton obj;
        return obj;
    }
    void foo() { cout << "foo" << endl; }
private:
    MayersSingleton() { cout << "MayersSingleton::ctor" << endl; };
    ~MayersSingleton() { cout << "MayersSingleton::destr" << endl; };

    MayersSingleton(const MayersSingleton&);
    MayersSingleton& operator=(const MayersSingleton&);
};

/// ���������� thread-safe singleton (Double-check locking pattern). ������ ��� � ACE
class Singleton
{
public:
    static Singleton* instance()
    {
        if ( _instance == NULL ) /// double checking
        {
            /// Do sync
            if ( _instance == NULL )
            {
                _instance = new Singleton;

            }
        }
        return _instance;
    }
    static void close_singleton()
    {
        if ( _instance != NULL )
        {
            delete _instance;
            _instance = NULL;
        }
    }
    void foo() { cout << "foo" << endl; }
protected:
    static Singleton* _instance;
private:
    Singleton() { cout << "Singleton::ctor" << endl; };
    ~Singleton() { cout << "Singleton::destr" << endl; };

    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
};
Singleton* Singleton::_instance = NULL;

int main()
{
    /// ������� ���������� ��������� ��� ������ �� ����������
    atexit(&Singleton::close_singleton);

    /// ���� ��� ������� � auto_ptr, �� ���������� �������� ������� ��������
    /// std::auto_ptr<Singleton> delete_instance( Singleton::instance() );

    //MayersSingleton& singleton = MayersSingleton::instance();
    //singleton.foo();

    Singleton* pSingleton = Singleton::instance();
    pSingleton->foo();
    return 0;
}






