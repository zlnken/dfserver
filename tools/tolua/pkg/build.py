import os
import platform

line_list = []

def main():
	path_dir = os.getcwd()
	os.system(path_dir + "/../tolua++ -o DFLuaServerLib.cpp DFLuaServerLib.pkg")

	f = open("DFLuaServerLib.cpp")
	line_list = f.readlines()
	f.close()



	line_list_len = len(line_list)

	if 'Windows' in platform.system():
		search_value = "TOLUA_API int tolua_DFLuaServerLib_open (lua_State* tolua_S);\n"
	else:
		search_value = "TOLUA_API int  tolua_DFLuaServerLib_open (lua_State* tolua_S);\n"

	
	line_list.remove(search_value)
	insert_index = 0
	search_value = "static void tolua_reg_types (lua_State* tolua_S)\n"
	for index, value in enumerate(line_list):
		if search_value == value :
			line_list.insert(index-1, "namespace DF{\n")
			line_list.append("}\n")
			break
	
	search_value = "TOLUA_API int tolua_DFLuaServerLib_open (lua_State* tolua_S)\n"	
	line_list.reverse()
	for index, value in enumerate(line_list):
		if search_value == value:
			real_search_len = line_list_len - index
			line_list[index] = "TOLUA_API int tolua_DFLuaServerLib_open (void* void_tolua_S)\n"
			line_list.insert(index-1, " lua_State* tolua_S = static_cast<lua_State*>(void_tolua_S);\n")
			break
	

	search_value = "static int tolua_DFLuaServerLib_DF_LuaFunction_screate00(lua_State* tolua_S)\n"	
	for index, value in enumerate(line_list):
		if search_value == value:
			line_list[index-6] = "!tolua_isnoobj(tolua_S,3,&tolua_err)\n"
			line_list.insert(index-5, " !lua_isfunction(tolua_S, 2) ||\n")
			break
			
	search_value = "static int tolua_DFLuaServerLib_DF_LuaFunction_screate01(lua_State* tolua_S)\n"	
	for index, value in enumerate(line_list):
		if search_value == value:
			line_list[index-6] = "!tolua_isnoobj(tolua_S,4,&tolua_err)\n"
			line_list.insert(index-5, " !lua_isfunction(tolua_S, 3) ||\n")
			break

	search_value = "static int tolua_DFLuaServerLib_DF_BaseServer_sendObject00(lua_State* tolua_S)\n"	
	for index, value in enumerate(line_list):
		if search_value == value:
			line_list[index-8] = "!tolua_isnoobj(tolua_S,5,&tolua_err)\n"
			break

	search_value = "static int tolua_DFLuaServerLib_DF_BaseServer_sendWhoObject00(lua_State* tolua_S)\n"	
	for index, value in enumerate(line_list):
		if search_value == value:
			line_list[index-8] = "!tolua_isnoobj(tolua_S,5,&tolua_err)\n"
			break


	search_value = "static int tolua_DFLuaServerLib_DF_PackMessage_packObject00(lua_State* tolua_S)\n"	
	for index, value in enumerate(line_list):
		if search_value == value:
			line_list[index-6] = "!tolua_isnoobj(tolua_S,3,&tolua_err)\n"
			break

	search_value = "static int tolua_DFLuaServerLib_DF_UnpackMessage_unpackObject00(lua_State* tolua_S)\n"	
	for index, value in enumerate(line_list):
		if search_value == value:
			line_list[index-20] = " return 1;\n"
			line_list[index-24] = " return 1;\n"
			break
	
	search_value = "static int tolua_DFLuaServerLib_DF_LuaSystem_loadFiles00(lua_State* tolua_S)\n"	
	for index, value in enumerate(line_list):
		if search_value == value:
			line_list[index-22] = " return 1;\n"
			line_list[index-26] = " return 1;\n"
			break
			
	search_value = "static int tolua_DFLuaServerLib_DF_LuaSystem_loadAllFiles00(lua_State* tolua_S)\n"	
	for index, value in enumerate(line_list):
		if search_value == value:
			line_list[index-24] = " return 1;\n"
			line_list[index-28] = " return 1;\n"
			break
		
	line_list.reverse()


	f = open(path_dir + "/../../../libserver/DFLuaServerLib.cpp", "w")
	f.writelines(line_list)
	f.close()
	os.system("pause")

if __name__ == "__main__":
	main()