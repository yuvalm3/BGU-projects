.data       #
# Place your arr here

.text       # Section for code
.globl main # Entry point for the program
main:
    #first 2 elements, dont forget to store them in arr
    li $t0, 0 
    li $t1, 1

    # Generate Fibonacci numbers and store them in arr

    # Load Fibonacci numbers from memory into registers

end:
    nop                # End of program
    # Keep the following lines commented to make the test work.
    # Normally, you would terminate your program like this:
    # li $v0, 10
    # syscall