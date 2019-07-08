import subprocess
import os

			
def consoleTest(command, testinput, testoutput):
	process = subprocess.Popen(command.split(), stdout=subprocess.pipe, stdin=subprocess.pipe)
	realoutput = process.communicate(self.input.encode("utf-8"))
	return testoutput == realoutput[0].decode("utf-8")

def fileTest(command, filePath, fileContent = None, testInput = ""):
	process = subprocess.Popen(command.split())
	process.communicate(testInput.encode("utf-8"))
	if os.path.exists(filePath):
		if fileContent != None:
			testFile = open(filePath, "r")
			if testFile.read() == fileContent:
				testFile.close()
				#print(1)
				return True
			else:
				testFile.close()
				#print(2)
				return False
		#print(3)
		return True
	else:
		#print(4)
		return False


print(fileTest("./upper", "testfilse.txt", "test\n")) #example
