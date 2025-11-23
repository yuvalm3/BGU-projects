.data   
T: .word 0    # Memory space for T

.text       # Section for code
.globl main # Entry point for the program
main:
    # Initialize registers with X and Y
    li $t0, 12 # X
    li $t1, 25 # Y

    # Step 1: Z = X * 4 + Y
    add $s0, $t0, $t0
    add $s0, $s0, $s0 
    add $s0, $s0, $t1
    # Step 2: W = Y * 3 - 15
    add $s1, $t1, $t1
    add $s1, $s1, $t1
    subi $s1, $s1, 15
    # Step 3: R = Y^2 + X^2
    square_y:
    move $t2, $zero        # Initialize $t2 to zero
    move $t3, $t1          # Create the counter
    
    loop_y:
        beqz $t3, end_y    # If counter $t3 == 0, break the loop
        add $t2, $t2, $t1  # Add Y repeatedly: $t2 += $t1
        subi $t3, $t3, 1   # Decrement counter $t3
        j loop_y
    end_y:
        # $t2 now contains Y^2

# Step 2: Compute X^2
mul_x:
    move $t4, $zero        # Initialize $t4 (X^2 accumulator) to 0
    move $t5, $t0          # Copy X to $t5 (counter for multiplication)
    loop_x:
        beqz $t5, end_x    # If counter $t5 == 0, break the loop
        add $t4, $t4, $t0  # Add X repeatedly: $t4 += $t0
        subi $t5, $t5, 1   # Decrement counter $t5
        j loop_x
    end_x:
        # $t4 now contains X^2

# Step 3: Compute R = Y^2 + X^2
    add $s2, $t2, $t4      # R = Y^2 + X^2, store result in $s2

    # Step 4: T = Z + W + R - 5

    # Step 5: Save the address of T in $v0


    # Keep the following lines commented to make the test work.
    # Normally, you would terminate your program like this:
    # li $v0, 10
    # syscall
