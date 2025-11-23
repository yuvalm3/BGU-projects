def generate_pascals_triangle(n):
    """
    Generate Pascal's triangle as a list of lists.

    Args:
        n (int): Number of rows to generate in Pascal's triangle. Should be a positive integer.

    Returns:
        list: A list of lists where each inner list represents a row in Pascal's triangle.
              Each inner list contains integers representing the values in that row.

    """
    my_triangle = []  # Initialize an empty list to store the triangle
    for i in range(n):
        row = [1] * (i + 1)  # Create a new row with all elements initialized to 1
        if i > 1:
            for j in range(1, i):
                row[j] = my_triangle[i - 1][j - 1] + my_triangle[i - 1][j]  # Calculate values based on the previous row
        my_triangle.append(row)  # Add the generated row to the triangle list
    return my_triangle  # Return the complete Pascal's triangle


def print_pascals_triangle(triangle):
    """
    Print Pascal's triangle with proper formatting.

    Args:
        triangle (list): A list of lists where each inner list represents a row in Pascal's triangle.
                         Each inner list should contain integers.

    Returns:
        None


    """
    max_width = len(' '.join([str(row) for row in triangle[-1]]))  # Determine maximum width for formatting
    for row in triangle:
        row_str = ' '.join([str(num) for num in row])  # Convert row elements to strings and join them with spaces
        print(row_str.center(max_width))  # Center align the row and print it

