#!/bin/sh

#test single commands
../bin/./rshell << EOF
ls
ls -a
ls -l
ls -alalalala
echo hello
echo hello my
echo hello my name is quynh
git status
mkdir NEW_DIRECTORY
ls
rmdir NEW_DIRECTORY
ls
cal
date
exit
EOF

#incorrect inputs
../bin/./rshell << EOF
asdfsddfgergth
mkdir
kal
dat
 ||
   &&
   ;;
exit
EOF
