#!/bin/sh

# newsboat -x print-unread is too slow
# so we're taking count directly from the cache file
CACHE_PATH="$HOME/.local/share/newsboat/cache.db"
[ -f $CACHE_PATH ] || return

articles=$(sqlite3 $CACHE_PATH "SELECT COUNT(*) FROM rss_item WHERE unread = TRUE")

if [ "$articles" -gt "0" ]; then
    echo -n " $articles"
fi
