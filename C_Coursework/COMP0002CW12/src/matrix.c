// Orhun Dogan
// C Coursework
// Matrix Calculator

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ADD 1
#define SUBTRACT 2
#define MULTIPLY 3
#define NEGATIVE 4
#define CONSTANT 5
#define TRANSPOSE 6
#define DETERMINANT 7
#define SAVE 8
#define QUIT 9

// Allowing compiler to see the function declerations
void menu(void);
void go(void);
int getMenuOption(void);
void doOption(int);
void printExample(int, int);
void enterValue(int row, int cols, int matrix[row][cols], int matrixIndex);
void printMatrix(int row, int cols, int array[row][cols], int matrix);
void addition(void);
void subtraction(void);
void multiplication(void);
void transposition(void);
void scalarMultiplication(void);
void getNegative(void);
void transpositionProcess(int row, int cols, int matrix[row][cols]);
void findDeterminant(void);
void saveMatrix(void);
void loadMatrix(int row, int cols, int matrix[row][cols], int matrixIndex);

// Function that displays the main menu
void menu()
{
  printf("\n*** Welcome To The Matrix Calculator ***\n");
  printf("%i. Add Two Matrices\n", ADD);
  printf("%i. Subtract Two Matrices\n", SUBTRACT);
  printf("%i. Multiply Two Matrices\n", MULTIPLY);
  printf("%i. Get The Negative Of A Matrix\n", NEGATIVE);
  printf("%i. Multiply A Matrix With A Constant\n", CONSTANT);
  printf("%i. Transpose A Matrix\n", TRANSPOSE);
  printf("%i. Find The Determinant Of A Matrix\n", DETERMINANT);
  printf("%i. Save A Matrix\n", SAVE);
  printf("%i. Quit\n", QUIT);
}

// Function that inputs the selected option in the main menu
int getMenuOption()
{
  int option;
  printf("\nEnter selection: ");
  scanf("%d", &option);
  return option;
}

// Function that chooses which calculation to perform according to the user's option
void doOption(int option){
  switch (option){
    case ADD : addition(); break;
    case SUBTRACT : subtraction(); break;
    case MULTIPLY : multiplication(); break;
    case NEGATIVE : getNegative(); break;
    case CONSTANT : scalarMultiplication(); break;
    case TRANSPOSE : transposition(); break;
    case DETERMINANT : findDeterminant(); break;
    case SAVE : saveMatrix(); break;             
    default : printf("\nSorry - don't recognise that option, try again\n");
  }
}

// Function that goes to the calculation that the user wants
void go(){
  while (1){
    menu();
    int option = getMenuOption();
    if (option == QUIT){
      break;
    } else{
      doOption(option);
    }
  }
}

// Function that prints an example matrix with specified rows and cols
void printExample(int row, int cols){
    printf("\nEnter the elements in this order: \n");
    int element = 97;                   // ASCII index of 'a'
    for(int i = 0; i<row; i++){
        for(int j = 0; j<cols; j++){
            char elementASCII = element;
            printf("%c\t", elementASCII);
            element++;
        }
        printf("\n");
    }
}

// Function that allows user to fill the matrix
void enterValue(int row, int cols, int matrix[row][cols], int matrixIndex){
    printf("\nRead from file(y/n)?: ");         
    char response[1];
    scanf("%s", &response);
    if(response[0] == 'y'){
        loadMatrix(row, cols, matrix, matrixIndex);         // Loads a matrix
    } else{
        printExample(row, cols);       // Printing the example
        int element = 97;                   // ASCII index of 'a' for elements
        for(int i = 0; i<row; i++){
            for(int j = 0; j<cols; j++){
                char elementASCII = element;            
                char matrixASCII = matrixIndex;             // ASCII index of 'A' for matrix 
                printf("Enter element %c for the matrix %c: ", elementASCII, matrixASCII);
                scanf("%d", &matrix[i][j]);
                element++;
            }
     }
         printf("\n");
    }
}

// Function that allows user to fill the matrix while saving it to a file. File contains row, cols, matrix.
void enterValueFile(int row, int cols, int matrixIndex, char fileName[], FILE *fp){
    int element = 97;
    for(int i = 0; i<row; i++){
        for(int j = 0; j<cols; j++){
            char elementASCII = element;
            char matrixASCII = matrixIndex;
            printf("Enter element %c for the matrix %c: ", elementASCII, matrixASCII);
            int value;
            scanf("%d", &value);
            fprintf(fp, "%d", value);
            fprintf(fp, " ");
            element++;
        }
        fprintf(fp, "\n");
    }
}

// Function that prints user's matrix
void printMatrix(int row, int cols, int array[row][cols], int matrix){
    char matrixASCII = matrix;                  // ASCII index of 'A' for matrix
    printf("Matrix %c: \n", matrixASCII);

    for(int i = 0; i<row; i++){
        for(int j=0;j<cols; j++){
            printf("%d\t", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function that combines inputting and printing matrix
void enterPrint(int row, int cols, int matrix[row][cols], int matrixIndex){
    enterValue(row, cols, matrix, matrixIndex);
    printMatrix(row, cols, matrix, matrixIndex);
}

// Function that adds two matrices
void additionCalculation(int row, int cols, int first[row][cols], int second[row][cols]){
    int resultMatrix[row][cols];
    for(int i = 0; i<row; i++){
        for(int j = 0; j<cols; j++){
            resultMatrix[i][j] = first[i][j] + second[i][j];        // Adding matrices
            printf("%d\t", resultMatrix[i][j]);                     // Printing solution
        }
        printf("\n");
    }
}

// Function that subtracts two matrices
void subtractionCalculation(int row, int cols, int first[row][cols], int second[row][cols]){
    int resultMatrix[row][cols];
    for(int i = 0; i<row; i++){
        for(int j = 0; j<cols; j++){
            resultMatrix[i][j] = first[i][j] - second[i][j];    // Subtracting matrices
            printf("%d\t", resultMatrix[i][j]);                 // Printing solution
        }
        printf("\n");
    }
}

// Function that multiplies two matrices
void multiplicationCalculation(int firstRow, int secondRow, int firstCols, int secondCols, int first[firstRow][firstCols], int second[secondRow][secondCols], int sum){
    int matrix = 65;            // ASCII index of 'A'
    char matrixASCII = matrix;
    int resultMatrix[firstRow][secondCols];

    printf("For the matrix %c: \n", matrixASCII);
    enterPrint(firstRow, firstCols, first, matrix);
    matrixASCII = matrix+1;     // ASCII index of 'B'
    printf("For the matrix %c: \n", matrixASCII);
    enterPrint(secondRow, secondCols, second, matrix+1);

    printf("The answer is: \n");
    // THis nested loops are used to store multiplication of A and B in one matrix
    for(int i = 0; i<firstRow; i++){
        for(int j = 0; j<secondCols; j++){
            for(int k = 0; k<secondRow; k++){
                sum += first[i][k] * second[k][j];
            }
            resultMatrix[i][j] = sum;           
            sum = 0;
        }
    }
    // Printing solution
    for(int i = 0; i<firstRow; i++){
        for(int j=0; j<secondCols; j++){
            printf("%d\t", resultMatrix[i][j]);
        }
        printf("\n");
    }

}

// Function that transposes a matrix
void transpositionProcess(int row, int cols, int matrix[row][cols]){
    int transposedMatrix[cols][row];
    printf("The answer is: \n");
    
    // Transposing the matrix
    for(int i = 0; i<row; i++){
        for(int j = 0; j<cols; j++){
            transposedMatrix[j][i] = matrix[i][j];
        }
    }
    // Printing the transposed matrix
    for(int i = 0; i<cols; i++){
        for(int j = 0; j<row; j++){
            printf("%d\t", transposedMatrix[i][j]);
        }
        printf("\n");
    } 
}

// Function that multiplies one matrix with a constant value
void scalarMultiplicationCalculation(int row, int cols, int matrix[row][cols], float constant){
    float resultMatrix[row][cols];
    for(int i = 0; i<row; i++){
        for(int j = 0; j<cols; j++){
            resultMatrix[i][j] = (float) constant * matrix[i][j];       // Scalar Multiplication 
            printf("%3.2f\t", resultMatrix[i][j]);                      // Printing solution
        }
        printf("\n");
    }
}

// Function that gets the negative values of each element in a matrix
void negativeProcess(int row, int cols, int matrix[row][cols]){
    int resultMatrix[row][cols];
    printf("The negative of the matrix: \n");
    for(int i = 0; i<row; i++){
        for(int j = 0; j<cols; j++){
            resultMatrix[i][j] = matrix[i][j] * (-1);       // Times (-1) to get negative value
            printf("%d\t", resultMatrix[i][j]);             // Printing solution
        }
        printf("\n");
    }
}

// Function that calculates the determinant of a matrix by using recursion
// 3x3 and bigger matrices are solved like 2x2. Each element of row 1 is multiplied by determinant of a smaller matrix(2x2).
// That submatrix is created by ignoring the rows/cols of the selected element. 
// Reference: https://www.youtube.com/watch?v=zXmhmZTbuWY&t=600s 
float determinantCalculation(int row, int cols, int matrix[row][cols]){
    int size = row; float sign = 1.0; float total = 0.0;
    if(size == 1){
        return matrix[0][0];            // 1x1 matrices' determinant is its only element
    }
    else if(size == 2){
        return matrix[0][0]*matrix[1][1] - matrix[0][1] * matrix[1][0];         // Process of 2x2 matrices
    } else{
    for(int i = 0; i<size; i++){
        int minorMatrix[size-1][size-1];                    // creating a minor matrix
        for(int j = 0; j<size; j++){                        // j = row
            for(int k = 0; k<size; k++){
                if(k<i){                                    // k = cols
                    minorMatrix[j-1][k] = matrix[j][k];
                }
                else if(k>i){
                    minorMatrix[j-1][k-1] = matrix[j][k];
                }
            }
        }
        // Determining the sign of the calculation
        if(i%2==0){
            sign = 1;
        } else{
            sign = -1;
        }
        total += sign * matrix[0][i] * determinantCalculation(row-1, cols-1, minorMatrix);
    }
    return total;
    }
}

// Function that operates the whole addition procedure
void addition(){
    int row, cols, matrix = 65;
    printf("Enter the size of matrix (?x?): ");             // Both A and B have the same size in addition
    scanf("%dx%d", &row, &cols);
    int firstMatrix[row][cols]; int secondMatrix[row][cols];

    enterPrint(row, cols, firstMatrix, matrix);
    enterPrint(row, cols, secondMatrix, matrix+1);

    printf("The answer is: \n");
    additionCalculation(row, cols, firstMatrix, secondMatrix);
    
}

// Function that operates the whole subtraction procedure
void subtraction(){
    int row, cols, matrix = 65;
    printf("Enter the size of matrix (?x?): ");         // Both A and B have the same size in subtraction
    scanf("%dx%d", &row, &cols);
    int firstMatrix[row][cols]; int secondMatrix[row][cols];

    enterPrint(row, cols, firstMatrix, matrix);
    enterPrint(row, cols, secondMatrix, matrix+1);

    printf("The answer is: \n");
    subtractionCalculation(row, cols, firstMatrix, secondMatrix);
}

// Function that operates the whole multiplication procedure
void multiplication(){
    int firstRow, secondRow, firstCols, secondCols, sum = 0, matrixIndex = 65;
    char matrixASCII = matrixIndex;
    printf("Enter the size of matrix %c (?x?): ", matrixASCII);         // Inputting the size of A
    scanf("%dx%d", &firstRow, &firstCols);
    matrixASCII = matrixIndex+1;
    printf("Enter the size of matrix %c (?x?): ", matrixASCII);         // Inputting the size of B
    scanf("%dx%d", &secondRow, &secondCols);
    matrixASCII = matrixIndex;
    int firstMatrix[firstRow][firstCols]; int secondMatrix[secondRow][secondCols];

    if(secondRow != firstCols){
        printf("\nSorry. These matrices can not be multiplied.\n");      // Row of B must be equal to Columns of A
    } else{
        multiplicationCalculation(firstRow, secondRow, firstCols, secondCols, firstMatrix, secondMatrix, sum);
    }
}

// Function that operates the whole transposition procedure
void transposition(){  
    int row, cols, matrixIndex = 65;
    printf("Enter the size of matrix (?x?): ");         // Inputting the size of the matrix
    scanf("%dx%d", &row, &cols);
    int matrix[row][cols];

    enterPrint(row, cols, matrix, matrixIndex);
    transpositionProcess(row, cols, matrix);
}

// Function that operates the whole scalar multiplication procedure
void scalarMultiplication(){
    int row, cols, matrixIndex = 65;
    float constant;
    printf("Enter the size of matrix (?x?): ");         // Inputting the size of the matrix
    scanf("%dx%d", &row, &cols);
    int matrix[row][cols];

    enterPrint(row, cols, matrix, matrixIndex);
    printf("\nEnter the constant: ");               // Inputting the constant value
    scanf("%f", &constant);

    scalarMultiplicationCalculation(row, cols, matrix, constant);
}

// Function that operates the whole getting negative procedure
void getNegative(){
    int row, cols, matrixIndex = 65;
    printf("Enter the size of matrix (?x?): ");      // Inputting the size of the matrix       
    scanf("%dx%d", &row, &cols);
    int matrix[row][cols];

    enterPrint(row, cols, matrix, matrixIndex);
    negativeProcess(row, cols, matrix);
}

// Function that operates the whole finding determinant procedure
void findDeterminant(){
    int row, cols, matrixIndex = 65;
    printf("Enter the size of matrix(?x?): ");          // Inputting the size of the matrix
    scanf("%dx%d", &row, &cols);
    
    if(row != cols){
        printf("The matrix must be square.\n");     // The matrix must be square (1x1, 2x2, 3x3, etc.)
    } else{
        int matrix[row][cols];
        enterPrint(row, cols, matrix, matrixIndex);
        printf("%3.2f\n", determinantCalculation(row, cols, matrix));
    }
}

// Function that saves a matrix into a file
void saveMatrix(){
    char fileName[20]; int row, cols, matrixIndex = 65;
    printf("Enter the file name: ");
    scanf("%s", &fileName); 
    FILE *fp = fopen(fileName, "w");            // File creation with user's file name
    printf("Enter the size of matrix (?x?): ");
    scanf("%dx%d", &row, &cols);
    fprintf(fp, "%d\n", row); fprintf(fp, "%d\n", cols);
    enterValueFile(row, cols, matrixIndex, fileName, fp);       // Fills the matrix
    fclose(fp);
}

// Function that loads previously saved matrices from files
void loadMatrix(int row, int cols, int matrix[row][cols], int matrixIndex){
    char fileName[20]; int repeat = 1; FILE *fp;
    while(repeat == 1){
        printf("\nEnter file name: ");
        scanf("%s", &fileName);
        if(access(fileName, F_OK) == -1){           // Checks if a file called fileName exists
            printf("Invalid file");
        } else{
            fp = fopen(fileName, "r");
            int rowFile, colsFile;
            fscanf(fp, "%d", &rowFile); fscanf(fp, "%d", &colsFile);
            if(rowFile != row || colsFile != cols){                 // Checks if that matrix's size suits the calculation
                printf("Input matrix must be dimension of %dx%d but the file has a matrix of %dx%d", row, cols, rowFile, colsFile);
                fclose(fp);
            } else{
                repeat = 0;
            }
        }
    }
    for(int i = 0; i<row; i++){
        for(int j = 0; j<cols; j++){
            int value;
            fscanf(fp, "%d", &value);
            matrix[i][j] = value;
        }
    }
    fclose(fp);
}

// Main function to run the code
int main(void){
    //fileGo();
    go();
    return 0;
}