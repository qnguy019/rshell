#!/bin/sh

echo "S: # ls -a || echo Hello world ; No commands should run"
# ls -a || echo Hello world ; No commands should run

echo "S: ls -l #List of files in the current directory"
ls -l #List of files in the current directory

echo "$: mkdir NEW_DIRECTORY # This makes a new folder called NEW_DIRECTORY"
mkdir NEW_DIRECTORY # This makes a new folder called NEW_DIRECTORY

echo "$: ls -a # As you can see, there is a new folder now!"
ls -a # As you can see, there is a new folder now!

echo "S: echo # This should echo nothing"
echo # This should echo a new line

echo "S: ls                 # -a # this should just run ls command with no flags"
ls                 # -a # this should just run ls command with no flags

echo "S: echo removing directory; rmdir NEW_DIRECTORY; ls -a # This is a comment"
echo removing directory; rmdir NEW_DIRECTORY; ls -a # This is a comment
