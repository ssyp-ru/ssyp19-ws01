import subprocess
import os

            
def consoleTest(command, testinput, testoutput):
    try:
        process = subprocess.Popen(command.split(), stdout=subprocess.pipe, stdin=subprocess.pipe)
        realoutput = process.communicate(self.input.encode("utf-8"))
    except:
        print("Creating process error. Your command is " + command + ".")
        return None
    return testOutput == realOutput[0].decode("utf-8")

def fileTest(command, filePath, fileContent = None, testInput = ""):
    try:
        process = subprocess.Popen(command.split())
        process.communicate(testInput.encode("utf-8"))
    except:
        print("Creating process error. Your command is " + command + ".")
        return None
    if not  os.path.exists(filePath):
        return False
    if fileContent != None:
        testFile = open(filePath, "r")
        content = testFile.read()
        testFile.close()
        return content == fileContent
    return True
    
print(fileTest("./upper", "testfile.txt", "test\n")) #example
