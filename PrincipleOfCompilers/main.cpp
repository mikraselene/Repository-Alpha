enum
{
	BLANK = 1,	 // 000001
	NEWLINE = 2, // 000010
	LETTER = 4,	 // 000100
	DIGIT = 8,	 // 001000
	HEX = 16,	 // 010000
	OTHER = 32,	 // 100000
};

static unsigned int map[256] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0,															//
	BLANK, NEWLINE, BLANK, BLANK,														// HT LF VT FF
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,							//
	BLANK,																				// (space)
	OTHER, OTHER, OTHER,																// ! " #
	0,																					//
	OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,		// % & , ( ) * + , - . /
	DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT,				// 0~9
	OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,											// : ; < = > ?
	0,																					//
	LETTER | HEX, LETTER | HEX, LETTER | HEX, LETTER | HEX, LETTER | HEX, LETTER | HEX, // A~F
	LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,		// G~Z
	LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,		// G~Z
	OTHER, OTHER, OTHER, OTHER,															// [ (backslash) ] ^
	LETTER,																				// _
	0,																					//
	LETTER | HEX, LETTER | HEX, LETTER | HEX, LETTER | HEX, LETTER | HEX, LETTER | HEX, // a~f
	LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,		// g~z
	LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,		// g~z
	OTHER, OTHER, OTHER, OTHER,															// { | } ~
	0,																					//
};
