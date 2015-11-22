#!/bin/sh
#test default flag
bin/rshell << EOF
ls 
test bin && echo It exists 
test LICENSE && echo It exists 
test Makefile && echo It exists 
test README.md && echo It exists 
test src && echo It exists 
test tests && echo It exists 
test asdfg && echo It exists 
test asdfg || echo It does not exists
echo
exit
EOF

#test -e flag
bin/rshell << EOF
ls 
test -e bin && echo It exists 
test -e LICENSE && echo It exists 
test -e Makefile && echo It exists 
test -e README.md && echo It exists 
test -e src && echo It exists 
test -e tests && echo It exists 
test -e asdfg && echo It exists 
test -e asdfg || echo It does not exists 
echo
exit
EOF

#test -d flag
bin/rshell << EOF
ls 
test -d bin && echo It exists 
test -d LICENSE && echo It exists 
test -d Makefile && echo It exists 
test -d README.md && echo It exists 
test -d src && echo It exists 
test -d tests && echo It exists 
test -d asdfg && echo It exists 
test -d asdfg || echo It does not exists 
echo
exit
EOF

# [] default flag
bin/rshell << EOF
ls 
[ bin ] && echo It exists 
[ LICENSE ] && echo It exists 
[ Makefile ] && echo It exists 
[ README.md ] && echo It exists 
[ src ] && echo It exists 
[ tests ] && echo It exists 
[ asdfg ] && echo It exists 
[ asdfg ] || echo It does not exists 
echo
exit
EOF

# [] -e flag
bin/rshell << EOF
ls 
[ -e bin ] && echo It exists 
[ -e LICENSE ] && echo It exists 
[ -e Makefile ] && echo It exists 
[ -e README.md ] && echo It exists 
[ -e src ] && echo It exists 
[ -e tests ] && echo It exists 
[ -e asdfg ] && echo It exists 
[ -e asdfg ] || echo It does not exists 
echo
exit
EOF

# [] -f flag
bin/rshell << EOF
ls 
[ -f bin ] && echo It exists 
[ -f LICENSE ] && echo It exists 
[ -f Makefile ] && echo It exists 
[ -f README.md ] && echo It exists 
[ -f src ] && echo It exists 
[ -f tests ] && echo It exists 
[ -f asdfg ] && echo It exists 
[ -f asdfg ] || echo It does not exists 
echo; exit
EOF

# [] -d flag
bin/rshell << EOF
ls 
[ -d bin ] && echo It exists 
[ -d LICENSE ] && echo It exists 
[ -d Makefile ] && echo It exists 
[ -d README.md ] && echo It exists 
[ -d src ] && echo It exists 
[ -d tests ] && echo It exists 
[ -d asdfg ] && echo It exists 
[ -d asdfg ] || echo It does not exists 
echo
exit 
EOF

# [] errors
bin/rshell << EOF
ls 
[  ] && echo It exists 
[  && echo It exists 
[[ -d Makefile ]] && echo It exists 
echo
exit
EOF

#test and [] invalid flags. The assignment only asks us to implement -e, -f, and -d, so other flags are invalid
bin/rshell << EOF
ls
[ -haergr ] || echo Thats not right!  
test -zzzz || echo That is still not right! 
exit
EOF

#test and [] too little arguments
bin/rshell << EOF
ls 
[ ] || echo It failed 
test || echo It failed 
echo
exit
EOF

#test and [] too many arguments
bin/rshell << EOF
ls 
[ bin asd rag ] || echo It failed 
[ -e LICENSE arga ] && echo It exists 
[ -f Makefile argr ] && echo It exists 
[ -d README.md argarg ] && echo It exists 
test -e src sdfg && echo It exists 
test -f tests asfe && echo It exists 
test -d  what is this asdfasdfg && echo It exists 
test vhgvht asdfg || echo It does not exists 
echo; exit
EOF