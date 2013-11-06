#include <iostream>

using namespace std;

/**
    class Derived : [virtual] [access-specifier] Base
    {
        // member list
    };

    ���� ������������ ������� ��������, �� ���������, ��� ������ PRIVATE!

    Public inheritance
    Base access specifier	Derived access specifier	Derived class access?	Public access?
    Public	                Public	                    Yes	                    Yes
    Private	                -	                        No	                    No
    Protected	            Protected	                Yes	                    No

    Protected inheritance
    Base access specifier	Derived access specifier	Derived class access?	Public access?
    Public	                Protected	                Yes	                    No
    Private	                -	                        No	                    No
    Protected	            Protected	                Yes	                    No

    Private inheritance
    Base access specifier	Derived access specifier	Derived class access?	Public access?
    Public	                Private	                    Yes	                    No
    Private                 -	                        No	                    No
    Protected	            Private	                    Yes	                    No
*/


/// ������� ������ ���� protected-����������� �� �����
/// ������� ����� �� �������-��������������� ������

class Secret
{
protected:
    virtual void tell()
    {
        cout << "Secret::tell" << endl;
    }
};

class Blabber : public Secret
{
public:
    virtual void tell()
    {
        Secret::tell();
    }
};
int main()
{
    Blabber blabber;
    blabber.tell();
    return 0;
}
