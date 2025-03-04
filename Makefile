all:
	g++ -g -Wall TimeCode.cpp TimeCodeTests.cpp -o tct
	g++ -Wall NasaLaunchAnalysis.cpp TimeCode.cpp -o nasa
	g++ -Wall PaintDryTimer.cpp TimeCode.cpp -o pdt

try: all