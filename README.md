# BIGINT for SAMP!

## Installation

Include in your code and begin using the library:

```pawn
#include <BigInt>
```
## Usage

To create a variable
```pawn
new_BigInt::<var_name>
```
This function adds numbers in bigint (max 2147483647/callback)
```pawn
add32Bit(var_name, 1231231231);
```

With this function you can add over the limit of 2147483647. It is recommended to use this function only when large numbers are needed.
```pawn
giveBigInt(var_name, 3453453453453525534);
```

This function formats your bigint variable.
```pawn
formatBigInt(var_name);

output example:
// 312.123.512.523
```

This function sets the variable to 0.
```pawn
resetBigInt(var_name);
```

This function returns the number as a string.
```pawn
returnBigInt(var_name);
```

This function converts from 64 bits to 32 bits.
```pawn
convert64to32(var_name);
```

With this function you can do some operations for the bigint variable.
```pawn
OP64(var_name, operator, oper1);

// Operators:
>=
<=
==
!=
<
>

// example:
if(OP64(var_name, <=, 10000)) return true;
```

This function checks for string numbers.
```pawn
isBigInt(const string[]);
```

This function transforms from a string to bigint. (be careful there are numbers in that string!).
```pawn
string_to_bigInt(var_name, const string[]);
```

To make it compatible with a money system:
```pawn
new_BigInt::<cash[MAX_PLAYERS]>

#define GivePlayerCash(%0,%1) add32Bit(cash[%0],%1)
#define GetPlayerCash(%0) convert64to32(cash[%0])

new str[50];
format(str, sizeof str, "%s", FormatBigInt(cash[playerid]));

```
