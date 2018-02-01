#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "cup.h"
#define	SEGY_NKEYS	71
/*********************************************************/
/* su segy trace and headers defination and offset begin */
/*********************************************************/
/* TYPEDEFS */
typedef struct {	/* segy - trace identification header */

	int tracl;	/* Trace sequence number within line
			   --numbers continue to increase if the
			   same line continues across multiple
			   SEG Y files.
			 */

	int tracr;	/* Trace sequence number within SEG Y file
			   ---each file starts with trace sequence
			   one
			 */

	int fldr;	/* Original field record number */

	int tracf;	/* Trace number within original field record */

	int ep;		/* energy source point number
			   ---Used when more than one record occurs
			   at the same effective surface location.
			 */

	int cdp;	/* Ensemble number (i.e. CDP, CMP, CRP,...) */

	int cdpt;	/* trace number within the ensemble
			   ---each ensemble starts with trace number one.
			 */

	short trid;	/* trace identification code:
			-1 = Other
		         0 = Unknown
			 1 = Seismic data
			 2 = Dead
			 3 = Dummy
			 4 = Time break
			 5 = Uphole
			 6 = Sweep
			 7 = Timing
			 8 = Water break
			 9 = Near-field gun signature
			10 = Far-field gun signature
			11 = Seismic pressure sensor
			12 = Multicomponent seismic sensor
				- Vertical component
			13 = Multicomponent seismic sensor
				- Cross-line component 
			14 = Multicomponent seismic sensor
				- in-line component 
			15 = Rotated multicomponent seismic sensor
				- Vertical component
			16 = Rotated multicomponent seismic sensor
				- Transverse component
			17 = Rotated multicomponent seismic sensor
				- Radial component
			18 = Vibrator reaction mass
			19 = Vibrator baseplate
			20 = Vibrator estimated ground force
			21 = Vibrator reference
			22 = Time-velocity pairs
			23 ... N = optional use 
				(maximum N = 32,767)

			Following are CWP id flags:

			109 = autocorrelation
			110 = Fourier transformed - no packing
			     xr[0],xi[0], ..., xr[N-1],xi[N-1]
			111 = Fourier transformed - unpacked Nyquist
			     xr[0],xi[0],...,xr[N/2],xi[N/2]
			112 = Fourier transformed - packed Nyquist
	 		     even N:
			     xr[0],xr[N/2],xr[1],xi[1], ...,
				xr[N/2 -1],xi[N/2 -1]
				(note the exceptional second entry)
			     odd N:
			     xr[0],xr[(N-1)/2],xr[1],xi[1], ...,
				xr[(N-1)/2 -1],xi[(N-1)/2 -1],xi[(N-1)/2]
				(note the exceptional second & last entries)
			113 = Complex signal in the time domain
			     xr[0],xi[0], ..., xr[N-1],xi[N-1]
			114 = Fourier transformed - amplitude/phase
			     a[0],p[0], ..., a[N-1],p[N-1]
			115 = Complex time signal - amplitude/phase
			     a[0],p[0], ..., a[N-1],p[N-1]
			116 = Real part of complex trace from 0 to Nyquist
			117 = Imag part of complex trace from 0 to Nyquist
			118 = Amplitude of complex trace from 0 to Nyquist
			119 = Phase of complex trace from 0 to Nyquist
			121 = Wavenumber time domain (k-t)
			122 = Wavenumber frequency (k-omega)
			123 = Envelope of the complex time trace
			124 = Phase of the complex time trace
			125 = Frequency of the complex time trace
			130 = Depth-Range (z-x) traces
			143 = Seismic Data, Vertical Component 
			144 = Seismic Data, Horizontal Component 1 
			145 = Seismic Data, Horizontal Component 2 
			146 = Seismic Data, Radial Component
			147 = Seismic Data, Transverse Component  
			201 = Seismic data packed to bytes (by supack1)
			202 = Seismic data packed to 2 bytes (by supack2)
			*/

	short nvs;	/* Number of vertically summed traces yielding
			   this trace. (1 is one trace, 
			   2 is two summed traces, etc.)
			 */

	short nhs;	/* Number of horizontally summed traces yielding
			   this trace. (1 is one trace
			   2 is two summed traces, etc.)
			 */

	short duse;	/* Data use:
				1 = Production
				2 = Test
			 */

	int offset;	/* Distance from the center of the source point 
			   to the center of the receiver group 
			   (negative if opposite to direction in which 
			   the line was shot).
			 */

	int gelev;	/* Receiver group elevation from sea level
			   (all elevations above the Vertical datum are 
			   positive and below are negative).
			 */

	int selev;	/* Surface elevation at source. */

	int sdepth;	/* Source depth below surface (a positive number). */

	int gdel;	/* Datum elevation at receiver group. */

	int sdel;	/* Datum elevation at source. */

	int swdep;	/* Water depth at source. */  

	int gwdep;	/* Water depth at receiver group. */

	short scalel;	/* Scalar to be applied to the previous 7 entries
			   to give the real value. 
			   Scalar = 1, +10, +100, +1000, +10000.
			   If positive, scalar is used as a multiplier,
			   if negative, scalar is used as a divisor.
			 */

	short scalco;	/* Scalar to be applied to the next 4 entries
			   to give the real value. 
			   Scalar = 1, +10, +100, +1000, +10000.
			   If positive, scalar is used as a multiplier,
			   if negative, scalar is used as a divisor.
			 */

	int  sx;	/* Source coordinate - X */

	int  sy;	/* Source coordinate - Y */

	int  gx;	/* Group coordinate - X */

	int  gy;	/* Group coordinate - Y */

	short counit;	/* Coordinate units: (for previous 4 entries and
				for the 7 entries before scalel)
			   1 = Length (meters or feet)
			   2 = Seconds of arc
			   3 = Decimal degrees
			   4 = Degrees, minutes, seconds (DMS)

			In case 2, the X values are longitude and 
			the Y values are latitude, a positive value designates
			the number of seconds east of Greenwich
				or north of the equator

			In case 4, to encode +-DDDMMSS
			counit = +-DDD*10^4 + MM*10^2 + SS,
			with scalco = 1. To encode +-DDDMMSS.ss
			counit = +-DDD*10^6 + MM*10^4 + SS*10^2 
			with scalco = -100.
			*/

	short wevel;	/* Weathering velocity. */

	short swevel;	/* Subweathering velocity. */

	short sut;	/* Uphole time at source in milliseconds. */

	short gut;	/* Uphole time at receiver group in milliseconds. */

	short sstat;	/* Source static correction in milliseconds. */

	short gstat;	/* Group static correction  in milliseconds.*/

	short tstat;	/* Total static applied  in milliseconds.
			   (Zero if no static has been applied.)
			*/

	short laga;	/* Lag time A, time in ms between end of 240-
			   byte trace identification header and time
			   break, positive if time break occurs after
			   end of header, time break is defined as
			   the initiation pulse which maybe recorded
			   on an auxiliary trace or as otherwise
			   specified by the recording system */

	short lagb;	/* lag time B, time in ms between the time break
			   and the initiation time of the energy source,
			   may be positive or negative */

	short delrt;	/* delay recording time, time in ms between
			   initiation time of energy source and time
			   when recording of data samples begins
			   (for deep water work if recording does not
			   start at zero time) */

	short muts;	/* mute time--start */

	short mute;	/* mute time--end */

	unsigned short ns;	/* number of samples in this trace */

	unsigned short dt;	/* sample interval; in micro-seconds */

	short gain;	/* gain type of field instruments code:
				1 = fixed
				2 = binary
				3 = floating point
				4 ---- N = optional use */

	short igc;	/* instrument gain constant */

	short igi;	/* instrument early or initial gain */

	short corr;	/* correlated:
				1 = no
				2 = yes */

	short sfs;	/* sweep frequency at start */  // use as time scale

	short sfe;	/* sweep frequency at end */

	short slen;	/* sweep length in ms */

	short styp;	/* sweep type code:
				1 = linear
				2 = cos-squared
				3 = other */

	short stas;	/* sweep trace length at start in ms */

	short stae;	/* sweep trace length at end in ms */

	short tatyp;	/* taper type: 1=linear, 2=cos^2, 3=other */

	short afilf;	/* alias filter frequency if used */

	short afils;	/* alias filter slope */

	short nofilf;	/* notch filter frequency if used */

	short nofils;	/* notch filter slope */

	short lcf;	/* low cut frequency if used */

	short hcf;	/* high cut frequncy if used */

	short lcs;	/* low cut slope */

	short hcs;	/* high cut slope */

	short year;	/* year data recorded */

	short day;	/* day of year */

	short hour;	/* hour of day (24 hour clock) */

	short minute;	/* minute of hour */

	short sec;	/* second of minute */

	short timbas;	/* time basis code:
				1 = local
				2 = GMT
				3 = other */

	short trwf;	/* trace weighting factor, defined as 1/2^N
			   volts for the least sigificant bit */

	short grnors;	/* geophone group number of roll switch
			   position one */

	short grnofr;	/* geophone group number of trace one within
			   original field record */

	short grnlof;	/* geophone group number of last trace within
			   original field record */

	short gaps;	/* gap size (total number of groups dropped) */

	short otrav;	/* overtravel taper code:
				1 = down (or behind)
				2 = up (or ahead) */

#ifdef UNOCAL_SEGY_H  /* begin Unocal SU segy.h differences */


	/* cwp local assignments */
	float d1;	/* sample spacing for non-seismic data */

	float f1;	/* first sample location for non-seismic data */

	float d2;	/* sample spacing between traces */

	float f2;	/* first trace location */

	float ungpow;	/* negative of power used for dynamic
			   range compression */

	float unscale;	/* reciprocal of scaling factor to normalize
			   range */

	short mark;	/* mark selected traces */

	/* UNOCAL local assignments */ 
	short mutb;	/* mute time at bottom (start time)  */
			/* bottom mute ends at last sample   */
	float dz;	/* depth sampling interval in (m or ft)  */
			/* if =0.0, input are time samples       */

	float fz;	/* depth of first sample in (m or ft)  */

	short n2;	/* number of traces per cdp or per shot */

        short shortpad; /* alignment padding */

	int ntr; 	/* number of traces */

	/* UNOCAL local assignments end */ 

	short unass[8];	/* unassigned */

#else

	/* cwp local assignments */
	float d1;	/* sample spacing for non-seismic data */

	float f1;	/* first sample location for non-seismic data */

	float d2;	/* sample spacing between traces */

	float f2;	/* first trace location */

	float ungpow;	/* negative of power used for dynamic
			   range compression */

	float unscale;	/* reciprocal of scaling factor to normalize
			   range */

	int ntr; 	/* number of traces */

	short mark;	/* mark selected traces */

        short shortpad; /* alignment padding */


	short unass[14];	/* unassigned--NOTE: last entry causes 
			   a break in the word alignment, if we REALLY
			   want to maintain 240 bytes, the following
			   entry should be an odd number of short/UINT2
			   OR do the insertion above the "mark" keyword
			   entry */
#endif

	float  data[32768];

} segy;

static struct {
	char *key;	char *type;	int offs;
} hdr[] = {
	{   "tracl",		"i",		0},
	{   "tracr",		"i",		4},
	{    "fldr",		"i",		8},
	{   "tracf",		"i",		12},
	{      "ep",		"i",		16},
	{     "cdp",		"i",		20},
	{    "cdpt",		"i",		24},
	{    "trid",		"h",		28},
	{     "nvs",		"h",		30},
	{     "nhs",		"h",		32},
	{    "duse",		"h",		34},
	{  "offset",		"i",		36},
	{   "gelev",		"i",		40},
	{   "selev",		"i",		44},
	{  "sdepth",		"i",		48},
	{    "gdel",		"i",		52},
	{    "sdel",		"i",		56},
	{   "swdep",		"i",		60},
	{   "gwdep",		"i",		64},
	{  "scalel",		"h",		68},
	{  "scalco",		"h",		70},
	{      "sx",		"i",		72},
	{      "sy",		"i",		76},
	{      "gx",		"i",		80},
	{      "gy",		"i",		84},
	{  "counit",		"h",		88},
	{   "wevel",		"h",		90},
	{  "swevel",		"h",		92},
	{     "sut",		"h",		94},
	{     "gut",		"h",		96},
	{   "sstat",		"h",		98},
	{   "gstat",		"h",		100},
	{   "tstat",		"h",		102},
	{    "laga",		"h",		104},
	{    "lagb",		"h",		106},
	{   "delrt",		"h",		108},
	{    "muts",		"h",		110},
	{    "mute",		"h",		112},
	{      "ns",		"u",		114},
	{      "dt",		"u",		116},
	{    "gain",		"h",		118},
	{     "igc",		"h",		120},
	{     "igi",		"h",		122},
	{    "corr",		"h",		124},
	{     "sfs",		"h",		126},
	{     "sfe",		"h",		128},
	{    "slen",		"h",		130},
	{    "styp",		"h",		132},
	{    "stas",		"h",		134},
	{    "stae",		"h",		136},
	{   "tatyp",		"h",		138},
	{   "afilf",		"h",		140},
	{   "afils",		"h",		142},
	{  "nofilf",		"h",		144},
	{  "nofils",		"h",		146},
	{     "lcf",		"h",		148},
	{     "hcf",		"h",		150},
	{     "lcs",		"h",		152},
	{     "hcs",		"h",		154},
	{    "year",		"h",		156},
	{     "day",		"h",		158},
	{    "hour",		"h",		160},
	{  "minute",		"h",		162},
	{     "sec",		"h",		164},
	{  "timbas",		"h",		166},
	{    "trwf",		"h",		168},
	{  "grnors",		"h",		170},
	{  "grnofr",		"h",		172},
	{  "grnlof",		"h",		174},
	{    "gaps",		"h",		176},
	{   "otrav",		"h",		178},
	{      "d1",		"f",		180},
	{      "f1",		"f",		184},
	{      "d2",		"f",		188},
	{      "f2",		"f",		192},
	{  "ungpow",		"f",		196},
	{ "unscale",		"f",		200},
	{     "ntr",		"i",		204},
	{    "mark",		"h",		208},
	{"shortpad",		"h",		210},
};

/*------------------------------------------------------------*/
/* function defined                                           */ 
/*------------------------------------------------------------*/
void ReadDat_2d(FILE *fp, float **data,int nz, int nx);
void WriteDat_1d(FILE *fp, float *data,int nz, int nx);
void WriteDat_2d(FILE *fp, float **data,int nz, int nx);

/*  PC byte swapping -- su swapbyte */
void swap_short_2(short *tni2);
void swap_u_short_2(unsigned short *tni2);
void swap_int_4(int *tni4);
void swap_u_int_4(unsigned int *tni4);
void swap_long_4(long *tni4);
void swap_u_long_4(unsigned long *tni4);
void swap_float_4(float *tnf4);
void swap_double_8(double *tndd8);

FILE *efopen(const char *file, const char *mode);