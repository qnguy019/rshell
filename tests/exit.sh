#!/bin/sh

echo 'ls -l; exit' | ../bin/rshell
echo 'ls -a || exit && echo hi || exit||exit && echo This is the end && exit' | ../bin/rshell
echo 'ls -l && exit' | ../bin/rshell
echo 'ls -a; echo Hello && asdfse || exit' | ../bin/rshell
echo 'exit; ls; git status; cal' | ../bin/rshell
echo 'ls -a; cal && aadfew && exit || echo Hello && exit' | ../bin/rshell
echo 'ls exit; echo exit; mkdir EXIT; ls && rmdir EXIT || exit || exit ; echo It still did not exit but now it will && exit' | ../bin/rshell
echo 'echo hello || exit || exit; echo It did not exit yet || exit && echo now it will exit; exit' | ../bin/rshell
echo '       exit' | ../bin/rshell
echo 'exit' | ../bin/rshell
echo 'ls -l; echo hello &&exit||echo world' | ../bin/rshell
echo 'ls -a; echo hello ||exit; echo world &&   exit' | ../bin/rshell

