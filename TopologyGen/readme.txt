This is document for generating correlation matrix

 1. Execute the blender python script and get the test sequence, and log.txt
	Saved in TestSequences/test_png
 2. Execute yuv_gen.py to convert the png file to the yuv raw data
	Need to give the test?_png path ($python yuv_gen.py --version ?)
 3. Execute encode.py to try all the combination of multi view encoding
	$Ex4_encode.py --version ? --phase 0 is to perform the independent coding
	
	Note that the encoder config file need to specified, 
    for indendent coding    : 00Ex4Idt.cfg, or 01Ex4Idt.cfg
    for differential coding : 00Ex4Diff.fig, or 01Ex4Diff.cfg
    the resoultion setting must match to the property of *.yuv file
	search range can be changed for higher performance

    $Ex4_encode.py --version ? --phase 1 --camera k is to perform the differential coding for camera k
 4. Execute parse.py to generate the rate.out and pos.out
	Give the path by $python parse.py --version ?
 
