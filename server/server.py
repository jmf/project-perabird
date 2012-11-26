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

