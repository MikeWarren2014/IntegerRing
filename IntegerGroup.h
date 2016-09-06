#ifndef DATAGROUP_H
#define DATAGROUP_H

#include "Array.h"

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
			int m;
			IntegerGroup* group;
			public: 
				GroupElement();
				GroupElement(int);
				GroupElement(int, IntegerGroup*);
				~GroupElement();
				GroupElement operator*(const GroupElement&);
				GroupElement operator*=(const GroupElement&);
				bool operator==(const GroupElement&);
				bool operator!=(const GroupElement&);
				int val() const;
				friend std::ostream& operator<<(std::ostream& o, const GroupElement& e)
				{
					return (o << e.m);
				}
				
		};
		GroupElement identity() const;
		int size() const;
		friend std::ostream& operator<<(std::ostream& o, const IntegerGroup& g)
		{
			return (o << g.elements);
		}
	private:
		int n;
		//GroupElement * identity;
		Array<GroupElement> elements;
		void createNewElement(int);
};

#endif