# ************************ HOMEWORK 1 QUESTION 4 **************************
def question_4(input_list):
    sum_num1 = 0  # sum of the elaborate numbers
    count = 0  # count the amount of the elaborate numbers
    for num1 in input_list:  # check each number in our list
        if num1 == 0:  # check if the number is 0
            break  # stop the "for" loop
        else:
            n = elaborate(num1)  # check if the number in the list is elaborate
            if n:  # if the number is elaborate:
                sum_num1 = sum_num1 + num1  # add this number to our sum of elaborated numbers
                count = count + 1  # add 1 to the amount of elaborated numbers
    if sum_num1 == 0:  # if there are no elaborated numbers in the list, print 0 as we've asked for
        print(sum_num1)
    else:
        print(round(sum_num1 / count, 2))  # print the average of elaborated numbers


def elaborate(num):  # function that return "True" if the unput number is elaborate
    sum2 = 0  # new variable
    for x in range(1, num):  # loop for all the numbers from 1 until the input
        if num % x == 0:  # check if number is natural divider
            sum2 += x  # add to sum of natural dividers
    if num == sum2:  # check if elaborate
        return True
    else:
        return False  # if not elaborate

