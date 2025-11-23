# ************************ HOMEWORK 1 QUESTION 2 **************************
def question_2(spell, witches_num):
    ''' This function gets a spell from user and number of witches. In each loop we print a string as commanded, by taking
    into account if the number of witches is double or not. In some of the combinations we'll print an empty string,
    and for any combination that doesn't exist in the instructions we'll also print an empty string.'''

    if spell == "Alohomora!":  # condition to match the spell
        if witches_num % 2 == 0:  # condition if number of witches is double
            print("Doors Unlocked")
        else:
            print("Windows Unlocked")
    elif spell == "Lumos!":
        if witches_num % 2 == 0:
            print("Light")
        else:
            print("")
    elif spell == "Nox!":
        if witches_num % 2 == 0:
            print("Darkness")
        else:
            print("")
    elif spell == "Riddikulus!":
        if witches_num % 2 == 0:
            print("")
        else:
            print("Funny")

    else:
        print("")







