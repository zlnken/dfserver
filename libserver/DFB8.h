/************************************************************************
* @File			:	DFB8.h
* @Author		:	Sword
* @DateTime		:	2013.12.9
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFB8_H__
#define __DFB8_H__
#include "DFPrerequisite.h"

namespace DF{
	class DFExport B8
	{
	public:
		B8(void) : m_ui64(0) { m_ui64 = 0; }
		B8(unsigned int b4_0, unsigned int b4_1) { m_ui32[0] = b4_0; m_ui32[1] = b4_1; }
		B8(uint64 ui64) : m_ui64(ui64) {}
	
		operator uint64() const { return m_ui64; }
	
		inline char&				i8_0(void) { return m_i8[0]; }
		inline char&				i8_1(void) { return m_i8[1]; }
		inline char&				i8_2(void) { return m_i8[2]; }
		inline char&				i8_3(void) { return m_i8[3]; }
		inline char&				i8_4(void) { return m_i8[4]; }
		inline char&				i8_5(void) { return m_i8[5]; }
		inline char&				i8_6(void) { return m_i8[6]; }
		inline char&				i8_7(void) { return m_i8[7]; }
		inline unsigned char&		ui8_0(void) { return m_ui8[0]; }
		inline unsigned char&		ui8_1(void) { return m_ui8[1]; }
		inline unsigned char&		ui8_2(void) { return m_ui8[2]; }
		inline unsigned char&		ui8_3(void) { return m_ui8[3]; }
		inline unsigned char&		ui8_4(void) { return m_ui8[4]; }
		inline unsigned char&		ui8_5(void) { return m_ui8[5]; }
		inline unsigned char&		ui8_6(void) { return m_ui8[6]; }
		inline unsigned char&		ui8_7(void) { return m_ui8[7]; }
		inline short&				i16_0(void) { return m_i16[0]; }
		inline short&				i16_1(void) { return m_i16[1]; }
		inline short&				i16_2(void) { return m_i16[2]; }
		inline short&				i16_3(void) { return m_i16[3]; }
		inline unsigned short&		ui16_0(void) { return m_ui16[0]; }
		inline unsigned short&		ui16_1(void) { return m_ui16[1]; }
		inline unsigned short&		ui16_2(void) { return m_ui16[2]; }
		inline unsigned short&		ui16_3(void) { return m_ui16[3]; }
		inline int&					i32_0(void) { return m_i32[0]; }
		inline int&					i32_1(void) { return m_i32[1]; }
		inline unsigned int&		ui32_0(void) { return m_ui32[0]; }
		inline unsigned int&		ui32_1(void) { return m_ui32[1]; }
		inline int64&				i64(void) { return m_i64; }
		inline uint64&				ui64(void) { return m_ui64; }

	public:
		union {
			uint64					m_ui64;
			int64					m_i64;
			char					m_i8[8];
			unsigned char			m_ui8[8];
			short					m_i16[4];
			unsigned short			m_ui16[4];
			int						m_i32[2];
			unsigned int			m_ui32[2];
		};
	};
}

#endif
