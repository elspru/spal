#!/bin/bash
#
#BASE=$(pwd)
#function file_compile {
#  stem=$1
#  echo "$PWD/$stem"
#  source_filename=$stem.tex
#  file_verification_text=$(cat "$source_filename.sha1")
#  verification_text=$(sha1sum "$source_filename")
#    echo "'$verification_text'"
#    echo "'$file_verification_text'"
#  if [[ ! "$verification_text" == "$file_verification_text" ]]
#  then
#    echo "'$verification_text'"
#    echo "'$file_verification_text'"
#    echo file verification fail
#    lualatex $stem
#    biber $stem
#    htlatex "$stem.tex" "$BASE/web"  &
#    lualatex $stem  &
#    wait;
#    ebook-convert "$stem.html" "$stem.epub"
#   # "$BASE/clean.sh"
#    echo "$verification_text" > "$source_filename.sha1";
#    echo "$source_filename"
#  else 
#    echo "'$verification_text'"
#    echo "'$file_verification_text'"
#    echo file verification perfect
#  fi
#}
#
#file_compile green_buddhism

NAME=spal
./clean.sh
lualatex $NAME
biber $NAME
lualatex $NAME
#htlatex $NAME "web,next"
./clean.sh

echo "done"
