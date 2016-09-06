#include "IntegerRing.h"
#include "IntegerGroup.h"
#include "Operators.h"

/*IntegerRing::Element::Element()
{
	
}*/

/*IntegerRing::Element(const IntegerGroup::GroupElement& el)
{
	// copy everything from el into *this
	this->m = el.m;
	this->group = el.group;
}
/*
IntegerRing::Element IntegerRing::Element::operator+(const IntegerRing::Element& b)
{
	// IntegerRing is simply Abelian group under addition
	// thus, we treat the elements like group elements first, multiply under that group, and cast to ring elements
	return (IntegerRing::Element)(((IntegerGroup::GroupElement)(*this)) * ((IntegerGroup::GroupElement)b));
}

IntegerRing::Element IntegerRing::Element::operator-(const IntegerRing::Element& b)
{
	int val;
	// if this has a group
	if (this->group)
	{
		// compute (this->m - b.m) % this->group->size()
		val = (this->m - b.m) % this->group->size();
		// if that value is negative, add this->group->size() to it
		if (val < 0) val = this->group->size() + val;
	}
	// otherwise, val is simply the integer difference of this->m,b.m
	else val = this->m - b.m;
	// return element with this value
	return Element(val);
}

IntegerRing::Element IntegerRing::Element::operator*(const IntegerRing::Element& b)
{
	if (this->group)
		return IntegerRing::Element((this->m - b.m) % this->group->size());
	return IntegerRing::Element(this->m - b.m);
}

IntegerRing::Element IntegerRing::Element::operator+=(const IntegerRing::Element& b)
{
	return ((*this) = (*this) + b);
}

IntegerRing::Element IntegerRing::Element::operator-=(const IntegerRing::Element& b)
{
	return ((*this) = (*this) - b);
}

IntegerRing::Element IntegerRing::Element::operator*=(const IntegerRing::Element& b)
{
	return ((*this) = (*this) * b);
}
*/
IntegerRing::Element IntegerRing::identity(Operators op)
{
	// if op is ADDITIVE
	if (op == ADDITIVE)
		// return what the base version of this method would return
		return (IntegerRing::Element)(((IntegerGroup::GroupElement*)this)->identity());
	// multiplicative identity requested, and it is 1
	return (IntegerRing::Element)this->elements[0];
}