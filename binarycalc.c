/********
 * Project 01: Binary calculator
 * COSC 208, Introduction to Computer Systems, Fall 2021
 ********/

#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 8
#define MAX_FORMULA_LEN (1 + MAX_DIGITS + 3 + 1 + MAX_DIGITS)

int b1len = 0; //operand 1 length
int b2len = 0; //operand 2 length
char mods_operator[3];
char b1[MAX_DIGITS+1];
char b2[MAX_DIGITS+1];
char outputFormula[MAX_FORMULA_LEN];
char product[MAX_DIGITS+1];
int flow;

int validate(char[]);

void extend(char[]);

void not(char[]);

void negate(char[]);

void addition(char[], char[]);

void and(char[], char[]);

void xor(char[], char[]);

void createFormula();

int main(int argc, char *argv[]) { 
    //checks valid amount of inputs. 
    if (argc != 2) {    
        printf("Provide a single, valid binary formula\n");
        return 1;
    }
    //makes sure input is not too long
    if (strlen(argv[1]) > MAX_FORMULA_LEN) {
        printf("Invalid binary formula\n");
        return 1;
    }

    char formula_str[MAX_FORMULA_LEN + 1];
    strcpy(formula_str, argv[1]);
    //validates format with validate function.
    if (validate(formula_str) == 1) {
        printf("Invalid binary formula\n");
        return 1;
    }
    //extend zeroes and print formula. 
    extend(formula_str);
    strcpy(formula_str, outputFormula);
    createFormula();
    printf("%s\n", outputFormula);
    //apply modifiers and reprint
    if(mods_operator[0] == '~'){
        not(b1);
    } else if ( mods_operator[0] == '-'){
        negate(b1);
    }
    if(mods_operator[2] == '~'){
        not(b2);
    } else if ( mods_operator[2] == '-'){
        negate(b2);
    }
    b2[MAX_DIGITS] = '\0';
    mods_operator[0] = ' ';
    mods_operator[2] = ' ';
    createFormula();
    printf("%s\n", outputFormula);
    //apply operand and print product and over/underflow if relevant
    if (mods_operator[1] == '+') {
        addition(b1, b2);
        printf("%s\n", product);
    }
    if (mods_operator[1] == '&') {
        and(b1, b2);
        printf("%s\n", product);
    }
    if (mods_operator[1] == '^') {
        xor(b1, b2);
        printf("%s\n", product);
    }   
    if (flow == 1) {
        printf("Overflow");
    } else if ( flow == -1){
        printf("Underflow");
    }
}
//ensures the input is in valid format. 
int validate( char formula[]){
    int index = 0; 
    // check for valid first modifier, store in mods_operator if there
    if(formula[0] == '~' || formula[0] == '-'){
        index++;
        mods_operator[0] = formula[0]; //store modifier 1
            
    } else if(formula[0] != '0' && formula[0] != '1'){ 
    }
    //check if first operand is valid binary and under MAX_DIGITS size, and makes a copy of it in b1.
    while(formula[index] == '0' || formula[index] == '1'){
        b1len++;
        if(b1len>MAX_DIGITS){
            return 1;
        }
        char temp[] = {formula[index], '\0'};
        strcat(b1, temp);
        index++;        
    }
    //following 3 if statements check for spaces and valid middle operator, saving operator
    if(formula[index] != ' '){
        return 1;
    }
    index++;
    if(formula[index] != '+' && formula[index] != '&' && formula[index] != '^' ){
        return 1;
    }
    mods_operator[1] = formula[index];
    index++;
    if(formula[index] != ' '){
        return 1;
    }
    index++;
    //checks for valid second modifier and saves in mods_operator if there
    if(formula[index] == '~' || formula[index] == '-'){
        mods_operator[2] = formula[index];
        index++;
    } else if (formula[index] != '0' && formula[index] != '1'){ 
        return 1;
    }
    //check if second operand is valid binary and under MAX_DIGITS size, and makes a copy of it in b2.
    while(formula[index] == '0' || formula[index] == '1'){
        b2len++;
        if(b2len>MAX_DIGITS){
            return 1;
        }
        char temp1[] = {formula[index], '\0'};
        strcat(b2, temp1);
        index++;        
    }
    //makes sure formula ends properly
    if(formula[index] != '\0'){
        return 1;
    }
    //makes sure both operands exist
    if(b1len < 1 || b2len < 1){
        return 1;
    }
    return 0;
}
//zero extends both operands. 
void extend(char formula[]) {
    //extend b1 to MAX_DIGITS length by concatenating b1 onto proper amount of 0s
    char temp[MAX_DIGITS];
    int i = 0;
    while(i<(MAX_DIGITS-b1len)){
        temp[i] = '0';
        i++;
    }
    temp[i]='\0';
    strcat(temp,b1);
    strcpy(b1,temp);

    //extend b2 to MAX_DIGITS length by concatenating b2 onto proper amount of 0s
    char temp2[MAX_DIGITS];
    i = 0;
    while(i<(MAX_DIGITS-b2len)){
        temp2[i] = '0';
        i++;
    }
    temp2[i]='\0';
    strcat(temp2,b2);
    strcpy(b2,temp2);
    // recreate binary formula using zero extended b1 and b2 and saved modifiers and operators in mods_operator []
}
//recreates the current formula in outputFormula
void createFormula(){
    memset(outputFormula, '\0', strlen(outputFormula));
    //use index to traverse current data and add each to outputFormula. 
    int index = 0;
    if (mods_operator[0] == '~' || mods_operator[0] == '-') {
        outputFormula[0] = mods_operator[0];
        index++;
    }
    strcat(outputFormula, b1);
    index += strlen(b1);
    outputFormula[index] = ' ';
    index++;
    outputFormula[index] = mods_operator[1];
    index++;
    outputFormula[index] = ' ';
    index++;
    if (mods_operator[2] == '~' || mods_operator[2] == '-') {
        outputFormula[index] = mods_operator[2];
        index++;
    }
    strcat(outputFormula, b2);
    
}
//flip all bits in given operand. 
void not(char b[]){
    //set each bit to opposite. 
    for(int i = 0; i<MAX_DIGITS; i++){
        if(b[i] == '1'){
            b[i] =  '0';
        } else {
            b[i] = '1';
        }
    }
}
//flips each bit and adds one. 
void negate(char b[]){
    not(b);
    char toAdd[MAX_DIGITS] = {'1', '\0'};
    char temp[MAX_DIGITS];
    //create a one in binary and extend it, then call addition() to add it onto flipped operand. 
    int i = 0;
    while(i<(MAX_DIGITS-1)){
        temp[i] = '0';
        i++;
    }
    temp[i]='\0';
    strcat(temp,toAdd);
    addition(b, temp);
    strcpy(b, product);
}
//takes two operands and adds them together, keeping track of overflow and underflow. 
void addition(char b1[], char b2[]){
    int carry = 0;

    product[MAX_DIGITS] = '\0';
    //iterates through operands and product, setting carry over and places in product as needed. 
    for (int i = MAX_DIGITS-1; i >= 0; i--) {
        if (carry == 1){
            if (b1[i] == '1' && b2[i] == '1') {
                product[i] = '1';
                carry = 1;
            }
            else if (b1[i] == '1' || b2[i] == '1') {
                product[i] = '0';
                carry = 1;
            }
            else {
                product[i] = '1';
                carry = 0;
            }
        }
        else {
            if (b1[i] == '1' && b2[i] == '1') {
                product[i] = '0';
                carry = 1;
            }
            else if (b1[i] == '1' || b2[i] == '1') {
                product[i] = '1';
                carry = 0;
            }
            else {
                product[i] = '0';
                carry = 0;
            }
        }

      
    }
    // checks for under and overflow based on signs of operands and product. 
    if (b1[0]=='1' && b2[0]=='1' && product[0] == '0'){
        flow = -1;
    } 
    if (b1[0]=='0' && b2[0]=='0' && product[0] == '1') {
        flow = 1;
    }
}
//given two operands, performs and operation. 
void and(char b1[], char b2[]){
    product[MAX_DIGITS] = '\0';
    //if both operands have a 1 in the same place, then product will as well. else it will have zero. 
    for (int i = 0; i < MAX_DIGITS; i++) {
        if (b1[i] == '1' && b2[i] == '1') {
            product[i] = '1';
        }
        else { product[i] = '0'; }
    } 
}
//given two operands, apply xor operation. 
void xor(char b1[], char b2[]){
    char one[2];
    one[0] = '1';
    char zero[2];
    zero[0] = '0';

    product[MAX_DIGITS] = '\0';
    //as long as the same place in b1 and b2 are not equal, add a 1 in that place in product. else add zero. 
    for (int i = 0; i < MAX_DIGITS; i++) {
        if (b1[i] == '1' && b2[i] == '0') {
            strncat(product, one, 1);
        }
        else if (b1[i] == '0' && b2[i] == '1') {
            strncat(product, one, 1);
        }
        else { strncat(product, zero, 1); }
    }
    
}
