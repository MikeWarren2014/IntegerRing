// This code was written by Michael Warren on April 10, 2014. If you have any questions, concerns, or suggestions, please e-mail him at mwarren04011990@gmail.com
// modified: September 5, 2016
#include "Array.h"

#include <iostream>
#include <new>
#include <stdexcept>
#include <typeinfo>

// header files of supported data types
#include "IntegerGroup.h"
#include "IntegerRing.h"

template <typename Object>
Array<Object>::Array()
{
    //make an empty array
    this->internalDataStorage = new(std::nothrow) Object[0];
    this->length = 0;
}

template <typename Object>
Array<Object>::Array(unsigned arraySize)
{
    //check the requested arraySize; it should NOT be greater than the capacity of Array
    if (arraySize < Array<Object>::capacity)
    {
        this->length = arraySize;
        this->internalDataStorage = new(std::nothrow) Object[arraySize];
    }
    else
    {
        std::string reason = "Requested too many elements. Maximum capacity: " +
            Array<Object>::intToString(Array<Object>::capacity);
        throw std::invalid_argument(reason);
    }
}

template <typename Object>
Array<Object>::Array(const Array& anotherArray)
 : length(anotherArray.length)
{
	// perform deep copy
	this->internalDataStorage = new(std::nothrow) Object[length];
	for (unsigned j = 0; j < length; j++)
		this->internalDataStorage[j] = anotherArray.internalDataStorage[j];
}

template <typename Object>
Array<Object>& Array<Object>::operator=(const Array& otherArray)
{
	// if the length of *this is different from the length of otherArray
	if (this->length != otherArray.length)
	{
		// set this->internalDataStorage to 0 (or delete it)
		delete[] this->internalDataStorage;
		// re-initialize it
		this->internalDataStorage = new(std::nothrow) Object[otherArray.length];
		// set this->length to otherArray.length
		this->length = otherArray.length;
	}
	// perform deep copy of otherArray
	for (unsigned j = 0; j < this->length; j++)
		this->internalDataStorage[j] = otherArray.internalDataStorage[j];
	// return *this
	return *this;
}

template <typename Object>
const std::string Array<Object>::intToString(int intToConvert)
{
    std::string intRepresentation = "";
    int power = 9, powerOfTen = 1, digit = 0;
    //setting the powerOfTen to pow(10,9), in a more reliable way
    for (int j = 1; j <= power; j++)
        powerOfTen *= 10;
    //find the first non-zero digit
    while ((digit = intToConvert / powerOfTen) == 0)
    {
        powerOfTen /= 10;
        power--;
    }
    //appending the actual digits to intRepresentation (including the current digit)
    while ((power--) >= 0)
    {
        //appending current digit to intRepresentation
        intRepresentation += (char)(0x30 + ((intToConvert / powerOfTen) % 10));
        powerOfTen /= 10;
    }
    return intRepresentation;
}

template <typename Object>
Array<Object>::~Array()
{
    if (this->internalDataStorage != 0)
        delete[] this->internalDataStorage;
}

// for knowing the size of the array (a typical C/C++ problem solved with the aid of typenames)
template <typename Object> unsigned Array<Object>::getLength() const { return this->length; }

// gets the type of data this Array holds
template <typename Object> std::string Array<Object>::getArrayType() const { return typeid(Object).name(); }

// for setting the Object at a position in an Array
template <typename Object>
void Array<Object>::setElementAt(unsigned index, const Object& newObjectValue)
{
    //check the index
    if (index >= this->length)
    {
        std::string explanation = "Index out of bounds. Array's length is: " + Array<Object>::intToString(this->length);
        throw std::invalid_argument(explanation);
    }
    //setting the element
    this->internalDataStorage[index] = newObjectValue;
}

// for fetching the current Object
template <typename Object> Object& Array<Object>::operator[](unsigned index)
{
    //check the index against the size of the array
    if (index >= this->length)
        throw std::invalid_argument("Array index out-of-bounds.");
    else
        return this->internalDataStorage[index];
}

// the const version of the function above
template <typename Object>
const Object& Array<Object>::operator[](unsigned index) const
{
    // check the index
    if (index >= this->getLength())
    {
        throw std::invalid_argument("Array index out-of-bounds.");
    }
    return this->internalDataStorage[index];
}

// for swapping elements
template <typename Object>
void Array<Object>::swapElements(unsigned a, unsigned b)
{
	if (a != b)
	{
		Object temp = (*this)[a];
		(*this)[a] = (*this)[b];
		(*this)[b] = temp;
	}
}

// a maximum capacity for ALL Arrays; if this value is exceeded, the Array object will fail to be created
template <typename Object> const unsigned Array<Object>::capacity = 25000;

//comparison operators
template <typename Object>
bool Array<Object>::operator==(const Array<Object>& anotherArray) const
{
    //the two should equal each other in size
    if (this->getLength() != anotherArray.getLength()) return false;
    //if the two Arrays are equal to each other, then ALL of their respective contents should equal each other
    for (int index = 0; index < this->getLength(); index++)
        if (this->internalDataStorage[index] != anotherArray[index])
            return false;
    //the code has reached here; the two Arrays ARE equal
    return true;
}

template <typename Object>
bool Array<Object>::operator!=(const Array<Object>& anotherArray) const { return !((*this)==anotherArray);  }

//for printing an Array

template <typename Object>
std::ostream& operator<<(std::ostream& outputStream, const Array<Object>& theArray)
{
    outputStream << "{ ";
    for (unsigned j = 0; j < theArray.getLength(); j++)
    {
        outputStream << theArray[j];
        if (j < theArray.getLength() - 1)
            outputStream << ", ";
    }
    return (outputStream << " }");
}

//supported type declarations go here
template class Array<int>;
template class Array<unsigned>;
template class Array<long>;
template class Array<float>;
template class Array<double>;
template class Array<long double>;
template class Array<char>;
template class Array<std::string>;
template class Array<bool>;

template class Array<IntegerGroup::GroupElement>;
//template class Array<IntegerRing::Element>;
template class Array<Array<int> >;
