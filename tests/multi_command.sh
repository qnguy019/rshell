#!/bin/sh

echo "$: ls; echo first; ls -a; echo second   ;    mkdir FIRST_DIR"
ls; echo first; ls -a; echo second   ;    mkdir FIRST_DIR

echo "$: ls -lala; rmdir FIRST_DIR;    echo Hello World; echo My name is Quynh Nguyen ;ls"
ls -lala; rmdir FIRST_DIR;    echo Hello World; echo My name is Quynh Nguyen ;ls

echo "$: fasefwe || asdfwe || echo See this || echo Don't see this || ls && echo CS100 is awesome!"
fasefwe || asdfwe || echo See this || echo Dont see this || ls && echo CS100 is awesome!

echo "$: fasefwe || asdfwe && echo Do not see this || echo See this || ls && echo CS100 is awesome!"
fasefwe || asdfwe && echo Do not see this || echo See this || ls && echo CS100 is awesome!

echo "$: kslej ; ls     -a; echo HELLO WORLD || asdfef ||      echo My name is Quynh Nguyen"
  ls cslej ; ls     -a; echo HELLO WORLD || asdfef ||      echo My name is Quynh Nguyen
