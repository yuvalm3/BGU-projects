#!/bin/bash

# wordFinder.sh - A script for extracting and filtering words from multiple files
#
# This script receives: 
#   <file1> [file2 ...] <char> <length>
# It validates the input, ensures all files exist, converts all content to lowercase
# alphanumeric words, and extracts only words that:
#   • start with the given character
#   • have length ≥ the given minimum
#
# The script combines all files, filters matching words, counts occurrences, removes
# duplicates, sorts the results (by count and lexicographically), and prints them.
#
# Usage:
#   wordFinder.sh <valid file name> [More Files] ... <char> <length>


arr_inp=("$@")  #an array to hold the input parameters

#check if received less then 3 parameters
if [[ ${#arr_inp[@]} -lt 3 ]]  
then
	 echo >&2 Number of parameters received : ${#arr_inp[@]}
	 echo "Usage : wordFinder.sh <valid file name> [More Files] ... <char> <length>"
	 exit 1  #to terminate the script
else  
    one_before_last=${arr_inp[${#arr_inp[@]}-2]}
    last=${arr_inp[${#arr_inp[@]}-1]}
    fi


#check if char and int parameters entered correctly
if [[ (${#one_before_last} -ne 1 || ! $one_before_last =~ ^[a-zA-Z0-9]*$) ]]
then	  
    echo >&2 Only one char needed : $one_before_last
	if [[ ! $last =~ ^[0-9]+$ ]] || [[ $last -le 0 ]] 
	then 
	     echo >&2 Not a positive number : $last
		 echo "Usage : wordFinder.sh <valid file name> [More Files] ... <char> <length>"  #how to properlly enter the input
		 exit 1
	     fi
	echo "Usage : wordFinder.sh <valid file name> [More Files] ... <char> <length>"
    exit 1

elif [[ (${#one_before_last} -ne 1 || ! $last =~ ^[1-9][0-9]*$) ]]
then
     echo >&2 Not a positive number : $last
	 echo "Usage : wordFinder.sh <valid file name> [More Files] ... <char> <length>"
	 exit 1
     fi

#change char input into lowercase
if [[ $one_before_last =~ [A-Z] ]]
    then
      one_before_last=$(echo "$one_before_last" | tr '[:upper:]' '[:lower:]')
    fi

count_err=0  #new variable to know if I have a problem with an input file


#check if the files entered correctly
for file in "${arr_inp[@]:0:${#arr_inp[@]}-2}"; #loop to check if the file are trully files
do
   if [[ ! -f "$file" ]]
   then   
        echo >&2 File does not exist : "$file"
		count_err+=1
		fi
done


#check if there are unvalid files
if [[ ! $count_err = 0 ]]
then 
     echo "Usage : wordFinder.sh <valid file name> [More Files] ... <char> <length>"
	 exit 1
	 fi
		


touch AllFiles.txt  #create new file to hold all files

arr_len=${#arr_inp[@]}  #holds the lenght of the parameters array


#change the word as needed (lowercase and only a-zA-z0-9 chars
for ((k = 0; k < arr_len - 2; k++));
do
  cat "${arr_inp[$k]}" | tr -c 'a-zA-Z0-9' ' ' | tr 'A-Z' 'a-z' >> AllFiles.txt
done

touch FinalFile.txt  #create the final file - the one i'm sorting


#move only the propper words to the final file
for word in $(cat AllFiles.txt); do
	if [[ $word =~ ^$one_before_last && ${#word} -ge $last ]]  #if the word stand on conditions
	then
	    echo $word >> FinalFile.txt #move to the fhe final file
    fi
done

#sorting as needed (in-place)
sort FinalFile.txt | uniq -c | awk '{print $1,$2}'| sort -k1,1n -k2,2 > temp_file && mv temp_file FinalFile.txt

#print the final result
cat FinalFile.txt

#remove the new files i'v added (to "clean" after me)
rm AllFiles.txt
rm FinalFile.txt

