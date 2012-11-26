
from protocol import *

#msgspec:
#	For user, password:
#		strhexstr

def parseMessage(msgspec, sock):
	parsed = []
	for t in msgspec.split(':'):
		c = ''
		o = -1
		if t == 'str':
			s = ''
			while 1:
				c, o = recv(sock)
				if o in (MSG_SEP,MSG_END): break
				s += c
			parsed.append(s)
		if t == 'hexstr':
			s = ''
			while 1:
				o = recv(sock)[1]
				if o in (MSG_SEP,MSG_END): break
				c = hex(o).replace('0x','')
				if len(c)==1: c='0'+c
				s += c
			parsed.append(s)
			c, o = recv(sock)
		if o != MSG_SEP: # can be MSG_END
			break
	return parsed
