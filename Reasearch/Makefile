main.o : main.cpp TopologyFactory.cpp
	g++ main.cpp TopologyFactory.cpp ScheduleFactory.cpp SimulationFactory.cpp SchedulingMetric.cpp SchedulingMetricConsiderByte.cpp SinrScheduling.cpp SAFactory.cpp -o main.out

.PHONY : clean
clean :
	-rm main.out
