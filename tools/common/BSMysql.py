#encoding=utf-8
import MySQLdb
import time
import Config
from datetime import datetime

# @brief 后台数据库连接
class BSMysql(object):
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
	# 	@brief 查找所有表
	def searchAllTables(self):
		sql = "show tables"
		self.executeSql(sql)
		return self._sqlvalues
	#-----------------------------------------------------------------------
	# 	@brief 用ID查找一个表数据
	#	@param[role_id] 角色ID		
	def searchLoginByRoleId(self, role_id):
		sql = "select * from tb_login where role_id = %d" % role_id
		self.executeSql(sql)
		return self._sqlvalues
	#-----------------------------------------------------------------------
	# 	@brief 用ID查找一个表数据
	#	@param[role_id] 角色ID		
	def searchLoginByRoleName(self, role_name):
		sql = "select * from tb_login where role_name = '%s'" % role_name
		self.executeSql(sql)
		return self._sqlvalues
	#-----------------------------------------------------------------------
	# 	@brief 用户名字查找表数据
	#	@param[user] 用户名
	def searchLoginIdByUser(self, user):
		sql = "select * from tb_login where user = '%s'" % user
		self.executeSql(sql)
		return self._sqlvalues
	#-----------------------------------------------------------------------
	# 	@brief 用角色id查找一个value数据
	#	@param[user] 角色ID
	def searchRoleValuesByRoleId(self, role_id):
		sql = "select role_name, role_values from tb_role where role_id = %d" % role_id
		self.executeSql(sql)
		return self._sqlvalues
	#-----------------------------------------------------------------------
	# 	@brief 用角色id查找一个value数据
	#	@param[user] 角色ID
	#	@param[enum] 下标
	def searchRoleEnumValueByRoleId(self, role_id, enum):
		self.searchRoleValuesByRoleId(role_id)
		data = self._sqlvalues[0]
		self._unpack.reset(data[1], len(data[1]))		
		name = data[0]
		vals =  self._unpack.unpackObject()
		return [name, Config.RoleValues[enum][1], str(long(vals[enum]))]
	#-----------------------------------------------------------------------
	# 	@brief 用角色id查找一个objects数据
	#	@param[role_id] 角色ID
	def searchRoleObjectsByRoleId(self, role_id):
		sql = "select role_name, role_objects from tb_role where role_id = %d" % role_id
		self.executeSql(sql)
		return self._sqlvalues
	#-----------------------------------------------------------------------
	# 	@brief 用角色id查找一个object数据
	#	@param[role_id] 角色ID
	#	@param[enum] 下标
	def searchRoleEnumObjectByRoleId(self, role_id, enum):
		self.searchRoleObjectsByRoleId(role_id)
		data = self._sqlvalues[0]
		self._unpack.reset(data[1], len(data[1]))		
		name = data[0]
		vals =  self._unpack.unpackObject()
		return [name, Config.ObjectValues[enum][1], str(vals[enum])]
	#-----------------------------------------------------------------------
	# 	@brief 用角色id查找一个mails数据
	#	@param[role_id] 角色ID
	def searchRoleMailsByRoleId(self, role_id):
		sql = "select role_name, role_mails from tb_role where role_id = %d" % role_id
		self.executeSql(sql)
		return self._sqlvalues
	#-----------------------------------------------------------------------
	# 	@brief 用角色id查找一个mails数据
	#	@param[role_id] 角色ID
	def searchRoleKeyMailsByRoleId(self, role_id, key):
		data = self.searchRoleMailsByRoleId(role_id)
		self._unpack.reset(data[1], len(data[1]))
		vals =  self._unpack.unpackObject()
		return [name, key, str(vals[key])]
	#-----------------------------------------------------------------------
	# 	@brief 查找全局数据
	#	@param[name] 名字
	def searchGlobalDataByName(self, name):
		sql = "select * from tb_global_datas where key_name = '%s'" % name
		self.executeSql(sql)
		return self._sqlvalues
	#-----------------------------------------------------------------------
	# 	@brief 查找一个角色日志
	#	@param[role_id] 角色ID
	#   @param[type_name] 日志类型
	#	@param[btime] 起始时间 格式是字符串"2017-8-12 0:0:0"
	#	@param[etime] 结束时间
	def searchLogByRoleId(self, role_id, type_name, btime, etime = datetime.now()):
		bt = datetime.strptime(btime, "%Y-%m-%d %H:%M:%S")
		bs = time.mktime(bt.timetuple())

		if type(etime) == str:
			et = datetime.strptime(etime, "%Y-%m-%d %H:%M:%S")
			es = time.mktime(et.timetuple())
		else:
			es = time.mktime(etime.timetuple())

		sql = "select role_name, time, data from tb_log where role_id = %d and type_name = '%s' and time >= %d and time <= %d" % (role_id, type_name, bs, es)
		
		self.executeSql(sql)
		lines = []
		for line in self._sqlvalues:
			t = datetime.utcfromtimestamp(line[1])
			self._unpack.reset(line[2], len(line[2]))
			val = self._unpack.unpackObject()
			lines.append([line[0], str(t), type_name, str(val[1]), str(val[2]), str(val[3])])
		return lines
	#-----------------------------------------------------------------------
	# 	@brief 查找一个角色日志
	#	@param[name] 角色名字
	#	@param[btime] 起始时间 格式是字符串"2017-8-12 0:0:0"
	#	@param[etime] 结束时间
	def searchLogByRoleName(self, name, btime, etime = datetime.now()):
		bt = datetime.strptime(btime, "%Y-%m-%d %H:%M:%S")
		bs = time.mktime(bt.timetuple())

		if type(etime) == str:
			et = datetime.strptime(etime, "%Y-%m-%d %H:%M:%S")
			es = time.mktime(et.timetuple())
		else:
			es = time.mktime(etime.timetuple())

		sql = "select * from tb_log where role_name = '%s' and time >= %d and time <= %d" % (name, bs, es)
		self.executeSql(sql)
		return self._sqlvalues