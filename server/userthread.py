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



from protocol import *
from auth import *
from msgparser import *

def userthread(sock,addr):
	while 1:
		o = recv(sock)[1]
		if not o: break
		if o != MSG_BEGIN: continue
		msgType = recv(sock)[1]
		if msgType == MSG_LOGIN:
			'''user = ""
			o=-1
			while 1:
				c, o = recv(sock)
				if o in (MSG_SEP,MSG_END): break
				user += c
			if o == MSG_END: continue
			pswd = ""
			while 1:
				o = recv(sock)[1]
				if o == MSG_END: break
				c = hex(o).replace('0x','')
				if len(c)==1: c='0'+c
				pswd += c'''
			parsed = parseMessage('str:hexstr',sock)
			if len(parsed) != 2: continue
			user, pswd = parsed
			if auth(user,pswd):
				print(user,"logged in from",addr[0])
			else:
				print(addr[0],"tried to login as",user)

