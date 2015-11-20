#!/bin/sh
#test default flag
echo 'ls; exit' | ../bin/rshell
echo 'test bin && echo It exists; exit' | ../bin/rshell
echo 'test LISCENSE && echo It exists; exit' | ../bin/rshell
echo 'test Makefile && echo It exists; exit' | ../bin/rshell
echo 'test README.md && echo It exists; exit' | ../bin/rshell
echo 'test src && echo It exists; exit' | ../bin/rshell
echo 'test tests && echo It exists; exit' | ../bin/rshell
echo 'test asdfg && echo It exists; exit' | ../bin/rshell
echo 'test asdfg || echo It does not exists; exit' | ../bin/rshell

#test -e flag
echo 'ls; exit' | ../bin/rshell
echo 'test -e bin && echo It exists; exit' | ../bin/rshell
echo 'test -e LISCENSE && echo It exists; exit' | ../bin/rshell
echo 'test -e Makefile && echo It exists; exit' | ../bin/rshell
echo 'test -e README.md && echo It exists; exit' | ../bin/rshell
echo 'test -e src && echo It exists; exit' | ../bin/rshell
echo 'test -e tests && echo It exists; exit' | ../bin/rshell
echo 'test -e asdfg && echo It exists; exit' | ../bin/rshell
echo 'test -e asdfg || echo It does not exists; exit' | ../bin/rshell

#test -d flag
echo 'ls; exit' | ../bin/rshell
echo 'test -d bin && echo It exists; exit' | ../bin/rshell
echo 'test -d LISCENSE && echo It exists; exit' | ../bin/rshell
echo 'test -d Makefile && echo It exists; exit' | ../bin/rshell
echo 'test -d README.md && echo It exists; exit' | ../bin/rshell
echo 'test -d src && echo It exists; exit' | ../bin/rshell
echo 'test -d tests && echo It exists; exit' | ../bin/rshell
echo 'test -d asdfg && echo It exists; exit' | ../bin/rshell
echo 'test -d asdfg || echo It does not exists; exit' | ../bin/rshell

# [] default flag
echo 'ls; exit' | ../bin/rshell
echo '[ bin ] && echo It exists; exit' | ../bin/rshell
echo '[ LISCENSE ] && echo It exists; exit' | ../bin/rshell
echo '[ Makefile ] && echo It exists; exit' | ../bin/rshell
echo '[ README.md ] && echo It exists; exit' | ../bin/rshell
echo '[ src ] && echo It exists; exit' | ../bin/rshell
echo '[ tests ] && echo It exists; exit' | ../bin/rshell
echo '[ asdfg ] && echo It exists; exit' | ../bin/rshell
echo '[ asdfg ] || echo It does not exists; exit' | ../bin/rshell

# [] -e flag
echo 'ls; exit' | ../bin/rshell
echo '[ -e bin ] && echo It exists; exit' | ../bin/rshell
echo '[ -e LISCENSE ] && echo It exists; exit' | ../bin/rshell
echo '[ -e Makefile ] && echo It exists; exit' | ../bin/rshell
echo '[ -e README.md ] && echo It exists; exit' | ../bin/rshell
echo '[ -e src ] && echo It exists; exit' | ../bin/rshell
echo '[ -e tests ] && echo It exists; exit' | ../bin/rshell
echo '[ -e asdfg ] && echo It exists; exit' | ../bin/rshell
echo '[ -e asdfg ] || echo It does not exists; exit' | ../bin/rshell

# [] -f flag
echo 'ls; exit' | ../bin/rshell
echo '[ -f bin ] && echo It exists; exit' | ../bin/rshell
echo '[ -f LISCENSE ] && echo It exists; exit' | ../bin/rshell
echo '[ -f Makefile ] && echo It exists; exit' | ../bin/rshell
echo '[ -f README.md ] && echo It exists; exit' | ../bin/rshell
echo '[ -f src ] && echo It exists; exit' | ../bin/rshell
echo '[ -f tests ] && echo It exists; exit' | ../bin/rshell
echo '[ -f asdfg ] && echo It exists; exit' | ../bin/rshell
echo '[ -f asdfg ] || echo It does not exists; exit' | ../bin/rshell

# [] -d flag
echo 'ls; exit' | ../bin/rshell
echo '[ -d bin ] && echo It exists; exit' | ../bin/rshell
echo '[ -d LISCENSE ] && echo It exists; exit' | ../bin/rshell
echo '[ -d Makefile ] && echo It exists; exit' | ../bin/rshell
echo '[ -d README.md ] && echo It exists; exit' | ../bin/rshell
echo '[ -d src ] && echo It exists; exit' | ../bin/rshell
echo '[ -d tests ] && echo It exists; exit' | ../bin/rshell
echo '[ -d asdfg ] && echo It exists; exit' | ../bin/rshell
echo '[ -d asdfg ] || echo It does not exists; exit' | ../bin/rshell

# [] errors
echo 'ls; exit' | ../bin/rshell
echo '[  ] && echo It exists; exit' | ../bin/rshell
echo '[  && echo It exists; exit' | ../bin/rshell
echo '[[ -d Makefile ]] && echo It exists; exit' | ../bin/rshell

#test and [] invalid flags. The assignment only asks us to implement -e, -f, and -d, so other flags are invalid
echo '[ -haergr ] || echo That's not right! ;exit' | ../bin/rshell
echo 'test -zzzz || echo That is still not right!; exit' | ../bin/rshell

#test and [] too little arguments
echo 'ls; exit' | ../bin/rshell
echo '[ ] && echo It exists; exit' | ../bin/rshell
echo 'test && echo It exists; exit' | ../bin/rshell

#test and [] too many arguments
echo 'ls; exit' | ../bin/rshell
echo '[ bin asd rag] && echo It exists; exit' | ../bin/rshell
echo '[ -e LISCENSE arga] && echo It exists; exit' | ../bin/rshell
echo '[ -f Makefile argr ] && echo It exists; exit' | ../bin/rshell
echo '[ -d README.md argarg ] && echo It exists; exit' | ../bin/rshell
echo 'test -e src sdfg && echo It exists; exit' | ../bin/rshell
echo 'test -f tests asfe && echo It exists; exit' | ../bin/rshell
echo 'test -d  what is this asdfasdfg && echo It exists; exit' | ../bin/rshell
echo 'test vhgvht asdfg || echo It does not exists; exit' | ../bin/rshell