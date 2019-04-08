#encoding=utf-8
import os

#-----------------------------------------------------------------------
#	@brief 枚举数组数据
valueEnums = []
objectEnums = []
messageEnums = []

IpAddrs = []



data_flag = []
data_flag.append("public static sbyte MAX_STACK_DEEP = 30;\n")
data_flag.append("public static sbyte NONE_FLAG = -100;\n")
data_flag.append("public static sbyte TRUE_FLAG = -101;\n")
data_flag.append("public static sbyte FALSE_FLAG = -102;\n")
data_flag.append("public static sbyte SMALL_TUPLE_FLAG = -103;\n")
data_flag.append("public static sbyte BIG_TUPLE_FLAG = -104;\n")
data_flag.append("public static sbyte SMALL_LIST_FLAG = -105;\n")
data_flag.append("public static sbyte BIG_LIST_FLAG = -106;\n")
data_flag.append("public static sbyte SMALL_SET_FLAG = -107;\n")
data_flag.append("public static sbyte BIG_SET_FLAG = -108;\n")
data_flag.append("public static sbyte SMALL_DICT_FLAG = -109;\n")
data_flag.append("public static sbyte BIG_DICT_FLAG = -110;\n")
data_flag.append("public static sbyte SMALL_STRING_FLAG = -111;\n")
data_flag.append("public static sbyte BIG_STRING_FLAG = -112;\n")
data_flag.append("public static sbyte DATETIME_FLAG = -113;\n")
data_flag.append("public static sbyte SIGNED_INT8_FLAG = -114;\n")
data_flag.append("public static sbyte SIGNED_INT16_FLAG = -115;\n")
data_flag.append("public static sbyte SIGNED_INT32_FLAG = -116;\n")
data_flag.append("public static sbyte SIGNED_INT64_FLAG = -117;\n")
data_flag.append("public static sbyte CLASS_OBJ_FLAG = -118;\n")
data_flag.append("public static sbyte FLOAT_FLAG = -119;\n")
data_flag.append("public static sbyte DOUBLE_FLAG = -120;\n")

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
		if line[0:len(key)] == key:
			str_val = line.split('=')
			if len(str_val) > 0:
				val = str_val[0].strip() + " = " + str(index) + ",\n"
				index = index + 1
				enum_list.append(val[2:])
#-----------------------------------------------------------------------
#	@brief 写出一个配置文件
#	@param[path] 文件路径
def writeConfigFile(path):
	wf = open(path + "/Config.cs", "w")

	wf.write("class Config{\n")
	
	wf.write("//@brief 打包标志\n")
	wf.writelines(data_flag)
	wf.write("\n")


	wf.write("//@brief 消息协议下标\n")
	wf.write("enum MsgTypeEnum{\n")
	wf.writelines(messageEnums)
	wf.write("};\n")

	wf.write("//@brief 角色单一数据下标\n")
	wf.write("enum RoleValuesEnum{\n")
	wf.writelines(valueEnums)
	wf.write("};\n")

	wf.write("//@brief 角色复杂数据下标\n")
	wf.write("enum RoleObjectsEnum{\n")
	wf.writelines(objectEnums)
	wf.write("};\n")
	wf.write("};\n")

	wf.close()
#-----------------------------------------------------------------------
#	@brief 主函数
def main():
	path = os.getcwd()
	target_path = path + "/../../media/script/enum/"

	buildEnums(target_path + "ValueEnums.lua", "P.Val", valueEnums)
	buildEnums(target_path + "ObjectEnums.lua", "P.Obj", objectEnums)
	buildEnums(target_path + "MessageEnums.lua", "P.Msg", messageEnums)

	
	
	writeConfigFile(path)



	os.system("pause")


#-----------------------------------------------------------------------
#	@brief 执行
if __name__ == '__main__':
	main()