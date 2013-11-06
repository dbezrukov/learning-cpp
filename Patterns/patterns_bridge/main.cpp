#include <iostream>

using namespace std;

/** Смысл в разделении множества объектов и множества возможных реализаций этих объектов
    Например, есть множество геометрических фигур и множество различных рисующих программ.
    Принципы рисования одинаковы, в то время как в каждой программе рисования есть нюансы.
    Чтобы избежать роста числа классов при добавлении новых объектов,
    будем комбинировать фигуры и программы рисования
*/

/// Семейство рисующих программ
class Drawing
{
public:
    virtual void drawLine(double x1, double y1,double x2, double y2) = 0; /// общее свойство
    virtual void drawCircle(double x, double y,double r) = 0;
};

class V1Drawing : public Drawing
{
public:
    void drawLine(double x1, double y1, double x2, double y2)
    {
        cout << "DP1::draw_line" << endl;
    }
    void drawCircle(double x, double y, double r)
    {
        cout << "DP1::draw_circle" << endl;
    }
};

class V2Drawing : public Drawing
{
public:
    void drawLine(double x1, double y1, double x2, double y2)
    {
        cout << "DP2::draw_line" << endl;
    }
    void drawCircle(double x, double y, double r)
    {
        cout << "DP2::draw_circle" << endl;
    }
};

/// Семейство фигур
class Shape
{
public:
    Shape(Drawing *dp)
        : _dp(dp)
    {
    }
    virtual void draw() = 0; /// общее свойство для всех фигур
protected: /// protected для того, чтобы был доступен производным классам
    Drawing* _dp;
};

class Rectangle : public Shape
{
public:
    Rectangle(Drawing *dp, double x1, double y1, double x2, double y2)
        : Shape(dp)
        , _x1(x1)
        , _y1(y1)
        , _x2(x2)
        , _y2(y2)
    {
    }
    void draw()
    {
        drawLine(_x1,_y1,_x2,_y1);
        drawLine(_x2,_y1,_x2,_y2);
        drawLine(_x2,_y2,_x1,_y2);
        drawLine(_x1,_y2,_x1,_y1);
    }
protected:
    void drawLine(double x1, double y1, double x2, double y2)
    {
        _dp->drawLine(x1,y1,x2,y2);
    }
    double _x1, _y1, _x2, _y2;
};

class Circle : public Shape
{
public:
    Circle(Drawing *dp, double x, double y, double r)
        : Shape(dp)
        , _x(x)
        , _y(y)
        , _r(r)
    {
    }
    void draw()
    {
        _dp->drawCircle( _x, _y, _r);
    }
protected:
    double _x, _y, _r;
};

int main()
{
    Shape* s1;
    Shape* s2;
    Drawing* dp1;
    Drawing* dp2;

    dp1 = new V1Drawing;
    s1 = new Rectangle(dp1, 1, 1, 2, 2);

    dp2 = new V2Drawing;
    s2 = new Circle(dp2, 2, 2, 4);

    s1->draw();
    s2->draw();

    delete s1; delete s2;
    delete dp1; delete dp2;
    return 0;
}
