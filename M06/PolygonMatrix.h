#ifndef PARTICLES_H_INCLUDED
#define PARTICLES_H_INCLUDED

#include "Matrices.h"
#include "Graph.h"

using namespace Matrices;

namespace Graph_lib
{
    ///used to map from pixels to Cartesian coordinates and back
    double mapRange(double n, double fromLow, double fromHigh, double toLow, double toHigh);

    ///PolygonMatrix allows transformation matrices to be applied to graphical polygons
    ///All (x,y) coordinates stored in the matrix must be mapped to Cartesian coordinates
    ///Each coordinate is stored as one column:
    /*
        x1  x2  x3  ...
        y1  y2  y3  ...
    */
    ///use mapRange to map from pixels to the specified cartesian coordinate range
    class PolygonMatrix : public Polygon
    {
        public:
            ///construct pointMatrix with 2 rows and 0 cols
            ///store xPixels and yPixels for range mapping
            PolygonMatrix(int _xPixels, int _yPixels);

            ///add a pixel vertex to the polygon
            ///call the parent add function with Point p
            ///use mapRange to map p.x and p.y to Cartesian coordinates
            ///use addCoordinate to add the mapped x and y values to pointMatrix
            void add(Point p);

            ///rotate polygon by theta radians counter-clockwise
            ///construct a RotationMatrix R, mulitply it by pointMatrix
            ///then call updatePixels
            void rotate(double theta);

            ///Scale the size of the polygon by factor c
            ///construct a ScalingMatrix S, multiply it by pointMatrix
            ///then call updatePixels
            void scale(double c);

            ///shift the polygon by (xShift, yShift) coordinates
            ///construct a TranslationMatrix T, add it to pointMatrix
            ///then call updatePixels
            void translate(double xShift, double yShift);

            ///Const getter for the unit tester to view the internal matrix
            const Matrix& getPointMatrix() const{return pointMatrix;}

        private:
            Matrix pointMatrix;
            int xPixels;
            int yPixels;

            ///Loop through each column of point matrix
            ///map each coordinate to pixels
            ///call Shape::set_point to update each pixel
            void updatePixels();
    };

}

#endif // PARTICLES_H_INCLUDED
