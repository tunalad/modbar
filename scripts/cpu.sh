#!/bin/sh

icon=""
[ "$(cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor)" = "powersave" ] && icon=""
echo -n "$icon" && (sensors | awk '/Core 0/ {print $3}')
