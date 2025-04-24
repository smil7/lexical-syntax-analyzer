## Introduction

To start off, I built a new programming language that is based on C++. My programming 
language has the following five unique features: 
- The first part is the declaration of variables, where the user needs to declare variables once 
they start to write a program. Basically, the user first needs to declare the name of the 
variable followed by ‘=’ and the value the user assigned to it. 
- The second feature is modifying the arithmetic operators that are in c++ to a normal human 
language, where the user will have the options to do arithmetic or logical operators using the 
following keywords, arithmetic operators such as (plus|minus|multiply|divide). 
- The third feature, if an array is declared there will be a new "for" loop to iterate through this 
array easily. What makes this for loop special in our language is that we can create a 
temporary variable after declaring the for loop this variable will act as an element to all 
elements in this array. For example, "for each elem in arr:" where the (for|each|in) are 
essential keywords that should be declared once a for loop is initialized, the "elem" is the 
element variable that will act as all elements inside an array once an iteration, and the "arr" 
is the array that we are trying to iterate through. The user also needs to add “begin” and 
“end” after the colon ‘:’ to start the for loop. 
- The fourth feature is the user has the option to do comparisons between two operands using 
the following keywords (less, greater, less_equal, greater_equal, equal_to) and to check if 
this statement is true using the “is” keyword.  
- Before using any of those new keywords you need to add a dollar sign ‘$’ so that the lexical 
and syntax analyzer understands that this is a new keyword. 
- At the end of each statment, there will be a full stop to end the statement.

## Keywords
| **Keywords** | **Meaning** |
| --- | --- |
| plus | + |
| minus | - |
| divide | / |
| less | < |
| greater | > |
| less_equal | <= |
| greater_equal | >= |
| begin | start of inner scope |
| end | end of inner scope |
| display | print out to the console |

## Language Grammer
The following language grammer is how the C++ system that I have developed will understand the new programming language.

`<program> → <statements> `

`<statements> → <variables>. {<statements>}| <math_operation>. {<statements>} | <display>. `

`{<statements>} | <is_condition> | <for_each_stmnt> `

`<variables> → <identifier> = <integer> | <string> | [<integer> {, <integer>}*] {<variables>} `

`<display> → $display({<integer> | <string> | <identifier>)} [, {<identifier> | <integer> | <string> }]) `

`<for_each_stmnt> → $for $each <identifier> $in <identifier>: $begin <statements> $end `

`<is_condition> → $is <compare>: $begin <statements> $end `

`<compare> → <operand> $(less | greater| less_equal | greater_equal| equal_to) <operand> `

`<math_operation> → <operand> $(plus | minus | multiply | divide | modulus) <operand> `

`<operand> → <identifier> | <integer>  `

`<integer> → {integer} + `

`<string> → {“(Integer | letter | symbols)”} * `

`<identifier> → letter {letter | symbols} * `

`letter → 'a' | 'b' |...| 'z' | 'A'|...|'Z' `

`integer → 0 | 1 | … | 9 `

`symbols → '!' | '@' | '#' |'(' | ...... | '?'`


## Examples
You will find more examples to test in the `project-code` directory. The following is one of the examples and its output.

*Code:*

`b = [1,2,3,4,5]. `

`x = 2. `

`$for $each a $in b: `

`$begin b $plus x.` 

`$end `

![image](https://github.com/user-attachments/assets/45df3a3b-7487-4f56-a6b6-ab97ce0b17f0)
![image](https://github.com/user-attachments/assets/20b85065-f06a-4fad-b1b2-e560ff5b9b26)


