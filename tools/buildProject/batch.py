#encoding=utf-8
import os
import platform
import shutil

def batchProject():
	normal_path = os.getcwd()
	batch_path = normal_path + "/../../"
	project_path = normal_path + "/"

	print(project_path)
	print(batch_path)


	#backstage
	root_backstage_path = batch_path + "tools/backstage"
	if not os.path.isdir(project_path):
		os.makedirs(project_path)

	tpath = project_path + "tools/backstage"
	if os.path.isdir(tpath):
		shutil.rmtree(tpath)
	shutil.copytree(root_backstage_path, tpath)

	#common
	root_common_path = batch_path + "tools/common"
	tpath = project_path + "tools/common"
	if os.path.isdir(tpath):
		shutil.rmtree(tpath)
	shutil.copytree(root_common_path, tpath)

	#test
	root_test_path = batch_path + "tools/test"
	tpath = project_path + "tools/test"
	if os.path.isdir(tpath):
		shutil.rmtree(tpath)
	shutil.copytree(root_test_path, tpath)

	# kill
	shutil.copy(batch_path + "/tools/kill.py", project_path + "tools/kill.py")	

	# restart
	shutil.copy(batch_path + "/tools/restart.py", project_path + "tools/restart.py")

	# batch
	shutil.copy(batch_path + "/tools/buildProject/batch.py", project_path + "batch.py")		


	# windows
	root_win_bin_path = batch_path + "wk.win/bin/Release"
	root_win_lib_path = batch_path + "wk.win/bin/Release/lib"
	tpath = project_path + "lib"
	if os.path.isdir(tpath):
		shutil.rmtree(tpath)
	shutil.copytree(root_win_lib_path, tpath)

	if os.path.isfile(tpath + "/libserver.exp"):
		os.remove(tpath + "/libserver.exp")

	file_list = os.listdir(root_win_bin_path)
	for file in file_list:
		if file[-3:] == "pdb":
			continue

		full_file = root_win_bin_path + "/" + file
		if os.path.isfile(full_file):
			shutil.copy(full_file, project_path + file)

	# # unix
	root_unix_bin_path = batch_path + "wk.unix/bin/release"
	root_unix_lib_path = batch_path + "wk.unix/bin/release/lib"

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

if __name__ == '__main__':
	batchProject()
	os.system("pause")