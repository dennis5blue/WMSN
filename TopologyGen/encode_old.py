#!/usr/bin/python2.7

from subprocess import Popen, PIPE
from subprocess import call
import re
import sys

encoderPath = "../JMVC/bin/H264AVCEncoderLibTestStaticd"
configurePath = "./cfgFile/"

# Independent coding
def idtCoding(processList, outFile):
    output = ""
    for i in range(len(processList)):
        call(["cp",testSeqPath+processList[i], "tmp_0.yuv"])
	print(testSeqPath+processList[i])
        #output = Popen([encoderPath,"-vf","01Ex4Idt.cfg","0"],stdout=PIPE).communicate()[0]
	output = Popen([encoderPath,"-vf",configurePath+"01Ex4Idt.cfg","0"],stdout=PIPE).communicate()[0]
	print (output)        
	print "encode: ", i
        lines = [line for line in output.split('\n') if "byte" in line]
        byteInfo = " ".join(lines[0].strip().replace("[","").replace("]","").split())
        outFile.write(" Code: "+str(i)+" "+byteInfo+"\n")

# Correlation discovering
def corrDiscover(processList, outFile):
    for i in range(len(processList)):
        call(["rm","rec_0.yuv","rec_1.yuv"])
        call(["cp",testSeqPath+processList[i], "tmp_0.yuv"])
        output_0 =  Popen([encoderPath,"-vf",configurePath+"01Ex4Diff.cfg","0"],stdout=PIPE).communicate()[0]
        for j in range(len(processList)):

            call(["cp",testSeqPath+processList[j], "tmp_1.yuv"])
            output_1 =  Popen([encoderPath,"-vf",configurePath+"01Ex4Diff.cfg","1"],stdout=PIPE).communicate()[0]

            print "ref: ", i,"code: ", j
            lines = [line for line in output_1.split('\n') if "byte" in line]
            byteInfo = " ".join(lines[0].strip().replace("[","").replace("]","").split())
            outFile.write("Ref "+str(i)+" Code: "+str(j)+" "+byteInfo+"\n")



def main(argv = None): 
    if sys.argv[1].startswith('--'):
		option = sys.argv[1][2:]
		if option == "version":
			global testSeqPath
			global fileNamePrefix
			global saveFilePath
			testSeqPath = "../TestSequences/test"+sys.argv[2]+"_yuv/"
			fileNamePrefix = "test"+sys.argv[2]+"_"
			saveFilePath = "../TestSequences/test"+sys.argv[2]+"_correlation/"
		if option == "help":
			print "Usage: --version i --phase [0|1] 0 for independent coding, 1 for discovering --camera k"
		
		output = Popen(["ls", testSeqPath],stdout=PIPE).communicate()[0] 
		fileList = output.split('\n')
		fileList = filter(None,fileList)
		#fileList.pop() # the last item is the position information txt file 
		processList = len(fileList)*[None]
		print (fileList)
		for i in range(len(fileList)):
			idx = int(re.sub(r'camera_|\.yuv','',fileList[i]))
			processList[idx] = fileList[i]
			print (processList)
		if sys.argv[3].startswith('--'):
			option2 = sys.argv[3][2:]
			if option2 == "phase":
				if sys.argv[4] == "0":
					call(["rm","rec_0.yuv","rec_1.yuv"])
					outFile = open(saveFilePath+fileNamePrefix+"_phase_"+str(0)+".out","w+")
					result = idtCoding(processList, outFile)
				if sys.argv[4] == "1":
					call(["rm","rec_0.yuv","rec_1.yuv"])
					outFile = open(saveFilePath+fileNamePrefix+"_phase_"+str(1)+".out","w+")
					corrDiscover(processList, outFile)
        
if __name__ == "__main__":
    sys.exit(main())
