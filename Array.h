// This code was written by Michael Warren, on April 10, 2014. If you have any questions, concerns, or suggestions, please e-mail him at mwarren04011990@gmail.com
#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <string>

/* This class will allow for a better way to store data in a container of constant size (without using a vector). In order to be
    any good, it will need to be templated. */
template <typename Object>

class Array
{
    public:
        Array();
        Array(unsigned arraySize);
        Array(const Array&);
        ~Array();
	Array& operator=(const Array&);
        unsigned getLength() const;
        //for detecting the type of this Array
        std::string getArrayType() const;
        //a setter
        void setElementAt(unsigned, const Object&);
	// a way to swap elements
	void swapElements(unsigned, unsigned);
        //operators that an Array should have
        Object& operator[](unsigned);
        const Object& operator[](unsigned) const;
        bool operator==(const Array<Object>&) const;
        bool operator!=(const Array<Object>&) const;
        friend std::ostream& operator<<(std::ostream& outputStream, const Array<Object>& theArray)
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
    private:
        static const unsigned capacity; // the size of any Array should not exceed this many elements
        unsigned length;
        Object * internalDataStorage;
        //helper function for parsing int to string
        static const std::string intToString(int);
};
//#include "Array.cpp"
#endif // ARRAY_H
