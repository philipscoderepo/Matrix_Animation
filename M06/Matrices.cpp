#include "Matrices.h"

namespace Matrices
{
    Matrix::Matrix(int _rows, int _cols){
        rows = _rows;
        cols = _cols;
                
        a.resize(_rows);
        
        if(_cols != 0){
            for(int i = 0; i < _rows; i++){
                a.at(i).resize(_cols);
                for(int j = 0; j < _cols; j++){
                    a.at(i).at(j) = 0;
                    }
            }
        }
    }
    
    void Matrix::addCoordinate(double x, double y){
        a.at(0).push_back(x);
        a.at(1).push_back(y);
        cols += 1;
    }

    Matrix operator+(const Matrix& a, const Matrix& b){
        try
        {
            if(a.getRows() != b.getRows() || a.getCols() != b.getCols()){
                throw ("Rows and Cols are not the same");
            }
            else{
                Matrix temp(a.getRows(), a.getCols()); 
                for(int i = 0; i < a.getRows(); i++){
                    for(int j = 0; j < a.getCols(); j++){
                        temp(i,j) = a(i,j) + b(i,j);
                    }
                }
                return temp;
            }

        }
        catch(exception& e) 
        {
            cerr << e.what() << endl;
        }
        return Matrix(0,0);
    }

    Matrix operator*(const Matrix& a, const Matrix& b){
        try
        {
            if(a.getCols() != b.getRows()){
                throw ("Rows and Cols are not the same");
            }
            else{
                
                int rows = a.getRows();
                int cols = b.getCols();
                Matrix temp(rows, cols); 
                
                
                for(int i = 0; i < cols; i++){
                    for(int j = 0; j < rows; j++){   
                        double total = 0;
                        for(int k = 0; k < rows; k++){
                            total += a(j,k) * b(k,i);
                        }
                        temp(j,i) = total;
                    }
                }

                return temp;
            }
        }
        catch(exception& e) 
        {
            cerr << e.what() << endl;
        }
        return Matrix(0,0);
    }

    bool operator==(const Matrix& a, const Matrix& b){
        bool isEqual = true;
        int rows = a.getRows();
        int cols = a.getCols();

        if(a.getRows() != b.getRows() || a.getCols() != b.getCols()){
            isEqual = false;
        }
        else
        {
            for(int i = 0; i < cols && isEqual; i++){
                for(int j = 0; j < rows; j++){     
                    if(a(i,j) != b(i,j)){
                        isEqual = false;
                    }
                }
            }
            
        }

        return isEqual;
    }

    bool operator!=(const Matrix& a, const Matrix& b){
        bool isNotEqual = true;
        int rows = a.getRows();
        int cols = a.getCols();

        if(a.getRows() == b.getRows() && a.getCols() == b.getCols()){
            isNotEqual = false;
        }
        else
        {
            for(int i = 0; i < cols && isNotEqual; i++){
                for(int j = 0; j < rows; j++){     
                    if(a(i,j) == b(i,j)){
                        isNotEqual = false;
                    }
                }
            }
            
        }

        return isNotEqual;
    }

    ostream& operator<<(ostream& os, const Matrix& a){
        
        for(int i = 0; i < a.getRows(); i++){
            for(int j = 0; j < a.getCols(); j++){
                os << a(i,j) << ' ';
            }
            os << '\n';
        }   

        return os;
    }

    RotationMatrix::RotationMatrix(double theta) : Matrix(2,2){
        a.resize(2);
        a.at(0).resize(2);
        a.at(1).resize(2);

        a.at(0).at(0) = cos(theta);
        a.at(0).at(1) = -sin(theta);
        a.at(1).at(0) = sin(theta);
        a.at(1).at(1) = cos(theta);
    }

    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2,2){
        a.resize(2);
        a.at(0).resize(2);
        a.at(1).resize(2);

        a.at(0).at(0) = scale;
        a.at(0).at(1) = 0;
        a.at(1).at(0) = 0;
        a.at(1).at(1) = scale;
    }

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2,nCols){
        a.resize(2);
        a.at(0).resize(nCols);
        a.at(1).resize(nCols);

        for(int i=0;i<nCols;i++){
            a.at(0).at(i) = xShift;
            a.at(1).at(i) = yShift;
        }
    }

}