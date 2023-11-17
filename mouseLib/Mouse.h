#ifndef MOUSE_H
#define MOUSE_H

#include "Transmitter.h"
#include <Windows.h>
#include <vector>

// Messages
#define MSG_SUCCESS      " - SUCCESS"
#define MSG_FAILED       " - FAILED"
#define MSG_LIBRARY_NAME "[Mouse]: "


// Parameters
#define MOUSE_CURSOR_STEP 10

// Signals for arduino board
#define MOUSE_LEFT_PRESS     '3'
#define MOUSE_LEFT_RELEASE   '4'
#define MOUSE_RIGHT_PRESS    '5'
#define MOUSE_RIGHT_RELEASE  '6'
#define MOUSE_MOVE_CURSOR    '7'

class Mouse : virtual public Transmitter
{
// Custom data types
// -------------------------------------
private:

    struct Direction
    {
        int32_t dx; // X direction
        int32_t dy; // Y direction
        int8_t sX;  // X step
        int8_t sY;  // Y step
        Direction() : dx{ 0 }, dy{ 0 }, sX{ 0 }, sY{ 0 }{};
    };

public:
    struct Point
    {
        int32_t x;
        int32_t y;
        Point() : x{ 0 }, y{ 0 }{};
        Point(int32_t X, int32_t Y) : x{ X }, y{ Y }{};
    };

    enum Curve
    {
        BezierLinear,
        BezierQuadratic,
        BezierCubic
    }; 

    enum Button
    {
        Left,
        Right
    };

// Variables
// -------------------------------------
private:
    static int8_t m_mouseStep;

    int m_defaultMouseSpeedModifier = 10;
    int m_systemMouseSpeedModifier = 0;

    const uint32_t m_screenWidth = 1920;
    const uint32_t m_screenHeight = 1080;

// Methods
// -------------------------------------
private: 
    int32_t getRandomInt(int32_t from, int32_t to);
    bool updatePosition(int32_t& currentPos, int32_t moveTo, int8_t step, bool isX);
    Direction calculateDirection(Point& currentPos, Point& moveTo, int8_t step); 
    void setMousePos(int8_t x, int8_t y);

public:
    Mouse(LPCWSTR comName);

    void setMousePos(Point& moveTo, Point& currentPos, int8_t mouseStep);
    bool setMouseStep(int8_t mouseStep);    

    template <typename T>
    void delay(T duration);
    
    Point getMousePos();
    Point getRandomPoint();

    Point bezierLinear(double t, Point& p0, Point& p1, std::vector<Point>& points);
    Point bezierQuadratic(double t, Point& p0, Point& p2, std::vector<Point>& points);
    Point bezierCubic(double t, Point& p0, Point& p3, std::vector<Point>& points);

    void press(Button button);
    void release(Button button);
    void click(Button button);
    void doubleClick(Button button);

    void move(Point& P3, Curve algorithm = Curve::BezierLinear, int8_t mouseStep = m_mouseStep);
};

#endif // Mouse_H
