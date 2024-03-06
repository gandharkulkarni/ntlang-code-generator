#!/usr/bin/bash

expr="$1"
name="$2"
a0="$3"
a1="$4"
a2="$5"
a3="$6"
a4="$7"
a5="$8"
a6="$9"
a7="${10}"

./ntlang -e "$expr" -c "$name" > "$name.s"
gcc -o "$name" "$name.s"
./"$name" $a0 $a1 $a2 $a3 $a4 $a5 $a6 $a7
rm "$name"
rm "$name.s"
