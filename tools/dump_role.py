#encoding=utf-8
import os
import socket
import time
from common import Config
from common import BSUnpack
from common import BSPack
from common import BSTcpClinet
from common import BSMysql
from common import DBRole

#-----------------------------------------------------------------------
#	@brief 打包对象
pack = BSPack.BSPack()
#-----------------------------------------------------------------------
#	@brief 解包对象
unpack = BSUnpack.BSUnpack()
#-----------------------------------------------------------------------
#	@brief 数据库配置
DATABASE_CONFIG = {}
#-----------------------------------------------------------------------
#	@brief 初始化数据库配置
def initDatas():
	#遍历
	for k, v in Config.IpAddrDatas:
		#裁剪
		d = k.split(":")
		#保存
		DATABASE_CONFIG[d[2]] = (d[0], d[1])

#-----------------------------------------------------------------------
#	@brief 倒号
#	@param[world] 数据服id
#	@param[role_name] 角色名字
#	@param[des_world] 目标数据服
#	@param[des_role_name] 目标角色名字
def dumpRole(world, role_name, des_world, des_role_name):
	# 获取数据库配置数据
	world_cfg = DATABASE_CONFIG[world]
	# 判断
	if world_cfg is None:
		print world + "is not found"
		return
	des_world_cfg = DATABASE_CONFIG[des_world]
	# 判断
	if des_world_cfg is None:
		print des_world + "is not found" 
		return
	# 创建数据角色
	db_role = DBRole.DBRole(world_cfg[0], 3306, "root", world_cfg[1], world)
	# 设置打包对象
	db_role.setPack(pack)
	# 设置解包对象
	db_role.setUnpack(unpack)
	# 从数据库初始化角色
	db_role.initRoleByName(role_name)
	# 到入到对应的数据库
	db_role.dumpTo(des_world_cfg[0], 3306, "root", des_world_cfg[1], des_world)



	# # 获取数据库配置数据

	# # 创建数据库
	# db_world = BSMysql.BSMysql(world_cfg[0], 3306, "root", world_cfg[1], world)
	# # 登录数据
	# login_data = db_world.searchLoginByRoleName(role_name)
	# _, user, password, _, role_id = login_data[0]
	# # 单一数据
	# values = db_world.selectRoleValues(role_id)[0][0]
	# # 复合数据
	# objects = db_world.selectRoleObjects(role_id)[0][0]
	# # 关闭
	# db_world.close()

	# # 创建目标数据库
	# print des_world_cfg[0], des_world_cfg[1]
	# des_world = BSMysql.BSMysql(des_world_cfg[0], 3306, "root", des_world_cfg[1], des_world)
	# # 删除角色
	# des_world.deleteRole(role_id)
	# # 创建角色
	# des_world.createRole(user, password, des_role_name, role_id)
	# # 拷贝单一数据
	# des_world.updateRoleValues(role_id, values)
	# # 拷贝复合数据
	# des_world.updateRoleObjects(role_id, objects)
	# print "dump role %s is suceed" % des_role_name

if __name__ == '__main__':
    initDatas()
    dumpRole("world_1", "rakaji", "world_2", "rakaji")