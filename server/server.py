#    Copyright (C) 2012 Zeg9
#    
#    This file is part of Project Perabird.
#    Project Perabird is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    Project Perabird is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Project Perabird.  If not, see <http://www.gnu.org/licenses/>


from socket import socket, AF_INET, SOCK_STREAM
from threading import Thread
from sys import argv

from acceptthread import *
from commands import *


def main():
	main_socket = socket(AF_INET,SOCK_STREAM)
	port = 5153
	if len(argv) >= 2:
		port = int(argv[1])
	main_socket.bind(('0.0.0.0',port))
	main_socket.listen(5)
	users = []
	
	t = Thread(target=acceptthread, args=(main_socket,users))
	t.daemon = True
	t.start()
	
	while 1:
		try:
			t = input("> ")
		except:
			break
		if type(t) != str: continue
		if t == "shutdown":
			break
		else:
			if not handleCommand(None,t,users): print("Unknown command. Try help.")
	main_socket.close()
	print("Exiting...")

if __name__ == "__main__":
	main()

