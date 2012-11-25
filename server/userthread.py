from protocol import *
from auth import *

def userthread(sock,addr):

	f = open('auth.db','r')
	authtext = f.readlines()
	f.close()
	while 1:
		o = recv(sock)[1]
		if not o: break
		if o != MSG_BEGIN: continue
		msgType = recv(sock)[1]
		if msgType == MSG_LOGIN:
			user = ""
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
				pswd += c
			if auth(user,pswd):
				print(user,"logged in from",addr[0])
			else:
				print(addr[0],"tried to login as",user)

