#encoding=utf-8

import math
import struct
import Config
from ctypes import create_string_buffer

MIN_INT8			= (-127 - 1)
MAX_INT8			= 127
MIN_INT16			= (-32767 - 1)
MAX_INT16			= 32767
MIN_INT32			= (-2147483647 - 1)
MAX_INT32			= 2147483647
MIN_INT64			= (-9223372036854775807L - 1)
MAX_INT64			= 9223372036854775807L
MAX_UINT8			= 255
MAX_UINT16			= 65535
MAX_UINT32			= 4294967295
MAX_UINT64			= 18446744073709551615L
MIN_FLOAT			= (-8388608 - 1)
MAX_FLOAT			= 8388608
MIN_DOUBLE			= (-9223372036854775807L - 1)
MAX_DOUBLE			= 9223372036854775807L


# @brief 打包
class BSPack(object):
	#-----------------------------------------------------------------------
	#	@brief 构造函数
	def __init__(self):
		self._curMaxSize = 655345
		self._curEmptySize = 655345
		self._stackDeep = 0
		self._totalBodySize = 0		
		self._packFence = bytearray(self._curMaxSize)
		self._offsetSize = 0
		self._isOk = True

	#-----------------------------------------------------------------------
	#	@brief 打包数据
	#	@param[size] 数据大小
	#	@param[fstr] 解包格式
	#	@param[data] 数据
	def packData(self, fstr, data, size):

		if size > self._curEmptySize:
			print "is full pack data"
			self._isOk = False	
			return

		struct.pack_into(fstr, self._packFence, self._offsetSize, data)
		self._curEmptySize -= size
		self._offsetSize += size
		self._totalBodySize += size
		struct.pack_into("H", self._packFence, 0, self._totalBodySize)

	#-----------------------------------------------------------------------
	#	@brief 打包一个消息类型
	#	@param[msgType] 消息类型(size, type)
	def packType(self, msg):
		self._curEmptySize = self._curMaxSize
		self._totalBodySize = 0
		self._offsetSize = 0
		self._isOk = True
		self.packData("H", msg[0], 2)
		self.packData("H", msg[1], 2)
	#-----------------------------------------------------------------------
	# 	@brief 获取剩余大小 
	def getEmptySize(self):
		return self._curEmptySize
	#-----------------------------------------------------------------------
	# 	@brief 获取大小 
	def getBufferSize(self):
		return self._totalBodySize
	#-----------------------------------------------------------------------
	# 	@brief 获取数据 
	def getBuffers(self):
		return self._packFence
	#-----------------------------------------------------------------------
	# 	@brief 获取数据 
	def getUseBuffers(self, offset):
		return self._packFence[offset:self._totalBodySize]
	#-----------------------------------------------------------------------
	#	@brief 打包一个char
	#	@param[val] 数据
	def packInt8(self, val):
		self.packData("b", val, 1)
	#-----------------------------------------------------------------------
	#	@brief 打包一个short
	#	@param[val] 数据
	def packInt16(self, val):
		self.packData("h", val, 2)

	#-----------------------------------------------------------------------
	#	@brief 打包一个int
	#	@param[val] 数据
	def packInt32(self, val):
		self.packData("i", val, 4)

	#-----------------------------------------------------------------------
	#	@brief 打包一个unsigned char
	#	@param[val] 数据
	def packUint8(self, val):
		self.packData("B", val, 1)
	#-----------------------------------------------------------------------
	#	@brief 打包一个unsigned short
	#	@param[val] 数据
	def packUint16(self, val):
		self.packData("H", val, 2)
	#-----------------------------------------------------------------------
	#	@brief 打包包一个unsigned short
	#	@param[val] 数据
	def packUint32(self, val):
		self.packData("I", val, 4)
	#-----------------------------------------------------------------------
	#	@brief 打包一个float
	#	@param[val] 数据
	def packFloat(self, val):
		self.packData("f", val, 4)
	#-----------------------------------------------------------------------
	#	@brief 打包一个double
	#	@param[val] 数据
	def packDouble(self, val):
		self.packData("d", val, 8)
	#-----------------------------------------------------------------------
	#	@brief 解包一个value
	#	@param[val] 数据
	def packValue(self, val):
		vd, _ = math.modf(val)
		if vd > 0.0:
			if val <= MAX_FLOAT and val >= MIN_FLOAT:
				self.packInt8(Config.FLOAT_FLAG)
				self.packFloat(val)
			else:
				self.packInt8(Config.DOUBLE_FLAG)
				self.packDouble(val)
		else:
			if val <= MAX_INT8 and val >= MIN_INT8:
				self.packInt8(Config.SIGNED_INT8_FLAG)
				self.packInt8(val)
			elif val <= MAX_INT16 and val >= MIN_INT16:
				self.packInt8(Config.SIGNED_INT16_FLAG)
				self.packInt16(val)
			elif val <= MAX_INT32 and val >= MIN_INT32:
				self.packInt8(Config.SIGNED_INT32_FLAG)
				self.packInt32(val)
			else:
				self.packInt8(Config.DOUBLE_FLAG)
				self.packDouble(val)
	#-----------------------------------------------------------------------
	#	@brief 打包一个srting
	#	@param[val] 数据
	def packString(self, val):
		if not val:
			self._isOk = False
			return 
		size = len(val) + 1
		if size > MAX_UINT8:
			self.packInt8(Config.BIG_STRING_FLAG)
			self.packUint16(size)
			self.packData(str(size) + "s", val + '\0', size)
		else:
			self.packInt8(Config.SMALL_STRING_FLAG)
			self.packUint8(size)
			self.packData(str(size) + "s", val + '\0', size)
	#-----------------------------------------------------------------------
	#	@brief 打包一个dict
	#	@param[val] 数据
	def packObject(self, obj):
		if type(obj) == int or type(obj) == float or type(obj) == long:
			self.packValue(obj)
		elif obj is None:
			self.packInt8(Config.NONE_FLAG)
		elif obj == True:
			self.packInt8(Config.TRUE_FLAG)
		elif obj == False:
			self.packInt8(Config.FALSE_FLAG)
		elif type(obj) == str:
			self.packString(obj)
		elif type(obj) == dict:
			self.dumpObject(obj)
		elif type(obj) == list:
			self.dumpList(obj)
		else:
			print "pack obj is error"

	#-----------------------------------------------------------------------
	#	@brief 遍历打包打包一个dict
	#	@param[obj] 数据
	def dumpObject(self, obj):
		size = len(obj)
		if size > MAX_UINT8:
			self.packInt8(Config.BIG_DICT_FLAG)
			self.packUint16(size)
		else:
			self.packInt8(Config.SMALL_DICT_FLAG)
			self.packUint8(size)

		for k, v in obj.iteritems():
			if type(k) == str:
				self.packString(k)
			else:
				self.packValue(k)
			self.packObject(v)


	def dumpList(self, obj):
		size = len(obj)
		if size > MAX_UINT8:
			self.packInt8(Config.BIG_DICT_FLAG)
			self.packUint16(size)
		else:
			self.packInt8(Config.SMALL_DICT_FLAG)
			self.packUint8(size)

		for i, v in enumerate(obj):
			self.packValue(i+1)
			self.packObject(v)