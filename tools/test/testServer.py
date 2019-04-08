	#encoding=utf-8
import os
import time
import socket
import sys
sys.path.append("..")
from common import Config
from common import BSMysql
from common import BSUnpack
from common import BSPack
from common import BSTcpClinet

def main():

	myname = socket.getfqdn(socket.gethostname())
	myaddr = socket.gethostbyname(myname)
	pack = BSPack.BSPack()
	unpack = BSUnpack.BSUnpack()
	#myaddr = "172.16.10.23"
	#login = BSTcpClinet.BSTcpClient(myaddr, 8080)
	login = BSTcpClinet.BSTcpClient("172.16.70.59", 3563)
	login.setPack(pack)
	login.setUnpack(unpack)
	login:sendObject(Config.Msg_Error, {1,2,3,4,5,"6",99})

	while True:
		login.recvMsg()
	#os.system("pause")

if __name__ == '__main__':
	main()