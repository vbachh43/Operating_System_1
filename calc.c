#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
	char input[100];
	double num1, num2, result;
	char operator;

	printf(">> ");
	fgets(input, 100, stdin);

	if (input == "EXIT") return 0;
	else{
		sscanf(input, "%lf %c %lf", &num1, &operator, &num2);

		switch (operator){
			case '+':
				result = num1 + num2;
				break;
			case '-':
				result = num1 - num2;
				break;
			case '*':
				result = num1 * num2;
				break;
			case '/':
				if (num2 == 0){
					printf("MATH ERROR\n");
					return 0;
				}
				result = num1 / num2;
				break;
			default:
				printf("SYNTAX ERROR\n");
				return 0;
		}
		// Print result:
		printf("%.2lf %c %.2lf = %.2lf\n", num1, operator, num2, result);

		return 0;
	}
}

