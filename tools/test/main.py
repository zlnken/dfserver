#encoding=utf-8
import os
import sys
import socket
sys.path.append("..")
from common import Config
from common import BSMysql
from common import BSUnpack
from common import BSPack
from common import BSTcpClinet

def main():

	pack = BSPack.BSPack()
	unpack = BSUnpack.BSUnpack()


	myname = socket.getfqdn(socket.gethostname())
	myaddr = socket.gethostbyname(myname)

	tcp_client = BSTcpClinet.BSTcpClient(myaddr, 8080)
	tcp_client.setPack(pack)
	tcp_client.setUnpack(unpack)

	text = "gm.newDBRole(\"sword9999\", \"123456\", \"rakaji\", 1)"
	tcp_client.sendRunScritp(text)

	while True:
		tcp_client.recvMsg()


	os.system("pause")

if __name__ == '__main__':
	main()