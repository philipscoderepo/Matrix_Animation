#include "PolygonMatrix.h"

namespace Graph_lib {

    void PolygonMatrix::updatePixels(){

        int nCols = pointMatrix.getCols();
        int xP, yP;
        for(int i=0; i<nCols; i++){
            xP = pointMatrix(0,i);
            yP = pointMatrix(1,i);
            xP = mapRange(xP, -xPixels, 0, -xPixels/2, xPixels/2);
            yP = mapRange(yP, yPixels, 0, -yPixels/2, yPixels/2);

            Polygon::set_point(i, Point{xP, yP});
            
        }
    }
    ///used to map from pixels to Cartesian coordinates and back
    double mapRange(double n, double fromLow, double fromHigh, double toLow, double toHigh){

        return ((n - fromLow)/(fromHigh-fromLow)) * (toHigh-toLow) + toLow;
    }

    ///PolygonMatrix allows transformation matrices to be applied to graphical polygons
    ///All (x,y) coordinates stored in the matrix must be mapped to Cartesian coordinates
    ///Each coordinate is stored as one column:
    /*
        x1  x2  x3  ...
        y1  y2  y3  ...
    */
    ///construct pointMatrix with 2 rows and 0 cols
    ///store xPixels and yPixels for range mapping
    PolygonMatrix::PolygonMatrix(int _xPixels, int _yPixels) : pointMatrix(2,0){
        Matrix pointMatrix(2,0);
        xPixels = _xPixels;
        yPixels = _yPixels;
    }

    ///add a pixel vertex to the polygon
    ///call the parent add function with Point p
    ///use mapRange to map p.x and p.y to Cartesian coordinates
    ///use addCoordinate to add the mapped x and y values to pointMatrix
    void PolygonMatrix::add(Point p){
        
        Polygon::add(p);
        p.x = mapRange(p.x, -xPixels/2, xPixels/2, -xPixels, 0);
        p.y = mapRange(p.y, -yPixels/2, yPixels/2, yPixels, 0);
        pointMatrix.addCoordinate(p.x,p.y);
    }

    ///rotate polygon by theta radians counter-clockwise
    ///construct a RotationMatrix R, mulitply it by pointMatrix
    ///then call updatePixels
    void PolygonMatrix::rotate(double theta){
        RotationMatrix r(theta);
        pointMatrix = r * pointMatrix;
        updatePixels();
    }

    ///Scale the size of the polygon by factor c
    ///construct a ScalingMatrix S, multiply it by pointMatrix
    ///then call updatePixels
    void PolygonMatrix::scale(double c){
        ScalingMatrix s(c);
        pointMatrix = s * pointMatrix;
        updatePixels();
    }

    ///shift the polygon by (xShift, yShift) coordinates
    ///construct a TranslationMatrix T, add it to pointMatrix
    ///then call updatePixels
    void PolygonMatrix::translate(double xShift, double yShift){
        TranslationMatrix t(xShift, yShift, pointMatrix.getCols());
        pointMatrix = t + pointMatrix;
        updatePixels();
    }
    
    
}