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
        call(["cp",testSeqPath+processList[i], "./tempFile/tmp_0.yuv"])
	print(testSeqPath+processList[i])
        #output = Popen([encoderPath,"-vf","01Ex4Idt.cfg","0"],stdout=PIPE).communicate()[0]
	output = Popen([encoderPath,"-vf",configurePath+"01Ex4Idt.cfg","0"],stdout=PIPE).communicate()[0]
	print (output)        
	print "encode: ", i
	lines = [line for line in output.split('\n') if "byte" in line]
	byteInfo = " ".join(lines[0].strip().replace("[","").replace("]","").split())
	outFile.write(" Code: "+str(i)+" "+byteInfo+"\n")
	
# Correlation discovering
def corrDiscover(camIndex, processList, outFile):
	encodeCamera = processList[int(camIndex)]
	print "Encoding Camera: ",encodeCamera

	for i in range(len(processList)):
		call(["rm","./tempFile/rec_0.yuv","./tempFile/rec_1.yuv"])
		call(["cp",testSeqPath+processList[i], "./tempFile/tmp_0.yuv"])
		output_0 =  Popen([encoderPath,"-vf",configurePath+"01Ex4Diff.cfg","0"],stdout=PIPE).communicate()[0]
		call(["cp",testSeqPath+encodeCamera, "./tempFile/tmp_1.yuv"])
		output_1 =  Popen([encoderPath,"-vf",configurePath+"01Ex4Diff.cfg","1"],stdout=PIPE).communicate()[0]
		
		print "ref: ", i,"code: ", camIndex
		lines = [line for line in output_1.split('\n') if "byte" in line]
		byteInfo = " ".join(lines[0].strip().replace("[","").replace("]","").split())
		outFile.write("Ref "+str(i)+" Code: "+str(camIndex)+" "+byteInfo+"\n")



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
			print "Usage: --version i: verify which test version"
			print "Usage: --phase [0|1]: 0 for independent coding, 1 for correlation discovering"
			print "Usage: --camera k: verify which camera we aim to encode (no need to use this command when indep coding)"
			exit()
		
		output = Popen(["ls", testSeqPath],stdout=PIPE).communicate()[0] 
		fileList = output.split('\n')
		fileList = filter(None,fileList)
		#fileList.pop() # the last item is the position information txt file 
		processList = len(fileList)*[None]
		#print (fileList)
		for i in range(len(fileList)):
			idx = int(re.sub(r'camera_|\.yuv','',fileList[i]))
			processList[idx] = fileList[i]
			#print (processList)
		if sys.argv[3].startswith('--'):
			option2 = sys.argv[3][2:]
			if option2 == "phase":
				if sys.argv[4] == "0":
					call(["rm","./tempFile/rec_0.yuv","./tempFile/rec_1.yuv"])
					outFile = open(saveFilePath+fileNamePrefix+"_phase_"+str(0)+".out","w+")
					result = idtCoding(processList, outFile)
				if sys.argv[4] == "1":
					if sys.argv[5] == "--camera":
						camIndex = sys.argv[6]
						print "Differential encode camera", camIndex
					else:
						print "Please verify which camera are encoding now"
						exit()
					call(["rm","./tempFile/rec_0.yuv","./tempFile/rec_1.yuv"])
					outFile = open(saveFilePath+fileNamePrefix+"_phase_"+str(1)+"_camera_"+str(camIndex)+".out","w+")
					#print (processList)
					corrDiscover(camIndex, processList, outFile)
        
if __name__ == "__main__":
    sys.exit(main())
