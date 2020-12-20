# ExprEval

![Logo](ExprEval.jpeg)

Expression-Evaluator is a C++ library to evaluate a given string as a mathematical expression.

## Options

* **-i** for immediate calculation
* **--interactive** for interactive mode

### Interactive mode

Interactive mode allows you to create your custom symbols(functions). For example, you can create a function such that *tell_percentage(x,y)=100\*x/y* and use it in your expressions. You can also delete any symbol that you have created before, and if you have long list of custom functions you can list them in your terminal.

```bash
./expreval -i "5+3-2"
 = 6
```

```bash
./expreval
: 5+3-2
 = 6

```

```bash
./expreval --interactive
(Enter 'h' for help)
: >   # To add new symbol
    > Symbol: my_function
    > Number of arguments: 3
    > Arguments: x y var # Positions: 1, 2, 3 respectively
    > Expression: x*y+var^2
= = = = = = = = =
: ?   # To list all user-defined symbols
    - my_function(x, y, var) = x*y+var^2
= = = = = = = = =
: (3+2)*my_function(3,0,2)
 = 20
: <   # To remove a user-defined symbol
    < Symbol: my_function
= = = = = = = = =
: ?
= = = = = = = = =
: s   # To save user-defined functions
    [w] File path(default: operators.spec): my_function.spec
= = = = = = = = =
: l   # To load user-defined functions
    [r] File path(default: operators.spec): my_function.spec
= = = = = = = = =

```

## Errors and exception handling

You can also get an exception instead of an actual number as a result of the expression you have given. This can happen due to at least one of two main reasons:

* The expression contains at least one symbol which is not defined(i.e. 5+3*a)
* The expression is logically ill-formed(i.e. 5+3*!)

In both cases, the program will display a relevant error message. However, you do not need to worry; you can just define the undefined symbol as a function or you can just rewrite your expression in a correct form.

**Note: If you do not know by which order your expression is going to be evaluated then you can always use parantheses('(' and ')') to make sure that the program will prioritize the operator(s) you want!**

For example,

```bash
./expreval
(2^2)^3
 = 64

2^(2^3)
 = 256

```
