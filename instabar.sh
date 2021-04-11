#!/usr/bin/env bash

# path:       /usr/bin/instabar
# author:     The-Repo-Club [wayne6324@gmail.com]
# github:     https://github.com/The-Repo-Club/instawm
# date:       2021-04-10 12:34:47.440579

[ "$(pidof -s instawm )" ] || (printf '%s\n' "instawm is not running!" && exit 1) || exit 1

backlight() {
	BACKLIGHT=$(xbacklight -get | cut -d. -f1)
	if [ "$BACKLIGHT" ]; then
		printf '%s\n' "  $BACKLIGHT"
	fi
}

volume() {
  PULSEVOLUME=$( amixer sget Master | grep -e 'Front Left: Playback' | sed 's/[^\[]*\[\([0-9]\{1,3\}%\).*\(on\|off\).*/\2 \1/' | sed 's/off/ M/' | sed 's/on / /' )
	if [ "$PULSEVOLUME" ]; then
		printf '%s\n' " | $PULSEVOLUME"
	else
		ALSAVOLUME=$( amixer sget Master | grep -e 'Mono: Playback' | sed 's/[^\[]*\[\([0-9]\{1,3\}%\).*\(on\|off\).*/\2 \1/' | sed 's/off/ M/' | sed 's/on / /' )
		printf '%s\n' " | $ALSAVOLUME"
	fi
}

wireless() {
	wifi=$(iwgetid -r)
  if [ "$wifi" ]; then
		printf '%s\n' " | 直  $wifi"
	else
		printf '%s\n' ""
	fi
}

layout() {
	klayout=$(setxkbmap -query | awk '/layout/{print $2}')
	if [ "$klayout" ]; then
		printf '%s\n' " |   $klayout"
	fi
}

datetime() {
  DATE=$(date +%R)
	printf '%s\n' "  ${DATE}"
}

while true
do
	xsetroot -name "$(backlight)$(volume)$(wireless)$(layout) | $(datetime)"
	sleep 3
done
