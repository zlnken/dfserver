import os
import platform
model_name = None

def commandNamespace(lstr):
	if lstr == "":
		return None
	key_word_name = "namespace"
	beg_pos = lstr.find(key_word_name)
	if beg_pos == -1:
		return None

	key_word_pos = beg_pos+len(key_word_name) + 1

	name_beg_pos = lstr.find("{", key_word_pos)
	if name_beg_pos == -1:
		return lstr[key_word_pos:]
	else:
		return lstr[key_word_pos:name_beg_pos]


def commandClass(lstr):
	if lstr == "":
		return None

	
	key_word_name = "class"
	beg_pos = lstr.find(key_word_name)
	if beg_pos == -1:
		return None
		
	
	key_word_pos = beg_pos+len(key_word_name) + 1
	
	name_beg_pos = lstr.find(":", key_word_pos)
	if name_beg_pos == -1:
		#print lstr[key_word_pos:]
		return lstr[key_word_pos:]
	else:
		#print lstr[key_word_pos:name_beg_pos]
		return lstr[key_word_pos:name_beg_pos]
		
		

class StaticCommand(object):
	def __init__(self):
		self.wf = None
		self.modelName = None
	def setData(self, wf, mpdelName):
		self.wf = wf
		self.modelName = mpdelName
		
	def doLine(self, lstr):
		key_word_name = "static"
		if -1 == lstr.find(key_word_name):
			return 0
		if -1 == lstr.find(";"):
			return 0
		if -1 != lstr.rfind(")"):
			return 0
			
		index = lstr.find(";")
		f_beg_pos = 0
		while (index >= 0):
			if lstr[index] == ' ' or lstr[index] == '\t':
				f_beg_pos = index
				f_beg_pos +=1
				break
			index = index-1
		#print lstr[f_beg_pos:-1]
		self.wf.write(self.modelName + "." + lstr[f_beg_pos:-1] + " = nil\n")
		return 1

class ValueCommand(object):
	def __init__(self):
		self.wf = None
		self.modelName = None
	def setData(self, wf, mpdelName):
		self.wf = wf
		self.modelName = mpdelName
		
	def doLine(self, lstr):
		if lstr == "" or lstr == "{" or lstr == "};" or lstr == "}":
			return	0
		if -1 == lstr.find(";"):
			return 0
		if -1 != lstr.rfind(")"):
			return 0
		#print lstr[0:-1]
		str_list = (lstr[0:-1]).split(',')
		for v in str_list:
			pos = v.rfind(' ')
			if pos == -1:
				pos = v.rfind('\t')
			real_v = v[pos+1:]
			self.wf.write(self.modelName + "." + real_v + " = nil\n")
		return 1


class EnumCommand(object):
	
	def __init__(self):
		self.enumName = None
		self.enumCommandState = 0
		self.enumList = []
		self.wf = None
		self.modelName = None

	def setData(self, wf, mpdelName):
		self.wf = wf
		self.modelName = mpdelName

		
	def doLine(self, lstr):
		self.doEnumName(lstr)
		self.addEnumLine(lstr)
		return self.enumCommandState


	def doEnumName(self, lstr):
		if self.enumCommandState != 0:
			return 0

		key_word_name = "enum"
		beg_pos = lstr.find(key_word_name)
		if beg_pos == -1:
			return	0
		key_word_pos = beg_pos+len(key_word_name) + 1
		name_beg_pos = lstr.find("{", key_word_pos)

		if name_beg_pos == -1:
			self.enumName = lstr[key_word_pos:]
			self.enumCommandState = 1
		else:
			self.enumName = lstr[key_word_pos:name_beg_pos]
			self.enumCommandState = 2


	def addEnumLine(self, lstr):

		if lstr == "":
			return 0

		if self.enumCommandState <= 0:
			return 0

		if lstr == "{" and self.enumCommandState == 1:
			self.enumCommandState = 2
			return 0

		if lstr == "};" and self.enumCommandState == 2:
			#print self.enumName, self.enumList
			for e in  self.enumList:
				self.wf.write(self.modelName +"." + e + "\n")
			self.enumCommandState = 0
			return 0

		if self.enumCommandState == 2:
			if lstr.find('=') != -1:
				self.enumList.append(lstr[0:lstr.find('=')] + " = nil")
			elif lstr.find(',') != -1:
				self.enumList.append(lstr[0:lstr.find(',')] + " = nil")
			else:
				print lstr
				self.enumList.append(lstr + " = nil")


class FuncCommand(object):

	def __init__(self):
		self.funcName = None
		self.funcState = 0
		self.argvList = []
		self.real_line_str = ""
		self.wf = None
		self.modelName = None
		self.gz = None

	def setData(self, wf, mpdelName, className):
		self.wf = wf
		self.modelName = mpdelName
		self.gz = className+"("

	def doLine(self, lstr):

		if lstr == "" or lstr == "{" or lstr == "};" or lstr == "}" or lstr[0] == "~" or -1 != lstr[0:len(self.gz)] == self.gz or -1 != lstr.find("operator"):
			#print lstr
			return

		if lstr[-1:] == ';' and self.real_line_str == "":
			self.real_line_str = lstr
			self.commandFunction(self.real_line_str)
			self.real_line_str = ""
		elif lstr[-1:] == ';' and self.real_line_str != "":
			self.real_line_str = self.real_line_str + lstr
			self.commandFunction(self.real_line_str)
			self.real_line_str = ""
		else:
			self.real_line_str = self.real_line_str + lstr

		
	def commandFunction(self, lstr):
		f_end_pos = lstr.find("(")
		index = f_end_pos
		f_beg_pos = 0
		while (index >= 0):
			if lstr[index] == ' ' or lstr[index] == '\t':
				f_beg_pos = index
				f_beg_pos +=1
				break
			index = index-1
		
		#print(lstr[f_beg_pos:f_end_pos])
		line_str = lstr[f_beg_pos:f_end_pos] + "("

		argv_end_pos = lstr.find(")", f_end_pos)
		argvs_str = lstr[f_end_pos+1:argv_end_pos]

		argvs_list = argvs_str.split(",")
		for argv_str in argvs_list:
			argv_str = argv_str.lstrip(" \t\n")
			argv_str = argv_str.rstrip(" \t\n")
			str_list = argv_str.split(" ")
			for i in range(len(str_list)-1,-1,-1):
				if ' ' == str_list[i]:
					del str_list[i]
				elif '\t' ==  str_list[i]:
					del str_list[i]
			#print str_list
			str_list_len = len(str_list)
			if str_list_len == 2 or str_list_len == 4:
				line_str = line_str + str_list[1] + ","
			elif str_list_len == 3:
				line_str = line_str + str_list[2] + ","

		if line_str[-1] == ',':
			line_str = line_str[0:-1]

		line_str = line_str + ")"

		if line_str == "()":
			return

		self.wf.write("function " + self.modelName + "." + line_str + "\n")
		self.wf.write("end\n")


def runfile(fileName, wf):

	global model_name
	namespace_name = None
	class_name = None
	
	staticCommand = StaticCommand()
	valueCommand = ValueCommand()
	enumCommand = EnumCommand()
	funcCommand = FuncCommand()

	line_list = []
	f = open(fileName)
	line_list = f.readlines()

	for lstr in line_list:
		lstr = lstr.lstrip(" \t\n")
		lstr = lstr.rstrip(" \t\n")

		if lstr == "public\n":
			continue

		if namespace_name == None:
			namespace_name = commandNamespace(lstr)
			continue

		if class_name == None:
			class_name = commandClass(lstr)
			class_name = class_name.lstrip(" \t\n")
			class_name = class_name.rstrip(" \t\n")
			
			model_name = namespace_name + "." + class_name
			staticCommand.setData(wf, model_name)
			valueCommand.setData(wf, model_name)
			enumCommand.setData(wf, model_name)
			funcCommand.setData(wf, model_name, class_name)
			wf.write("--------------------" + model_name + "-------------------\n")
			continue

		if staticCommand.doLine(lstr) != 0:
			continue
		if valueCommand.doLine(lstr) != 0:
			continue
		if enumCommand.doLine(lstr) == 0:
			funcCommand.doLine(lstr)
			
def main():

	path_dir = os.getcwd()
	list_files = os.listdir(path_dir)

	if not os.path.isdir(path_dir + "/API"):
		os.mkdir(path_dir + "/API")
	else:
		list_files.remove("API")

	#print list_files
	
	list_files.remove("build.py")
	list_files.remove("build_api.py")
	#list_files.remove("DFMath.pkg")
	

	#print(list_files)
	
	for fName in list_files:
		fileName= fName[0:-4]
		print fileName
		wf = open("API/" + fileName + ".lua" , "w")
		runfile(fileName + ".pkg", wf)
		
	list_files = os.listdir(path_dir + "/API")
	if "DFLuaServerLibApi.lua" in list_files:
		list_files.remove("DFLuaServerLibApi.lua")
	
	aip_wf = open("API/DFLuaServerLibApi.lua", "w")
	aip_wf.write("-------------Common-----------------\n")		
	aip_wf.write("function warning(str)\nend\n")
	aip_wf.write("function printInfo(str)\nend\n")
	aip_wf.write("function printError(str)\nend\n")

	if 'Windows' in platform.system():
		aip_Windows_wf = open("C:/Users/zhenke/Documents/BabeLua/Completion/DFLuaServerLibApi.lua", "w") 
		aip_Windows_wf.write("-------------Common-----------------\n")		
		aip_Windows_wf.write("function warning(str)\nend\n")
		aip_Windows_wf.write("function printInfo(str)\nend\n")
		aip_Windows_wf.write("function printError(str)\nend\n")
		
	for fName in list_files:
		fileName= fName[0:-4]
		rf = open("API/" + fileName + ".lua" , "r")
		list_list = rf.readlines()
		aip_wf.writelines(list_list)
		if 'Windows' in platform.system():
			aip_Windows_wf.writelines(list_list)




	
	os.system("pause")

if __name__ == "__main__":
	main()