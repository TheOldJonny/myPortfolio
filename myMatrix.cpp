#include "myMatrix.h"
#include <iostream>
#include <stdio.h>

void validateIndices(int rowIndex, int columnIndex, int dim)
{
    if (rowIndex > dim - 1 || columnIndex > dim -1 || rowIndex < 0 || columnIndex < 0)
    {
        std::cerr<<"ERROR: Index out of range\n";
        exit(-1);
    } 
}

DiagonalMatrix::DiagonalMatrix(int* _diag, int _dim)
{
    diag = new int[_dim];
    dim = _dim;
    memcpy(diag, _diag, dim * sizeof(int));
}

DiagonalMatrix::~DiagonalMatrix()
{
    delete [] diag;
}


int DiagonalMatrix::getElement(int rowIndex, int columnIndex)
{
    validateIndices(rowIndex, columnIndex, dim);

    if (rowIndex == columnIndex)
        return diag[rowIndex];

    return 0;

}

// For a diagonal matrix you can set only the diagonal elements
void DiagonalMatrix::setElement(int index, int value)
{
    validateIndices(index, index, dim);

    diag[index] = value;
}

void DiagonalMatrix::display()
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            std::cout<<getElement(i, j)<<" ";
        }
        std::cout<<std::endl;
    }
}


LowerTriangularMatrix::LowerTriangularMatrix(int *_data, int _dim, bool _rowMajor)
{
    dim = _dim;
    int nNonZeroElements = dim * (dim + 1) / 2;
    data = new int [nNonZeroElements];
    memcpy(data, _data, nNonZeroElements * sizeof(int));

    rowMajor = _rowMajor;
}

LowerTriangularMatrix::~LowerTriangularMatrix()
{
    delete [] data;
}

int LowerTriangularMatrix::getElement(int rowIndex, int columnIndex)
{
    validateIndices(rowIndex, columnIndex, dim);

    int linearizedIndex;
    if (rowIndex >= columnIndex)
    {
        if (rowMajor)
            linearizedIndex = rowIndex * (rowIndex + 1) / 2 + columnIndex;
        else
            linearizedIndex = dim * (dim + 1) / 2 - (dim - columnIndex) * (dim - columnIndex + 1) / 2 + rowIndex - columnIndex;
   
        return data[linearizedIndex];
    }
        
    return 0;
}

void LowerTriangularMatrix::setElement(int rowIndex, int columnIndex, int value)
{
    validateIndices(rowIndex, columnIndex, dim);

    int linearizedIndex;
    if (rowIndex >= columnIndex)
    {
        if (rowMajor)
            linearizedIndex = rowIndex * (rowIndex + 1) / 2 + columnIndex;
        else
            linearizedIndex = dim * (dim + 1) / 2 - (dim - columnIndex) * (dim - columnIndex + 1) / 2 + rowIndex - columnIndex;
    
        data[linearizedIndex] = value;
    }
}

void LowerTriangularMatrix::display()
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            std::cout<<getElement(i, j)<<" ";
        }
        std::cout<<std::endl;
    }
}

// Upper triangular matrix
UpperTriangularMatrix::UpperTriangularMatrix(int *_data, int _dim, bool _rowMajor)
{
    dim = _dim;
    int nNonZeroElements = dim * (dim + 1) / 2;
    data = new int [nNonZeroElements];
    memcpy(data, _data, nNonZeroElements * sizeof(int));

    rowMajor = _rowMajor;
}

UpperTriangularMatrix::~UpperTriangularMatrix()
{
    delete [] data;
}

int UpperTriangularMatrix::getElement(int rowIndex, int columnIndex)
{
    validateIndices(rowIndex, columnIndex, dim);

    int linearizedIndex;
    if (rowIndex <= columnIndex)
    {
        if (rowMajor)
            linearizedIndex = dim * (dim + 1) / 2 - (dim - rowIndex) * (dim - rowIndex + 1) / 2 + columnIndex - rowIndex;
        else
            linearizedIndex = columnIndex * (columnIndex + 1) / 2 + rowIndex;

        return data[linearizedIndex];
    }
        
    return 0;
}

void UpperTriangularMatrix::setElement(int rowIndex, int columnIndex, int value)
{
    validateIndices(rowIndex, columnIndex, dim);
    int linearizedIndex;
    if (rowIndex <= columnIndex)
    {
        if (rowMajor)
            linearizedIndex = dim * (dim + 1) / 2 - (dim - rowIndex) * (dim - rowIndex + 1) / 2 + columnIndex - rowIndex;
        else
            linearizedIndex = columnIndex * (columnIndex + 1) / 2 + rowIndex;

        data[linearizedIndex] = value;
    }

}

void UpperTriangularMatrix::display()
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            std::cout<<getElement(i, j)<<" ";
        }
        std::cout<<std::endl;
    }
}

// Symmetric matrix
SymmetricMatrix::SymmetricMatrix(int *_data, int _dim, bool _rowMajor)
{
    dim = _dim;
    int uniqueElements = dim * (dim + 1) / 2;
    data = new int [uniqueElements];
    memcpy(data, _data, uniqueElements * sizeof(int));

    rowMajor = _rowMajor;
}

SymmetricMatrix::~SymmetricMatrix()
{
    delete [] data;
}

int SymmetricMatrix::getElement(int rowIndex, int columnIndex)
{
    validateIndices(rowIndex, columnIndex, dim);
    int linearizedIndex;
    if (rowIndex <= columnIndex)
    {
        if (rowMajor)
            linearizedIndex = dim * (dim + 1) / 2 - (dim - rowIndex) * (dim - rowIndex + 1) / 2 + columnIndex - rowIndex;
        else
            linearizedIndex = columnIndex * (columnIndex + 1) / 2 + rowIndex;

        return data[linearizedIndex];
    }
        
    return getElement(columnIndex, rowIndex);
}

void SymmetricMatrix::setElement(int rowIndex, int columnIndex, int value)
{
    validateIndices(rowIndex, columnIndex, dim);
    int linearizedIndex;
    if (rowIndex <= columnIndex)
    {
        if (rowMajor)
            linearizedIndex = dim * (dim + 1) / 2 - (dim - rowIndex) * (dim - rowIndex + 1) / 2 + columnIndex - rowIndex;
        else
            linearizedIndex = columnIndex * (columnIndex + 1) / 2 + rowIndex;

        data[linearizedIndex] = value;
        return;
    }
        
    setElement(columnIndex, rowIndex, value);

}


void SymmetricMatrix::display(bool rowMajor)
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            std::cout<<getElement(i, j)<<" ";
        }
        std::cout<<std::endl;
    }
}

// Tridiagonal matrix
TridiagonalMatrix::TridiagonalMatrix(int *_data, int _dim)
{
    dim = _dim;
    int nNonZeroElements = 3 * dim - 2;
    data = new int [nNonZeroElements];
    memcpy(data, _data, nNonZeroElements * sizeof(int));
}

TridiagonalMatrix::~TridiagonalMatrix()
{
    delete [] data;
}

int TridiagonalMatrix::getElement(int rowIndex, int columnIndex)
{
    validateIndices(rowIndex, columnIndex, dim);
    if (rowIndex - columnIndex == 1)
        return data[columnIndex];
    else if (rowIndex - columnIndex == 0)
        return data[dim -1 + columnIndex];
    else if (rowIndex - columnIndex == -1)
        return data[ dim + dim - 1 + columnIndex - 1];
    else
        return 0;      
}

void TridiagonalMatrix::setElement(int rowIndex, int columnIndex, int value)
{
    validateIndices(rowIndex, columnIndex, dim);
    int index;
    if (rowIndex - columnIndex == 1)
        index = columnIndex;
    else if (rowIndex - columnIndex == 0)
        index = dim -1 + columnIndex;
    else if (rowIndex - columnIndex == -1)
        index = dim + dim - 1 + columnIndex - 1;
    else
        return;

    data[index] = value;    
}

void TridiagonalMatrix::display()
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            std::cout<<getElement(i, j)<<" ";
        }
        std::cout<<std::endl;
    }
}

// Square band matrix
SquareBandMatrix::SquareBandMatrix(int *_data, int _dim, int _bands)
{
    dim = _dim;
    if (_bands % 2 == 0)
    {
        std::cerr<<"ERROR: the number of bands must be an odd number\n";
        exit(-1);
    }

    bands = _bands;

    int nNonZeroElements = 0;
    for (int i = 0; i < bands/2; i++)
        nNonZeroElements += (dim - i -1) * 2;
    
    nNonZeroElements += dim;
    data = new int [nNonZeroElements];
    memcpy(data, _data, nNonZeroElements * sizeof(int));
}

SquareBandMatrix::~SquareBandMatrix()
{
    delete [] data;
}

int SquareBandMatrix::getElement(int rowIndex, int columnIndex)
{
    validateIndices(rowIndex, columnIndex, dim);
    int bandIndex = bands/2 - (rowIndex - columnIndex);
    int offset = 0;
    int index;
    if (bandIndex >= 0 && bandIndex < bands)
    {
        for (int b = 0; b < bandIndex; b++)
            offset += (dim - abs(bands/2 - b));

        index = rowIndex > columnIndex ? columnIndex : rowIndex;
        
        return data[offset + index]; 

    }

    return 0;
}

void SquareBandMatrix::setElement(int rowIndex, int columnIndex, int value)
{
    validateIndices(rowIndex, columnIndex, dim);
    int bandIndex = bands/2 - (rowIndex - columnIndex);
    int offset = 0;
    int index;
    if (bandIndex >= 0 && bandIndex < bands)
    {
        for (int b = 0; b < bandIndex; b++)
            offset += (dim - abs(bands/2 - b));

        index = rowIndex > columnIndex ? columnIndex : rowIndex;
        
        data[offset + index] = value; 

    }
}

void SquareBandMatrix::display()
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            std::cout<<getElement(i, j)<<" ";
        }
        std::cout<<std::endl;
    }
}

// Toeplitz matrix
ToeplitzMatrix::ToeplitzMatrix(int *_data, int _dim)
{
    dim = _dim;
    
    int nUniqueElements = 2*dim - 1;

    data = new int [nUniqueElements];
    memcpy(data, _data, nUniqueElements * sizeof(int));
}

ToeplitzMatrix::~ToeplitzMatrix()
{
    delete [] data;
}

int ToeplitzMatrix::getElement(int rowIndex, int columnIndex)
{
    validateIndices(rowIndex, columnIndex, dim);
    if (rowIndex <= columnIndex)
        return data[columnIndex - rowIndex];

    return data[dim + rowIndex - columnIndex - 1];
        
}

void ToeplitzMatrix::setElement(int rowIndex, int columnIndex, int value)
{
    validateIndices(rowIndex, columnIndex, dim);
    if (rowIndex <= columnIndex)
        data[columnIndex - rowIndex] = value;
    else
        data[dim + rowIndex - columnIndex - 1] = value;

    return;
}

void ToeplitzMatrix::display()
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            std::cout<<getElement(i, j)<<" ";
        }
        std::cout<<std::endl;
    }
}