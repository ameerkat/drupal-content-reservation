# Utility that installs files with extension .githook into the git hooks folder
# Ameer Ayoub <ameer.ayoub@gmail.com>

from os import listdir
from shutil import copy2

git_hook_dir = "../.git/hooks/"

def fslash(f):
	"""Replaces all backslashes with forward slashes"""
	return f.replace("\\", "/")

def get_extension(f):
	"""Returns the last file extension, without the . delimiter"""
	return f[f.rfind(".")+1:]

def remove_extension(f):
	"""Removes the last file extension"""
	return f[:f.rfind(".")]

def install_githook(f):
	global git_hook_dir
	try:
		#copy2 copies file and permissions
		copy2(f, git_hook_dir+remove_extension(f))
		return True,
	except IOError, e:
		return False, e

if __name__ == "__main__":
	for f in listdir("."):
		f = fslash(f)
		if get_extension(f) == "githook":
			install_status = install_githook(f)
			if install_status[0]:
				print "Git hook " + remove_extension(f) + " installed successfully."
			else:
				print "Git hook " + remove_extension(f) + " install failed! error: " + install_status[1]

