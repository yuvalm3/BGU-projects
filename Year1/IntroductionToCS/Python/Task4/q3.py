'''
    Main function:
    input: two lists og integers
    output: the largest zigzag list we can make from the lists.

    zigzag list a list that holds the conditions:
    If each member in place of i in the list fulfills one of the following conditions:
1. is less than half the value of each of the members in positions i - 1, i + 1 in the list.
2. Greater than twice the value of each of the members in positions i - 1, i + 1 in the list.
  for  0 < i < len(lst)-1 .


  Given two lists of numbers, we will define a "zig-zag squared" list according to the following conditions:
- Zig-zag list.
- Each element from one of the input lists can appear at most once in the squared zig-zag list.
- Each member at index i from an input list that appears in the square zig-zag list will be at a lower index in the list
Zigzag in a square confirms all elements whose indices are greater than i in the input list from which it came.
That is, there are no changes in the order of appearance of the members in relation to the input lists.
'''


def merge_zigzag(list1, list2):
    if len(list1) <= 2 and len(list2) <= 2:  # Check if the size of lists is two
        return list1
    else:
        return rec_merge_zigzag(list1, list2, [])



''' 
    Helper function:
    input: two input lists we get from the user and new list initialized to an empty list that accumulating organs.
    output: The largest zigzag list as needed.
    
    This function does this with the idea of the "knapsack problem".
    
'''
def rec_merge_zigzag(lst1: list, lst2: list, curr_list: list):

    #Base cases: if the lists are not over and we have more organs to check if we can enter them to the zigzag list
    if len(curr_list) != 0 and len(curr_list) != 1:

        #check the condition of zigzag list
        if not (curr_list[-2] > 2 * curr_list[-1] or curr_list[-1] > 2 * curr_list[-2]):
            return []

    #Base case 2: if the lists are over we return the list we made so far
    if len(lst1) == 0 and len(lst2) == 0:
        return curr_list

    # option 1: add the first organ in lst1 to the current list and slice the list
    if len(lst1) >= 1:
        option1 = rec_merge_zigzag(lst1[1:], lst2, curr_list + [lst1[0]])
    else:
        option1 = curr_list
    # option 2: add the first organ in lst2 to the current list and slice the list
    if len(lst2) >= 1:
        option2 = rec_merge_zigzag(lst1, lst2[1:], curr_list + [lst2[0]])
    else:
        option2 = curr_list
    # option 3: don't choose any organ and slice lst1
    if len(lst1) >= 1:
        option3 = rec_merge_zigzag(lst1[1:], lst2, curr_list)
    else:
        option3 = curr_list
    # option 4: don't choose any organ and slice lst2
    if len(lst2) >= 1:
        option4 = rec_merge_zigzag(lst1, lst2[1:], curr_list)
    else:
        option4 = curr_list
    # return the option with the largest zigzag list
    return max(option1, option2, option3, option4, key=len)


# z = merge_zigzag([15, 10], [2, 3, 4])
# print(z)

