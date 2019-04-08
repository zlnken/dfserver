#include "DFPackMessage.h"
#include "DFMessageBase.h"
#include "DFIO.h"
#include "DFDateTime.h"
namespace DF{
	// -----------------------------------------------------------------------
	PackMessage::~PackMessage(void)
	{
		packType(0);
	}
	// -----------------------------------------------------------------------
	PackMessage::PackMessage(void) :
		m_BufQueue(),
		m_pCurBufHead(NULL),
		m_pCurPackFence(NULL),
		m_uCurMaxSize(0),
		m_uCurEmptySize(0),
		m_uStackDeep(0),
		m_uTotalBodySize(0),
		m_bIsOK(false)
	{
		/*
		这里m_uCurMaxSize比m_pCurBufHead的实际大小少100用于预留一些其他的数据空间。
		断言m_uCurMaxSize的大小，是为了保证PackBytes函数的打包规则正确。
		*/
		m_pCurBufHead = new char[Config::MAX_UINT16];
		m_uCurMaxSize = Config::MAX_UINT16 - 100;
		memset(m_pCurBufHead, 0, m_uCurMaxSize);
		DF_ASSERT(this->m_uCurMaxSize > Config::MAX_UINT16 / 2);
		packType(0);
	}
	// -----------------------------------------------------------------------
	void PackMessage::packType(unsigned short uType)
	{
		MessageBase msg(uType);
		packMsg(&msg);
	}
	// -----------------------------------------------------------------------
	MessageBase* PackMessage::getMsg(void)const
	{
		return reinterpret_cast<MessageBase*>(m_pCurBufHead);
	}
	// -----------------------------------------------------------------------
	void PackMessage::packMsg(MessageBase* pMsg)
	{
		m_pCurPackFence = m_pCurBufHead;
		m_uCurEmptySize = m_uCurMaxSize;
		m_uTotalBodySize = pMsg->getBodySize();
		m_uStackDeep = 0;
		m_bIsOK = true;

		// 清空buf队列
		while (!m_BufQueue.empty())
		{
			delete m_BufQueue.front();
			m_BufQueue.pop();
		}

		if (pMsg->getSize() > this->m_uCurEmptySize)
		{
			m_bIsOK = false;
			DF_EXC << "msg size too long in " << __FUNCTION__ << DF_END;
		}
		else
		{
			unsigned short uSize = pMsg->getSize();
			memcpy(m_pCurPackFence, pMsg, static_cast<size_t>(uSize));
			m_pCurPackFence += uSize;
			m_uCurEmptySize -= uSize;
		}
	}
	// -----------------------------------------------------------------------
	void PackMessage::packByteByNormal(void* pHead, unsigned short uSize)
	{
		// 正常打包
		memcpy(m_pCurPackFence, pHead, uSize);
		m_pCurPackFence += uSize;
		m_uCurEmptySize -= uSize;
		getMsg()->addSize(uSize);
	}

	// -----------------------------------------------------------------------
	void PackMessage::packBytes(void* pHead, unsigned short uSize)
	{

		if (m_bIsOK && m_uTotalBodySize < Config::MAX_PACK_SIZE)
		{
			// 数据大小 > 当前Buf剩余空间
			if (uSize > m_uCurEmptySize)
			{
				// 偏移长度
				unsigned short uOffsetSize = uSize - (uSize - m_uCurEmptySize);
				// 消息类型
				unsigned short uMsgType = getMsg()->getType();
				// 先打包一部分
				packByteByNormal(pHead, m_uCurEmptySize);
				// 将当前Buf存入队列，在新创建当前BUf
				m_BufQueue.push(m_pCurPackFence);
				m_pCurBufHead = new char[Config::MAX_UINT16];
				// 计算指针头
				void* pSurplusHead = static_cast<char*>(pHead)+uOffsetSize;
				unsigned short uSurplusSize = uSize - uOffsetSize;
				// 修正当前指针头
				m_pCurPackFence = m_pCurBufHead;
				m_uCurEmptySize = m_uCurMaxSize;
				// 储存消息头
				MessageBase MB(uMsgType);
				packByteByNormal(&MB, MB.getSize());
				// 储剩余数据
				packByteByNormal(&pSurplusHead, uSurplusSize - MB.getSize());
			}
			else
			{	// 正常打包
				packByteByNormal(pHead, uSize);
			}
			// 记录总长度
			m_uTotalBodySize += uSize;
		}
		else
		{
			// 打包失败
			m_bIsOK = false;
		}
	}

	// -----------------------------------------------------------------------
	void PackMessage::packInt8(char i8)
	{
		packBytes(&i8, static_cast<unsigned short>(sizeof(i8)));
	}
	// -----------------------------------------------------------------------
	void PackMessage::packInt16(short i16)
	{
		packBytes(&i16, static_cast<unsigned short>(sizeof(i16)));
	}
	// -----------------------------------------------------------------------
	void PackMessage::packInt32(int i32)
	{
		packBytes(&i32, static_cast<unsigned short>(sizeof(i32)));
	}

	// -----------------------------------------------------------------------
	void PackMessage::packUint8(unsigned char ui8)
	{
		packBytes(&ui8, static_cast<unsigned short>(sizeof(ui8)));
	}
	// -----------------------------------------------------------------------
	void PackMessage::packUint16(unsigned short ui16)
	{
		packBytes(&ui16, static_cast<unsigned short>(sizeof(ui16)));
	}
	// -----------------------------------------------------------------------
	void PackMessage::packUint32(unsigned int ui32)
	{
		packBytes(&ui32, static_cast<unsigned short>(sizeof(ui32)));
	}
	// -----------------------------------------------------------------------
	void PackMessage::packFloat(float f)
	{
		packBytes(&f, static_cast<unsigned short>(sizeof(f)));
	}
	// -----------------------------------------------------------------------
	void PackMessage::packDouble(double d)
	{
		packBytes(&d, static_cast<unsigned short>(sizeof(d)));
	}
	// -----------------------------------------------------------------------
	void PackMessage::packInt(int d)
	{
		if (d <= Config::MAX_INT8 && d >= Config::MIN_INT8)
		{
			char i8 = static_cast<char>(d);
			packInt8(Config::SIGNED_INT8_FLAG);
			packInt8(i8);
		}
		else if (d <= Config::MAX_INT16 && d >= Config::MIN_INT16)
		{
			short i16 = static_cast<short>(d);
			packInt8(Config::SIGNED_INT16_FLAG);
			packInt16(i16);
		}
		else if (d <= Config::MAX_INT32 && d >= Config::MIN_INT32)
		{
			int i32 = static_cast<int>(d);
			packInt32(Config::SIGNED_INT32_FLAG);
			packInt32(i32);
		}
	}

	// -----------------------------------------------------------------------
	void PackMessage::packValue(double d)
	{
		double fd;
		double vd = std::modf(d, &fd);
		if (vd > 0.0)
		{
			if (d <= Config::MAX_FLOAT && d >= Config::MIN_FLOAT)
			{
				packInt8(Config::FLOAT_FLAG);
				packFloat(d);
			}
			else
			{
				packInt8(Config::DOUBLE_FLAG);
				packDouble(d);
			}
		}
		else
		{
			if (d <= Config::MAX_INT8 && d >= Config::MIN_INT8)
			{
				char i8 = static_cast<char>(d);
				packInt8(Config::SIGNED_INT8_FLAG);
				packInt8(i8);
			}
			else if (d <= Config::MAX_INT16 && d >= Config::MIN_INT16)
			{
				short i16 = static_cast<short>(d);
				packInt8(Config::SIGNED_INT16_FLAG);
				packInt16(i16);
			}
			else if (d <= Config::MAX_INT32 && d >= Config::MIN_INT32)
			{
				int i32 = static_cast<int>(d);
				packInt8(Config::SIGNED_INT32_FLAG);
				packInt32(i32);
			}
			else
			{
				packInt8(Config::DOUBLE_FLAG);
				packDouble(d);
			}
		}
	}
	// -----------------------------------------------------------------------
	void PackMessage::packDict(unsigned short uSize)
	{
		if (uSize > Config::MAX_UINT8)
		{
			packInt8(Config::BIG_DICT_FLAG);
			packUint16(uSize);
		}
		else
		{
			packInt8(Config::SMALL_DICT_FLAG);
			packUint8(uSize);
		}
	}
	// -----------------------------------------------------------------------
	void PackMessage::packString(const char* v)
	{
		if (!v)
		{
			m_bIsOK = false;
			return;
		}

		size_t len = strlen(v) + 1;
		if (len > Config::MAX_UINT8)
		{
			packInt8(Config::BIG_STRING_FLAG);
			packUint16(static_cast<unsigned short>(len));
			packBytes((void*)v, static_cast<unsigned short>(len));
		}
		else
		{
			packInt8(Config::SMALL_STRING_FLAG);
			packUint8(static_cast<unsigned char>(len));
			packBytes((void*)v, static_cast<unsigned short>(len));
		}
	}

}