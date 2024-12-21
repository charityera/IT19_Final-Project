#include <stdio.h> // Include the standard input-output header for file and console operations
#include <string.h> // Include string header for string operations
#include <stdlib.h> // Include standard library header for functions like exit()

// Function prototypes to declare the functions before defining them
int convertRomanToDecimal(char romanNumeral[]); // Function to convert Roman numerals to decimal
void handleFileProcessing(const char *inputFilePath, const char *outputFilePath); // Function to process input and output files
void writeNumberInWords(FILE *outputFile, int number); // Function to write a number in words to a file
int executeOperation(char operatorChar, int firstOperand, int secondOperand); // Function to perform arithmetic operations
void convertNumberToWords(int number, char *outputWords); // Function to convert a number to words

// Main function, the entry point of the program
int main() {
    const char *inputFilePath = "C:\\Users\\charity\\Desktop\\ITE 19 Proj\\input.txt"; // Path to the input file
    const char *outputFilePath = "C:\\Users\\charity\\Desktop\\ITE 19 Proj\\output.txt"; // Path to the output file

    handleFileProcessing(inputFilePath, outputFilePath); // Call the function to process the files

    printf("Processing complete. Check the output at: %s\n", outputFilePath); // Notify user about completion
    return 0; // Return 0 to indicate successful program execution
}

// Function to convert a Roman numeral to a decimal number
int convertRomanToDecimal(char romanNumeral[]) {
    int romanValues[256] = {0}; // Initialize an array to map Roman characters to their values
    romanValues['I'] = 1; // Value of I is 1
    romanValues['V'] = 5; // Value of V is 5
    romanValues['X'] = 10; // Value of X is 10
    romanValues['L'] = 50; // Value of L is 50
    romanValues['C'] = 100; // Value of C is 100
    romanValues['D'] = 500; // Value of D is 500
    romanValues['M'] = 1000; // Value of M is 1000

    int decimalValue = 0, index; // Variable to store the decimal result and index for iteration
    int romanLength = strlen(romanNumeral); // Get the length of the Roman numeral string

    for (index = 0; index < romanLength; index++) { // Loop through each Roman numeral character
        // Check if the next Roman numeral has a higher value (subtraction case)
        if (index + 1 < romanLength && romanValues[romanNumeral[index]] < romanValues[romanNumeral[index + 1]]) {
            decimalValue -= romanValues[romanNumeral[index]]; // Subtract the value
        } else {
            decimalValue += romanValues[romanNumeral[index]]; // Add the value
        }
    }
    return decimalValue; // Return the final decimal value
}

// Function to process the input file and generate the output file
void handleFileProcessing(const char *inputFilePath, const char *outputFilePath) {
    FILE *inputFile = fopen(inputFilePath, "r"); // Open the input file in read mode
    FILE *outputFile = fopen(outputFilePath, "w"); // Open the output file in write mode

    // Check if the input file failed to open
    if (inputFile == NULL) {
        printf("Error: Unable to open input file at %s\n", inputFilePath); // Print an error message
        exit(1); // Exit the program with error code
    }
    // Check if the output file failed to open
    if (outputFile == NULL) {
        printf("Error: Unable to create output file at %s\n", outputFilePath); // Print an error message
        fclose(inputFile); // Close the input file
        exit(1); // Exit the program with error code
    }

    char fileLine[256], romanNumber1[100], romanNumber2[100], operatorChar; // Variables for input data
    int operand1, operand2, operationResult; // Variables for operands and operation result

    // Read the input file line by line
    while (fgets(fileLine, sizeof(fileLine), inputFile) != NULL) {
        sscanf(fileLine, "%s %c %s", romanNumber1, &operatorChar, romanNumber2); // Parse the line into two Roman numbers and an operator

        operand1 = convertRomanToDecimal(romanNumber1); // Convert the first Roman number to decimal
        operand2 = convertRomanToDecimal(romanNumber2); // Convert the second Roman number to decimal

        operationResult = executeOperation(operatorChar, operand1, operand2); // Perform the operation

        writeNumberInWords(outputFile, operationResult); // Write the result in words to the output file
    }

    fclose(inputFile); // Close the input file
    fclose(outputFile); // Close the output file
}

// Function to perform an arithmetic operation
int executeOperation(char operatorChar, int firstOperand, int secondOperand) {
    switch (operatorChar) { // Determine the operation based on the operator character
        case '+': 
            return firstOperand + secondOperand; // Addition
        case '-': 
            return firstOperand - secondOperand; // Subtraction
        case '*': 
            return firstOperand * secondOperand; // Multiplication
        case '/': 
            return firstOperand / secondOperand; // Division
        default:
            printf("Error: Unknown operation %c\n", operatorChar); // Print an error for unknown operators
            exit(1); // Exit the program with error code
    }
}

// Function to write a number in words to the output file
void writeNumberInWords(FILE *outputFile, int number) {
    char wordRepresentation[1000]; // Buffer to store the number in words
    convertNumberToWords(number, wordRepresentation); // Convert the number to words
    fprintf(outputFile, "%s\n", wordRepresentation); // Write the words to the file
}

// Function to convert a number to its English words representation
void convertNumberToWords(int number, char *outputWords) {
    char *singleDigits[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"}; // Words for single digits
    char *teenNumbers[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"}; // Words for teen numbers
    char *tensMultiples[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"}; // Words for multiples of ten
    char *higherUnits[] = {"", "Thousand", "Million"}; // Words for higher units

    if (number == 0) { // Handle the case for zero
        strcpy(outputWords, "Zero"); // Set the output to "Zero"
        return;
    }

    char resultBuffer[1000] = ""; // Buffer to store the final result
    int tempNumber = number, unitIndex = 0; // Temporary number and unit index for higher units

    while (tempNumber > 0) { // Loop through each group of three digits
        int threeDigitChunk = tempNumber % 1000; // Get the last three digits

        if (threeDigitChunk != 0) { // If the chunk is not zero
            char segmentBuffer[100] = ""; // Buffer for the current segment

            int hundredsPlace = threeDigitChunk / 100; // Get the hundreds place
            int remainder = threeDigitChunk % 100; // Get the remainder

            if (hundredsPlace > 0) { // If there is a hundreds place
                sprintf(segmentBuffer, "%s Hundred ", singleDigits[hundredsPlace]); // Add the hundreds place to the segment
            }

            if (remainder >= 10 && remainder < 20) { // If the remainder is a teen number
                strcat(segmentBuffer, teenNumbers[remainder - 10]); // Add the teen number to the segment
            } else { // If the remainder is not a teen number
                int tensPlace = remainder / 10; // Get the tens place
                int onesPlace = remainder % 10; // Get the ones place

                if (tensPlace > 0) { // If there is a tens place
                    strcat(segmentBuffer, tensMultiples[tensPlace]); // Add the tens place to the segment
                    if (onesPlace > 0) { // If there is a ones place
                        strcat(segmentBuffer, " "); // Add a space before the ones place
                    }
                }
                if (onesPlace > 0) { // If there is a ones place
                    strcat(segmentBuffer, singleDigits[onesPlace]); // Add the ones place to the segment
                }
            }

            if (unitIndex > 0) { // If there is a higher unit (thousand, million, etc.)
                char unitBuffer[100]; // Buffer for the unit
                sprintf(unitBuffer, " %s", higherUnits[unitIndex]); // Add the unit to the buffer
                strcat(segmentBuffer, unitBuffer); // Add the buffer to the segment
            }

            if (strlen(resultBuffer) > 0) { // If the result buffer is not empty
                strcat(segmentBuffer, ", "); // Add a comma and space before the segment
            }

            char tempBuffer[1000]; // Temporary buffer to store the updated result
            strcpy(tempBuffer, segmentBuffer); // Copy the segment to the temporary buffer
            strcat(tempBuffer, resultBuffer); // Append the result buffer to the temporary buffer
            strcpy(resultBuffer, tempBuffer); // Copy the temporary buffer to the result buffer
        }

        tempNumber /= 1000; // Remove the last three digits
        unitIndex++; // Move to the next higher unit
    }

    strcpy(outputWords, resultBuffer); // Copy the final result to the output
}
