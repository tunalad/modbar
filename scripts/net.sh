#!/bin/sh

# nerd fonts
WIFI_FULL="󰤨"
WIFI_HIGH="󰤥"
WIFI_MED="󰤢"
WIFI_LOW="󰤟"
WIFI_NONE="󰤮"
ETH_UP="󰈁"
ETH_DOWN="󰈂"

# braille
#WIFI_FULL="[⢀⣠⣴⣾]"
#WIFI_HIGH="[⢀⣠⣴ ]"
#WIFI_MED="[⢀⣠  ]"
#WIFI_LOW="[⢀   ]"
#WIFI_NONE="[    ]"
#ETH_UP="[⠶⠶⠶E]"
#ETH_DOWN="[⠶  X]"

detect_wifi() {
    for iface in /sys/class/net/wl*; do
        [ -d "$iface" ] && basename "$iface" && return
    done
    echo ""
}

detect_eth() {
    for iface in /sys/class/net/en* /sys/class/net/eth*; do
        [ -d "$iface" ] && basename "$iface" && return
    done
    echo ""
}

# ------------------------------------------------------

eth_iface=$(detect_eth)
wifi_iface=$(detect_wifi)

if [ -n "$eth_iface" ]; then
    eth_state=$(cat /sys/class/net/"$eth_iface"/operstate 2>/dev/null)
fi

if [ -n "$wifi_iface" ]; then
    wifi_signal=$(iw dev "$wifi_iface" link 2>/dev/null | grep -i "signal" | awk '{print $2}' | tr -d ' dBm')
fi

# priority: eth up > wifi
if [ "$eth_state" = "up" ]; then
    echo "$ETH_UP"
    return
fi

if [ -n "$wifi_signal" ]; then
    if [ "$wifi_signal" -ge -50 ]; then
        echo "$WIFI_FULL"
    elif [ "$wifi_signal" -ge -65 ]; then
        echo "$WIFI_HIGH"
    elif [ "$wifi_signal" -ge -80 ]; then
        echo "$WIFI_MED"
    else
        echo "$WIFI_LOW"
    fi
    return
fi

echo "$ETH_DOWN"
