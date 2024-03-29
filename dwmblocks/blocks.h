//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/

	{ "   ", "echo $(~/.scripts/status-wifi.sh) ",	5,	0 },

	{ " ", "uptime  | awk '{printf \"%.2f %.2f %.2f\", $(NF-2), $(NF-1), $(NF)}'",	5,	0 },

	{ "﬙ ", "free --mega -h | awk 'NR==2{printf \"%s/%s\", $3,$2}'", 5,	0 },

	{ " ", "echo \"$(pacman -Qu | wc -l)/$(pacman -Q | wc -l)\"", 3600, 30},

	{ "", "echo $(~/.scripts/status-volume.sh)", 0, 10},

	{ "", "echo $(~/.scripts/status-battery.sh)", 5, 20},

	{ "", "date +'%A, %B %d - %H:%M:%S'",					1,		0 },

	{ "", "echo $(whoami)@$(uname -n)' '",					0,		0 },

};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
