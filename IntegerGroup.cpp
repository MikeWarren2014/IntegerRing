#include "IntegerGroup.h"

#include <new>
#include <iostream>

IntegerGroup::IntegerGroup()
{
	
}

IntegerGroup::IntegerGroup(int n)
 : n(n), elements(Array<IntegerGroup::GroupElement>(n))
{
	//this is to have integers in [0,n-1]
	for (int j = 0; j < n; j++)
	{
		this->createNewElement(j);
	}
}

void IntegerGroup::createNewElement(int m)
{
	// create new GroupElement
	GroupElement newElement(m, this);
	// store it at index m in elements
	this->elements[m] = newElement;
}

IntegerGroup::GroupElement::GroupElement() 
	: group(0)
{
	
}

IntegerGroup::GroupElement::GroupElement(int m) 
	: m(m),group(0)
{
	
}

IntegerGroup::GroupElement::GroupElement(int m, IntegerGroup * g)
	: group(g)
{
	// this->m must be in [0, g->size() - 1]
	this->m = m % g->size();
	if (this->m < 0) this->m = g->size() + this->m;
}

IntegerGroup::GroupElement::~GroupElement()
{
	if (this->group)
	{
		this->group = 0;
	}
}

IntegerGroup::GroupElement IntegerGroup::identity() const
{
	// IntegerGroup consists of all integers in [0, n-1], and identity is 0
	return this->elements[0];
}

// this group is simply the integers mod n, and should be populated integers in [0,n-1]
// thus, multiplication is simply a matter of returning the element at index (a+b)%n
IntegerGroup::GroupElement IntegerGroup::GroupElement::operator*(const IntegerGroup::GroupElement& b)
{
	// if the group is not defined
	if (!this->group)
		// we simply perform integer multiplication
		return GroupElement(this->val() * b.val());
	// otherwise, perform group multiplication
	return GroupElement((this->val() + b.val()) % this->group->size());
}

IntegerGroup::GroupElement IntegerGroup::GroupElement::operator*=(const IntegerGroup::GroupElement& b)
{
	return ((*this) = (*this) * b);
}

bool IntegerGroup::GroupElement::operator==(const IntegerGroup::GroupElement& b)
{
	return this->m == b.m;
}

bool IntegerGroup::GroupElement::operator!=(const IntegerGroup::GroupElement& b)
{
	return !(*this == b);
}

int IntegerGroup::GroupElement::val() const { return this->m; }

int IntegerGroup::size() const { return this->n; }