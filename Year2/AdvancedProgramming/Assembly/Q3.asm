.data
input_array: .word 42, -12, 56, 7, -98, 102, -8, 67, 13, 76  # Input array

# Output array (4 words for max, min, sum, average)

.text
.globl main
main:

# Calculate max, min, sum, average

# Store results in output_array

# Load address of output_array into $v0


# Keep the following lines commented to make the test work.
# Normally, you would terminate your program like this:
# li $v0, 10
# syscall