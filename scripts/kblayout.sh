#!/bin/sh

lv=$(setxkbmap -query | grep -e "layout" | awk '{print $2}')$(setxkbmap -query | grep -e "variant" | awk '{print $2}')

case "$lv" in
"rslatin") echo " SRB" ;;
"us") echo " EN-US" ;;
"rs") echo " СРБ" ;;
*) echo " ERROR" ;;
esac
