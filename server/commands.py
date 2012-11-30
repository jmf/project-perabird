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

CMD_UNKNOWN = 0
CMD_SUCCESS = 1
CMD_FAIL = 2
CMD_BREAK = 3

def handleCommand(sender,command,users):
	args = command.split(' ')
	if args[0] == "shutdown":
		return CMD_BREAK
	elif args[0] == "say":
		if len(args) < 2:
			sendChat(sender, "Usage: say <message>")
			return CMD_FAIL
		for u in users:
			sendChat(u,"(server) "+" ".join(args[1:]))
		return CMD_SUCCESS
	elif args[0] == "list":
		l = ""
		for u in users:
			if u.name:
				l += u.name + ', '
		sendChat(sender,l)
		return CMD_SUCCESS
	sendChat(sender,"Unknown command.")
	return CMD_UNKNOWN

