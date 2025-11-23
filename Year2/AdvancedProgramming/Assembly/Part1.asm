.data

menu_message: .asciiz "Welcome to the vending machine!\n Please select an item:\n1. Chips - 75 cents\n2. Soda - 100 cents\n3. Candy - 50 cents\n4. Gum - 25 cents\n"

invalid_selection_message: .asciiz "Invalid selection. Please try again.\nEnter your selection:\n"

chips_message: .asciiz "You selected: Chips - 75 cents\n"

soda_message: .asciiz "You selected: Soda - 100 cents\n"

candy_message: .asciiz "You selected: Candy - 50 cents\n"

gum_message: .asciiz "You selected: Gum - 25 cents\n"  

insert_prompt: .asciiz "Insert coins (1, 5, 10, or 25 cents): "

valid_coin_message_part1: .asciiz "Current total: "

GetDownLine: .asciiz "\n"

invalid_coin_message: .asciiz "Invalid coin. Please insert 1, 5, 10, or 25 cents.\n"

too_many_attempts_part1: .asciiz "Transaction failed. Returning coins: "

too_many_attempts_part2: .asciiz " cents\n"

exact_amount_inserted: .asciiz "Dispensing chips...\nThank you for your purchase!\n"

change_required_part1: .asciiz "Dispensing chips...\nReturning Change: "

change_required_part2: .asciiz " cents\nThank you for your purchase!\n"


price_of_chips: .word 75

price_of_soda: .word 100

price_of_candy: .word 50

price_of_gum: .word 25



.text

main:

# Main loop

MenuLoop:
        
        jal DisplayMenu           # Display the menu
        
        jal HandleSelection       # Handle the user's selection
        
        jal HandleCoins           # Handle the coin insertion and transaction process
        
        j MenuLoop              # Return to the main menu after completing a transaction



# Function to display the menu

DisplayMenu:

    li $v0, 4                 # Print string syscall

    la $a0, menu_message      # Load address of menu_message

    syscall

    jr $ra                    # Return to caller



# Function to handle the user's selection

HandleSelection:

    li $v0, 5                 # Read integer syscall

    syscall

    move $t0, $v0             # Save the user's selection in $t0



    # Compare the selection to valid options

    li $t1, 1                 # Load the value 1 (first option)

    beq $t0, $t1, PrintChips  # If selection is 1, jump to PrintChips



    li $t1, 2                 # Load the value 2 (second option)

    beq $t0, $t1, PrintSoda   # If selection is 2, jump to PrintSoda



    li $t1, 3                 # Load the value 3 (third option)

    beq $t0, $t1, PrintCandy  # If selection is 3, jump to PrintCandy



    li $t1, 4                 # Load the value 4 (fourth option)

    beq $t0, $t1, PrintGum    # If selection is 4, jump to PrintGum



    # If interpreter got here - invalid selection: print the error message

    li $v0, 4                 # Print string syscall

    la $a0, invalid_selection_message

    syscall
    

    j HandleSelection                   # Start user's choise again



# Function to print the Chips message

PrintChips:

    li $v0, 4                 # Print string syscall

    la $a0, chips_message     # Load address of chips_message

    syscall

    jr $ra                    # Return to caller



# Function to print the Soda message

PrintSoda:

    li $v0, 4                 # Print string syscall

    la $a0, soda_message      # Load address of soda_message

    syscall

    jr $ra                    # Return to caller



# Function to print the Candy message

PrintCandy:

    li $v0, 4                 # Print string syscall

    la $a0, candy_message     # Load address of candy_message

    syscall

    jr $ra                    # Return to caller



# Function to print the Gum message

PrintGum:

    li $v0, 4                 # Print string syscall

    la $a0, gum_message       # Load address of gum_message

    syscall

    jr $ra                    # Return to caller



# Function to handle user's purchase 

HandleCoins:


    # Valid input: store it in $s0 for persisting

    move $s0, $t0


    addi $sp, $sp, -8        # Allocate stack space

    sw $s0, 0($sp)           # Save $s0 (selected item)

    sw $ra, 4($sp)           # Save return address



    # Determine the price of the selected item

    la $t1, price_of_chips      # Load address of price_of_chips (first in the order in data section)

    li $t2, 4                # Maximum selection index

    sub $t2, $s0, 1          # Index = selected item - 1

    sll $t2, $t2, 2          # Multiply index by 4 (size of word)

    add $t1, $t1, $t2        # Address of the selected item's price

    lw $t3, 0($t1)           # Load the actuall price into $t3


    li $t4, 0                # Initialize total amount inserted to 0

    li $t6, 0                # Initialize total attempts counter
    
    
    
     # Ask user to enter coins
       
     li $v0, 4           

     la $a0, insert_prompt

     syscall


        
        
# Function to read and parse user's input coin 
 
     read_coin_input: 
     
     
       # If total attempts exceed 3, fail the transaction

        bgt $t6, 2, fail_transaction
     
     
        li $v0, 5            # Read the coin value

        syscall

        move $t7, $v0        # Save coin input into $t7
        


        # Check if input is a valid coin (1, 5, 10, or 25)

        li $t8, 1            

        beq $t7, $t8, valid_coin

        li $t8, 5

        beq $t7, $t8, valid_coin

        li $t8, 10

        beq $t7, $t8, valid_coin

        li $t8, 25

        beq $t7, $t8, valid_coin


# Function to handle invalid coin
        
       invalid_coin:
       
       addi $t6, $t6, 1     # Increment total attempts
        
        # If total attempts exceed 3, fail the transaction

        bgt $t6, 2, fail_transaction
         
        
        # Invalid coin, print message and increment total attempts counter

        li $v0, 4

        la $a0, invalid_coin_message

        syscall
        
        
        j read_coin_input


# Function to handle valid coin

    valid_coin:
    

       addi $t6, $t6, 1     # Increment total attempts
        
       add $t4, $t4, $t7    # Add valid coin to total
       
        # Check if total >= price

        bge $t4, $t3, dispense_item
        
         # If total attempts exceed 3, fail the transaction

        bgt $t6, 2, fail_transaction
       
 

        # Print the first part of the message

        li $v0, 4

        la $a0, valid_coin_message_part1

        syscall

        
        # Print current total

        li $v0, 1

        move $a0, $t4           # $t4 contains the current total

        syscall



        # Print the second part of the message

        li $v0, 4

        la $a0, GetDownLine

        syscall
        
        
      
        li $v0, 4            # Print the prompt to insert coins

        la $a0, insert_prompt

        syscall
        

        j read_coin_input


# Function to handle the amount of change to user

    dispense_item:

        sub $t9, $t4, $t3    # Calculate change 

        bgtz $t9, dispense_change



        # If exact amount

        li $v0, 4

        la $a0, exact_amount_inserted

        syscall

        j end_transaction


# If user needs amount

    dispense_change:

        # Print the first part of the message

        li $v0, 4

        la $a0, change_required_part1

        syscall



        # Print the change amount

        li $v0, 1

        move $a0, $t9           # $t9 contains the change amount

        syscall



        # Print the second part of the message

        li $v0, 4

        la $a0, change_required_part2

        syscall



        j end_transaction #jump to the end of transection


# Function to handle fail transaction

    fail_transaction:

        # Print the first part of the message

        li $v0, 4

        la $a0, too_many_attempts_part1

        syscall



        # Print the total amount inserted

        li $v0, 1

        move $a0, $t4  # because $t4 contains the total amount inserted

        syscall



        # Print the second part of the message

        li $v0, 4

        la $a0, too_many_attempts_part2

        syscall


# Function to finish transaction

    end_transaction:

        lw $s0, 0($sp)       # Restore $s0

        lw $ra, 4($sp)       # Restore return address

        addi $sp, $sp, 8     # Deallocate stack space

        jr $ra               # Return to caller
