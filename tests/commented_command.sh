#!/bin/sh

#Comments before connectors
../bin/rshell << EOF
#ls ; echo hello || cal && echo Hello Again1 || git status
ls ; #echo hello || cal && echo Hello Again2 || git status
ls ; echo hello #|| cal && echo Hello Again3 || git status
ls ; echo hello || cal #&& echo Hello Again4 || git status
ls ; echo hello || cal && echo Hello Again5 #|| git status
ls ; echo hello || cal && echo Hello Again6 || git status#
exit
EOF

#Comments after connectors
../bin/rshell << EOF
ls ;# echo hello && cal && echo Hello Again || git status
ls ; echo hello &&# cal && echo Hello Again || git status
ls ; echo hello && cal &&# echo Hello Again || git status
ls ; echo hello && cal && echo Hello Again ||# git status
ls ; echo h#i#;#echo hello
ls ; echo h#i#y#a||#echo hello
exit
EOF

#Comments attached to commands
../bin/rshell << EOF
ls #-a || echo hello
ls -a# && echo hello
ls -a && #echo hello
ls ; echo h#e#l#l#o# ; #echo hello
exit
EOF

#More comments
../bin/rshell << EOF
ls -a     #hello
echo hello#; echo #
mkdir #
echo hello; ls -ala && git status&& # echo World
exit
EOF
