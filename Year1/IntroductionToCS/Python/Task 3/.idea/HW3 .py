import math

# Global Variables
stop_words = [
    "a", "an", "and", "are", "as", "at", "be", "by", "for", "from", "has", "have",
    "in", "is", "it", "its", "of", "on", "that", "the", "to", "was", "were", "with",
    "i", "you", "we", "he", "she", "it", "my", "your", "our", "his", "her", "its", "their",
    "this", "these", "those", "here", "there", "where", "when", "how", "all", "any",
    "many", "much", "more", "most", "other", "some", "such"
]
punctuations = ['.', ',', ':', ';', '!', '?', '"', "'", '(', ')', '[', ']', '{', '}',
                '-', '/', '\\', '&', '@', '#', '$', '%', '*', '_', '~']


corpus = {1: "The cat played the piano",
          2: "5 cats are playing ball in the backyard!",
          3: "The grand piano is in the house"}


####### Part A #########
'''The function accepts as input a string (str) and returns a new string (str) that corresponds to the input,
after removing punctuation marks.'''
def remove_punctuation(text):
    new_text = ""
    for punc_letter in text:
        if punc_letter not in punctuations:
            new_text += punc_letter
        else:
            new_text += " "
    return new_text


# n = remove_punctuation("Hi,I'm here!")
# print(n)

'''The function receives as input a document (str) and returns a new document (str) corresponding to the input, without numbers.
   Each digit in the input will be replaced by a blank character in the output.'''
def remove_digits(text):
    new_text = ""
    reference_digits_str = "0123456789"
    for is_digit in text:
        if is_digit not in reference_digits_str:
            new_text += is_digit
        else:
            new_text += " "
    return new_text


'''The function receives as input a document (str) and returns a new document (str) corresponding to the input,
   where each sequence of spaces will be replaced in a single space'''
def remove_spaces(text):
    new_text = ""
    num_in_range = 0
    for is_space in text[:-1]:
        if is_space != " ":
            new_text += is_space
        else:
            if text[num_in_range + 1] != " ":
                new_text += " "
            else:
                new_text = new_text
        num_in_range += 1
    if text[-1] != " ":
        new_text += text[-1]
    else:
        new_text = new_text
    return new_text


'''The function receives as input a list of words and returns a new list matching the input, but without stop words
   in the list defined words - stop_words.'''
def remove_stopwords(words_list):
    new_list = []
    for not_stop_word in words_list:
        if not_stop_word not in stop_words:
            new_list.append(not_stop_word)
        else:
            new_list = new_list
    return new_list


'''The function takes as input a list of words and returns a new list matching the input, as each word is converted
to its base shape.
 In order to convert a word to the base form, the end of the word must be changed according to specific rules.'''
def stemming(words_list):
    if words_list == [""]:
        words_list = []
        return words_list
    else:
        new_list = []
        for stem_word in words_list:
            if len(stem_word) != 0:
                if stem_word[-1] == "s":
                    if len(stem_word) == 1:
                        new_list.append(stem_word)
                    else:
                        if stem_word[-2] == "e":
                            if len(stem_word) == 2:
                                new_list.append("e")
                            if len(stem_word) >= 3:
                                if stem_word[-3] == "i":
                                    new_list.append(stem_word[:-3] + "y")
                            if len(stem_word) >= 4:
                                if stem_word[-3] == "s" and stem_word[-4] == "s":
                                    new_list.append(stem_word[:-4] + "ss")
                                else:
                                    new_list.append(stem_word[:-1])
                        else:
                            new_list.append(stem_word[:-1])
                elif stem_word[-1] == "d" and stem_word[-2] == "e" and len(stem_word) >= 2:
                    new_list.append(stem_word[:-2])
                elif stem_word[-1] == "g" and stem_word[-2] == "n" and stem_word[-3] == "i" and len(stem_word) >= 3:
                    new_list.append(stem_word[:-3])
                else:
                    new_list.append(stem_word)
        return new_list


'''A function that unifies the preprocessing process of a document. The function receives as input a document (str) and returns
list of words after preprocessing.
The function performs the following steps (in this order):
● Removal of punctuation marks.
● Removing digits.
● Removal of unnecessary spaces.
● Converting "capital" letters to lowercase (case lower)
● Splitting the document into a list of words, the separation between words is determined by the existence of a space.
● Removal of stop words.
● Performing stemming.
● Removal of empty strings (if there is "" in the list).'''
def preprocessing(text):
    new_list = []
    new_text = remove_punctuation(text)
    new_text = remove_digits(new_text)
    new_text = remove_spaces(new_text)
    new_text = new_text.lower()
    single_word = ""
    if len(new_text) == 1 or 0:
        new_list.append(new_text)
    else:
        for letter in new_text[:-1]:
            if letter != " ":
                single_word += letter
            else:
                new_list.append(single_word)
                single_word = ""
        if new_text[-1] == " ":
            new_list.append(single_word)
        else:
            single_word += new_text[-1]
            new_list.append(single_word)
    new_list = remove_stopwords(new_list)
    new_list = stemming(new_list)
    final_list = []
    for words_in_list in new_list:
        if words_in_list != "" and words_in_list != " ":
            final_list.append(words_in_list)
        else:
            final_list = final_list
    return final_list


###### Part B #######
'''A function that creates data documents for a document repository. The function receives as input a dictionary representing a buffer
documents, where the keys are the identification numbers of the document (int) and the values are the strings representing the
The corresponding documents (str). The function returns documents_data - a dictionary whose keys are the number represents
the identifier of each document (int) and the values are the number of words in the document after the preprocessing process from part 'A'.'''
def get_documents_data(corpus):
    new_dict = {}
    # key = 1
    for key in corpus:
        value_in_corpus = corpus[key]
        list_after_process = preprocessing(value_in_corpus)
        final_list = []
        for word in list_after_process:
            if word not in final_list:
                final_list.append(word)
            else:
                continue
        num_of_words = len(final_list)
        new_dict[key] = num_of_words
        # key += 1
    return new_dict


'''A function that creates an inverted index for a document repository. The function receives as input a dictionary representing a document database,
where the keys are the identification number of the document (int) and the values are the strings representing the document (str).
The function returns the inverted index of the document pool after preprocessing.'''
def create_inverted_index(corpus):
    inverted_index = {}
    for num_of_doc in corpus:
        value_in_corpus = corpus[num_of_doc]
        list_after_process1 = preprocessing(value_in_corpus)
        for word_in_list in list_after_process1:
            if word_in_list in inverted_index and num_of_doc in inverted_index[word_in_list]:
                inverted_index[word_in_list][num_of_doc] += 1
            elif word_in_list in inverted_index and num_of_doc not in inverted_index[word_in_list]:
                inverted_index[word_in_list][num_of_doc] = 1
            else:
                inverted_index[word_in_list] = {num_of_doc: 1}
    return inverted_index


final_inverted_index = create_inverted_index(corpus)


'''A function that adds a new document to the database. The function receives as inpu:
- inverted_index (dict)
- documents_data (dict)
- ID number of the new document (int)
- string of the new document (str)

The function returns
inverted_index and documents_data (in this order) that are updated according to the new document.'''
def add_to_data(inverted_index, documents_data, doc_id: int, text: str):
    new_dict = {doc_id: text}  # create the new dictionery
    list_after_process_for_text = preprocessing(text)  # make a list for the 'text' after preprocessing
    for word_in_list in list_after_process_for_text:  # check each word and add to her place in 'documents data' and 'inverted index'
        if word_in_list in inverted_index:
            if doc_id in inverted_index[word_in_list]:
                inverted_index[word_in_list][doc_id] += 1
            else:
                inverted_index[word_in_list][doc_id] = 1  # add 1 to number of הופעותיה in her place
        else:
            inverted_index[word_in_list] = {doc_id: 1}  # create new place for the word
    new_documents_data = get_documents_data(new_dict)  # keep in new variable the value of the new document
    documents_data[doc_id] = new_documents_data[doc_id]  # update in the document data
    return (inverted_index,
            documents_data)


'''A function that deletes a document from the database. 
The function receives as input:
- inverted_index
- documents_data
- ID number of the document you want to delete (int) 

The function returns inverted_index and documents_data (in that order) updated without the document we want to delete.'''

def remove_from_data(inverted_index: dict, documents_data: dict, doc_id: int):
    for word_in_index in inverted_index:  # to pop the doc_id
        if doc_id in inverted_index[word_in_index]:
            keep_the_value = inverted_index[word_in_index]
            keep_the_value.pop(doc_id)
        if doc_id in documents_data:  # to pop the doc_id
            documents_data.pop(doc_id)
    return inverted_index, documents_data


###### Part C #######
from math import log


'''A function that calculates the IDF-TF value of a document from the database relative to the query.
 The function accepts as input:
- word (str)
- doc_id: document ID number (int)
- inverted_index (dict)
- documents_data (dict)

The function returns the TF-IDF value of the word 'word' in the context of the document 'doc'.'''
def calculate_tf_idf(word: str, doc_id: int, inverted_index: dict, documents_data: dict):
    num_of_documents_with_word = len(inverted_index[word])
    tot_num_of_documents = len(documents_data)
    in_log = tot_num_of_documents / num_of_documents_with_word
    idf = log(in_log, 2)
    tf = inverted_index[word][doc_id] / documents_data[doc_id]
    tf_idf = tf * idf
    return round(tf_idf, 3)


'''The function receives as input:
- query: query which is a list of words (lst)
- inverted_index (dict)
- documents_data (dict)

The function returns a dictionary where the keys are the ID number of the relevant documents and the values are the TF-IDF score
between the query words and the document.'''
def get_scores_of_relevance_docs(query, inverted_index, documents_data):
    temp_dict = {}
    final_dict = {}
    new_query = []
    for words in query:
        if words in inverted_index:
            new_query.append(words)
    print(new_query)
    for spec_doc in documents_data:
        count = 0
        for word in new_query:
            if spec_doc in inverted_index[word]:
                count += calculate_tf_idf(word, spec_doc, inverted_index, documents_data)
        temp_dict[spec_doc] = count
    for i in temp_dict:
        if temp_dict[i] != 0:
            final_dict[i] = temp_dict[i]
    return final_dict


###### Part D #######
'''The function receives as input:
database of documents (dict) whose keys are the identification numbers of the documents and values
are the strings of each document

Then the user will get the menu and needs to choose beetween five options:

1 - 
   Choosing option (A): All documents relevant to the query he entered and the TF-IDF score will be printed for the user
   Choosing option (B): The number of the document with the highest TF-IDF score will be printed to the user
   hoosing option (C): the user will return to the main menu.
2 - Adding a document to the database. 
3 - Calculate the TF-IDF value between word and document.
4 - Deleting a document from the database.
5 - This option will end the function run.

The function does not return anything.'''
def menu(corpus):
    inverted_index = create_inverted_index(corpus)
    documents_data = get_documents_data(corpus)
    while True:
        choice = input(
            'Choose an option from the menu:\n\t(1) Insert a query.\n\t(2) Add document to corpus.\n\t(3) Calculate TF-IDF Score for a word in a document.\n\t(4) Delete a document from the corpus.\n\t(5) Exit.\nYour choice: ')
        if choice == '1':
            query = input('Write your query here: ')
            preprocessed_query = preprocessing(query)
            scores_of_relevance_docs = get_scores_of_relevance_docs(preprocessed_query, inverted_index, documents_data)
            while True:
                query_choice = input(
                    'Choose the type of results you would like to retrieve:\n\t(A) All relevant documents.\n\t(B) The most relevant document.\n\t(C) Back to the main menu.\nYour choice: ')
                if query_choice == 'A':
                    for doc_id, score in sorted(scores_of_relevance_docs.items()):
                        print(f'{doc_id} : {score}')
                elif query_choice == 'B':
                    highest_score = 0
                    highest_score_doc = 0
                    for doc_id, score in scores_of_relevance_docs.items():
                        if score > highest_score:
                            highest_score = score
                            highest_score_doc = doc_id
                    if highest_score > 0:
                        print(f'The most relevant document is {highest_score_doc} with a score of {highest_score}')
                elif query_choice == 'C':
                    break
                else:
                    print('Invalid choice. Please select a valid option.')

        elif choice == '2':
            while True:
                doc_id = input('Insert the document ID: ')
                # print(type(doc_id))
                # print(documents_data)
                # print(doc_id)
                if int(doc_id) not in documents_data:
                    # doc_id = input('Insert the document ID: ')
                    text = input('Insert the text of the document: ')
                    inverted_index, documents_data = add_to_data(inverted_index, documents_data, doc_id, text)
                    # print(inverted_index)
                    # print(documents_data)
                    print(f'Document {doc_id} was successfully added!')
                    break
                else:
                    print('The document ID {doc_id} is already in corpus.')

        elif choice == '3':
            while True:
                doc_id = int(input('Insert the document ID: '))
                if int(doc_id) in documents_data:
                    word = input('Insert a word: ')
                    new_list = []
                    new_list.append(word)
                    # word_as_list = input('Insert a word: ')
                    term = stemming(new_list)
                    term = term[0].lower()
                    # print(term, type(term))
                    if term not in inverted_index:
                        print(f'The word {term} is not in corpus.')
                        continue
                    else:
                        tf_idf = calculate_tf_idf(term, doc_id, inverted_index, documents_data)
                        print(f'TF-IDF of the word {term} in document {doc_id} is: {tf_idf}')
                        break
                else:
                    print('The document ID {doc_id} is not in corpus. ')
                    continue

        elif choice == '4':
            while True:
                doc_id = int(input('Insert the document ID: '))
                if int(doc_id) in documents_data:
                    inverted_index, documents_data = remove_from_data(inverted_index, documents_data, doc_id)
                    print(f'Document {doc_id} is successfully deleted.')
                else:
                    print('The document ID {doc_id} is not in corpus. ')
                    break

        elif choice == '5':
            return

        else:
            print('Invalid choice. Please select a valid option.')


gg = menu(corpus)
print(gg)

choice = input('Choose an option from the menu:\n\t(1) Insert a query.\n\t(2) Add document to corpus.\n\t(3) Calculate TF-IDF Score for a word in a document.\n\t(4) Delete a document from the corpus.\n\t(5) Exit.\nYour choice: ')
query_choice = input('Choose the type of results you would like to retrieve:\n\t(A) All relevant documents.\n\t(B) The most relevant document.\n\t(C) Back to the main menu.\nYour choice: ')


