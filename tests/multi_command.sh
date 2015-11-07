#!/bin/sh

#; commands
../bin/./rshell << EOF
ls; echo first; ls -a; echo second; date
ls -lalal; mkdir NEW_DIRECTORY; ls; echo I made a new directory
ls; echo you can see the new directory; echo I will now delete it; rmdir NEW_DIRECTORY
ls; echo As you can see, I deleted it
exit

EOF

#|| commands
../bin/./rshell << EOF
asdfsd || echo hello || ls || echo world
ls -a || echo dont see this
asdf || ls -a
exit

EOF
#&& commands
../bin/./rshell << EOF
adsfs && echo dont see this
echo Hello World && asdgag
echo Hello World && ls -a
exit

EOF
#mixed commands
../bin/./rshell << EOF
ssdf || asdf || echo Hello || echo World || ls && echo CS100 is awesome!
asdf || asdf && echo Hello || echo World || ls && echo CS100 is awesome!
ls asdf ; ls     -a ; echo Hello World || afe ||      echo My name is Quynh
exit

EOF
#invalid connectors
../bin/./rshell << EOF
ls -a | echo hello & date
ls -a ;; echo hello
echo hello & ls -a || echo world
exit

EOF
#invalid beginning connectors
../bin/./rshell << EOF
|ls -a
||ls -a
&&echo hello
&echo hello
;ls -l
exit

EOF
#invalid ending connectors 
../bin/./rshell << EOF
ls -a |
ls -l ||
echo hello &
date &&
ls -l;;
exit

EOF
