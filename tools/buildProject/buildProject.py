#encoding=utf-8
import os
import platform
import shutil

def newProject(name):
	path_dir = os.getcwd()
	print("projectName:", name)
	projectName = name

	
	#backstage
	root_backstage_path =  path_dir + "/../backstage"
	project_path = path_dir + "/../../project/" + projectName + "/"
	if not os.path.isdir(project_path):
		os.makedirs(project_path)

	tpath = project_path + "tools/backstage"
	if os.path.isdir(tpath):
		shutil.rmtree(tpath)
	shutil.copytree(root_backstage_path, tpath)



	#common
	root_common_path = path_dir + "/../common"
	tpath = project_path + "tools/common"
	if os.path.isdir(tpath):
		shutil.rmtree(tpath)
	shutil.copytree(root_common_path, tpath)


	#test
	root_test_path = path_dir + "/../test"
	tpath = project_path + "tools/test"
	if os.path.isdir(tpath):
		shutil.rmtree(tpath)
	shutil.copytree(root_test_path, tpath)


	# media
	root_script_path = path_dir + "/../../media/script"
	root_file_path = path_dir + "/../../media/files"
	tpath = project_path + "media/script"
	if not os.path.isdir(tpath):
		shutil.copytree(root_script_path, tpath)

	tpath = project_path + "media/files"
	if not os.path.isdir(tpath):
		shutil.copytree(root_file_path, tpath)

	# windows
	root_win_bin_path = path_dir + "/../../wk.win/bin/Release"
	root_win_lib_path = path_dir + "/../../wk.win/bin/Release/lib"
	tpath = project_path + "lib"
	if os.path.isdir(tpath):
		shutil.rmtree(tpath)
	shutil.copytree(root_win_lib_path, tpath)

	if os.path.isfile(tpath + "/libserver.exp"):
		os.remove(tpath + "/libserver.exp")
	#os.system("shell rm -r " + tpath + "/*.exp")


	file_list = os.listdir(root_win_bin_path)
	for file in file_list:
		if file[-3:] == "pdb":
			continue

		full_file = root_win_bin_path + "/" + file
		if os.path.isfile(full_file):
			shutil.copy(full_file, project_path + file)

	# unix
	root_unix_bin_path = path_dir + "/../../wk.unix/bin/release"
	root_unix_lib_path = path_dir + "/../../wk.unix/bin/release/lib"

	tpath = project_path + "lib"
	file_list = os.listdir(root_unix_lib_path)
	for file in file_list:
		full_file = root_unix_lib_path + "/" + file
		if os.path.isfile(full_file):
			shutil.copy(full_file, tpath + "/" + file)

	file_list = os.listdir(root_unix_bin_path)
	for file in file_list:
		full_file = root_unix_bin_path + "/" + file
		if os.path.isfile(full_file):
			shutil.copy(full_file, project_path + file)

	# batch
	shutil.copy(path_dir + "/batch.py", project_path + "batch.py")

	# kill
	shutil.copy(path_dir + "/../kill.py", project_path + "tools/kill.py")	

	# restart
	shutil.copy(path_dir + "/../restart.py", project_path + "tools/restart.py")	


if __name__ == '__main__':
	print("input your project name:")
	model_name = raw_input()
	newProject(model_name)
	os.system("pause")