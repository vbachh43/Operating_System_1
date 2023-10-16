#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

#pragma GCC diagnostic ignored "-Wunused-result"

//double init_ANS = DBL_MAX;
double ANS = 0;
double add(double a, double b) {
   return a + b;
}

double subtract(double a, double b) {
   return a - b;
}

double multiply(double a, double b) {
   return a * b;
}

double divide(double a, double b) {
   return a / b;
}

double divide_integer(double a, double b) {
   return (int)(a / b);
}

int isNumeric(const char* token) {
   if (strcmp(token, "ANS") == 0) {
      return 1; // "ANS" is not a numeric value
   }
   char* endptr;
   strtod(token, &endptr);
   return *endptr == '\0';
}

void calculate(char* input) {
   char* token = strtok(input, " ");
   if (token == NULL || !isNumeric(token)) {
      printf("SYNTAX ERROR");
      return;
   }
   double result;

   //check if ANS needs to be used
   if (strcmp(token, "ANS") == 0) {
      result = ANS;
   } else {
      result = atof(token);
   }

   // operator
   token = strtok(NULL, " ");
   char* operator = token;

   // get the second number
   // check if operator is "ANS"
   if (strcmp(operator, "ANS") == 0) {
      // use the value of ANS in the calculation
      result = ANS;
   } else {
      // get the second number
      token = strtok(NULL, " ");
      if (token == NULL || !isNumeric(token)) {
         printf("SYNTAX ERROR");
         return;
      }
      double num2;
      if (strcmp(token, "ANS") == 0) {
         num2 = ANS;
      } else {
         num2 = atof(token);
      }
      //double num2 = atof(token);

      // perform the calculation
      if (strcmp(operator, "+") == 0) {
         //result = result + num2;
         result = add(result, num2);
      } else if (strcmp(operator, "-") == 0) {
         //result = result - num2;
         result = subtract(result, num2);
      } else if (strcmp(operator, "*") == 0) {
         //result = result * num2;
         result = multiply(result, num2);
      } else if (strcmp(operator, "/") == 0) {
         if(num2 == 0){
            printf("MATH ERROR\n");
            return;
         }
         //result = result / num2;
         result = divide(result, num2);
      } else if (strcmp(operator, "%") == 0) {
         if(num2 == 0){
            printf("MATH ERROR\n");
            return;
         }
         //result = (int)(result / num2);
         result = divide_integer(result, num2);
      } else {
         printf("SYNTAX ERROR");
         return;
      }
   }

   //check for MATH ERROR
   if (isnan(result)) {
      printf("MATH ERROR");
      return;
   } else {
      //result = round(result * 100) / 100;
      printf("%.2f\n", result);
      ANS = result;
   }
}

int main() {
   while (1) {
      FILE *file;
      file = fopen("ans.txt", "r");
      fscanf(file, "%lf", &ANS);
      fclose(file);
      printf(">> ");
      char input[100];
      fgets(input, sizeof(input), stdin);
      
      input[strcspn(input, "\n")] = '\0';

      if (strcmp(input, "EXIT") == 0) {
         break;
      }

      calculate(input);
      file = fopen("ans.txt", "w");
      fprintf(file, "%lf", ANS);
      fclose(file);
      getchar();
      system('cls');
   }

   return 0;
}
