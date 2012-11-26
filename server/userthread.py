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


from user import *
from protocol import *
from auth import *
from msgparser import *

def userthread(user,users):
	sock = user.sock
	addr = user.addr
	try:
		print(addr[0],'connected')
		while 1:
			o = recv(sock)[1]
			if not o: break
			if o != MSG_BEGIN: continue
			msgType = recv(sock)[1]
			if msgType == MSG_LOGIN:
				parsed = parseMessage('str:hexstr',sock)
				if len(parsed) != 2: continue
				name, pswd = parsed
				if auth(name,pswd):
					user.name = name
					print(user.name,"logged in from",addr[0])
					for u in users:
						send(u.sock,MSG_BEGIN)
						send(u.sock,MSG_JOIN)
						send(u.sock,user.name)
						send(u.sock,MSG_END)
				else:
					print(addr[0],"tried to login as",name)
					send(user.sock,MSG_BEGIN)
					send(user.sock,MSG_QUIT)
					send(user.sock,MSG_END)
					break
	except:
		print(addr[0],"lost connection")
	user.sock.close()
	users.remove(user)

