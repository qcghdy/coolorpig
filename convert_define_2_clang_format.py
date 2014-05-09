#!/usr/bin/python
# -*- coding: utf-8 -*-

import re

#mingw_define.txt 
fp = open('mingw_define.txt', 'r')

for eachline in fp.readlines():
	m = re.match(r'^#define\s+(\S+)\s+(\S+)$', eachline, re.M)
	if(m):
	    print '"-D'+m.group(1)+'='+m.group(2)+'",'
	else:
		pass
		
fp.close()
