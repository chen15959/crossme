//
//	Board.hpp
//	emssroc
//
//	Created by chen.zhang on 2019/1/13.
//	Copyright © 2019 chen.zhang. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp


class Point;
class Line;


class Board
{
public:
	Board(int col_size, int row_size);
	Board(const Board &);
	~Board();
	
private:
	Board & operator=(const Board &);
	
public:
	char getPointVal(int row, int col) const;
	int getPointRound(int row, int col) const;
	
	
public:
	inline
	int getRowSize() const
	{
		return this->row_size;
	}
	
	inline
	int getColSize() const
	{
		return this->col_size;
	}
	
private:
	int col_size;
	int row_size;
	
	Point ** points;

	inline
	int getIndex(int row, int col) const
	{
		return row * this->col_size + col;
	}
};


#endif /* Board_hpp */
