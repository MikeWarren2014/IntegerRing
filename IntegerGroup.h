#ifndef DATAGROUP_H
#define DATAGROUP_H

#include "Array.h"
#include <vector>	// for some reason, this didn't work.

#include <iostream>

// This group is the integers mod n
// multiplication in integer group is simply integer addition modulo n
class IntegerGroup
{
	public:
		IntegerGroup();
		IntegerGroup(int);
		class GroupElement
		{
			protected:
				int m;
				IntegerGroup* group;
			public: 
				GroupElement();
				GroupElement(int);
				GroupElement(int, IntegerGroup*);
				~GroupElement();
				GroupElement operator*(const GroupElement&);
				GroupElement operator*(int);
				friend GroupElement operator*(int, const GroupElement&);
				GroupElement operator*=(const GroupElement&);
				GroupElement operator*=(int);
				int operator%(int) const;
				bool operator==(const GroupElement&);
				bool operator!=(const GroupElement&);
				int val() const;
				friend std::ostream& operator<<(std::ostream& o, const GroupElement& e)
				{
					return (o << e.m);
				}
				
		};
		GroupElement operator[](int) const;
		GroupElement identity() const;
		int size() const;
		friend std::ostream& operator<<(std::ostream& o, const IntegerGroup& g)
		{
			return (o << g.elements);
		}
	protected:
		int n;
		//GroupElement * identity;
		Array<GroupElement> elements;
		//std::vector<GroupElement> elements;
		void createNewElement(int);
};

#endif
