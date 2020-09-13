
#include <stdio.h>

int readNum();
float calculations();
void clean();

int input, error; /* These are the only global variables we use. Making these global makes the development easier and the programm smaller since we dont have to use pointers */

	/* Errors:
	/* 0 stands for no error
	/* 1 is the unexpected char error
	/* 2 is for unexpected end of input
	/* 3 is for no closing parenthesis
	/*
	/* Inputs:
	/* These are given character by character to our program
	/* Each character is assigned to the variable "input"
	/* Using a global variable for this makes our program 
	/* a lot smaller and easier to read
	*/
	

int main(void) {

	int counter = 0;
	float result  = 0; /* counter is just a number of results counter, result is the number our program will return to show to the user */

	while (input != EOF) {	/* run the program until we need to exit (EOF as input) */

		error = 0;			/* error starts as none (0) cause we expect no errors */

		printf("Enter the calculation you want to make: ");
		result = calculations();

		counter++;			/* counter increments by one every time */

		if (input != EOF && error == 0)  /* We print the result only if we aren't supposed to exit and we also have no errors */
			printf("Result %d: %.2f\n", counter, result);

		switch(error) {

			case 1:
				printf("Result %d: Unexpected Character!\n", counter);
				break;
			case 2:
				printf("Result %d: Unexpected end of input!\n", counter);
				break;
			case 3:
				printf("Result %d: Missing closing parenthesis!\n", counter);
				break;

		}

	}

	return 0;

}

float calculations() { /* The result is handled by the calculations function. This function can compute any operation contaning + , - or * */

	int oper1 = 1, oper2 = 1, mult_oper, div_flag = 0;
	float num1 = 0, num2 = 0, total, parenthesis;
	input = '+';		/* This is the only time we manipulate input so as the first number will be added to the sum */

	while (input != '\n' && input != ')') { /* we do this while we have no new line (means end or operation) or closing parenthesis (means end of parentesis computation) */

		/*
		/* The program uses two types of calculating
		/* One for addition and subtraction
		/* And one for multiplication
		*/

		if (input == '-' || input == '+') {			/* Here is where the addition and subtraction method takes place */

				while (input == '+' || input == '-' || input == ' ' || input == '\t') { 

					if (input == '-') { 				/*if we read a minus we change the operator accordingly*/

						if (!num1) {

							oper1 *= -1;

						} else if (!num2) {

							oper2 *= -1;

						}

					}

					input = getchar();

				}

				if (input == EOF)
					return 0;

				if (input == '(') {		/* if we read an opening parenthesis, we must call the calculations function to compute the inside */

					parenthesis = calculations();

					if (input != ')') {

						error = 3;
						while (input != '\n')
							input = getchar();
						return -1;

					}

					input = getchar();				/*input here will be) so we read the next input character*/
					
					if (num1) {

						total += oper1 * num1;
						oper1 = oper2;
						oper2 = 1;
						num1 = parenthesis;

					} else {

						num1 = parenthesis;
					}

				} else {		/*input is a number*/
				
					if (num1) {

						total += oper1 * num1;
						oper1 = oper2;
						oper2 = 1;
						num1 = readNum();

					} else {

						num1 = readNum();
					}

				}

		} else if (input == '*' || input == '/') {			/* Here is where the multiplication method takes place */

				if(input == '/')
					div_flag = 1;

				mult_oper = 1;					/* This is used to make us able to compute complex operations like -3*+-3 */
				input = getchar();	

				if (input == EOF)
					return 0;

				clean();

				while (input == '+' || input == '-') {

					if (input == '-') {

						mult_oper *= -1;
						
					}

					input = getchar();

				}

				if (input == '*' || input == '/') {

					error = 1;
					while (input != '\n')
						input = getchar();
					return -1;

				}

				if (input == '(') {				/* if we read an opening parenthesis, we must call the calculations function to compute the inside */

					parenthesis = calculations();

					if (input != ')') {

						error = 3;
						while (input != '\n')
							input = getchar();
						return -1;

					}

					input = getchar();				/*input here will be) so we read the next input character*/

					if (!num1) {

						total *= mult_oper * parenthesis;

					} else if (!num2){

						num1 *= mult_oper * parenthesis;
					}

				} else { /*input is a number*/

					if (!num1) {
					
						if(div_flag) {
							
							total /= mult_oper * readNum();
							div_flag = 0;
					
						} else {
						
							total *= mult_oper * readNum();

						}


					} else if (!num2) {

						if(div_flag) {
							
							num1 /= mult_oper * readNum();
							div_flag = 0;
					
						} else {
						
							num1 *= mult_oper * readNum();

						}

					}

				}

		} else { /* if we get in this else, it means that a non expected character has appeared, so we must show the corresponding error*/

			error = 1; 
			while (input != '\n')
				input = getchar();

		}

		clean();

		if (error != 0) { /* This is here for the error that takes place in readNum and also for safety reasons */

			return -1;

		}

	}

	total += oper1 * num1; /* we sum */
	return total;

}

int readNum() { /*This function is used to read a number*/

	int oper = 1, number = 0;

	clean();

	while (input == '-' || input == '+') {

		if (input == '-') {

			oper *= -1;

		}

		input = getchar();

	}

	if (input == '\n') {

		error = 2;

	}

	while (input >= '0' && input <= '9') {

	   	number = number * 10 + input - '0';
	 	input = getchar();

	}

 	number *= oper;
   	return number;

}

void clean() { /*This is a simple function ignoring spaces and tabs, used to make the program smaller*/

	while (input == ' ' || input == '\t') {

		input = getchar();

	}

}
