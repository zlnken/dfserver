import os
import platform
import subprocess

def main():
	path_dir = os.getcwd() + "/../"
	if 'Windows' in platform.system():
		if not os.path.isfile(path_dir + "logServer.exe"):
			path_dir = path_dir + "wk.win/bin/Release/"
		log = path_dir +"logServer.exe"
		os.system("taskkill -f -im " + "logServer.exe")
		os.system("start " + log)
	else:
		if not os.path.isfile(path_dir + "logServer"):
			path_dir = path_dir + "wk.unix/bin/release/"
			
		log = "logServer"
		os.system("ps -ef | grep logServer | grep -v grep|awk '{print $2}'|xargs kill -9")
		subprocess.Popen("cd " + path_dir + "\n./" + log, shell=True)
		
if __name__ == "__main__":
	main()
