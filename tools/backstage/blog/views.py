# -*- coding: utf-8 -*-
from __future__ import unicode_literals
from django.shortcuts import render


# Create your views here.
from django.template import loader,Context
from django.http import HttpResponse
from django.shortcuts import render
from blog import models

import sys
sys.path.append("../")
from common import BSMysql
from common import BSUnpack
from common import BSPack
from common import BSTcpClinet
from common import BSMysql
from common import Config

pack = BSPack.BSPack()
unpack = BSUnpack.BSUnpack()

def page_not_found(request):
    '''
    404报错页面
    '''
    return render(request,'404.html')

def page_error(request):
    '''
    500报错页面
    '''
    return render(request,'500.html')


def main(request):
	if request.method == "GET" and len(request.GET) > 0:
		

		# 获取数据
		ip = request.GET["ip_addr"]
		role_id = long(request.GET["role_id"])
		role_value_enum = int(request.GET["role_values"])
		role_object_enum = int(request.GET["role_objects"])
		role_mail_key = request.GET["role_mails"]
		role_log_bt =  request.GET["log_begin_time"]
		role_log_et = request.GET["log_end_time"]
		if role_value_enum == 0 and role_object_enum == 0 and role_mail_key == "":
			return HttpResponse("None")

		# 连接数据库
		ip_data = ip.split(":")
		dbip = ip_data[0]
		dbpw = ip_data[1]
		dbname = ip_data[2]
		bsSql = BSMysql.BSMysql(dbip, 3306, "root", dbpw, dbname)
		bsSql.setPack(pack)
		bsSql.setUnpack(unpack)

		# 设置数据给html
		data_lines = []
		sql_line = []
		log_key = role_mail_key

		if role_value_enum > 0:
			log_key = Config.RoleValues[role_value_enum][1]
			if role_log_bt == "":
				sql_line = bsSql.searchRoleEnumValueByRoleId(role_id, role_value_enum)
				data_lines.append([u'角色名字', u'枚举下标', u'枚举值'])
		elif role_object_enum > 0:
			log_key = Config.ObjectValues[role_object_enum][1]
			if role_log_bt == "":
				sql_line = bsSql.searchRoleEnumObjectByRoleId(role_id, role_object_enum)
				data_lines.append([u'角色名字', u'枚举下标', u'枚举值'])
		elif role_mail_key != "" and role_log_bt == "":
			sql_line = bsSql.searchRoleKeyMailsByRoleId(role_id, role_object_enum)
			data_lines.append([u'角色名字', u'邮件键值', u'邮件内容'])

		data_lines.append(sql_line)

		if role_log_bt:
			if role_log_et != "":
				print(role_log_et)
				data_lines = bsSql.searchLogByRoleId(role_id, log_key, role_log_bt, str(role_log_et))			
			else:
				data_lines = bsSql.searchLogByRoleId(role_id, log_key, role_log_bt)

			data_lines.insert(0, [u'角色名字', u'时间', u'日志类型', u'下标', u'旧内容', u'新内容'])
			
		bsSql.close()
		return render(request, 'result.html', {"lines":data_lines})

	else:
		obj = models.RolePage()
		return render(request, 'role.html', {"obj":obj})