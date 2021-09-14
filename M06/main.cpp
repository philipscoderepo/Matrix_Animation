#include "Simple_window.h"
#include "PolygonMatrix.h"
using namespace Graph_lib;  // use our graphics interface library

const double pi = 3.14159265358979323846;

const int FPS = 60;
const double TIMESTEP = 1.0 / FPS;

void createStar(PolygonMatrix&, int, int);
static void Timer_CB(void *obj);
void transform(PolygonMatrix&);

void unitTests();

int main()
{
    int max_w = Fl::w();
    int max_h = Fl::h();

    cout << "Starting unit tests..." << endl;
    unitTests();
    cout << "Unit tests complete.  Starting graphics engine..." << endl;

    Point tl(0,0);

    Graph_lib::Window win(tl, max_w, max_h,"Polygon Matrix"); // make a simple window
    win.color(FL_BLACK);
    PolygonMatrix poly(max_w, max_h);
    createStar(poly, max_w, max_h);
    win.attach(poly);   // connect poly to the window

    ///create a timer to transform the polygon at 60FPS
    ///calls Timer_CB every TIMESTEP seconds
    Fl::add_timeout(TIMESTEP, Timer_CB, (void*)(&poly));
    Fl::run();
}

void createStar(PolygonMatrix& poly, int w, int h)
{
    int centerX = w / 2;
    int centerY = h / 2;

    poly.add(Point(centerX - 200, centerY));
    poly.add(Point(centerX - 40, centerY + 20));
    poly.add(Point(centerX - 100, centerY + 100));
    poly.add(Point(centerX - 20, centerY + 40));
    poly.add(Point(centerX, centerY + 200));
    poly.add(Point(centerX + 20, centerY + 40));
    poly.add(Point(centerX + 100, centerY + 100));
    poly.add(Point(centerX + 40, centerY + 20));
    poly.add(Point(centerX + 200, centerY));
    poly.add(Point(centerX + 40, centerY - 20));
    poly.add(Point(centerX + 100, centerY - 100));
    poly.add(Point(centerX + 20, centerY - 40));
    poly.add(Point(centerX, centerY - 200));
    poly.add(Point(centerX - 20, centerY - 40));
    poly.add(Point(centerX - 100, centerY - 100));
    poly.add(Point(centerX - 40, centerY - 20));

    poly.set_fill_color(Color::yellow);
}

bool almostEqual(double a, double b, double eps = 0.0001)
{
    return fabs(a - b) < eps;
}

void unitTests()
{

    int score = 0;

    cout << "Testing Matrices.h..." << endl;
    cout << "Testing addCoordinate...";
    Matrix a(2,0);
    a.addCoordinate(500, -750);
    if(a.getRows() == 2 && a.getCols() == 1 && almostEqual(a(0,0), 500) && almostEqual(a(1,0), -750))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing RotationMatrix constructor...";
    double theta = pi / 4.0;
    RotationMatrix r(pi / 4);
    if(r.getRows() == 2 && r.getCols() == 2 && almostEqual(r(0,0), cos(theta))
       && almostEqual(r(0,1), -sin(theta))
       && almostEqual(r(1,0), sin(theta))
       && almostEqual(r(1,1), cos(theta)))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing ScalingMatrix constructor...";
    ScalingMatrix s(1.5);
    if(s.getRows() == 2 && s.getCols() == 2
       && almostEqual(s(0,0), 1.5)
       && almostEqual(s(0,1), 0)
       && almostEqual(s(1,0), 0)
       && almostEqual(s(1,1), 1.5))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing TranslationMatrix constructor...";
    TranslationMatrix t(5, -5, 3);
    if(t.getRows() == 2 && t.getCols() == 3
       && almostEqual(t(0,0), 5)
       && almostEqual(t(1,0), -5)
       && almostEqual(t(0,1), 5)
       && almostEqual(t(1,1), -5)
       && almostEqual(t(0,2), 5)
       && almostEqual(t(1,2), -5))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing PolygonMatrix.h..." << endl;

    cout << "Testing mapRange...";
    if(almostEqual(mapRange(0.1, -1.0, 1.0, -500, 500), 50) &&
       almostEqual(mapRange(50, -500, 500, -1.0, 1.0), 0.1) &&
       almostEqual(mapRange(50, 500, -500, -1.0, 1.0), -0.1))
    {
        cout << "mapRange passed. +1" << endl;
        score++;
    }
    else
    {
        cout << "mapRange failed." << endl;
    }

    cout << "Adding a single point to a PolygonMatrix..." << endl;
    PolygonMatrix p(1200, 1000);
    p.add(Point{600, 800});
    if(p.number_of_points() == 1
       && p.point(0).x == 600
       && p.point(0).y == 800
       && almostEqual(p.getPointMatrix()(0,0), 0)
       && almostEqual(p.getPointMatrix()(1,0), -300))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Adding multiple points to a PolygonMatrix...";
    p.add(Point{400, 800});
    p.add(Point{400, 200});
    p.add(Point{600, 200});
    if(p.number_of_points() == 4
       && p.point(0).x == 600
       && p.point(0).y == 800
       && almostEqual(p.getPointMatrix()(0,0), 0)
       && almostEqual(p.getPointMatrix()(1,0), -300)
       && p.point(1).x == 400
       && p.point(1).y == 800
       && almostEqual(p.getPointMatrix()(0,1), -200)
       && almostEqual(p.getPointMatrix()(1,1), -300)
       && p.point(2).x == 400
       && p.point(2).y == 200
       && almostEqual(p.getPointMatrix()(0,2), -200)
       && almostEqual(p.getPointMatrix()(1,2), 300)
       && p.point(3).x == 600
       && p.point(3).y == 200
       && almostEqual(p.getPointMatrix()(0,3), 0)
       && almostEqual(p.getPointMatrix()(1,3), 300))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying one rotation of 90 degrees...";
    PolygonMatrix p2(1200, 1000);
    p2.add(Point{800, 800});
    p2.add(Point{400, 800});
    p2.add(Point{400, 200});
    p2.add(Point{800, 200});
    p2.rotate(pi / 2);

    if(p2.number_of_points() == 4
       && almostEqual(p2.point(0).x, 900, 1.1)
       && almostEqual(p2.point(0).y, 300, 1.1)
       && almostEqual(p2.getPointMatrix()(0,0), 300)
       && almostEqual(p2.getPointMatrix()(1,0), 200)
       && almostEqual(p2.point(1).x, 900, 1.1)
       && almostEqual(p2.point(1).y, 700, 1.1)
       && almostEqual(p2.getPointMatrix()(0,1), 300)
       && almostEqual(p2.getPointMatrix()(1,1), -200)
       && almostEqual(p2.point(2).x, 300, 1.1)
       && almostEqual(p2.point(2).y, 700, 1.1)
       && almostEqual(p2.getPointMatrix()(0,2), -300)
       && almostEqual(p2.getPointMatrix()(1,2), -200)
       && almostEqual(p2.point(3).x, 300, 1.1)
       && almostEqual(p2.point(3).y, 300, 1.1)
       && almostEqual(p2.getPointMatrix()(0,3), -300)
       && almostEqual(p2.getPointMatrix()(1,3), 200))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying a scale of 0.5...";
    PolygonMatrix p3(1200, 1000);
    p3.add(Point{700, 800});
    p3.add(Point{500, 800});
    p3.add(Point{500, 200});
    p3.add(Point{700, 200});
    p3.scale(0.5);

    if(p3.number_of_points() == 4
       && almostEqual(p3.point(0).x, 650, 1.1)
       && almostEqual(p3.point(0).y, 650, 1.1)
       && almostEqual(p3.getPointMatrix()(0,0), 50)
       && almostEqual(p3.getPointMatrix()(1,0), -150)
       && almostEqual(p3.point(1).x, 550, 1.1)
       && almostEqual(p3.point(1).y, 650, 1.1)
       && almostEqual(p3.getPointMatrix()(0,1), -50)
       && almostEqual(p3.getPointMatrix()(1,1), -150)
       && almostEqual(p3.point(2).x, 550, 1.1)
       && almostEqual(p3.point(2).y, 350, 1.1)
       && almostEqual(p3.getPointMatrix()(0,2), -50)
       && almostEqual(p3.getPointMatrix()(1,2), 150)
       && almostEqual(p3.point(3).x, 650, 1.1)
       && almostEqual(p3.point(3).y, 350, 1.1)
       && almostEqual(p3.getPointMatrix()(0,3), 50)
       && almostEqual(p3.getPointMatrix()(1,3), 150))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying a translation of (10, 5)...";
    PolygonMatrix p4(1200, 1000);
    p4.add(Point{700, 800});
    p4.add(Point{500, 800});
    p4.add(Point{500, 200});
    p4.add(Point{700, 200});
    p4.translate(10, 5);

    if(p3.number_of_points() == 4
       && almostEqual(p4.point(0).x, 710, 1.1)
       && almostEqual(p4.point(0).y, 795, 1.1)
       && almostEqual(p4.getPointMatrix()(0,0), 110)
       && almostEqual(p4.getPointMatrix()(1,0), -295)
       && almostEqual(p4.point(1).x, 510, 1.1)
       && almostEqual(p4.point(1).y, 795, 1.1)
       && almostEqual(p4.getPointMatrix()(0,1), -90)
       && almostEqual(p4.getPointMatrix()(1,1), -295)
       && almostEqual(p4.point(2).x, 510, 1.1)
       && almostEqual(p4.point(2).y, 195, 1.1)
       && almostEqual(p4.getPointMatrix()(0,2), -90)
       && almostEqual(p4.getPointMatrix()(1,2), 305)
       && almostEqual(p4.point(3).x, 710, 1.1)
       && almostEqual(p4.point(3).y, 195, 1.1)
       && almostEqual(p4.getPointMatrix()(0,3), 110)
       && almostEqual(p4.getPointMatrix()(1,3), 305))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Score: " << score << " / 10" << endl;
}

void transform(PolygonMatrix& poly)
{
    static int testCounter = 0;
    static double d_theta = (4 * pi) / (FPS * 2);
    static double d_scale = 0.1;
    static double g_scale = 1.0;
    static int shiftCount = FPS / 2;
    static double g_shift = (Fl::w() > Fl::h() ? Fl::h(): Fl::w()) / FPS;

    if(testCounter < FPS * 2)   ///rotate
    {
        poly.rotate(d_theta);
        testCounter++;
    }
    else if(testCounter < FPS * 4)    ///scale
    {
        ///revert back to 1.0 scale
        poly.scale(1 / g_scale);
        ///Scale
        if(g_scale >= 3.0 || g_scale <= 0.2) d_scale *= -1;
        g_scale += d_scale;
        poly.scale(g_scale);
        testCounter++;
        if(testCounter == FPS * 4)
        {
            poly.scale(1 / g_scale);
            g_scale = 1.0;
        }
    }
    else if(testCounter < FPS * 6)   ///translate
    {
        ///Translate
        if(shiftCount >= FPS)
        {
            g_shift *= -1;
            shiftCount = 0;
        }
        poly.translate(g_shift, g_shift);
        testCounter++;
        shiftCount++;
    }
    else if(testCounter < FPS * 8)   ///rotate and scale
    {
        ///revert back to 1.0 scale
        poly.scale(1 / g_scale);
        ///rotate
        poly.rotate(d_theta);
        ///Scale
        if(g_scale >= 3.0 || g_scale <= 0.2) d_scale *= -1;
        g_scale += d_scale;
        poly.scale(g_scale);
        testCounter++;
        if(testCounter == FPS * 8)
        {
            poly.scale(1 / g_scale);
            g_scale = 1.0;
        }
    }
    else   ///start over
    {
        testCounter = 0;
    }
}

static void Timer_CB(void *obj)
{
    PolygonMatrix& poly = *((PolygonMatrix*)obj);
    transform(poly);
    Fl::redraw();
    Fl::repeat_timeout(TIMESTEP, Timer_CB, (void*)(&poly));
}
