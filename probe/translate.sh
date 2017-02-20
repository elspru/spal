#!/bin/bash
# if locale doesn't exist add it
# echo pya.UTF8 >> /var/lib/locales/supported.d/local

if [ ! -d po/ ]; then
  mkdir po/
fi

xgettext  -d pyac -o po/"$1".pot -L C  -k_ -s "${1}.c" 

for language_code in zh en hi ru
do
if [ ! -d po/"$language_code" ]; then
  mkdir po/"$language_code"
fi
cp  po/"$1".pot   po/"$language_code"/"$1".po
# translate to msgid's in the po file
done
