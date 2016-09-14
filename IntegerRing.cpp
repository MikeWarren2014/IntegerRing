#include "IntegerRing.h"
#include "IntegerGroup.h"
#include "Operators.h"

#include <iostream>

IntegerRing::Element::Element()
	: IntegerGroup::GroupElement()
{
	
}

IntegerRing::IntegerRing(int n)
	: IntegerGroup::IntegerGroup(n)
{
	
}

IntegerRing::Element::Element(int m, IntegerGroup * g)
	: IntegerGroup::GroupElement(m, g)
{
	
}

IntegerRing::Element::Element(const IntegerGroup::GroupElement& el)
	: IntegerGroup::GroupElement(el)
{
	
}

IntegerRing::Element IntegerRing::Element::operator+(int x)
{
	return (IntegerRing::Element)(((IntegerGroup::GroupElement)(*this)) * x);
}

IntegerRing::Element IntegerRing::Element::operator+(const IntegerRing::Element& b)
{
	// IntegerRing is simply Abelian group under addition
	// thus, we treat the elements like group elements first, multiply under that group, and cast to ring elements
	return (IntegerRing::Element)(((IntegerGroup::GroupElement)(*this)) * ((IntegerGroup::GroupElement)b));
}

IntegerRing::Element operator+(int x, const IntegerRing::Element& el)
{
	return (const_cast <IntegerRing::Element&>(el) + x);
}

IntegerRing::Element IntegerRing::Element::operator-()
{
	return IntegerRing::Element(-this->m, this->group);
}

IntegerRing::Element IntegerRing::Element::operator-(int x)
{
	return ((*this) - IntegerRing::Element(x, this->group));
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
	return Element(val, this->group);
}


IntegerRing::Element operator-(int x, const IntegerRing::Element& el)
{
	//return (x + -(const_cast<IntegerRing::Element>(el)));
	return IntegerRing::Element(x - el.m, el.group);
}

IntegerRing::Element IntegerRing::Element::operator*(int x)
{
	return ((*this) * IntegerRing::Element(x, this->group));
}

IntegerRing::Element IntegerRing::Element::operator*(const IntegerRing::Element& b)
{
	if (this->group)
		return IntegerRing::Element((this->m * b.m) % this->group->size(), this->group);
	return IntegerRing::Element(this->m * b.m, this->group);
}

IntegerRing::Element operator*(int x, const IntegerRing::Element& el)
{
	return (const_cast<IntegerRing::Element&>(el) * x);
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

IntegerRing::Element IntegerRing::identity(Operators op)
{
	// if op is ADDITIVE
	if (op == ADDITIVE)
		// return what the base version of this method would return
		return (IntegerRing::Element)(((IntegerGroup)(*this)).identity());
	// multiplicative identity requested, and it is 1
	return (IntegerRing::Element)this->elements[0];
}

IntegerRing::Element IntegerRing::inverse(int x)
{
	// make sure x in (0, this->n) . If not, either throw exception or return 0
	if ((x <= 0) || (x >= this->n)) throw IntegerRing::Element(0, this);
	// Extended Euclidean Algorithm
	int t = 0,
		r = this->n,
		newT = 1,
		newR = x;		
	while (newR != 0)
	{
		int quotient = r / newR,
			tCopy = t,
			rCopy = r,
			newTCopy = newT,
			newRCopy = newR;
		t = newT;
		newT = tCopy - quotient * newTCopy;
		r = newR;
		newR = rCopy - quotient * newRCopy;
	}
	if (r > 1)
	{
		throw IntegerRing::Element(0, this);
	}
	if (t < 0) t = t + this->n;
	return IntegerRing::Element(t, this);
}

IntegerRing::Element IntegerRing::inverse(const IntegerRing::Element& el)
{
	return this->inverse(el.val());
}
