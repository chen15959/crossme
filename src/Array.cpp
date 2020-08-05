#include "Array.hpp"



bool Array::operator==(const Array & other) const
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




