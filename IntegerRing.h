#ifndef INTEGERRING_H
#define INTEGERRING_H

#include "IntegerGroup.h"
#include "Operators.h"

class IntegerRing : public IntegerGroup
{
	public:
		IntegerRing();
		IntegerRing(int);
		IntegerRing(const IntegerGroup&);
		class Element : public IntegerGroup::GroupElement::GroupElement
		{
			Element * inverse;
			public: 
				Element();
				Element(int, IntegerGroup*);
				//~Element();
				operator IntegerGroup::GroupElement() { return IntegerGroup::GroupElement(); }
				Element(const IntegerGroup::GroupElement&);
				Element operator+(int);
				Element operator+(const Element&);
				friend Element operator+(int, const Element&);
				Element operator-();
				Element operator-(int);
				Element operator-(const Element&);
				friend Element operator-(int, const Element&);
				Element operator*(int);
				Element operator*(const Element&);
				friend Element operator*(int, const Element&);
				Element operator+=(const Element&);
				Element operator-=(const Element&);
				Element operator*=(const Element&);
				
		};
		Element identity(Operators);
		Element inverse(int);
		Element inverse(const Element&);
	private:
		
};

#endif
