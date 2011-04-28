#include "CEException.h"
#include "CEUtils.h"
#include <string>

const char* ChEngn::BadMove::what() throw()
{
	std::string mess = "Cant make move: ";
	mess +=  itostr( m_num );
	mess += " : ";
	mess += m_ply.toStdString();
	return mess.c_str();
}

