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
	
	virtual Exp& set_error(string& strError)
	{
		m_error = strError;
		return *this;
	}

	virtual Exp& set_error(const char * szError )
	{
		m_error = szError ? szError : ""; 
		return *this;
	}

	virtual Exp& set_errno(const int& errcode)
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
	
	virtual ~Exp(){}
private:
	int m_errno;
	string m_error;
};

class RelayExp : public Exp
{
public:
	RelayExp(int errcode = 0, string strErrorInfo = "")
	:Exp(errcode, strErrorInfo)
	{

	}
	
	virtual ~RelayExp(){} 
};

int main()
{
	std::stringstream oss;
	Exp().set_error("row not found").set_errno(10).dump(oss);
	string info = oss.str(); 
	std::cout << info << std::endl;

	oss.str("");	
	
	RelayExp().set_error("connection failed...").set_errno(20).dump(oss);
	std::cout << oss.str() << std::endl;	
	
	std::cout << "----------------demo1--------------------" << std::endl;	
	try
	{
		throw RelayExp().set_error("connection failed...").set_errno(20);
	}
	catch(const RelayExp& exp)
	{
		std::cout << "Relay Exption:" << exp.get_error() << std::endl;
		std::cout << typeid(exp).name() << std::endl;
	}
	catch(const Exp& exp)
	{
		std::cout << "Exption:" << exp.get_error() << std::endl;
		std::cout << typeid(exp).name() << std::endl;
	}

	std::cout << "----------------demo2--------------------" << std::endl;	
	try
	{
		RelayExp f;
		f.set_error("connection failed...").set_errno(20);
		throw f;
	}
	catch(const Exp& exp)
	{
		std::cout << "Exption:" << exp.get_error() << std::endl;
		std::cout << typeid(exp).name() << std::endl;
	}	
	catch(const RelayExp& exp)
	{
		std::cout << "Relay Exption:" << exp.get_error() << std::endl;
		std::cout << typeid(exp).name() << std::endl;
	}

	std::cout << "----------------demo3--------------------" << std::endl;	
	try
	{
		RelayExp f;
		f.set_error("org relay exception -- connection failed...").set_errno(201);
		throw f;
	}
	catch(Exp& exp)
	{
		std::cout << "Exption:" << exp.get_error() << std::endl;
		std::cout << typeid(exp).name() << std::endl;
		try
		{
#if 0
			//case 1,throw Exp obj
			//throw exp; 
#endif

#if 1
			//case 2, modify obj, then throw real type,this case is RelayExp
			exp.set_error("org relay exception has been caught by Exp obj, Exp obj modify error info -- connection server failed...").set_errno(2021);
			throw;       
#endif
		}
		catch(const RelayExp& exp)
		{
			std::cout << "Relay Exption:" << exp.get_error() << std::endl;
			std::cout << typeid(exp).name() << std::endl;
		}
		catch(const Exp& exp)
		{
			std::cout << "Exption:" << exp.get_error() << std::endl;
			std::cout << typeid(exp).name() << std::endl;
		}
		catch(...)
		{
			std::cout << "unKown Exption:"  << std::endl;
		}
	}	


	return 0;
}

/* *tese result*

errno=10&error=row not found
errno=20&error=connection failed...
----------------demo1--------------------
Exption:connection failed...
3Exp
----------------demo2--------------------
Exption:connection failed...
8RelayExp
----------------demo3--------------------
Exption:org relay exception -- connection failed...
8RelayExp
Relay Exption:org relay exception has been caught by Exp obj, Exp obj modify error info -- connection server failed...
8RelayExp

*/
