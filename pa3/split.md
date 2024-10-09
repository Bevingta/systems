# Task Splitting

### Introduction to pa3
- User enters number in decimal format
- Prints all bits of floating point representation
- Bit patterns of:
    - Sign
    - Exponent
    - Mantissa
- Reconstitutes original value and prints it as a decimal number using the formula $v = (-1)^s * (1+m) * 2^{e-b}$
- $s$ is the sign bit, $m$ is the mantissa, $e$ is the exponent, and $b$ is the bias
- 0 is a special case where you do not print the equation
- There is a different formula for denormalized numbers

