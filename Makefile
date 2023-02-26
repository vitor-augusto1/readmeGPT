all:
	gcc -c ./src/lib/request.c -I ./src/includes -o ./obj/request.o
	gcc -c ./src/lib/formatString.c -I ./src/includes -o ./obj/formatString.o
	gcc -c ./src/lib/generateFinalInput.c -I ./src/includes -o ./obj/generateFinalInput.o
	gcc -c ./src/lib/parseJSON.c -I ./src/includes -o ./obj/parseJSON.o
	gcc -c ./src/lib/writeTofile.c -I ./src/includes -o ./obj/writeTofile.o
	gcc -c ./src/lib/userguide.c -I ./src/includes -o ./obj/userguide.o
	gcc ./src/main.c ./obj/*.o -I ./src/includes -o ./readmeGPT -lcurl -ljson-c -ldotenv

clean:
	rm ./obj/*
