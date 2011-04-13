#include "CEException.h"

ChEngn::Exception::Exception( const ChEngn::ERROR_CODE code,
							  const ChEngn::ERROR_MSG mess )
							  throw()
{
	setCode( code );
	setMessage( mess );
}

ChEngn::Exception::Exception( const ChEngn::Exception& other )
							  throw()
{
	setCode( other.code() );
	setMessage( other.what() );
}
