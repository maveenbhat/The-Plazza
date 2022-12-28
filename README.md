# The-Plazza-C++

This project is to make you realize a simulation of a pizzeria, which is composed of the reception that accepts new commands, of several kitchens, themselves with several cooks, themselves cooking several pizzas.

Through this project I learnt to deal with various problems, including load balancing, process and thread synchronization and communication.

--> The reception must be started using the command line the following way:
```bash
./plazza 2 5 2000
```
• The first parameter is a multiplier for the cooking time of the pizzas.It is used to examine your program more easily. Moreover this parameter is able to accept numbers with value in between 0 to 1 to obtain a divisor of the pizzas cooking time.
• The second parameter is the number of cooks per kitchen.
• The third parameter is the time in milliseconds, used by the kitchen stock to replace ingredients. 

--> The reception is an interactive shell with the following actions:
• Commands of a pizza by the user though command line, for example “regina XXL x7”. 
• Displays the kitchens status, including the current occupancy of the cooks, as well as theirs stocks of ingredients. using the status command.

--> Pizza ordering MUST respect the following grammar:

S := TYPE SIZE NUMBER [; TYPE SIZE NUMBER]* TYPE := [a..zA..Z]+
SIZE := S|M|L|XL|XXL
NUMBER := x[1..9][0..9]*
Ordering example which is grammatically valid:
regina XXL x2; fantasia M x3; margarita S x1
