#include "CEException.h"
#include "CEUtils.h"
#include <string>

const char* CE::BadMove::what() throw()
{
	std::string mess = "Cant make move: ";
	mess +=  itostr( m_num );
	mess += " : ";
	mess += m_ply.toStdString();
	return mess.c_str();
}


CE::BadMove& CE::BadMove::operator << (const char* txt) throw()
{
	return *this << (std::string(txt));
}

CE::BadMove& CE::BadMove::operator << (const std::string& txt) throw()
{
	m_comm += txt;
	return *this;
}

CE::BadMove& CE::BadMove::operator << ( bool val) throw()
{
	if(val)
		m_comm += "true";
	else
		m_comm += "false";
	return *this;
}

CE::BadMove& CE::BadMove::operator << ( int val) throw()
{
	return *this << itoa(val);
}
