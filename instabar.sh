#!/usr/bin/env bash

# path:       /usr/bin/instabar
# author:     The-Repo-Club [wayne6324@gmail.com]
# github:     https://github.com/The-Repo-Club/instawm
# date:       2021-04-10 12:34:47.440579

DaySuffix() {
    if [ "x`date +%-d | cut -c2`x" = "xx" ]
    then
        DayNum=`date +%-d`
    else
        DayNum=`date +%-d | cut -c2`
    fi

    CheckSpecialCase=`date +%-d`
    case $DayNum in
    0 )
      echo "th" ;;
    1 )
      if [ "$CheckSpecialCase" = "11" ]
      then
        echo "th"
      else
        echo "st"
      fi ;;
    2 )
      if [ "$CheckSpecialCase" = "12" ]
      then
        echo "th"
      else
        echo "nd"
      fi ;;
    3 )
      if [ "$CheckSpecialCase" = "13" ]
      then
        echo "th"
      else
        echo "rd"
      fi ;;
    [4-9] )
      echo "th" ;;
    * )
      return 1 ;;
    esac
}

sep() {
	echo " | "
}

ram() {
	mem=$(free -h | awk '/Mem:/ { print $3 }' | cut -f1 -d 'i')
	echo  "$mem"
}

cpu() {
	read -r cpu a b c previdle rest < /proc/stat
	prevtotal=$((a+b+c+previdle))
	sleep 0.5
	read -r cpu a b c idle rest < /proc/stat
	total=$((a+b+c+idle))
	cpu=$((100*( (total-prevtotal) - (idle-previdle) ) / (total-prevtotal) ))
	echo  "$cpu"%
}

network() {
	conntype=$(ip route | awk '/default/ { print substr($5,1,1) }')

	if [ -z "$conntype" ]; then
		echo " No internet"
	elif [ "$conntype" = "e" ]; then
		upspeed=$(numfmt --to=iec-i </sys/class/net/enp12s0/statistics/tx_packets)
		downspeed=$(numfmt --to=iec-i </sys/class/net/enp12s0/statistics/rx_packets)
		echo " $upspeed - $downspeed"
	elif [ "$conntype" = "w" ]; then
		upspeed=$(numfmt --to=iec-i </sys/class/net/wlp0s20f3/statistics/tx_packets)
		downspeed=$(numfmt --to=iec-i </sys/class/net/wlp0s20f3/statistics/rx_packets)
		echo " $upspeed - $downspeed"
	fi
}

volume_pa() {
	muted=$(pactl list sinks | awk '/Mute:/ { print $2 }')
	vol=$(pactl list sinks | grep Volume: | awk 'FNR == 1 { print $5 }' | cut -f1 -d '%')

	if [ "$muted" = "yes" ]; then
		echo " muted"
	else
		if [ "$vol" -ge 90 ]; then
			echo " $vol%"
		elif [ "$vol" -ge 65 ]; then
			echo " $vol%"
		elif [ "$vol" -ge 50 ]; then
			echo " $vol%"
		elif [ "$vol" -ge 25 ]; then
			echo " $vol%"
		elif [ "$vol" -ge 0 ]; then
			echo " $vol%"	
		fi
	fi

}

volume_alsa() {

	mono=$(amixer -M get Master | grep Mono: | awk '{ print $2 }')

	if [ -z "$mono" ]; then
		muted=$(amixer -M get Master | awk 'FNR == 6 { print $7 }' | sed 's/[][]//g')
		vol=$(amixer -M get Master | awk 'FNR == 6 { print $5 }' | sed 's/[][]//g; s/%//g')
	else
		muted=$(amixer -M get Master | awk 'FNR == 5 { print $6 }' | sed 's/[][]//g')
		vol=$(amixer -M get Master | awk 'FNR == 5 { print $4 }' | sed 's/[][]//g; s/%//g')
	fi

	if [ "$muted" = "yes" ]; then
		echo " muted"
	else
		if [ "$vol" -ge 90 ]; then
			echo " $vol%"
		elif [ "$vol" -ge 65 ]; then
			echo " $vol%"
		elif [ "$vol" -ge 50 ]; then
			echo " $vol%"
		elif [ "$vol" -ge 25 ]; then
			echo " $vol%"
		elif [ "$vol" -ge 0 ]; then
			echo " $vol%"	
		fi
	fi
}

updates() {
	updates=$(checkupdates+aur | wc -l)
	if [ "$updates" -eq "0" ]; then
		echo " No Updates"
	elif [ "$updates" -ge "1" ]; then
		echo " $updates Update"
	else
		echo " $updates Updates"
	fi
}

clock() {
	date=$(date +"%-d`DaySuffix` %b %Y")
	time=$(date +"%I:%M %P")

	echo " $date  $time"
}

main() {
	while true; do
		instawm -s "$(ram)$(sep)$(cpu)$(sep)$(updates)$(sep)$(network)$(sep)$(volume_pa)$(sep)$(clock)"
		sleep 5s
	done 
}

main