#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "def.hpp"


class Array
{
public:
	virtual VALUE_T value(LENGTH_T pos) const = 0;

	virtual LENGTH_T length() const = 0;


public:

	inline
	VALUE_T operator[] (LENGTH_T pos) const 
	{
		return value(pos);
	}



	inline
	bool operator==(const Array & other) const
	{
		if (length() == other.length())
		{
			for (LENGTH_T pos = 0; pos < length(); ++pos)
			{
				if (other[pos] != VAL_UNKNOWN && value(pos) != VAL_UNKNOWN)
				{
					if (other[pos] != value(pos))
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
	bool operator!=(const Array & other) const
	{
		return !(*this == other);
	}
};


#endif
