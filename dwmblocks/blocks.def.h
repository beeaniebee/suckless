//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/

	{ "   ", "echo $(/etc/scripts/status-wifi.sh) ",	5,	0 },

	{ " ", "uptime  | awk '{printf \"%.2f %.2f %.2f\", $(NF-2), $(NF-1), $(NF)}'",	5,	0 },

	{ "﬙ ", "free --mega -h | awk 'NR==2{printf \"%s/%s\", $3,$2}'", 5,	0 },

	{ "", "echo $(/etc/scripts/status-volume.sh)", 0, 10},

	/*{ " Volume: ", "echo $(pulsemixer --get-volume | cut -d ' ' -f 1)$(if [[ $(pulsemixer --get-mute) == 1 ]] ; then echo '!'; fi)", 1, 10 },*/

	{ "", "echo $(/etc/scripts/status-battery.sh)", 5, 0},

	/*{ "Battery: ", "echo $(cat /sys/class/power_supply/BAT0/capacity) '('$(cat /sys/class/power_supply/BAT0/status)')'",	1,		0 },*/

	{ "", "date +'%A, %B %d - %H:%M:%S'",					1,		0 },

	{ "", "echo $(whoami)@$(uname -n)' '",					0,		0 },

};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;