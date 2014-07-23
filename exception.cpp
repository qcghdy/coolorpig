#include <string>
#include <sstream>
#include <iostream>
using namespace std;

class Exp
{

public:
	Exp(int errcode = 0, string strErrorInfo = "")
	:m_errno(errcode), m_error(strErrorInfo)
	{
	}
	
	Exp& set_error(string& strError)
	{
		m_error = strError;
		return *this;
	}

	Exp& set_error(const char * szError )
	{
		m_error = szError ? szError : ""; 
		return *this;
	}

	Exp& set_errno(const int& errcode)
	{
		m_errno = errcode;
		return *this;
	}

	const string& get_error() const
	{
		return m_error;
	}

	const int& get_errno() const
	{
		return m_errno;
	}	
	
	std::ostream& dump(std::ostream& os) const
	{
		os << "errno=" << m_errno << "&error=" << m_error;
		return os;
	}
private:
	int m_errno;
	string m_error;
};

int main()
{
	std::stringstream oss;
	Exp().set_error("row not found").set_errno(10).dump(oss);
	string info = oss.str(); 
	std::cout<< info << std::endl;
	
	return 0;
}
