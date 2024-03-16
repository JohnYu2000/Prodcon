compile: main.o consumer.o producer.o command.o logger.o tands.o mutex.o workQueue.o
	g++ -o prodcon *.o -pthread

main.o: main.cpp
	g++ -c main.cpp

consumer.o: consumer.cpp consumer.h
	g++ -c consumer.cpp

producer.o: producer.cpp producer.h
	g++ -c producer.cpp

command.o: command.cpp command.h
	g++ -c command.cpp

logger.o: logger.cpp logger.h
	g++ -c logger.cpp

tands.o: tands.cpp tands.h
	g++ -c tands.cpp

mutex.o: mutex.cpp mutex.h
	g++ -c mutex.cpp

workQueue.o: workQueue.cpp workQueue.h
	g++ -c workQueue.cpp

compress:
	zip prodcon.zip README.md makefile *.cpp *.h

clean:
	rm -f prodcon *.o *.log prodcon.zip