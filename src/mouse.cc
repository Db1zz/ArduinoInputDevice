#include "mouse.h"
#include <cmath>
#include <random>
#include <chrono>

Mouse::Mouse(LPCWSTR comName)
    : Transmitter{ comName } { 
    SystemParametersInfo(SPI_GETMOUSESPEED, 0, &m_systemMouseSpeedModifier, 0);
    m_mouseStep = MOUSE_CURSOR_STEP;
}

Mouse::Point Mouse::bezierLinear(double t, Point& p0, Point& p1, std::vector<Mouse::Point>& points) {
    return 
    Point(p0.x + t *(p1.x - p0.x), 
          p0.y + t *(p1.y - p0.y));
}

Mouse::Point Mouse::bezierQuadratic(double t, Point& p0, Point& p2, std::vector<Mouse::Point>& points) {
    Point p1{ points[0] };

    return 
    Point(pow((1 - t), 2) * p0.x + 2 * (1 - t) * t * p1.x + pow(t, 2) * p2.x, 
          pow((1 - t), 2) * p0.y + 2 * (1 - t) * t * p1.y + pow(t, 2) * p2.y);
}

Mouse::Point Mouse::bezierCubic(double t, Point& p0, Point& p3, std::vector<Mouse::Point>& points) {
    Point p1{ points[0] };
    Point p2{ points[1] };
    double uT = 1 - t;

    return 
    Point(pow(uT, 3) * p0.x + 3 * pow(uT, 2) * t * p1.x + 3 * uT * pow(t, 2) * p2.x + pow(t, 3) * p3.x,
          pow(uT, 3) * p0.y + 3 * pow(uT, 2) * t * p1.y + 3 * uT * pow(t, 2) * p2.y + pow(t, 3) * p3.y);
}

int32_t Mouse::getRandomInt(int32_t from, int32_t to) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<uint32_t> dist(from, to);
    return dist(gen);
}

bool Mouse::setMouseStep(int8_t step) {
    if (step > 127 || step < -128) {
        std::cout << MSG_LIBRARY_NAME << "Incorrect step value: " << step << MSG_FAILED << std::endl;
        return false;
    } else {
        m_mouseStep = step;
        return true;
    }
}

void Mouse::move(Point& p1, Curve algorithm, int8_t mouseStep) {
    double t = 0.00;
    int8_t step = mouseStep;
    Point currPos = getMousePos();
    std::vector<Point> points;
    Mouse::Point (Mouse::*moveAlgorithm)(double, Point&, Point&, std::vector<Mouse::Point>&) = nullptr;

    if (algorithm == Curve::BezierLinear) {
        moveAlgorithm = &Mouse::bezierLinear;
    } else if (algorithm == Curve::BezierQuadratic) {
        moveAlgorithm = &Mouse::bezierQuadratic;
        points = std::vector<Point>{getRandomPoint()};
    } else if (algorithm == Curve::BezierCubic) {
        moveAlgorithm = &Mouse::bezierCubic;
        points = std::vector<Point>{getRandomPoint(), getRandomPoint()};
    }

    if (moveAlgorithm) {
        for(int i = 0; i <= 100; i++) {
            Point p = (this->*moveAlgorithm)(t, currPos, p1, points);

            if(t <= 0.50 && (i % 10 == 0) && step > 1)
                --step;
            else if(t > 0.50 && (i % 10 == 0) && step <= mouseStep)
                ++step;

            setMousePos(p, currPos, step);
            t += 0.01;
        }
        setMousePos(p1, currPos, step);
    }
}

Mouse::Point Mouse::getMousePos() {
    POINT p;
    GetCursorPos(&p);
    
    return Point(p.x, p.y);
}

Mouse::Point Mouse::getRandomPoint() {    
    return Point(getRandomInt(0, m_screenWidth), (0, m_screenHeight));
}

void Mouse::setMousePos(int8_t x, int8_t y) {
    sendDataToComPort(MOUSE_MOVE_CURSOR);
    sendDataToComPort(x);
    sendDataToComPort(y);
}

void Mouse::setMousePos(Point& moveTo, Point& currentPos, int8_t mouseStep) {
    Direction direction = calculateDirection(currentPos, moveTo, mouseStep);

    int err = direction.dx - direction.dy;
    bool reachedX = moveTo.x == currentPos.x ? true : false;
    bool reachedY = moveTo.y == currentPos.y ? true : false;

    while (!reachedX || !reachedY) {
        int err2 = 2 * err;
        if (err2 > - direction.dy) {
            err -= direction.dy;
            if (!reachedX) {
                reachedX = updatePosition(currentPos.x, moveTo.x, direction.sX, true);
            }
        }
        if (err2 < direction.dx) {
            err += direction.dx;
            if (!reachedY) {
                reachedY = updatePosition(currentPos.y, moveTo.y, direction.sY, false);
            }
        }
    }
}

Mouse::Direction Mouse::calculateDirection(Point& currentPos, Point& moveTo, int8_t step) {
    Direction direction;
    direction.dx = abs(moveTo.x - currentPos.x);
    direction.dy = abs(moveTo.y - currentPos.y);
    direction.sX = currentPos.x > moveTo.x ? -step : step;
    direction.sY = currentPos.y > moveTo.y ? -step : step;

    return direction;
}

bool Mouse::updatePosition(int32_t& currentPos, int32_t moveTo, int8_t step, bool isX) {
    if ((step > 0 && currentPos + step >= moveTo) || (step < 0 && currentPos + step <= moveTo)) {
        char lastStep = step > 0 ? step - abs((step + currentPos) - moveTo)
                                 : step + abs((step + currentPos) - moveTo);
        setMousePos(isX ? lastStep : 0, 
                    isX ? 0 : lastStep);
        currentPos += lastStep;
        return true;
    } else {
        setMousePos(isX ? step : 0, 
                    isX ? 0 : step);
        currentPos += step;
        return false;
    }
}

void Mouse::press(Button button) {
    if(button == Button::Left)
        sendDataToComPort(MOUSE_LEFT_PRESS);
    else if(button == Button::Right)
        sendDataToComPort(MOUSE_RIGHT_PRESS);
}

void Mouse::release(Button button) {
    if(button == Button::Left)
        sendDataToComPort(MOUSE_LEFT_RELEASE);
    else if(button == Button::Right)
        sendDataToComPort(MOUSE_RIGHT_RELEASE);
}

void Mouse::click(Button button) {
    press(button);
    delay(std::chrono::milliseconds(getRandomInt(51, 99)));
    release(button);
}

void Mouse::doubleClick(Button button) {
    click(button);
    delay(std::chrono::milliseconds(getRandomInt(100, 150)));
    click(button);
}

template <typename T>
void Mouse::delay(T duration) {
    std::this_thread::sleep_for(duration);
}
