run: exercise_04
	./exercise_04

exercise_04: exercise_04.o 
	g++ exercise_04.o -o exercise_04

exercise_04.ii: exercise_04.cpp
	g++ -E exercise_04.cpp -o exercise_04.ii


exercise_04.s: exercise_04.ii
	g++ -S exercise_04.ii -o exercise_04.s


exercise_04.o: exercise_04.s
	g++ -c exercise_04.s -o exercise_04.o

clean:
	rm -rf *.ii *.s *.o exercise_04

