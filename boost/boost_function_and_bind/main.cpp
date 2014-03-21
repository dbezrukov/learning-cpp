#include <iostream>
#include <boost\function.hpp>
#include <boost\bind.hpp>

/**
class Button
{
public:
    Button(boost::function<void()> f)
        : _onClick( f ) {}
    void click()
    {
        if ( !_onClick.empty() )
            _onClick();
    }
protected:
    boost::function<void()> _onClick;
};

struct Player
{
    void Run() { };
    void Jump(int meters) { std::cout << meters << std::endl; };
};

int main()
{
    Player player;
    Button runButton(boost::bind(&Player::Run, &player));
    Button jumpButton(boost::bind(&Player::Jump, &player, 10));
    runButton.click();
    jumpButton.click();
    return 0;
}
*/

/// Пример содержит реализацию паттерна Command

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include "boost\function.hpp"
#include "boost\bind.hpp"

struct Plane
{
	void incAlt()         {cout << "Throttle up.."       << endl;}
	void incSpeed()       {cout << "Decrease pressure.." << endl;}
	void comm(string str) {cout << "This is "            << str << endl;}
};

/// command object
class Command
{
public:
	 Command() {}
	 Command(string name, boost::function<void ()> f)
	     : _name( name )
	     , _onCmd( f )
     {
     }
	 void execute()
	 {
	     if( !_onCmd.empty() )
			_onCmd();
	 }
	 bool b() const { return 0; }
	 const string& name() const
	 {
	     return _name;
	 }
protected:
	 string _name;
	 boost::function<void()> _onCmd;
};

bool isIncAlt(const Command& cmd)
{
    return ( cmd.name() == "incAlt" );
}

int main()
{
	Plane plane;

	Command cmdComm ( "comm",     boost::bind(&Plane::comm,     &plane, "N123456") );
    Command cmdAlt  ( "incAlt",   boost::bind(&Plane::incAlt,   &plane) );
    Command cmdSpeed( "incSpeed", boost::bind(&Plane::incSpeed, &plane) );

	cmdComm .execute();
	cmdAlt  .execute();
    cmdSpeed.execute();

	vector<Command> cmdVec;

	cmdVec.push_back(cmdComm);
	cmdVec.push_back(cmdAlt);
	cmdVec.push_back(cmdSpeed);

	/// run the command sequence
	for_each( cmdVec.begin(), cmdVec.end(), boost::bind(&Command::execute, _1) ); /// _1 передает this

	cout << "search for the command <incAlt> and execute" << endl;
	vector<Command>::iterator it;

	it = std::find_if( cmdVec.begin(), cmdVec.end(), bind( &Command::name, _1 ) == "incAlt" );
	if ( it != cmdVec.end() )
    {
        cout << "element found=" << it->name() << endl;
    }
    else
    {
        cout << "not found" << endl;
    }

	return 0;
}

