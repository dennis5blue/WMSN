#!/usr/bin/python2.7

import re
import sys
def channelGain(x, y):
    g = 10**(-13.11-4.281)*(x**x+y**y)**(1/2)/1000
    return g

def main(argv=None):
	if sys.argv[1].startswith('--'):
		option = sys.argv[1][2:]
	if option == "version":
		corrFilePath = "../TestSequences/test"+sys.argv[2]+"_correlation/test"+sys.argv[2]+"__phase_0.out"
		saveFilePath = "../TestSequences/test"+sys.argv[2]+"_correlation/"
		posFilePath = "../TestSequences/test"+sys.argv[2]+"_png/log.txt"
	if option == "help":
		print "Usage: --version i (parse for the test i data)"
		sys.exit()

	W = 180 # kHz bandwidth
	P = 10  # dbm power
	ifCompression = open(corrFilePath,"r")
	ifPosition = open(posFilePath,'r')
	ofRate = open(saveFilePath+"rate.out","w+")
	ofPos = open(saveFilePath+"pos.out","w+")

	lines = ifCompression.readlines();
	for line in lines:
		tokens = re.split(' |\[',line)
		tokens = filter(None,tokens);
		#print tokens
	#if tokens[0] == "average":
		ofRate.write(str(float(tokens[5]))+'\n')

	lines = ifPosition.readlines()
	for line in lines:
		line.strip()
		tokens = line.split()
		print tokens    	
		if tokens[0] == "Pos":
        	#print tokens[1]+' '+tokens[2]+' '+tokens[3]
			xx = float(tokens[1])*100
			yy = float(tokens[2])*100
			ofPos.write(str(xx)+' '+str(yy)+'\n')

if __name__ == "__main__":
	sys.exit(main())
