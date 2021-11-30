# BIGINT for SAMP!

## Installation

Include in your code and begin using the library:

```pawn
#include <BigInt>
```
## Usage

To create a variable
```pawn
new BigInt:var_name;
```
This function adds numbers in bigint (max 2147483647/callback)
```pawn
addBytes32(var_name, 1231231231);
```

With this function you can add over the limit of 2147483647. It is recommended to use this function only when large numbers are needed.
```pawn
addBytes64(var_name, 3453453453453525534);
```

This function formats your bigint variable.
```pawn
formatBytes(var_name);

output example:
// 312.123.512.523
```

This function sets the variable to 0.
```pawn
resetBigInt(var_name);
```

This function returns the number as a string.
```pawn
valueBigInt(var_name);
```

This function converts from 64 bits to 32 bits.
```pawn
bytes32(var_name);
```

With this function you can do some operations for the bigint variable.
```pawn
OPByte(var_name, operator, oper1);

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
converBytes(var_name, const string[]);
```
These functions are compatible on mysql r41-4 and r-39-6
```pawn
cache_get_value_name_bigint(var_name, row, column[]); // r41-4
cache_get_field_content_bigint(var_name, row, column[]); // r39-6
```

To make it compatible with a money system:
```pawn
new BigInt:cash[MAX_PLAYERS];

#define GivePlayerCash(%0,%1) addBytes32(cash[%0],%1)
#define GetPlayerCash(%0) bytes32(cash[%0])

// show money
new str[50];
format(str, sizeof str, "%s", formatBytes(cash[playerid]));

// login
cache_get_value_name_bigint(cash[playerid],0,"Money");

// disconect save
public OnPlayerDisconect(playerid) {
    new query[128];
    mysql_format(handle, query, "UPDATE `users` SET `Money` = '%s' ...", valueBigInt(cash[playerid]));
    mysql_tquery(handle, query);
    return true;
}

```
