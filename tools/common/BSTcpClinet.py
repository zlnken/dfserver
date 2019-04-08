#encoding=utf-8
import socket
import time
import BSUnpack
import BSPack
import struct
import Config
from datetime import datetime
# @brief 后台数据库连接
class BSTcpClient(object):
	#-----------------------------------------------------------------------
	#	@brief 构造函数
	#	@param[sHost] ip地址
	#	@param[iPort] 端口号
	def __init__(self, host, port):
		self._host = host
		self._port = port
		self._pack = None
		self._unpack = None
		self._socket = None
		self._buffer = bytearray(655345)

		try:
			self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		except socket.error, err_msg:
			print err_msg 
			return
		try:
			self._socket.connect((self._host, self._port))
		except socket.error, err_msg:
			print err_msg 
			self._socket.close()
			return

		self._socket.fileno()

	#-----------------------------------------------------------------------
	#	@brief 关闭
	def close(self):
		self._socket.close()
		self._host = None
		self._port = None
		self._pack = None
		self._unpack = None
		self._socket = None
	
	#-----------------------------------------------------------------------
	#	@brief 无效网络
	def isInvalid(self):
		return not self._socket
	#-----------------------------------------------------------------------
	#	@brief 设置打包
	#	@param[pack] 打包对象
	def setPack(self, pack):
		self._pack = pack
	#-----------------------------------------------------------------------
	#	@brief 设置解包
	#	@param[unpack] 解包对象
	def setUnpack(self, unpack):
		self._unpack = unpack
	#-----------------------------------------------------------------------
	#	@brief 发送字节流
	#	@param[byte_array] 数据
	def sendBytes(self, byte_array):
		if self.isInvalid():
			return
		self._socket.sendall(byte_array)
	#-----------------------------------------------------------------------
	#	@brief 发送打包数据
	def sendPackMsg(self):
		if self.isInvalid():
			return
		if not self._pack:
			return
		buf_size = self._pack.getBufferSize()
		buffers = self._pack.getBuffers()
		self.sendBytes(buffers[0:buf_size])
	#-----------------------------------------------------------------------
	#	@brief 发送一个对象
	#	@param[type] 消息类型
	#	@param[obj] 复合对象
	def sendObject(self, type, obj):
		if self.isInvalid():
			return
		if not self._pack:
			return
		self._pack.packType((0, type))
		self._pack.packObject(obj)
		self.sendPackMsg()
	#-----------------------------------------------------------------------
	#	@brief 收取数据
	def recvMsg(self):
		if self.isInvalid():
			return

		recv_size = self._socket.recv_into(self._buffer, 4)
		if recv_size <= 0:
			return

		msg_size, msg_type = struct.unpack_from("HH", self._buffer, 0)
		recv_size = self._socket.recv_into(self._buffer, msg_size - 4)
		self._unpack.reset(self._buffer, recv_size)
		data_object = self._unpack.unpackObject()
		print(msg_type)
		print(data_object)
	#-----------------------------------------------------------------------
	#	@brief 发送一个脚本给服务器
	#	@param[str_script] 脚本字符串
	def sendRunScritp(self, str_script):
		self._pack.packType((0, Config.Msg_GMRunScript))
		self._pack.packValue(0)
		self._pack.packString(str_script)
		self.sendPackMsg()
	#-----------------------------------------------------------------------
	#	@brief 发送一个关服命令给服务器(本机才能操作)
	def sendKillServer(self):
		self._pack.packType((0, 0))
		self._pack.packString("zhenke.luo")
		self._pack.packString("@#192748291`'[-=36-p-")
		self.sendPackMsg()
		