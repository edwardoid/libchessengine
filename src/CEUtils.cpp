#include "CEUtils.h"
#include <stdio.h>

std::string CE::itostr( int num )
{
	return std::string(itoa(num));
	if( num == 0 )
		return std::string("0");

	std::string res;
	if ( num < 0 )
		res += '-';
	while( num != 0 )
	{
		res +=  '0' + num % 10;
		num /= 10;
	}
}

const char* CE::itoa( int num )
{
	char* numStr = new char[10];
	sprintf(numStr, "%d", num);
	return numStr;
}



