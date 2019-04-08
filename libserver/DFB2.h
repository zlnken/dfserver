/************************************************************************
* @File			:	DFB2.h
* @Author		:	Sword
* @DateTime		:	2013.12.9
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFB2_H__
#define __DFB2_H__
#include "DFPrerequisite.h"

namespace DF{
	class DFExport B2
	{
	public:
		B2(void):m_ui16(0){}
		B2(unsigned short ui16):m_ui16(ui16){}
		B2(unsigned char ui8_0, unsigned char ui8_1) { m_ui8[0] = ui8_0; m_ui8[1] = ui8_1; }

		inline operator unsigned short(void) const { return m_ui16; }
		inline char&			i8_0(void){ return m_i8[0]; }
		inline char&			i8_1(void){ return m_i8[1]; }
		inline unsigned char&	ui8_0(void){ return m_ui8[0]; }
		inline unsigned char&	ui8_1(void){ return m_ui8[1]; }
		inline short&			i16(void){ return m_i16; }
		inline unsigned short&	ui16(void){ return m_ui16; }

	public:
		union {
			unsigned short		m_ui16;
			short				m_i16;
			unsigned char		m_ui8[2];
			char				m_i8[2];
		};
	};
}

#endif
