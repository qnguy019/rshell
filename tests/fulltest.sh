#!/bin/sh
#test both test command and precedence operators
bin/rshell << EOF
ls 
(test bin && echo It exists ) || echo hello && echo Bin Exists
(test bin && echo It exists ) && echo world
test LICENSE && (echo It exists && asdf) || (test bin && (echo A && echo B)) || echo Quynh
test asdfg && (echo A && echo B) || (echo It does not exists || echo A && test bin) && echo Bin Exists
test asdf || (echo A && (test bin && (echo Bin Exists && asdf || echo See this)) || (echo Dont see this2) && echo See this too!) || echo No
echo;exit
EOF