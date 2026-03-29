#!/bin/sh

vol=$(volumectl.sh)

if echo "$vol" | grep -q "MUTE"; then
    echo "$vol"
    return
fi

vol_num=$(echo "$vol" | sed 's/%$//')

if command -v amixer >/dev/null 2>&1 && amixer -c 0 contents 2>/dev/null | grep -A2 "name='Headphone Jack'" | grep -q "values=on"; then
    icon="🎧"
elif [ "$vol_num" -gt 70 ]; then
    icon="🔊"
elif [ "$vol_num" -lt 30 ]; then
    icon="🔈"
else
    icon="🔉"
fi

echo "$icon$vol"
