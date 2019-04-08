#encoding=utf-8
import socket
import threading
import SocketServer


#-----------------------------------------------------------------------
#   @brief 多线程TCP回调类
#   @param[SocketServer.BaseRequestHandler] 继承
class ThreadedTCPRequestHandler(SocketServer.BaseRequestHandler):
    #-----------------------------------------------------------------------
    #   @brief 数据回调
    def handle(self):

        try:  
            data = self.request.recv(10240)
        except socket.timeout:  # 如果接收超时会抛出socket.timeout异常  
            print(self.ip+":"+str(self.port)+"接收超时！即将断开连接！")  
        if data:    # 判断是否接收到数据  
            # cur_thread = threading.current_thread()  
            # response = bytes("{}: {}".format(cur_thread.name, data), 'ascii')  
            # self.request.sendall(response)  
            try:
                print data
            except:
                print "error data ......."

            #self.request.close()

#-----------------------------------------------------------------------
#   @brief 多线程TCP服务器
#   @param[SocketServer.ThreadingMixIn] 继承
#   @param[SocketServer.TCPServer] 继承
class ThreadedTCPServer(SocketServer.ThreadingMixIn, SocketServer.TCPServer):
    pass

#-----------------------------------------------------------------------
if __name__ == '__main__':
    myname = socket.getfqdn(socket.gethostname())
    HOST = socket.gethostbyname(myname)
    PORT = 1010
    server = ThreadedTCPServer((HOST, PORT), ThreadedTCPRequestHandler)
    ip, port = server.server_address
    print 'starting listen on ip %s, port %s'% (ip, port)
    server_thread = threading.Thread(target=server.serve_forever)
    server_thread.daemon = True
    server_thread.start()
    server.serve_forever()
    server.shutdown()
    server.server_close()