#encoding=utf-8
import os

#-----------------------------------------------------------------------
#	@brief 枚举数组数据
valueEnums = []
objectEnums = []
messageEnums = []

IpAddrs = []



data_flag = []
data_flag.append("MAX_STACK_DEEP = 30\n")
data_flag.append("NONE_FLAG = -100\n")
data_flag.append("TRUE_FLAG = -101\n")
data_flag.append("FALSE_FLAG = -102\n")
data_flag.append("SMALL_TUPLE_FLAG = -103\n")
data_flag.append("BIG_TUPLE_FLAG = -104\n")
data_flag.append("SMALL_LIST_FLAG = -105\n")
data_flag.append("BIG_LIST_FLAG = -106\n")
data_flag.append("SMALL_SET_FLAG = -107\n")
data_flag.append("BIG_SET_FLAG = -108\n")
data_flag.append("SMALL_DICT_FLAG = -109\n")
data_flag.append("BIG_DICT_FLAG = -110\n")
data_flag.append("SMALL_STRING_FLAG = -111\n")
data_flag.append("BIG_STRING_FLAG = -112\n")
data_flag.append("DATETIME_FLAG = -113\n")
data_flag.append("SIGNED_INT8_FLAG = -114\n")
data_flag.append("SIGNED_INT16_FLAG = -115\n")
data_flag.append("SIGNED_INT32_FLAG = -116\n")
data_flag.append("SIGNED_INT64_FLAG = -117\n")
data_flag.append("CLASS_OBJ_FLAG = -118\n")
data_flag.append("FLOAT_FLAG = -119\n")
data_flag.append("DOUBLE_FLAG = -120\n")

#-----------------------------------------------------------------------
#	@brief 构造枚举数组
#	@param[tar_path] 文件路径
#	@param[key] 匹配钥匙
#	@param[enum_list] 保存到数组
def buildEnums(tar_path, key, enum_list):
	file_name = tar_path
	rf = open(file_name, "r")
	list_lines = rf.readlines()
	rf.close()
	index = 1
	for line in list_lines:
		line = line.strip()
		if line[0:2] == "--":
			enum_list.append("# " + line[2:] + "\n")
		elif line[0:len(key)] == key:
			str_val = line.split('=')
			if len(str_val) > 0:
				val = str_val[0].strip() + " = " + str(index) + "\n"
				index = index + 1
				enum_list.append(val[2:])

#-----------------------------------------------------------------------
#	@brief 构造枚举数组
#	@param[tar_path] 文件路径
#	@param[key] 匹配钥匙
#	@param[ip_map] 保存到字典
def buildIpAddrs(tar_path, key, ip_list):
	file_name = tar_path
	rf = open(file_name, "r")
	list_lines = rf.readlines()
	for line in list_lines:
		line = line.strip()
		if line[0:len(key)] == key:
			e = line.index("]", 2)
			
			ip = line[3:e-1]

			b = line.index("name") + len("name")
			e = line.index(",", b)
			name = line[b:e-1].strip(" =")

			b = line.index("id") + len("id")
			e = line.index(",", b)
			world_id = "world_" + line[b:e].strip(" =")
			
			b = line.index("passwd") + len("passwd")
			e = line.index(",", b)
			passwd = line[b:e].strip(" =")

			ip_list.append("(\"" + ip + ":" + passwd[1:-1]  + ":" + world_id + "\"," + name + ":" + ip + "\"),\n") 
	ip_list[-1] = ip_list[-1][0:-2] + "\n"
				

def writeIpAdds(wf):
	wf.write("#@brief Ip地址列表数据\n")
	wf.write("IpAddrDatas=[\n")
	wf.writelines(IpAddrs)
	wf.write("]\n\n")


def writeValues(wf):
	wf.write("#@brief Ip地址列表数据\n")
	wf.write("RoleValues=[\n")
	wf.write("(0, 'Val_None'),\n")
	count = len(valueEnums)
	for i, line in enumerate(valueEnums):
		if line[0] == "#":
			pass#wf.write(line + '\n')
		else:
			datas = line.split("=")
			if i == count -1:
				wf.write("(" + datas[1].strip() + ", '" + datas[0].strip() + "')\n")
			else:
				wf.write("(" + datas[1].strip() + ", '" + datas[0].strip() + "'),\n")		
	wf.write("]\n\n")


def writeObject(wf):
	wf.write("#@brief Ip地址列表数据\n")
	wf.write("ObjectValues=[\n")
	wf.write("(0, 'Obj_None'),\n")
	count = len(objectEnums)
	for i, line in enumerate(objectEnums):
		if line[0] == "#":
			#print(line)
			pass #wf.write(line + '\n')
		else:
			datas = line.split("=")
			if i == count -1:
				wf.write("(" + datas[1].strip() + ", '" + datas[0].strip() + "')\n")
			else:
				wf.write("(" + datas[1].strip() + ", '" + datas[0].strip() + "'),\n")		
	wf.write("]\n\n")



#-----------------------------------------------------------------------
#	@brief 写出一个配置文件
#	@param[path] 文件路径
def writeConfigFile(path):
	wf = open(path + "/Config.py", "w")
	
	wf.write("#encoding=utf-8\n\n")
	
	#wf.write("#@brief 打包标志\n")
	wf.writelines(data_flag)
	wf.write("\n")

	#wf.write("#@brief 消息协议下标\n")
	wf.writelines(messageEnums)
	wf.write("\n")

	#wf.write("#@brief 角色单一数据下标\n")
	wf.writelines(valueEnums)
	wf.write("\n")


	#wf.write("#@brief 角色复杂数据下标\n")
	wf.writelines(objectEnums)
	wf.write("\n")

	writeIpAdds(wf)
	writeValues(wf)
	writeObject(wf)

	wf.close()
#-----------------------------------------------------------------------
#	@brief 主函数
def main():
	path = os.getcwd()
	target_path = path + "/../../media/script/enum/"

	buildEnums(target_path + "ValueEnums.lua", "P.Val", valueEnums)
	buildEnums(target_path + "ObjectEnums.lua", "P.Obj", objectEnums)
	buildEnums(target_path + "MessageEnums.lua", "P.Msg", messageEnums)

	buildIpAddrs(target_path + "../core/" + "ServerConfig.lua", "P[", IpAddrs)
	writeConfigFile(path)



	os.system("pause")


#-----------------------------------------------------------------------
#	@brief 执行
if __name__ == '__main__':
	main()