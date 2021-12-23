# Monte Carlo Simulation
## Malliavin calculus and its application in financial mathematics.
The Malliavin calculus, also referred to as stochastic calculus of variations, allows to establish integration by parts formulas on the Wiener space that write : for some smooth function $f$, $E[f'(X_T)G] = E[f(X_T)H(X_T, G))]$ or $∂xE[f(X_T)G] = E[f(X_T)H(X_T, G)]$ for some explicit weight $H(X_T, G)$, where $X_T$ is the solution taken at time T of some non-degenerate stochastic differential equation. It has many applications, notably in mathematical finance for the computation of Greeks for Delta hedging purpose. The aims of this project are :
- to understand the basic principle of Malliavin calculus,
- to implement the method in some simple examples related to the computation of Greeksof financial derivatives.

<br>

## Références
[1] Fournié, E. and Lasry, J.-M. and Lebuchoux, J. and Lions, P.-L. and Touzi, N, Applications
of Malliavin calculus to Monte Carlo methods in finance, Finance and Stochastics, Volume 3,
Number 4 (1999), 391–412.

[2] Fournié, E. and Lasry, J.-M. and Lebuchoux, J. and Lions, P.-L. Applications of Malliavin
calculus to Monte-Carlo methods in finance. II, Finance and Stochastics, Volume 5, Number 2
(2001), 201–236.
