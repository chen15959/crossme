#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include "def.hpp"


class Sequence
{
public:
	virtual VALUE_T operator[] (LENGTH_T pos) const = 0;

	virtual LENGTH_T length() const = 0;


public:
	inline
	bool operator==(const Sequence & other) const
	{
		if (length() == other.length())
		{
			for (LENGTH_T pos = 0; pos < length(); ++pos)
			{
				if (other[pos] != VAL_UNKNOWN && (*this)[pos] != VAL_UNKNOWN)
				{
					if (other[pos] != (*this)[pos])
					{
						return false;
					}
				}
			}

			return true;
		}
		else
		{
			return false;
		}
	}



	inline
	bool operator!=(const Sequence & other) const
	{
		return !(*this == other);
	}
};


#endif
