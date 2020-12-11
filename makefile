make: personal_utils.h
	gcc -c -o personal_utils.o personal_utils.h
	gcc -shared -o personal_utils.so personal_utils.o