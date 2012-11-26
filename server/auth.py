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



import hashlib


accounts = []
f = open("auth.db","r")
for l in f.readlines():
	data = l.replace('\n','').split(':',2)
	if len(data) != 2: continue
	accounts.append(data)

def auth(user,pswd):
	data = [user,hashlib.sha256(pswd.encode()).hexdigest()]
	return data in accounts
