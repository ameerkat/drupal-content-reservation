# increment_version_num.py
# Utility to incremement version number in drupal info files
# Ameer Ayoub <ameer.ayoub@gmail.com>
import re, sys, os

major_v = 0
minor_v = 0

def inc_dv_num(s, minor = True):
	global major_v, minor_v
	pattern = re.compile("(version = (\d\.x)-)(\d+)\.(\d+)")
	m = re.match(pattern, s)
	if m:
		major_v = int(m.group(3))
		minor_v = int(m.group(4))
		if minor:
			minor_v += 1
			return m.group(1)+m.group(3)+"."+str(minor_v)+"\n"
		else:
			
			major_v += 1
			return m.group(1)+str(major_v)+".0\n"
	else:
		return s

if __name__ == "__main__":
	minor_version = True
	file = False
	file_to_mod = ""
	if sys.argv[0] == "python" or sys.argv[0] == "python.exe":
		this_name = sys.argv[1]
	else:
		this_name = sys.argv[0]

	for arg in sys.argv:
		if file:
			file_to_mod = arg
			file = False
		elif arg == "--major":
			minor_version = False
		elif arg == "--minor":
			minor_version = True
		elif arg == "--file":
			file = True
	if not file_to_mod:
		print("Usage: {0} --file path_to_file [--major]".format(this_name))
		exit()
	tmp_file = "~"+file_to_mod
	f = open(file_to_mod, "r")
	b = open(tmp_file, "w")
	for line in f:
		b.write(inc_dv_num(line))
	f.close()
	b.close()
	print("Working Version: {0}-{1}".format(major_v, minor_v))
	os.remove(file_to_mod)
	os.rename(tmp_file, file_to_mod)
