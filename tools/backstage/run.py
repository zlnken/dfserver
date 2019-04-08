#!/usr/bin/env python
import os
import sys
import socket
if __name__ == "__main__":
    myname = socket.getfqdn(socket.gethostname())
    myaddr = socket.gethostbyname(myname)
    os.system("python manage.py runserver " + myaddr + ":2020")
