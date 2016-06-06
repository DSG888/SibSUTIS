#ifndef TheMyString
#define TheMyString

int slen(char *s);
int schr(char s[], char c);
int stok(char str[], char delim, char *ptr[]);
int suntok(char *str, char delim, char *ptr[80],int cnt);
void scpy(char m[], char y[]);
int scmp(char m[], char n[]);
int myisspace(int c);
int myisdigit(int c);
int myatoi(char *string);

#endif

/*
	#ASCII Codes Table: Standard characters
DEC	CHR		DEC	CHR		DEC	CHR		DEC	CHR		DEC	CHR		DEC	CHR		DEC	CHR
----------|-----------|-----------|-----------|-----------|-----------|---------
0	NUL		20	DC4		40	(		60	<		80	P		100	d		120	x
1	SOH		21	NAK		41	)		61	=		81	Q		101	e		121	y
2	STX		22	SYN		42	*		62	>		82	R		102	f		122	z
3	ETX		23	ETB		43	+		63	?		83	S		103	g		123	{
4	EOT		24	CAN		44	,		64	@		84	T		104	h		124	|
5	ENQ		25	EM		45	-		65	A		85	U		105	i		125	}
6	ACK		26	SUB		46	.		66	B		86	V		106	j		126	~
7	BEL		27	ESC		47	/		67	C		87	W		107	k			
8	BS		28	FS		48	0		68	D		88	X		108	l			
9	TAB		29	GS		49	1		69	E		89	Y		109	m			
10	LF		30	RS		50	2		70	F		90	Z		110	n			
11	VT		31	US		51	3		71	G		91	[		111	o			
12	FF		32	(space)	52	4		72	H		92	\		112	p			
13	CR		33	!		53	5		73	I		93	]		113	q			
14	SO		34	"		54	6		74	J		94	^		114	r			
15	SI		35	#		55	7		75	K		95	_		115	s			
16	DLE		36	$		56	8		76	L		96	`		116	t			
17	DC1		37	%		57	9		77	M		97	a		117	u			
18	DC2		38	&		58	:		78	N		98	b		118	v			
19	DC3		39	'		59	;		79	O		99	c		119	w			
*/

/*
void OUUT(char *pat, int size)
{
	int i;
	for (i=0; i < size; i++)
	{
		printf("[%c]", pat[i]);
	}
	printf("\n");
}*/


/*
	clWhite = "\033[38;05;15m";		clBoldWhite = "\033[01;38;05;15m";
	clGreen = "\033[38;05;46m";		clBoldGreen = "\033[01;38;05;46m";
	clBlue = "\033[38;05;21m";		clBoldBlue = "\033[01;38;05;21m";
	clYellow = "\033[38;05;226m";	clBoldYellow = "\033[01;38;05;226m";
	clBlack = "\033[38;05;232m";	clBoldBlack = "\033[01;38;05;232m";
*/
