'''
This function solves recursively a task.
Input: * target_word (str)
       * char_list (list)
Output: Boolean True/False

In our task, we would like to decide whether it is possible to assemble the input string using the characters
from the input list under the following constraints:
 (1) each character can be used more than once
 (2) after using a certain character in index i, do not use characters in indices < i.

 The function returns True if it is possible and False if it is not
 '''
def word_reconstruction(target_word: str, char_list: list):
    if len(char_list) == 0:
        return False
    if len(target_word) == 0:
        return True
    if target_word[0] == char_list[0]:
        return word_reconstruction(target_word[1:], char_list)
    else:
        return word_reconstruction(target_word, char_list[1:])


g = word_reconstruction("sad", ["s", "b", "a", "f", "b", "5", "*", "55"])
print(g)