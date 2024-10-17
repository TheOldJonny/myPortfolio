#include "myArray.h"
#include <iostream>
#include <stdio.h>

// Constructor 1: passing the size and the length of the array,
// where size >= length. If autoInizialize is set to true, all
// the array elements are inizialized to 0.
Array::Array(int length, int size, bool autoInitialize)
{
  if (length > size)
  {
    std::cout<<"ERROR: The array length should not be greater than its size\n";
    exit(-1);
  }
  this->size = size;
  this->length = length;


  A = new int[this->size];  

  if (!autoInitialize)
  {
    std::cout<<"Enter all elements\n";
    for (int i = 0; i < this->length; i++)
        std::cin>>A[i];
  }

  else
  {
    for (int i = 0; i < this->length; i++)
        A[i] = 0;
  }
  
}

// Constructor 2Iniziaizing the array with a provided array, its length, and its size
Array::Array(int *A, int length, int size)
{
    if (length > size)
    {
      std::cout<<"ERROR: The array length should not be greater than its size\n";
      exit(-1);
    }
    this->A = new int[size];
    this->length = length;
    this->size = size;

    memcpy(this->A, A, this->length * sizeof(int));
}

// Copy constructor
Array::Array(Array &sourceArray)
{
    this->length = sourceArray.length;
    this->size = sourceArray.size;

    this->A = new int[size];
    memcpy(this->A, sourceArray.A, this->length*sizeof(int));
}



// The destructor
Array::~Array()
{
    delete [] A;
}

// It displays the elements inside the array
void Array::display()
{
    std::cout<<"Displaying all the elements in the array\n";
    for (int i = 0; i < length; i++)
        std::cout<<A[i]<<std::endl;
}

// It appends the elements x to the end of the array
void Array::append(int x)
{
    if (length == size)
    {
        std::cout<<"You cannot insert more values. Limit reached\n";
        return;
    }

    length++;
    A[length - 1] = x;
}

// Inserting value at index
void Array::insert(int index, int value)
{
    if (index > length - 1 || index < 0)
    {
        std::cout<<"The index selected is not compatible with the size of the array\n";
        return;
    }

    if (length == size)
    {
        std::cout<<"You cannot insert more values. Limit reached\n";
        return;
    }

    for (int i = length - 1; i > index - 1; i--)
        A[i + 1] = A[i];

    A[index] = value;
    length++;
}

// Removing the element at index
void Array::remove(int index)
{
    if (index > length - 1 || index < 0)
    {
        std::cout<<"The index selected is not compatible with the size of the array\n";
        return;
    }

    for (int i = index; i < length; i++)
    {
        A[i] = A[i + 1];
    }

    length--;
}

// Searching the value starting from startingIndex
int Array::linearSearch(int value, int startingIndex)
{
    for (int i = startingIndex; i < length; i++)
    {
        if (A[i] == value)
            return i;
    }

    return -1;
}

// It returns the minimum of the array
int Array::min()
{
    int m = A[0];
    for (int i = 0; i < length; i++)
    {
        if (m>A[i])
            m = A[i];
    }

    return m;
}

// It returns the maximum of the array
int Array::max()
{
    int m = A[0];
    for (int i = 0; i < length; i++)
    {
        if (m<A[i])
            m = A[i];
    }

    return m;
}

// Sorting the array in ascending order
void Array::sort()
{
    int *B = new int[length];
    int recover_length = length;

    int i = 0;
    while (true)
    {
        int actual_min = min();
        int index_min = linearSearch(actual_min);
        B[i] = actual_min;

        i++;
        remove(index_min);
        if (length == 0)
            break;
    }

    delete [] A;
    A = B;
    length = recover_length;
    B = nullptr;
    delete [] B;
}

int Array::binarySearch(int value)
{
    int l = 0;
    int h = length;
    while (l <= h)
    {
        int mid = (l + h)/2;
        if (value == A[mid])
            return mid;

        else if (value < A[mid])
            h = mid - 1;
        
        else
            l = mid + 1;
    }

    return -1; 
}

int Array::get(int index)
{
    if (index > length - 1 || index < 0)
    {
        std::cout<<"The index selected is not compatible with the size of the array\n";
        return -1;
    }

    return A[index];
}

void Array::set(int index, int value)
{
    if (index > length - 1 || index < 0)
    {
        std::cout<<"The index selected is not compatible with the size of the array\n";
        return;
    }

    A[index] = value;
}

int Array::sum()
{
    int s = 0;
    for (int i = 0; i<length; i++)
        s+=A[i];

    return s;
}

int Array::average()
{
    return sum()/length;
}

void Array::reverse()
{
    int *B = new int[length];
    for (int i = 0; i < length; i++)
    {
        B[i] = A[length - 1 - i];
    }

    delete [] A;
    A = B;
    B = nullptr;

}

void Array::reverse_v2()
{
    int i, j;
    for(i=0, j = length -1; i < j; i++, j--)
    {
        int tmp = A[i];
        A[i] = A[j];
        A[j] = tmp;
    }
}

void Array::leftShift()
{
    for (int i = 1; i < length; i++)
        A[i-1] = A[i];

    A[length -1] = 0;

}

void Array::rightShift()
{
    for (int i = length - 2; i > -1; i--)
        A[i + 1] = A[i];

    A[0] = 0;
}

void Array::leftRotation()
{
    int tmp = A[0];
    for (int i = 1; i < length; i++)
        A[i-1] = A[i];

    A[length -1] = tmp;
}

void Array::rightRotation()
{
    int tmp = A[length -1];
    for (int i = length - 2; i > -1; i--)
        A[i + 1] = A[i];

    A[0] = tmp;
}

bool Array::isSorted()
{
    for (int i = 0; i < length; i++)
    {
        if (A[i] > A[i + 1] && i != length - 1)
            return false;
    }

    return true;
}

void Array::insertInSortedArray(int value)
{
    if (! isSorted())
    {
        std::cout<<"You should use this method only for a sorted array\n";
        return;
    }

    for (int i = 0; i < length; i++)
    {
        if (A[i] > value)
        {
            insert(i, value);
            return;
        }
    }

    append(value);
}

Array Array::merge(Array *secondArray)
{
    int totLength = length + secondArray->length;
    int totSize = size + secondArray->size;
    int *B = new int[totSize];
    for (int i = 0; i < totLength; i++)
    {
        if (i < length)
            B[i] = A[i];
        else
        {
            B[i] = secondArray->A[i - length];
        }
    }

    return Array::Array(B, totLength, totSize);
}

void Array::mergeInPlace(Array *secondArray)
{
    int totLength = length + secondArray->length;
    int totSize = size + secondArray->size;
    int *B = new int[totLength];

    for (int i = 0; i < totLength; i++)
    {
        if (i < length)
            B[i] = A[i];
        else
        {
            B[i] = secondArray->A[i - length];
        }
    }    
    delete [] A;
    A = B;
    B = nullptr;
    length = totLength;
    size = totSize;   
}

bool Array::compare(Array *secondArray)
{
    if (length != secondArray->length)
        return false;

    for(int i = 0; i < length; i++)
    {
        if (A[i] != secondArray->A[i])
            return false; 
    }
    return true;
}

int Array::countOccurrences(int value)
{
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (value == A[i])
            count++;
    }
    return count;

}

void Array::unique()
{
    int *pValue = A;
    int counter = 0;
    while (true)
    {
        deleteReplicates(*pValue);
        pValue++;
        counter++;

        if (counter == length)
            break;


    }
    
}

void Array::setIntersection(Array *secondArray)
{
    // removing the duplicated values in both the arrays 
    this->unique();
    secondArray->unique();

    int index = 0;
    
    while (true)
    {
        if (linearSearch(A[index]) == -1)
        {
            remove(index);
        }

        else
            index++;

        if (index == length)
            break;
    }

}

void Array::setUnion(Array *secondArray)
{
    this->mergeInPlace(secondArray);
    this->unique();
}

void Array::setDifference(Array *secondArray)
{
    this->unique();
    secondArray->unique();
    int index;
    for (int i = 0; i< secondArray->length; i++)
    {
        index = linearSearch(secondArray->A[i]);
        if (index != -1)
            remove(index);
    }
}

void Array::deleteAllOccurrencies(int value)
{
    int *pValue = A;
    int n = countOccurrences(value);

    for (int i = 0; i < n; i++)
    {
        int index = linearSearch(value);
        remove(index);
    }
}

// It leaves only one occurrence of the parameter value
void Array::deleteReplicates(int value)
{
    int *pValue = A;
    int n = countOccurrences(value) - 1;
    int startIndex = linearSearch(value);

    for (int i = 0; i < n; i++)
    {
        int index = linearSearch(value, startIndex + 1);
        remove(index);
    }
}