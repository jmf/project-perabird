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


from userthread import *
from socket import socket, AF_INET, SOCK_STREAM
from threading import Thread

main_socket = socket(AF_INET,SOCK_STREAM)
main_socket.bind(('0.0.0.0',5153))
main_socket.listen(5)

done = False

while not done:
	try: sock, addr = main_socket.accept()
	except: break
	t = Thread(target=userthread, args=(sock,addr))
	t.start()

print("Exiting...")

