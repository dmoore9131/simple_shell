#!/bin/bash

# Define the correct password
correct_password="secretpassword"

# Prompt the user for a password
echo "Enter the password: "
read user_password

# Check if the user's input matches the correct password
if [ "$user_password" == "$correct_password" ]; then
    echo "Access granted."
else
    echo "Access denied."
fi

