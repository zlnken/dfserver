#include "DFTrigger.h"
#include "DFManager.h"
namespace DF
{
	// -----------------------------------------------------------------------
	void Trigger::sremvoe(unsigned int uId)
	{
		Manager<unsigned int, Trigger>::instancePtr()->remove(uId);
	}
	// -----------------------------------------------------------------------
	Trigger* Trigger::sfind(unsigned int uId)
	{
		return Manager<unsigned int, Trigger>::instancePtr()->find(uId);
	}
}