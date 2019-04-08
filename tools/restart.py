import os
import platform
import subprocess

def main():
	path_dir = os.getcwd() + "/../"
	if 'Windows' in platform.system():
		if not os.path.isfile(path_dir + "logicServer.exe"):
			path_dir = path_dir + "wk.win/bin/Release/"
	
		logic = path_dir +"logicServer.exe"
		db = path_dir +"dbServer.exe"
		login = path_dir +"loginServer.exe"
		os.system("taskkill -f -im " + "loginServer.exe")
		os.system("taskkill -f -im " + "logicServer.exe")
		os.system("taskkill -f -im " + "dbServer.exe")
		os.system("start " + db)
		os.system("start " + logic)
		os.system("start " + login)
	else:
		if not os.path.isfile(path_dir + "logicServer"):
			path_dir = path_dir + "wk.unix/bin/release/"
			
		logic = "logicServer"
		db = "dbServer"
		login = "loginServer"
		
		os.system("ps -ef | grep loginServer | grep -v grep|awk '{print $2}'|xargs kill -9")
		os.system("ps -ef | grep logicServer | grep -v grep|awk '{print $2}'|xargs kill -9")
		os.system("ps -ef | grep dbServer | grep -v grep|awk '{print $2}'|xargs kill -9")

		subprocess.Popen("cd " + path_dir + "\n./" + db, shell=True)
		subprocess.Popen("cd " + path_dir + "\n./" + logic, shell=True)
		subprocess.Popen("cd " + path_dir + "\n./" + login, shell=True)

		
		#os.system("cd " + path_dir + "\n open " + db)
		# os.system("open terminal\n cd " + path_dir + "\n ./" + logic)
		# os.system("open terminal\n cd " + path_dir + "\n ./" + login)
		
if __name__ == "__main__":
	main()
