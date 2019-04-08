#include "DFIO.h"
#include "DFDateTime.h"
namespace DF{
	// -----------------------------------------------------------------------
	IO::~IO(void)
	{
	}
	// -----------------------------------------------------------------------
	IO::IO(void):
	m_bIsAfterPrint(false)
	{
	}
	// -----------------------------------------------------------------------
	void IO::redirectOutAndErrStream(const char* sFilePath)
	{
		static std::ofstream _out;
		if (_out.is_open())
		{
			_out.close();
		}
		_out.open(sFilePath, std::ios::app);
		if (!_out)
		{
			DF_EXC << "file(" << sFilePath << ") error on redirect cout!" << DF_END;
		}
		else
		{
			std::cout.rdbuf(_out.rdbuf());
			std::cerr.rdbuf(_out.rdbuf());
		}
	}
	// -----------------------------------------------------------------------
	void IO::afterPrint(const char* pString)
	{
	}
	// -----------------------------------------------------------------------
	void IO::onWork()
	{
		
	}

}