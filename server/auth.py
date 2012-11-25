
import hashlib


accounts = []
f = open("auth.db","r")
for l in f.readlines():
	data = l.replace('\n','').split(':',2)
	if len(data) != 2: continue
	accounts.append(data)
	print(data)

def auth(user,pswd):
	data = [user,hashlib.sha256(pswd.encode()).hexdigest()]
	print(data)
	return data in accounts