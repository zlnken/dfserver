import os
local_dir = os.getcwd()
def main():
	fileDir = local_dir + os.sep + "./"
	for root, dirs, files in os.walk(fileDir):
		for child_dir in dirs:
			os.path.join(root, child_dir)
		for file in files:
			full_file = os.path.join(root, file)
			if full_file > 5 and full_file[-5:] == ".luac":
				os.remove(full_file)
	os.system("pause")

if __name__ == "__main__":
	main()