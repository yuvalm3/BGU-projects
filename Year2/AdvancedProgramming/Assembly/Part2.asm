.data

menu_message: .asciiz "Welcome to the vending machine!\n Please select an item:\n"

Chips_message1: .asciiz "1. Chips - 75 cents (Available: "

Soda_message1: .asciiz "2. Soda - 100 cents (Available: "

Candy_message1: .asciiz "3. Candy - 50 cents (Available: "

Gum_message1: .asciiz "4. Gum - 25 cents (Available: "

end_menu_message: .asciiz ")"

SoldOutChips_message: .asciiz "Sorry, Chips are Sold Out.\n"

SoldOutSoda_message: .asciiz "Sorry, Soda is Sold Out.\n"

SoldOutCandy_message: .asciiz "Sorry, Candy is Sold Out.\n"

SoldOutGum_message: .asciiz "Sorry, Gum is Sold Out.\n"

Manager_message1: .asciiz "0. Manager Mode"

Valid_Pin_message: .asciiz "Access granted. Entering Manager Mode...\n Manager Mode:\n Enter new stock for each item:\n"

Pin_message: .asciiz "Enter Pin:\n"

Incorrect_pin_message: .asciiz "Incorrect PIN. Returning to main menu.\n"

invalid_selection_message: .asciiz "Invalid selection. Please try again.\nEnter your selection:\n"

chips_message: .asciiz "You selected: Chips - 75 cents\n"

soda_message: .asciiz "You selected: Soda - 100 cents\n"

candy_message: .asciiz "You selected: Candy - 50 cents\n"

gum_message: .asciiz "You selected: Gum - 25 cents\n"  

insert_prompt: .asciiz "Insert coins (1, 5, 10, or 25 cents): "

valid_coin_message_part1: .asciiz "Current total: "

valid_coin_message_part2: .asciiz "\n"

invalid_coin_message: .asciiz "Invalid coin. Please insert 1, 5, 10, or 25 cents.\n"

too_many_attempts_part1: .asciiz "Transaction failed. Returning coins: "

too_many_attempts_part2: .asciiz " cents\n"

exact_amount_inserted: .asciiz "Dispensing chips...\nThank you for your purchase!\n"

change_required_part1: .asciiz "Dispensing chips...\nReturning Change: "

change_required_part2: .asciiz " cents\nThank you for your purchase!\n"

GetDownLine: .asciiz "\n"

update_part1: .asciiz "Updated "
update_part2: .asciiz " Stock to "
update_part3: .asciiz " .\n"

Returning_message: .asciiz "Returning to main menu.\n"

NamesArray: .word chipsN, sodaN, candyN, gumN

chipsN: .asciiz "Chips"
sodaN: .asciiz "Soda"
candyN: .asciiz "Candy"
gumN: .asciiz "Gum"

ItemsArray: .word chipsItem, sodaItem, candyItem, gumItem

chipsItem: .asciiz "1. Chips (Current: "
sodaItem: .asciiz "2. Soda (Current: "
candyItem: .asciiz "3, Candy (Current: "
gumItem: .asciiz "4. Gum (Current: "

ItemPart2: .asciiz ") - Enter your quantity:\n"

price_of_chips: .word 75
price_of_soda: .word 100
price_of_candy: .word 50
price_of_gum: .word 25

# Available dynamically stock

stockChips: .word 5
stockSoda: .word 3
stockCandy: .word 10
stockGum: .word 8



.text

main:

# Main loop

MenuLoop:
        
        jal DisplayMenu           # Display the menu
        
        jal HandleSelection       # Handle the user's selection
        
        jal HandleCoins           # Handle the coin insertion and transaction process
        
        jal MenuLoop              # Return to the main menu after completing a transaction



# Function to display the menu

DisplayMenu:

    li $v0, 4                 # Print string syscall

    la $a0, menu_message      # Load address of menu_message

    syscall
    
    # Print Chips stock
    
    li $v0, 4
    
    la $a0, Chips_message1
    
    syscall

    la $t0, stockChips      # Load Chips stock
    
    lw $t1, 0($t0)           # Load the value of chips_stock
    
    li $v0, 1
    
    move $a0, $t1            # Move stock value to $a0 for printing
    
    syscall
    
    li $v0, 4
    
    la $a0, end_menu_message # Jump to string's continue
    
    syscall

    li $v0, 4
    
    la $a0,GetDownLine # New line
    
    syscall

    # Print Soda stock
    
    li $v0, 4
    
    la $a0, Soda_message1
    
    syscall

    la $t0, stockSoda       # Load Soda stock
    
    lw $t1, 0($t0)           # Load the value of soda_stock
    
    li $v0, 1
    
    move $a0, $t1            # Move stock value to $a0 for printing
    
    syscall
    
    li $v0, 4
    
    la $a0, end_menu_message # Jump to string's continue
    
    syscall

    li $v0, 4
    
    la $a0, GetDownLine
    
    syscall

    # Print Candy stock
    
    li $v0, 4
    
    la $a0, Candy_message1
    
    syscall

    la $t0, stockCandy      # Load Candy stock
    
    lw $t1, 0($t0)           # Load the value of candy_stock
    
    li $v0, 1
    
    move $a0, $t1            # Move stock value to $a0 for printing
    
    syscall
    
    li $v0, 4
    
    la $a0, end_menu_message # Jump to string's continue
    
    syscall

    li $v0, 4
    
    la $a0, GetDownLine
    
    syscall

    # Print Gum stock
    
    li $v0, 4
    
    la $a0, Gum_message1
    
    syscall

    la $t0, stockGum        # Load Gum stock
    
    lw $t1, 0($t0)           # Load the value of gum_stock
    
    li $v0, 1
    
    move $a0, $t1            # Move stock value to $a0 for printing
    
    syscall
    
    li $v0, 4
    
    la $a0, end_menu_message # Jump to string's continue
    
    syscall

    li $v0, 4
    
    la $a0, GetDownLine
    
    syscall

    # Print Manager Mode option
    
    li $v0, 4
    
    la $a0, Manager_message1 # Jump to a function that prints Manager Mode
    
    syscall
    
    li $v0, 4
    
    la $a0, GetDownLine
    
    syscall

    jr $ra                   # Return to caller



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
    
    
    li $t1, 0                # Load the value 0 (Manager option)

    beq $t0, $t1, PinDisplay    # If selection is 0, jump to restocking menu



    # If interpreter got here - invalid selection: print the error message

    li $v0, 4                 # Print string syscall

    la $a0, invalid_selection_message

    syscall
    

    j HandleSelection                   # Start user's choise again



# Function to print the Chips message

PrintChips:

    la $t8, stockChips # Load address to check if item is sold out
    
    lw $t7, 0($t8)
    
    beq $t7, 0, SoldOutChips
   
    li $v0, 4                 # Print string syscall

    la $a0, chips_message     # Load address of chips_message

    syscall

    jr $ra                    # Return to caller - continue transaction
    
    
SoldOutChips:

    li $v0, 4                 # Print string syscall

    la $a0, SoldOutChips_message     # Load address

    syscall
    
    j MenuLoop



# Function to print the Soda message

PrintSoda:

     la $t8, stockSoda # Load address to check if item is sold out
    
    lw $t7, 0($t8)
    
    beq $t7, 0, SoldOutSoda
   
    li $v0, 4                 # Print string syscall

    la $a0, soda_message     # Load address of soda_message

    syscall

    jr $ra                    # Return to caller - continue transaction
    
    
SoldOutSoda:

    li $v0, 4                 # Print string syscall

    la $a0, SoldOutSoda_message     # Load address

    syscall
    
    j MenuLoop



# Function to print the Candy message

PrintCandy:

    la $t8, stockCandy # Load address to check if item is sold out
    
    lw $t7, 0($t8)
    
    beq $t7, 0, SoldOutCandy
   
    li $v0, 4                 # Print string syscall

    la $a0, soda_message     # Load address

    syscall

    jr $ra                    # Return to caller - continue transaction
    
    
SoldOutCandy:

    li $v0, 4                 # Print string syscall

    la $a0, SoldOutCandy_message     # Load address

    syscall
    
    j MenuLoop



# Function to print the Gum message

PrintGum:

    la $t8, stockGum # Load address to check if item is sold out
    
    lw $t7, 0($t8)
    
    beq $t7, 0, SoldOutGum
   
    li $v0, 4                 # Print string syscall

    la $a0, gum_message     # Load address

    syscall

    jr $ra                    # Return to caller - continue transaction
    
    
SoldOutGum:

    li $v0, 4                 # Print string syscall

    la $a0, SoldOutGum_message     # Load address

    syscall
    
    j MenuLoop
    

# Start of Manager Mode by asking PIN from user   

PinDisplay:

    li $v0, 4
    
    la $a0, Pin_message
    
    syscall  
                                  
    li $v0, 5                 # Read integer from user

    syscall

    move $t0, $v0             # Save the user's selection in $t0
    
    li $t1, 1234                 # Load the correct pin

    bne $t0, $t1, FailPin    # If pin is incorrect, jump to Fail PIN function
    
    j HandleRestock  # If pin is correct, jump to HandleRestock
    
    
    
# Function that handles incorrectn PIN - go back to main menu   
   
FailPin:

    li $v0, 4
    
    la $a0, Incorrect_pin_message
    
    syscall
    
    j MenuLoop

    

# Function that handles Manager's actions after entering the correct PIN

HandleRestock:

    # Print the Manager message

    li $v0, 4

    la $a0, Valid_Pin_message

    syscall



    # Load the address of ItemsArray

    la $t0, ItemsArray       # This holds the address of the item descriptions (Chips, Soda, etc.)



    # Load the address of NamesArray

    la $t4, NamesArray       # This holds the names of items (Chips, Soda, etc.)



    # Initialize index (item counter)

    li $t1, 0                # Index to iterate over the ItemsArray


# Function that make the loop of quantity update

loop:

    # Check if we have updated all 4 items
    # If yes - jump to end Manager Mode
    # If no - continue to the next item

    li $t5, 4                

    beq $t1, $t5, EndManagerMode
    
    lw $a0, 0($t0) # Load the current item string (Chips, Soda, Candy, or Gum)     
    
    li $v0, 4 # Print the current item description
    
    syscall



    # Load stock address based on $t1. Decide which of the items is the current one

    beq $t1, 0, load_stock_chips

    beq $t1, 1, load_stock_soda

    beq $t1, 2, load_stock_candy

    beq $t1, 3, load_stock_gum



load_stock_chips:

    la $t2, stockChips

    j print_current_stock



load_stock_soda:

    la $t2, stockSoda

    j print_current_stock



load_stock_candy:

    la $t2, stockCandy

    j print_current_stock



load_stock_gum:

    la $t2, stockGum



print_current_stock:

    lw $a1, 0($t2) # Load current stock value from the selected address         

    li $v0, 1

    move $a0, $a1

    syscall



    # Print part2 of item description message

    li $v0, 4

    la $a0, ItemPart2

    syscall



    # Read new quantity from user

    li $v0, 5

    syscall


    sw $v0, 0($t2) # Store the new stock value in the corresponding item location in memory

    li $v0, 4

    la $a0, GetDownLine

    syscall


    # Print confirmation message
    
    li $v0, 4

    la $a0, update_part1 

    syscall


    lw $a0, 0($t4) # Print item name

    li $v0, 4

    syscall


    li $v0, 4

    la $a0, update_part2

    syscall


    lw $a1, 0($t2)

    li $v0, 1 # Print updated stock

    move $a0, $a1

    syscall



    li $v0, 4

    la $a0, update_part3

    syscall



    # Increments for the loop

    addi $t0, $t0, 4         # Move to the next item in ItemsArray

    addi $t4, $t4, 4         # Move to the next item in NamesArray

    addi $t1, $t1, 1         # Increment index



    j loop                   # Continue to the next item



EndManagerMode:

    # Print 'returning to menu' message

    li $v0, 4

    la $a0, Returning_message

    syscall


    j MenuLoop # Go back to menu



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

        la $a0, valid_coin_message_part2

        syscall
        
        
      
        li $v0, 4            # Print the prompt to insert coins

        la $a0, insert_prompt

        syscall
        

        j read_coin_input


# Function to handle the amount of change to user

    dispense_item:
    
        # Find the selected item
    
        beq $s0, 1, DecreseChips
        
        beq $s0, 2, DecreseSoda
        
        beq $s0, 3, DecreseCandy
        
        beq $s0, 4, DecreseGum
        
        
# Decresing functions of items - update the available quantity
        
    DecreseChips:
    
       la $t5, stockChips # Load the address of stockChips into a register

       lw $t6, 0($t5)  # Load the current value of stockChips into another register

       subi $t6, $t6, 1  # Subtract 1 from the value
       
       sw $t6, 0($t5) # Store the updated value back into stockChips
       
       j cont_disp_item
       
       
    DecreseSoda:
    
       la $t5, stockSoda # Load the address of stockSoda into a register

       lw $t6, 0($t5)  # Load the current value of stockSoda into another register

       subi $t6, $t6, 1  # Subtract 1 from the value
       
       sw $t6, 0($t5) # Store the updated value back into stockSoda
       
       j cont_disp_item
       
      
     DecreseCandy:
    
       la $t5, stockCandy # Load the address of stockCandy into a register

       lw $t6, 0($t5)  # Load the current value of stockCandy into another register

       subi $t6, $t6, 1  # Subtract 1 from the value
       
       sw $t6, 0($t5) # Store the updated value back into stockCandy
       
       j cont_disp_item
       
      
     DecreseGum:
    
       la $t5, stockGum # Load the address of stockGum into a register

       lw $t6, 0($t5)  # Load the current value of stockGum into another register

       subi $t6, $t6, 1  # Subtract 1 from the value
       
       sw $t6, 0($t5) # Store the updated value back into stockGum
       
       j cont_disp_item

        
    cont_disp_item: # Continue transaction of dispensing item

        sub $t9, $t4, $t3    # Calculate change 

        bgtz $t9, dispense_change # Check if needed change



        # If exact amount

        li $v0, 4

        la $a0, exact_amount_inserted

        syscall

        j end_transaction


# If user needs change

    dispense_change:

        # Print the first part of the message to dispense change

        li $v0, 4

        la $a0, change_required_part1

        syscall



        # Print the change amount

        li $v0, 1

        move $a0, $t9           # $t9 contains the change amount

        syscall



        # Print the second part of the dispensing change ammount

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

        move $a0, $t4  # $t4 contains the total amount inserted

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
