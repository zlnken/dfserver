#encoding=utf-8
import traceback
import MySQLdb
import time
import Config
from datetime import datetime

# @brief 后台数据库连接
class DBRole(object):
	#-----------------------------------------------------------------------
	#	@brief 构造函数
	#	@param[sHost] ip地址
	#	@param[iPort] 端口号
	#	@param[sUser] mysql用户名
	#	@param[sPasswd] mysql密码
	#	@param[sDB] 数据库名字
	def __init__(self, sHost, iPort, sUser, sPasswd, sDB):
		self._conn = MySQLdb.connect(host=sHost, port=iPort, user=sUser, passwd=sPasswd,db=sDB)
		if not self._conn:
			print("connect database is error by[" + sHost + ":" + str(iPort) + " " + sUser +":" + sPasswd, " " + sDB)
			return
		self._cursor = self._conn.cursor()
		self._sqlvalues = None
		self._pack = None
		self._unpack = None
	#-----------------------------------------------------------------------
	#	@brief 关闭
	def close(self):
		if self._cursor:
			self._cursor.close()
		if self._conn:
			self._conn.close()
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
	# 	@brief 执行数据库语句
	#	@param[sql] 数据库语句	
	def executeSql(self, sql):
		try:
			self._cursor.execute(sql)
			self._sqlvalues = self._cursor.fetchall()
		except  MySQLdb.Error,e:
			print "Mysql Error %d: %s" % (e.args[0], e.args[1])
		return self._sqlvalues
	#-----------------------------------------------------------------------
	# 	@brief 提交SQL
	def commitSql(self):
		if self._conn:
			self._conn.conmit()
	#-----------------------------------------------------------------------
	# 	@brief 检测
	def check(self):
		if self._pack is None:
			print "[DBRole:check] self._pack is None"
			print traceback.print_exc()
			return True
		if self._unpack is None:
			print "[DBRole:check] self._unpack is None"
			print traceback.print_exc()
			return True
		if self._roleID is None:
			print "[DBRole:check] self._roleID is None"
			print traceback.print_exc()
			return True
	#-----------------------------------------------------------------------
	# 	@brief 角色ID索引初始化角色
	#	@param[sql] 数据库语句	
	def initRoleByID(self, role_id):
		sql = "select user, password, role_name, role_id from tb_login where role_id = %d" % role_id
		self.executeSql(sql)
		data = self._sqlvalues[0]
		self.initRoleData(data)
	#-----------------------------------------------------------------------
	# 	@brief 角色ID索引初始化角色
	#	@param[sql] 数据库语句	
	def initRoleByName(self, name):
		sql = "select user, password, role_name, role_id from tb_login where role_name = '%s'" % name
		self.executeSql(sql)
		data = self._sqlvalues[0]
		self.initRoleData(data)
	#-----------------------------------------------------------------------
	# 	@brief 清空角色数据
	def clearRoleData(self):
		# 用户
		self._user = None
		# 密码
		self._password = None
		# 角色ID
		self._roleID = None
		# 名字
		self._name = None
		# 单一数据组
		self._values = None
		# 复合数据组
		self._object = None
		# 邮件数据组
		self._mails = None
	#-----------------------------------------------------------------------
	# 	@brief 初始化角色
	#	@param[data] 数据	
	def initRoleData(self, data):
		# 用户
		self._user = data[0]
		# 密码
		self._password = data[1]
		# 名字
		self._name = data[2]
		# 角色ID
		self._roleID = data[3]

		# 检测
		if self.check():
			return 

		# 二进制单一数据
		binary_values = self.selectValues()[0][0]
		# 二进制复合数据
		binary_objects = self.selectObjects()[0][0]
		# 二进制邮件数据
		binary_mails = self.selectMails()[0][0]
		# 制单一数据
		self._unpack.reset(binary_values, len(binary_values))		
		self._values = self._unpack.unpackObject()
		# 复合数据
		self._unpack.reset(binary_objects, len(binary_objects))		
		self._objects = self._unpack.unpackObject()
		# 邮件数据
		self._unpack.reset(binary_mails, len(binary_mails))		
		self._mails = self._unpack.unpackObject()
	#-----------------------------------------------------------------------
	# 	@brief 新建一个角色
	#	@param[user] 用户
	#	@param[password] 密码
	#	@param[role_name] 角色名字
	#	@param[role_id] 角色ID
	def newRole(self, user, password, role_name, role_id):
		tbLoginInsert = "insert into tb_login(user, password, role_name, role_id) values('%s', '%s', '%s', %d);"
		sql = tbLoginInsert % (user, password, role_name, role_id)
		self.executeSql(sql)

		tbRoleInsert = "insert into tb_role(role_name, role_id) values('%s', %d);"
		sql = tbRoleInsert % (role_name, role_id)
		self.executeSql(sql)
		# 用户
		self._user = user
		# 密码
		self._password = password
		# 角色ID
		self._roleID = role_id
		# 名字
		self._name = role_name
		# 单一数据组
		self._values = []
		# 复合数据组
		self._object = []
		# 邮件数据组
		self._mails = {}
	#-----------------------------------------------------------------------
	# 	@brief 删除一个角色
	def deleteRole(self):
		# 从角色表删除
		tbRoleDeleteRole = "delete from tb_role where role_id=%d;"
		sql = tbRoleDeleteRole % self._roleID
		self.executeSql(sql)
		# 从登录表删除
		tbLoginDeleteUser = "delete from tb_login where role_id=%d;"
		sql = tbLoginDeleteUser % self._roleID
		self.executeSql(sql)
		# 清空数据
		self.clearRoleData()
	#-----------------------------------------------------------------------
	# 	@brief 保存
	def save(self):
		# 单一数据
		self._pack.packType((0,0))
		self._pack.packObject(self._values)
		self.updateValues(MySQLdb.Binary(self._pack.getUseBuffers(4)))
		# 复合数据
		self._pack.packType((0,0))
		self._pack.packObject(self._objects)
		self.updateValues(MySQLdb.Binary(self._pack.getUseBuffers(4)))
		# 邮件数据
		self._pack.packType((0,0))
		self._pack.packObject(self._mails)
		self.updateValues(MySQLdb.Binary(self._pack.getUseBuffers(4)))
	#-----------------------------------------------------------------------
	# 	@brief 倒号
	#	@param[sHost] ip地址
	#	@param[iPort] 端口号
	#	@param[sUser] mysql用户名
	#	@param[sPasswd] mysql密码
	#	@param[sDB] 数据库名字
	def dumpTo(self, sHost, iPort, sUser, sPasswd, sDB):
		# 创建
		dump_role = DBRole(sHost, iPort, sUser, sPasswd, sDB)
		# 赋值解包和压包
		dump_role._pack = self._pack
		dump_role._unpack = self._unpack
		# 创建一个新角色
		dump_role.newRole(self._user, self._password, self._name, self._roleID)
		# 赋值数据
		dump_role._values = self._values
		dump_role._objects = self._objects
		dump_role._mails = self._mails
		# 写入数据库
		dump_role.save()
	#-----------------------------------------------------------------------
	# 	@brief 更新角色单一数据
	#	@param[datas] 二进制数据
	def updateValues(self, datas):
		if self.check():
			return
		if datas is None:
			return
		sql = "update tb_role set role_values='%s' where role_id=%d;" % (datas, self._roleID)
		self.executeSql(sql)
	#-----------------------------------------------------------------------
	# 	@brief 更新角色复合数据
	#	@param[role_id] 角色ID
	#	@param[datas] 二进制数据
	def updateObjects(self, datas):
		if self.check():
			return
		if datas is None:
			return
		sql = "update tb_role set role_objects='%s' where role_id=%d;" % (datas, self._roleID)
		self.executeSql(sql)
	#-----------------------------------------------------------------------
	# 	@brief 获取角色邮件数据
	#	@param[role_id] 角色ID
	#	@param[datas] 二进制数据
	def updateMails(self, datas):
		if self.check():
			return
		if datas is None:
			return
		sql = "update tb_role set role_mails='%s' where role_id=%d;" % (datas, self._roleID)
		self.executeSql(sql)
	#-----------------------------------------------------------------------
	# 	@brief 更新角色单一数据
	def selectValues(self):
		if self.check():
			return
		sql = "select role_values from tb_role where role_id= %d;" % self._roleID
		return self.executeSql(sql)
	#-----------------------------------------------------------------------
	# 	@brief 获取角色复合数据
	def selectObjects(self):
		if self.check():
			return
		sql = "select role_objects from tb_role where role_id= %d;" % self._roleID
		return self.executeSql(sql)
	#-----------------------------------------------------------------------
	# 	@brief 获取角色邮件数据
	def selectMails(self):
		if self.check():
			return
		sql = "select role_mails from tb_role where role_id= %d;" % self._roleID
		return self.executeSql(sql)
	#-----------------------------------------------------------------------
	# 	@brief 获取角色单一数据
	#	@param[enum] 枚举
	def getEnumValue(self, enum):
		if self.check():
			return
		return self._values[enum]
	#-----------------------------------------------------------------------
	# 	@brief 获取角色复合数据
	#	@param[enum] 枚举
	def getEnumObject(self, enum):
		if self.check():
			return
		return self._objects[enum]
	#-----------------------------------------------------------------------
	# 	@brief 获取角色邮件数据
	#	@param[enum] 枚举
	def getEnumMail(self, enum):
		if self.check():
			return
		return self._mails[enum]
	#-----------------------------------------------------------------------
	# 	@brief 设置角色单一数据
	#	@param[enum] 枚举
	#	@param[val] 值
	def setEnumValue(self, enum, val):
		if self.check():
			return
		self._values[enum] = val
	#-----------------------------------------------------------------------
	# 	@brief 获取角色邮件数据
	#	@param[enum] 枚举
	#	@param[val] 值
	def setEnumObject(self, enum, val):
		if self.check():
			return
		self._objects[enum] = val
	#-----------------------------------------------------------------------
	# 	@brief 获取角色邮件数据
	#	@param[enum] 枚举
	#	@param[val] 值
	def setEnumMail(self, enum, val):
		if self.check():
			return
		self._mails[enum] = val


