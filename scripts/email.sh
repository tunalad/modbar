#!/bin/sh

MAILBOXES="$HOME/.local/share/mail"

[ -d "$MAILBOXES" ] || return

mail_sum=0

for mail in "$MAILBOXES"/*; do
    [ -d "$mail" ] || continue
    count=$(ls "$mail"/INBOX/new 2>/dev/null | wc -l)
    mail_sum=$((mail_sum + count))
done

if [ "$mail_sum" != 0 ]; then
    echo " $mail_sum"
else
    echo ""
fi
