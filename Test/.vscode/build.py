import os
import argparse
import subprocess
import platform

systemOS = platform.system()
type = ""
outExt = ""
defineType = ""
if systemOS == "Linux":
    type = "elf"
    outExt = ".o"
    defineType = "ELF_TYPE"
elif systemOS == "Windows":
    type = "win32"
    outExt = ".obj"
    defineType = "COFF_TYPE"
else:
    print(systemOS)

argParser = argparse.ArgumentParser()
argParser.add_argument("-w", "--workspace", help="Workspace of vscode")
argParser.add_argument("-cwd", "--workingdirectory", help="Current working directory")
argParser.add_argument("-r", "--rel", help="Relative File")
argParser.add_argument("-b","--basename", help="Basename of file")
args = argParser.parse_args()

if(args.rel.split(".")[-1]!="asm"):
    print("An assembly file was not passed!")
    exit()

dir = os.path.realpath("./Projects/")

inputfile=args.rel


#Ensures temp directory exists
if os.path.isdir(dir) == False:
    os.mkdir(dir)

def cleanDir(dir_path):
    if os.path.isdir(dir_path) == False:
        os.mkdir(dir_path)
    for file in os.scandir(dir_path):
        os.remove(file.path)

fileOpen = open(inputfile, "r")
data = fileOpen.read()
fileOpen.close()

includeString = "%include \""
data1 = data.replace(includeString, includeString+"linux-ex/")

if systemOS == "Windows":
    data1 = data1.replace("asm_main", "_asm_main")

arrIncludes = []
location = 0
while data.find(includeString, location) != -1:
    location = data.find(includeString, location) + len(includeString)
    end = data.find("\"", location)
    arrIncludes.append(data[location:end])
    location = end

#creates/cleans directory for files
cleanDir(dir+"/"+args.basename)


fileOpen = open(dir+"/"+args.basename+"/"+"DEP"+args.basename+".asm","w")
fileOpen.write(data1)
fileOpen.close()
fileOpen = open(dir+"/"+args.basename+"/"+args.basename+".asm","w")
fileOpen.write(data)
fileOpen.close()


includes = ""
for inc in arrIncludes:
    includes += "\""+os.path.join(args.workspace, "linux-ex", "".join(inc.split(".")[0:-1]) + outExt + "\" ")

print(includes)

assemble=""
if(subprocess.getstatusoutput("nasm -v")[0] == 0):
    print(" Preparing Linked Files\n------------------------")
    for inc in arrIncludes:
        inc = os.path.join(args.workspace, "linux-ex","".join(inc.split(".")[0:-1]))
        if not os.path.exists(inc+outExt):
            check = subprocess.getstatusoutput("nasm -f {type} -d {define} {asm} -o \"{out}\"".format(type=type, define=defineType, asm=inc+".asm", out=inc+outExt))
            if(check[0] != 0):
                print("Error:\n"+check[1])
                exit()

    fileASM = os.path.realpath('{dir}/{fileBasename}/DEP{fileBasename}.asm'.format(dir=dir, relativeFile=args.rel,fileBasename=args.basename))
    fileO = os.path.realpath('{dir}/{fileBasename}/{fileBasename}{outExt}'.format(dir=dir, relativeFile=args.rel,fileBasename=args.basename, outExt=outExt))
    assemble="nasm -f {type} -d {define} {asm} -o {out}".format(type=type, define=defineType, asm=fileASM, out=fileO)
else:
    print("No Assembler Installed")
    exit()

if systemOS=="Linux":
    type=""
elif systemOS=="Windows":
    type=".exe"
else:
    type=""

compile = ""
if(subprocess.getstatusoutput("gcc --version")[0] == 0):
    fileExe = os.path.realpath('{dir}/{fileBasename}/{fileBasename}{type}'.format(dir=dir, fileBasename=args.basename, type=type))
    fileO = os.path.realpath('{dir}/{fileBasename}/{fileBasename}{outExt}'.format(dir=dir, fileBasename=args.basename, outExt=outExt))
    driver = os.path.realpath('{workspace}/linux-ex/driver.c'.format(workspace=args.workspace))
    compile="gcc -m32 -o \"{fileExe}\" \"{fileO}\" \"{driver}\" {includes}".format(type=type, dir=dir, fileExe=fileExe, fileO=fileO, driver=driver, includes=includes)
else:
    print("No Compiler Installed")
    exit()
#print(assemble, "\n", compile)
print("\n Assembling Assembly File\n--------------------------")
check = subprocess.getstatusoutput(assemble)
os.remove(dir+"/"+args.basename+"/"+"DEP"+args.basename+".asm") #Remove Dependency File
if(check[0] == 1):
    print("Error:\n"+check[1])
    exit()

print("\n Compiling and Linking Files\n-----------------------------")
check = subprocess.getstatusoutput(compile)
if(check[0] == 1):
    print("Error:\n"+check[1])
    exit()

print("\n Running Program\n-----------------")
exe = os.path.abspath('{dir}/{fileBasename}/{fileBasename}{type}'.format(dir=dir,fileBasename=args.basename, type=type))
check = os.system(exe)