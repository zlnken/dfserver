#encoding=utf-8
import os
import socket
import time
from common import Config
from common import BSUnpack
from common import BSPack
from common import BSTcpClinet

def main():

	myname = socket.getfqdn(socket.gethostname())
	myaddr = socket.gethostbyname(myname)
	pack = BSPack.BSPack()
	unpack = BSUnpack.BSUnpack()

	login = BSTcpClinet.BSTcpClient(myaddr, 4096)
	login.setPack(pack)
	login.setUnpack(unpack)

	logic = BSTcpClinet.BSTcpClient(myaddr, 8080)
	logic.setPack(pack)
	logic.setUnpack(unpack)
	
	db = BSTcpClinet.BSTcpClient(myaddr, 8000)
	db.setPack(pack)
	db.setUnpack(unpack)


	login.sendKillServer()
	time.sleep(1)
	logic.sendKillServer()
	time.sleep(1)
	db.sendKillServer()
	time.sleep(1)
	#os.system("pause")

if __name__ == '__main__':
	main()