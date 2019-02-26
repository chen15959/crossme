#ifndef util_hpp
#define util_hpp


//用斯特林公式求n的阶乘(的近似值)
double factorial_stirling(unsigned long n);


//信息压缩与解压缩
long zip(short a, short b);
void unzip(long zip, short & a, short & b);


#endif
