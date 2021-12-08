This is a reupload. Additional credit to my partner Malcolm Bell, credit to Colgate University for starter code. 

#Binary calculator

The program runs in the terminal.
To use the binary calculator, run the command:
```bash
$ ./binarycalc "FORMULA"
```
replacing `FORMULA` with an acceptable binary formula (details below). For example:
```bash
$ ./binarycalc "10 + 11"
```
The program supports formulas with the following format.
* An optional modifier (`~`, `-`)
* At least one and up to `MAX_DIGITS` ones and zeros
* A space
* An operator (`+`, `&`, `^`)
* A space
* An optional modifier (`~`, `-`)
* At least one and up to `MAX_DIGITS` ones and zeros

If the inputs are valid, the program will zero-extend both operands to the specified maximum digits, then apply the modidiers, then apply the operators, and finally return the answer. 


