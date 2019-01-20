//
//	Param.hpp
//	emssroc
//
//	Created by chen.zhang on 2019/1/13.
//	Copyright © 2019 chen.zhang. All rights reserved.
//

#ifndef Param_hpp
#define Param_hpp


class Param
{
public:
	Param(int size, char type = 'A');
	
	Param(const Param & other);
	~Param();
	
	Param & operator=(const Param & rhs);
	
public:
	inline
	char getType() const
	{
		return _type;
	}
	
	inline
	int getSize() const
	{
		return _size;
	}
	
	inline
	bool isValid() const
	{
		return _size > -1;
	}
	
	
private:
	char _type;
	int _size;
};


#endif /* Param_hpp */
