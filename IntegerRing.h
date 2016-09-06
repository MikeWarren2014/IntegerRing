#ifndef INTEGERRING_H
#define INTEGERRING_H

#include "IntegerGroup.h"
#include "Operators.h"

class IntegerRing : public IntegerGroup
{
	public:
		class Element : public IntegerGroup::GroupElement
		{
			public: 
				using IntegerGroup::GroupElement;
				/*Element();
				Element(int);
				Element(int, IntegerRing*);
				~Element();*/
				operator IntegerGroup::GroupElement() { return IntegerGroup::GroupElement(); }
				Element(const IntegerGroup::GroupElement& el)
				{
					// copy everything from el into *this
					this->m = el.m;
					this->group = el.group;
				}
				/*Element operator+(const Element&);
				Element operator-(const Element&);
				Element operator*(const Element&);
				Element operator+=(const Element&);
				Element operator-=(const Element&);
				Element operator*=(const Element&);*/
				
		};
		Element identity(Operators);
	private:
		
};

#endif
