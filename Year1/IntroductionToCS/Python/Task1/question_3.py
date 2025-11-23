# ************************ HOMEWORK 1 QUESTION 3 **************************
def question_3(input_num):
    for i in reversed(range(1, input_num + 1)):  # loop from 1 to number (include) in reverse
        print(i, end="")  # print the input number
        for x in range(0, i):  # new "for" loop that print asterisks
            print("*", end="")  # print asterisks as needed
        print(i)  # print the number that closes the string and now we can continue to the next number
