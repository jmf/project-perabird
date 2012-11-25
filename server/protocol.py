MSG_SEP = 0
MSG_BEGIN = 1
MSG_END = 2
MSG_LOGIN = 5

def recv(sock):
	data = sock.recv(1)
	if not data: return None, None
	return chr(ord(data)), ord(data)

