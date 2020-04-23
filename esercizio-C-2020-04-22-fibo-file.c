/**************TESTO ESERCIZIO****************
riprendere l'esercizio https://github.com/marcotessarotto/esercizio-C-2020-03-30/

calcolare fibonacci_array(39) e scrivere i valori dell'array in formato testo in un file chiamato fibonacci.txt

se il file esiste, deve essere sovrascritto

il programma scrive nel file un valore (in formato testo) per riga


per convertire un numero intero in stringa, vedere:

https://github.com/marcotessarotto/exOpSys/tree/master/003.2sprintf
*/
/*
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>

#include <math.h>

unsigned long fibonacci(unsigned int n);
int min_string_len(unsigned long number);
char * ltoa_printf(unsigned long number);

int main(int argc, char * argv[]) {
	//APERTURA DEL FILE
	char * file_name = "./fibonacci.txt";

	int fd = open(file_name,
					  O_CREAT | O_TRUNC | O_WRONLY,
					  S_IRUSR | S_IWUSR // l'utente proprietario del file avrà i permessi di lettura e scrittura sul nuovo file
					 );

	if (fd == -1) { // errore!
		perror("open()");
		exit(EXIT_FAILURE);
	}

	//SCRITTURA NEL FILE
	unsigned int n = 39;
	int text_to_write_len;

	unsigned long fibonacci_result = fibonacci(n);

	char * text_to_write = ltoa_printf(fibonacci_result);
	text_to_write_len = strlen(text_to_write) + 1;

	int res = write(fd, text_to_write, text_to_write_len);
	if (res == -1) {
		perror("write()");
		exit(EXIT_FAILURE);
	}

	//CHIUSURA DEL FILE
	if (close(fd) == -1) {
		perror("close");
		exit(EXIT_FAILURE);
	}

	free(text_to_write);

	return 0;
}

unsigned long fibonacci(unsigned int n){
	if(n == 0)
		return 0;
	else if(n == 1)
		return 1;

	return fibonacci(n-1) + fibonacci(n-2);
}

// minima lunghezza della stringa di caratteri per rappresentare number (in base 10)
int min_string_len(unsigned long number) {

	// man ceil -> smallest integral value not less than argument
	// man log10 -> logaritmo base 10
	// man labs -> valore assoluto


	int result =  (int)( ceil( log10(number )) + 1 ) * sizeof(char);

	return result;
}

char * ltoa_printf(unsigned long number){
	char * result;
	int len = min_string_len(number);

	result = calloc(len, sizeof(char));

	snprintf(
			result, // zona di memoria in cui snprintf scriverà la stringa di caratteri
			len, // dimensione della zona di memoria
			"%lu", // stringa di formattazione
			number); // numero intero da convertire in stringa

	return result;
}
