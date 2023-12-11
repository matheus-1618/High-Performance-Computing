import subprocess
import sys

# Define the command to invoke busca_local
if len(sys.argv) < 2:
    print("Usage: python3 check.py <number_of_input>")
    exit()
print("============================")
print("Results for random search: ")
print("============================")
command = f'cat in{sys.argv[1]}.txt | ./busca_local'


# Initialize variables to keep track of the best result and its line
best_result = None
best_line = None

# Initialize variables to store the line above the best line and the items after the best line
line_above_best = None
items_after_best = None

# Run the command 10 times
for i in range(100):
    # Run the command and capture its output
    result = subprocess.run(command, stdout=subprocess.PIPE, text=True, shell=True, executable='/bin/bash')

    # Split the output into lines
    lines = result.stdout.strip().split('\n')

    # Extract the second line and the line above it
    for index, line in enumerate(lines):
        if index == 1:
            second_line = line
            line_above_best = lines[index - 1]

    # Extract the second number from the second line
    second_number = int(second_line.split()[1])

    # Check if this is the best result so far
    if best_result is None or second_number > best_result:
        best_result = second_number
        best_line = second_line
        items_after_best = lines[2:]  # Capture items after the best line

# Print the line above the best line
print(line_above_best)

# Print the best line
print(best_line)

# Print the items after the best line
print('\n'.join(items_after_best))

print("============================")
print("Results for Full bag: ")
print("============================")
command = f'cat in{sys.argv[1]}.txt | ./mochila_cheia'


# Initialize variables to keep track of the best result and its line
best_result = None
best_line = None

# Initialize variables to store the line above the best line and the items after the best line
line_above_best = None
items_after_best = None

# Run the command 10 times
for i in range(100):
    # Run the command and capture its output
    result = subprocess.run(command, stdout=subprocess.PIPE, text=True, shell=True, executable='/bin/bash')

    # Split the output into lines
    lines = result.stdout.strip().split('\n')

    # Extract the second line and the line above it
    for index, line in enumerate(lines):
        if index == 1:
            second_line = line
            line_above_best = lines[index - 1]

    # Extract the second number from the second line
    second_number = int(second_line.split()[1])

    # Check if this is the best result so far
    if best_result is None or second_number > best_result:
        best_result = second_number
        best_line = second_line
        items_after_best = lines[2:]  # Capture items after the best line

# Print the line above the best line
print(line_above_best)

# Print the best line
print(best_line)

# Print the items after the best line
print('\n'.join(items_after_best))
