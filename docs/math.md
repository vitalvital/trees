# Basic Definitions

### Balance function B(n)
Let's denote _balance function_ as **B(n)**: Ν -> Ν  
Any such function...

### Classic balance function
Classic balance function is based on σ(n), in this case:  
B(n) = σ<sub>1</sub>(n) - n  
sum of proper divisors of n,
giving classical definitions of _abundant_, _deficient_
and _perfect_ numbers, etc. 

We will slightly generalize here by using generic B(n) instead of a σ based def.
Considering this, any following definitions, while bearing familiar classical names,
will have meaning only with respect to a given balance function.
Henceforward "with respect to a given balance function" will always be assumed and omitted, in most cases.

### Gain
G(n) = B(n) - n

### Deficient Number
n is _deficient_ if G(n) < 0 ( or n > B(n) )

### Abundant Number
n is _abundant_ if G(n) > 0 ( or n < B(n) )

### Perfect Number
n is _perfect_ if G(n) = 0 ( or n = B(n) )

### B<sub>k</sub>(n)
B<sub>0</sub>(n) = n  
B<sub>1</sub>(n) = B(n)  
B<sub>k</sub>(n) = B(B<sub>k - 1</sub>(n))

### Path
A sequence:
B<sub>0</sub>(n), B<sub>1</sub>(n) ...

