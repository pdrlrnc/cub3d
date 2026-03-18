"""

Compile cub3D, then run:
`python3 .tests/test.py`

"""

import os
from subprocess import call

TESTS = [
	{"name":	"map0.cub",				"expected":		0},
	{"name":	"map1.cub",				"expected":		0},
	{"name":	"map2.cub",				"expected":		0},
	{"name":	"map3.cub",				"expected":		0},
	{"name":	"map4.cub",				"expected":		0},
	{"name":	"map5.cub",				"expected":		0},
	{"name":	"map6.cub",				"expected":		0},
	{"name":	"map7.cub",				"expected":		0},
	{"name":	"map8.cub",				"expected":		2},
	{"name":	"map9.cub",				"expected":		2},
	{"name":	"map10.cub",			"expected":		2},
	{"name":	"map11.cub",			"expected":		2},
	{"name":	"map12.cub",			"expected":		2},
	{"name":	"map13.cub",			"expected":		2},
	{"name":	"map14.cub",			"expected":		2},
	{"name":	"map15.cub",			"expected":		0},
	{"name":	"map16.cub",			"expected":		2},
	{"name":	"map17.cub",			"expected":		2},
	{"name":	"map18.cub",			"expected":		2},
	{"name":	"map19.cub",			"expected":		2},
	{"name":	"map20.cub",			"expected":		2},
	{"name":	"map21.cub",			"expected":		2},
	{"name":	"map22.cub",			"expected":		2},
	{"name":	"map23.cub",			"expected":		2},
	{"name":	"map24.cub",			"expected":		2},
	{"name":	"map25.cub",			"expected":		2},
	{"name":	"map26.cub",			"expected":		2},
	{"name":	"map27.cub",			"expected":		2},
	{"name":	"map28.cub",			"expected":		2},
	{"name":	"map28.2.cub",			"expected":		2},
	{"name":	"map29.cub",			"expected":		2},
	{"name":	"map30.cub",			"expected":		2},
	{"name":	"map31.cub",			"expected":		2},
	{"name":	"map32.cub  cub",		"expected":		2},
	{"name":	"map33.cub",			"expected":		2},
	{"name":	"map34.cub",			"expected":		0},
	{"name":	"map35.cub",			"expected":		0},
	{"name":	"map36.cub",			"expected":		2},
	{"name":	"map37.cub",			"expected":		2},
	{"name":	"map38.cub",			"expected":		6},
	{"name":	"map39.cub",			"expected":		6},
	{"name":	"map40.cub",			"expected":		2},
	{"name":	"map41.cub",			"expected":		2},
	{"name":	"map42.cub",			"expected":		2},
]

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def main():
	for i in TESTS:
		res_code = call(["./cub3D", f"tests/{i['name']}"])
		if res_code == i["expected"]:
			print(
				f"{bcolors.BOLD}{i['name']}{bcolors.ENDC}",
				"EXP:", i["expected"],
				"CUR:", res_code,
				f"{bcolors.OKGREEN}{res_code == i['expected']}{bcolors.ENDC}"
			)
		else:
			print(
				f"{bcolors.BOLD}{i['name']}{bcolors.ENDC}",
				"EXP:", i["expected"],
				"CUR:", res_code,
				f"{bcolors.FAIL}{res_code == i['expected']}{bcolors.ENDC}"
			)

main()
