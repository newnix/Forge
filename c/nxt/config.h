/* 
 * Configuration file for nxt
 */

/* The fontconfig truetype/opentype configuration string used */
static const char *font = "Termsynu:style=Regular:pixelsize=9:autohint=true:antialias=true:minspace=true";
/* The shell executed by default if *utmp is NULL */
static const char *shell = "/bin/sh";
/* What gets launched by default */
static const char *utmp = "/usr/local/bin/tmux";
/* The value of the $TERM environmental variable */
static const char *term = "xterm-256color";
/* Terminal configuration flags */
static const char *stty = "";

/* Define the colorscheme */
static const char *colorscheme[] = { 
	/* 8 "normal" colors */
	"0x000000", /* [000] */
	"0x000000", /* [001] */
	"0x000000", /* [002] */
	"0x000000", /* [003] */
	"0x000000", /* [004] */
	"0x000000", /* [005] */
	"0x000000", /* [006] */
	"0x000000", /* [007] */

	/* 8 "bright" colors */
	"0x000000", /* [008] */
	"0x000000", /* [009] */
	"0x000000", /* [010] */
	"0x000000", /* [011] */
	"0x000000", /* [012] */
	"0x000000", /* [013] */
	"0x000000", /* [014] */
	"0x000000", /* [015] */

	/*
	[255] = 0, is this even necessary?
	*/

	/* Additional colors for extra things */
	"0x000000", /* [016] */
	"0x000000", /* [017] */
	"0x000000", /* [018] */
	"0x000000", /* [019] */
};

static const char *ascii = 
	" !@#$%^&*()/\\-.,'<>[]{}|=-+~`\'\""
	"abcdefghijklmnopqrstuvwxyz"
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"0123456789";
