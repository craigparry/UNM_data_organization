#!/bin/bash

gcc -ansi -Wall -pedantic -g qsort.c

S1=`./a.out < wordlist1.txt`
if [ "$S1" != "Burris's
Gretzky
Iblis
McKinley's
babbling
barman
breakfast
departed
fast's
gloated
gruffer
languages
maharanees
mill's
postulated
snarl
tibiae
touted
trochee's
upsurging" ]; then
   echo $S1
fi
S1=`./a.out -f < wordlist1.txt`
if [ "$S1" != "babbling
barman
breakfast
Burris's
departed
fast's
gloated
Gretzky
gruffer
Iblis
languages
maharanees
McKinley's
mill's
postulated
snarl
tibiae
touted
trochee's
upsurging" ]; then
   echo $S1
fi
S1=`./a.out -r < wordlist1.txt`
if [ "$S1" != "upsurging
trochee's
touted
tibiae
snarl
postulated
mill's
maharanees
languages
gruffer
gloated
fast's
departed
breakfast
barman
babbling
McKinley's
Iblis
Gretzky
Burris's" ]; then
   echo $S1
fi
S1=`./a.out -f -r < wordlist1.txt`
if [ "$S1" != "upsurging
trochee's
touted
tibiae
snarl
postulated
mill's
McKinley's
maharanees
languages
Iblis
gruffer
Gretzky
gloated
fast's
departed
Burris's
breakfast
barman
babbling" ]; then
   echo $S1
fi
S1=`./a.out -n < numlist1.txt`
if [ "$S1" != "30523729
230373883
275888990
323698337
328247899
343757994
354345288
430936682
521204161
536605338
586531691
589970029
601698550
671631511
677864486
701108971
701273338
717041156
970757412
972049932" ]; then
   echo $S1
fi
S1=`./a.out -n -r < numlist1.txt`
if [ "$S1" != "972049932
970757412
717041156
701273338
701108971
677864486
671631511
601698550
589970029
586531691
536605338
521204161
430936682
354345288
343757994
328247899
323698337
275888990
230373883
30523729" ]; then
   echo $S1
fi
S1=`./a.out -n -r -f < numlist1.txt`
if [ "$S1" != "Error: Too many arguments" ]; then
   echo $S1
fi
S1=`./a.out -n -f < numlist1.txt`
if [ "$S1" != "Incompatible flags" ]; then
   echo $S1
fi