#include "IntegerGroup.h"

#include <new>
#include <iostream>

IntegerGroup::IntegerGroup()
{
	
}

IntegerGroup::IntegerGroup(int n)
 : n(n), elements(Array<IntegerGroup::GroupElement>(n))
   //elements(std::vector<IntegerGroup::GroupElement>(n))
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

IntegerGroup::GroupElement::GroupElement(int x)
	: m(x), group(0)
{
	
}

IntegerGroup::GroupElement::GroupElement(int m, IntegerGroup * g)
	: group(g)
{
	// this->m must be in [0, g->size() - 1], if g not null
	if (g)
	{
		this->m = m % g->size();
		if (this->m < 0) this->m = g->size() + this->m;
	}
	else
	{
		this->m = m;
	}
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
		return GroupElement(this->val() * b.val(), this->group);
	// otherwise, perform group multiplication
	return GroupElement((this->val() + b.val()) % this->group->size(), this->group);
}

IntegerGroup::GroupElement IntegerGroup::GroupElement::operator*(int x)
{
	if (!this->group)
		return GroupElement(this->val() * x, this->group);
	return GroupElement((this->val() * x) % this->group->size());
}

IntegerGroup::GroupElement operator*(int x, const IntegerGroup::GroupElement& el)
{
	return (const_cast <IntegerGroup::GroupElement&> (el) * x);
}

IntegerGroup::GroupElement IntegerGroup::GroupElement::operator*=(const IntegerGroup::GroupElement& b)
{
	return ((*this) = (*this) * b);
}

IntegerGroup::GroupElement IntegerGroup::GroupElement::operator*=(int x)
{
	return ((*this) = (*this) * x);
}

int IntegerGroup::GroupElement::operator%(int x) const
{
	return (this->m % x);
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
IntegerGroup::GroupElement IntegerGroup::operator[](int x) const 
{
	if (x < 0) x += this->n;
	return this->elements[x % this->n]; 
}

int IntegerGroup::size() const { return this->n; }
