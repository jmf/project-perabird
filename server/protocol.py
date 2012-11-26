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

