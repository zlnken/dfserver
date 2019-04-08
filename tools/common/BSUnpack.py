#encoding=utf-8

import struct
import Config

# @brief 解包
class BSUnpack(object):
	#-----------------------------------------------------------------------
	#	@brief 构造函数
	def __init__(self):
		self._surplusSize = 0
		self._isOK = False
		self._unpackFence = None

	#-----------------------------------------------------------------------
	#	@brief 重置位解包数据
	#	@param[pack] 打包对象
	def resetMsg(self, msg):
		if not msg:
			print("[BSUnpack.resetMsg] msg is None")
			return
		msg_size, msg_type = struct.unpack_from("HH", msg, 0)
		print(msg_size, msg_type)
		self.reset(msg, msg_size)

	#-----------------------------------------------------------------------
	#	@brief 重置位解包数据
	#	@param[data] 数组
	#	@param[size] 数据大小
	def reset(self, data, size):
		if not data:
			print("[BSUnpack.reset] data is None")
			return
		self._unpackFence = data
		self._surplusSize = size
		self._offsetSize = 0
		self._isOK = True
	#-----------------------------------------------------------------------
	#	@brief 解包数据
	#	@param[size] 数据大小
	#	@param[fstr] 解包格式
	def unpackData(self, size, fstr):
		value = (None,)
		if size <= 0:
			return value

		if size > self._surplusSize:
			self._isOK = False
		else:
			value = struct.unpack_from(fstr, self._unpackFence, self._offsetSize)
			self._surplusSize -= size
			self._offsetSize += size
		return value
	#-----------------------------------------------------------------------
	# 	@brief 获取剩余大小 
	def getSurplusSize(self):
		return self._surplusSize
	#-----------------------------------------------------------------------
	#	@brief 解包一个消息 
	#	@param[size] 数据大小
	#	@return[(size, msg)] 返回一个元组消息头和数据大小
	def unpackMsg(self):
		return self.unpackData(4, "HH")
	#-----------------------------------------------------------------------
	#	@brief 解包一个char
	#	@return[char] 
	def unpackInt8(self):
		return self.unpackData(1, "b")[0]
	#-----------------------------------------------------------------------
	#	@brief 解包一个short
	#	@return[short] 
	def unpackInt16(self):
		return self.unpackData(2, "h")[0]
	#-----------------------------------------------------------------------
	#	@brief 解包一个short
	#	@return[int] 
	def unpackInt32(self):
		return self.unpackData(4, "i")[0]
	#-----------------------------------------------------------------------
	#	@brief 解包一个unsigned char
	#	@return[unsigned char] 
	def unpackUint8(self):
		return self.unpackData(1, "B")[0]
	#-----------------------------------------------------------------------
	#	@brief 解包一个unsigned short
	#	@return[unsigned short] 
	def unpackUint16(self):
		return self.unpackData(2, "H")[0]
	#-----------------------------------------------------------------------
	#	@brief 解包一个unsigned short
	#	@return[unsigned int] 
	def unpackUint32(self):
		return self.unpackData(4, "I")[0]
	#-----------------------------------------------------------------------
	#	@brief 解包一个float
	#	@return[float] 
	def unpackFloat(self):
		return self.unpackData(4, "f")[0]
	#-----------------------------------------------------------------------
	#	@brief 解包一个double
	#	@return[double] 
	def unpackDouble(self):
		return self.unpackData(8, "d")[0]
	#-----------------------------------------------------------------------
	#	@brief 解包一个value
	#	@return[value] 
	def unpackValue(self):
		if self._surplusSize <= 0:
			self._isOK = False;
			return 0

		st = self.unpackInt8()
		if st == Config.DOUBLE_FLAG:
			return self.unpackDouble()
		elif st == Config.FLOAT_FLAG:
			return self.unpackFloat()
		elif st == Config.SIGNED_INT8_FLAG:
			return self.unpackInt8()			
		elif st == Config.SIGNED_INT16_FLAG:
			return self.unpackInt16()
		elif st == Config.SIGNED_INT32_FLAG:
			return self.unpackInt32()
		else:
			print "unpack value error."
			return None	
	#-----------------------------------------------------------------------
	#	@brief 解包一个double
	#	@return[double] 
	def unpackString(self):
		st = self.unpackInt8()
		if st == Config.SMALL_STRING_FLAG:
			size = self.unpackUint8()
			return self.unpackData(size, str(size) + "s")[0]
		elif st == Config.BIG_STRING_FLAG:
			size = self.unpackUint16()
			return self.unpackData(size, str(size) + "s")[0]
		else:
			print "unpack string error."
			return None
	#-----------------------------------------------------------------------
	#	@brief 递归数据
	#   @param[count] 数量
	def dumpObject(self,count):
		data = {}
		key = None
		for i in xrange(0, count):
			st = self.unpackInt8()
			if st == Config.SMALL_STRING_FLAG:
				size = self.unpackUint8()
				key = self.unpackData(size, "s")[0]
			elif st == Config.BIG_STRING_FLAG:
				size = self.unpackUint16()
				key = self.unpackData(size, "s")[0]
			elif st == Config.SIGNED_INT8_FLAG:
				key = self.unpackInt8()			
			elif st == Config.SIGNED_INT16_FLAG:
				key = self.unpackInt16()
			elif st == Config.SIGNED_INT32_FLAG:
				key = self.unpackInt32()

			data[key] = self.unpackObject()
		
		return data			
	#-----------------------------------------------------------------------
	#	@brief 解包一个object
	#	@return[object]
	def unpackObject(self):
		st = self.unpackInt8()
		value = None
		if st == Config.SMALL_STRING_FLAG:
			size = self.unpackUint8()
			value = self.unpackData(size, str(size) + "s")[0]
		elif st == Config.BIG_STRING_FLAG:
			size = self.unpackUint16()
			value = self.unpackData(size, str(size) + "s")[0]
		elif st == Config.SIGNED_INT8_FLAG:
			value = self.unpackInt8()			
		elif st == Config.SIGNED_INT16_FLAG:
			value = self.unpackInt16()
		elif st == Config.SIGNED_INT32_FLAG:
			value = self.unpackInt32()
		elif st == Config.DOUBLE_FLAG:
			value = self.unpackDouble()
		elif st == Config.FLOAT_FLAG:
			value =	self.unpackFloat()
		elif st == Config.FALSE_FLAG:
			value = False
		elif st == Config.TRUE_FLAG:
			value = True
		elif st == Config.NONE_FLAG:
			value = None
		elif st == Config.SMALL_DICT_FLAG:
			count = self.unpackUint8()
			value = self.dumpObject(count)
		elif st == Config.BIG_DICT_FLAG:
			count = self.unpackUint16()
			value = self.dumpObject(count)
		else:
			print "can not support type"
			return None
		
		return value