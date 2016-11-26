import os,sys,shutil,subprocess

SOURCE_DIR = "proto"
DIS_DIR = "java"

def main():
    reload(sys)
    sys.setdefaultencoding("utf-8")
    if os.path.isdir(DIS_DIR):
        shutil.rmtree(DIS_DIR)
    os.mkdir(DIS_DIR)
    currentdir = sys.path[0]
    disdir = currentdir + "/" + DIS_DIR 
    sourceDir = currentdir + "/" + SOURCE_DIR
    fileList = os.listdir(sourceDir)
    os.chdir("proto")    
    for file in fileList:
        tempFile = sourceDir + "/" + file
        print " generate cs File %s " %(tempFile)
        os.system('%s\protocJava.exe -I=%s --java_out=%s %s' %(currentdir,sourceDir,disdir,tempFile))

if __name__ == "__main__":
    main()
