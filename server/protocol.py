MSG_SEP = 0 # used as a separator in messages
MSG_BEGIN = 1 # used as first byte of a message
MSG_END = 2 # used as last byte of a message
MSG_LOGIN = 5 # login/identify message
MSG_JOIN = 6 # join message
MSG_QUIT = 7 # quit message (can be used to kick, too)
MSG_PLAYERPOS = 8 # player position update

def recv(sock):
	data = sock.recv(1)
	if not data: return None, None
	return chr(ord(data)), ord(data)

