/************************************************************************
* @File			:	DFB4.h
* @Author		:	Sword
* @DateTime		:	2013.12.9
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFB4_H__
#define __DFB4_H__
#include "DFPrerequisite.h"

namespace DF{
	class DFExport B4
	{
	public:
		B4(void) :m_ui32(0){}
		B4(unsigned int ui32) :m_ui32(ui32){}
		B4(unsigned short ui16_0, unsigned short ui16_1) { m_ui16[0] = ui16_0; m_ui16[1] = ui16_1; }

		inline operator unsigned int() const { return m_ui32; }

		inline char&				i8_0(void) { return m_i8[0]; }
		inline char&				i8_1(void) { return m_i8[1]; }
		inline char&				i8_2(void) { return m_i8[2]; }
		inline char&				i8_3(void) { return m_i8[3]; }
		inline unsigned char&		ui8_0(void) { return m_ui8[0]; }
		inline unsigned char&		ui8_1(void) { return m_ui8[1]; }
		inline unsigned char&		ui8_2(void) { return m_ui8[2]; }
		inline unsigned char&		ui8_3(void) { return m_ui8[3]; }
		inline short&				i16_0(void) { return m_i16[0]; }
		inline short&				i16_1(void) { return m_i16[1]; }
		inline unsigned short&		uI16_0(void) { return m_ui16[0]; }
		inline unsigned short&		uI16_1(void) { return m_ui16[1]; }
		inline int&					i32(void) { return m_i32; }
		inline unsigned int&		uI32(void) { return m_ui32; }

	public:
		union {
			unsigned int		m_ui32;
			int					m_i32;
			char				m_i8[4];
			unsigned char		m_ui8[4];
			short				m_i16[2];
			unsigned short		m_ui16[2];
		};
	};
}

#endif
