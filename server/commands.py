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

def handleCommand(sender,command,users):
	args = command.split(' ')
	if args[0] == "list":
		l = ""
		for u in users:
			if u.name:
				l += u.name + ', '
		print(l)
		return True
	elif args[0] == "send":
		if len(args) < 2:
			print("Usage: send <message>")
			return True
		for u in users:
			send(u.sock,MSG_BEGIN)
			send(u.sock,MSG_CHAT)
			send(u.sock," ".join(args[1:]))
			send(u.sock,MSG_END)
		return True
	return False

