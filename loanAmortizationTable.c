/* Programmer: Brian Loftus
 * Date: 2/25/2017
 * Class: COP-1220-92784 
 */
 
 /* 
  * This program is to calcuate the monthly payments of a laon. The user will 
  * enter the amount borrowed, the annual interest rate and the number of
  * payments. The program will then print the payments due each month displaying
  * the interest and the principal and the remaining principal balance.
  */
  
# include <stdio.h>     /* needed for printf and scanf */
# include <math.h>

/* function protypes */

double roundNumber(double);                    /* rounds the number to the nearest cent */

int
main(void)
{
          double principal,                    /* initial loan amount*/
                 annualInterestRate,           /* input from user */
                 monthlyInterestRate,          /* annual interest rate divided by 12 */
                 payment,                      /* amount to be paid each month before rounding to the nearest cent */
                 paymentRounded,               /* amount to be paid each month after rounding to the nearest cent */
                 interestAmount,               /* portion of the monthly payment that is interest */
                 principalAmount,              /* portion of the monthly payment that goes toward the principal */
                 finalPayment,                 /* variable used to store the amount of the final which may be different due to rounding */
                 totalInterest = 0;                /* total interest paid over the life of the loan */
          int totalNumberOfPayments,           /* input, number of payments */
              i;                               /* counter for the for loop */
          FILE *outp;                          /* pointer to output file */
          
          
          /* setup for output file */
          outp = fopen("loan_amortization_table.txt", "w");
                 
          /* give the user initial instruction */
          printf("Please enter the information about your loan.\nThis program will then print a custom amortization table to an output file. \nPlease input only numbers and then press the Enter key.\nDue to rounding to the nearest cent the final payment may differ from the \nothers.");
          
          /* prompt for and get the purchase price */
          printf("\n\nEnter the amount borrowed> ");
          scanf("%lf", &principal);
          
          /* prompt for and get the annual interest rate */
          printf("Enter the Annual Interest Rate as a decimal> ");
          scanf("%lf", &annualInterestRate);

          /* prompt for and get the number of payments */
          printf("Enter the Number Of Payments> ");
          scanf("%d", &totalNumberOfPayments);
                    
          monthlyInterestRate = annualInterestRate / 12;
          payment = (monthlyInterestRate * principal) / (1 - pow((1 + monthlyInterestRate), -totalNumberOfPayments));
          paymentRounded = roundNumber(payment);
          
          /* print the summary information at the beginning of the output file */
          fprintf(outp, "Principal\t\t$%.2f", principal);
          fprintf(outp, "\nPayment\t\t\t$%.2f", paymentRounded);
          fprintf(outp, "\nAnnual Interest Rate\t%.2f%%", (annualInterestRate * 100));
          fprintf(outp, "\nTerm\t\t\t%d months", totalNumberOfPayments);
          
          /* print the headings at the top of the table */
          fprintf(outp, "\n\nPayment\t  Interest\tPrincipal\tPrincipal Balance");
          
          /* loop to create the table */
          for (i = 1; i < totalNumberOfPayments; ++i)
          {
              interestAmount = roundNumber(principal * monthlyInterestRate);
              totalInterest += interestAmount;
              principalAmount = paymentRounded - interestAmount;
              principal -= principalAmount;
              fprintf(outp, "\n%5d\t%8.2f\t%8.2f\t%10.2f", i, interestAmount, principalAmount, principal);
          }
          /* calculate the final payment */
          
          interestAmount = roundNumber(principal * monthlyInterestRate);
          finalPayment = interestAmount + principal;
          totalInterest += interestAmount;
          fprintf(outp, "\n%5d\t%8.2f\t%8.2f\t      0.00", totalNumberOfPayments, interestAmount, principal);
          fprintf(outp, "\n\nFinal Payment\t%.2f", finalPayment);
          fprintf(outp, "\n\nTotal Interestt\t%.2f", totalInterest);
          
          /* close the output file */
          fclose(outp);
          
          /* direct the user to go to the output file. */
          printf("\nThe output file is now complete.\nPress ANY KEY to exit the program.\nThe output file will be in the same folder.");
          getch();
          
          return(0);
}
  
double
roundNumber(double number)
{
          double roundedNumber;
          roundedNumber = floor(number * 100 + .5) / 100;
          return(roundedNumber);
}                 
