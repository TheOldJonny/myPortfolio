// To do:
// 2. setElement function for all the classes
// rowMajor as private attribute of the classes

class DiagonalMatrix
{
    public:
        // Constructor
        DiagonalMatrix(int *_diag, int _dim);
        ~DiagonalMatrix();

        int getElement(int rowIndex, int columnIndex);
        void setElement(int index, int value);
        void display();
    
    private:
        int *diag;
        int dim;


};

class LowerTriangularMatrix
{
    public:
        LowerTriangularMatrix(int * _data, int _dim, bool _rowMajor = true);
        ~LowerTriangularMatrix();
        
        int getElement(int rowIndex, int columnIndex);
        void setElement(int rowIndex, int columnIndex, int value);
        void display();

    private:
        int *data;
        int dim;
        bool rowMajor;

};

class UpperTriangularMatrix
{
    public:
        UpperTriangularMatrix(int * _data, int _dim, bool _rowMajor = true);
        ~UpperTriangularMatrix();
        
        int getElement(int rowIndex, int columnIndex);
        void setElement(int rowIndex, int columnIndex, int value);
        void display();

    private:
        int *data;
        int dim;
        bool rowMajor;
};

class SymmetricMatrix
{
    public:
        SymmetricMatrix(int * _data, int _dim, bool _rowMajor = true);
        ~SymmetricMatrix();
        
        int getElement(int rowIndex, int columnIndex);
        void setElement(int rowIndex, int columnIndex, int value);
        void display(bool rowMajor = true);

    private:
        int *data;
        int dim;
        bool rowMajor;
};

// Tridiagonal matrix
class TridiagonalMatrix
{
    public:
        TridiagonalMatrix(int * _data, int _dim);
        ~TridiagonalMatrix();
        
        int getElement(int rowIndex, int columnIndex);
        void setElement(int rowIndex, int columnIndex, int value);
        void display();

    private:
        int *data;
        int dim;
};

class SquareBandMatrix
{
    public:
        SquareBandMatrix(int *_data, int _dim, int _bands=3);
        ~SquareBandMatrix();
        
        int getElement(int rowIndex, int columnIndex);
        void setElement(int rowIndex, int columnIndex, int value);
        void display();

    private:
        int *data;
        int dim;
        int bands;
};

class ToeplitzMatrix
{
    public:
        ToeplitzMatrix(int *_data, int _dim);
        ~ToeplitzMatrix();
        
        int getElement(int rowIndex, int columnIndex);
        void setElement(int rowIndex, int columnIndex, int value);
        void display();

    private:
        int *data;
        int dim;
        int bands;
};