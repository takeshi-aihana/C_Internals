# define a global variable asm_var and export it so that C code can use.
.data
.global asm_var
asm_var:
.long

# define a function asm_fun and export it so that C code can use.
.text
.global asm_fun
asm_fun:
    ret;
