#!/bin/sh

#test single ()
bin/rshell << EOF
(echo A && echo B) && echo C
(asdf && echo B) && echo C
(asdf && echo B) || echo C
(asdf || echo B) && echo C
(asdf || echo B) || echo C
(echo A && asdf) && echo B
(echo A && asdf) || echo B
(echo A || asdf) && echo B
(echo A || asdf) || echo B
echo A && (asdf && echo B) || echo C
asdf && (echo B || echo C)
asdf && (echo B || echo C) || echo D
echo; exit
EOF

#test multiple ()
bin/rshell << EOF
(echo A && echo B) && (echo C && echo D) 
(echo A && echo B) || (echo C && echo D) && echo H
echo Hello && asdf || (echo A && asdf) && (echo C && echo D) || echo World
(asdf && echo B) && echo C && asdf && (asdf || echo Hello World) || (echo Quynh && echo Nguyen)
echo Hello || (asdf || asdf) && echo World
echo; exit
EOF

#test () errors
bin/rshell << EOF
ls
(echo A && echo B && echo C
(asdf && echo B)) && echo C
((asdf && echo B) || echo C
(asdf || echo B) && ( )
(asdf || echo B&&) || echo C
(||echo A && asdf) && echo B
(;echo A && asdf) || echo B
(echo A || asdf) && echo B)
echo; exit
EOF


#test single ()
bin/rshell << EOF
ls
(echo A && echo B) && echo C
(asdf && echo B) && echo C
(asdf && echo B) || echo C
(asdf || echo B) && echo C
(asdf || echo B) || echo C
(echo A && asdf) && echo B
(echo A && asdf) || echo B
(echo A || asdf) && echo B
(echo A || asdf) || echo B
echo A && (asdf && echo B) || echo C
asdf && (echo B || echo C)
asdf && (echo B || echo C) || echo D

echo; exit
EOF

