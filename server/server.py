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

from user import *
from userthread import *


def main():
	main_socket = socket(AF_INET,SOCK_STREAM)
	port = 5153
	if len(argv) >= 2:
		port = int(argv[1])
	main_socket.bind(('0.0.0.0',port))
	main_socket.listen(5)
	
	users = []

	done = False

	while not done:
		try: sock, addr = main_socket.accept()
		except: break
		user = User(sock,addr)
		users.append(user)
		t = Thread(target=userthread, args=(user,users))
		t.start()

	print("Exiting...")

if __name__ == "__main__":
	main()

