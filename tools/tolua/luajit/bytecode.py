import os

file_list = ["main.lua"]
local_dir = os.getcwd()
script_dir = "/../../../media/script"
bytecode_dir = "DragonFireRunScene/"



def luajit_bycode_file(full_file, file):
	if len(file) > 4 and file[-3:] == "lua":
		print("luajit bytecode " + file)
		lua_full_path = full_file
		luac_full_path = lua_full_path[0:-4] + ".luac"
		str_command = local_dir + "/luajit -b " + lua_full_path + " " + luac_full_path
		os.system(str_command)



def main():
	fileDir = local_dir + script_dir + os.sep + bytecode_dir
	for root, dirs, files in os.walk(fileDir):
		for child_dir in dirs:
			os.path.join(root, child_dir)
		for file in files:
			full_file = os.path.join(root, file)
			luajit_bycode_file(full_file, file)

	os.system("pause")

if __name__ == "__main__":
	main()