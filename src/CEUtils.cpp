#include "CEUtils.h"

std::string ChEngn::itostr( int num )
{
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

const char* ChEngn::itoa( int num )
{
	return itostr( num ).c_str();
}
