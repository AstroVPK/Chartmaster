import os


debug = False

cwd = os.getcwd()
srcDir = os.path.join(cwd, 'src')
headerDir = os.path.join(cwd, 'include')
binDir = os.path.join(cwd, 'bin')
if not os.path.isdir(binDir):
	os.mkdir(binDir)

if debug:
	ccflags = ['-std=c++20', '-g', '-O0']
else:
	ccflags = ['-std=c++20', '-O3']

execFile = os.path.join(srcDir, 'radec.cpp')
execOut = os.path.join(binDir, 'radec')


env = Environment(CPPPATH = [cwd])
env.Replace(CC = "gcc-11")
env.Replace(CXX = "g++-11")
env.Append(CCFLAGS=ccflags)
env.Program(execOut, execFile)
env.Repository(headerDir)