#!/bin/bash

# Default GitHub Repository URL
default_repo_url="https://github.com/Vaibhav-Saha/COL-761-Data-Mining.git"

git clone "$default_repo_url" 

# Check if the clone was successful
if [ $? -eq 0 ]; then
  echo "Repository cloned successfully ."
else
  echo "Failed to clone repository."
  exit 1
fi

# Optional: Change to the cloned directory
# cd "$script_dir"

# Optional: List the contents of the cloned directory
# ls