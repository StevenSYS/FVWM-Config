#include <stdio.h>
#include <string.h>

#define LENGTH_HEXCOLOR ((2 * 3) + 2)
#define RCOLOR(_min, _max) \
	for (j = _min; j < (_max + 1); j++) { \
		if (!vals[j][0]) { \
			color = nextColor(); \
			snprintf( \
				vals[j], \
				LENGTH_HEXCOLOR, \
				"#%02X%02X%02X", \
				withOffset(color, 0), \
				withOffset(color, 1), \
				withOffset(color, 2) \
			); \
		} \
	}

/* Output */
#ifndef OUTPUT
	#define OUTPUT "output.cs"
#endif

/* Offsets */
#ifndef OFFSET1
	#define OFFSET1 0x00
#endif
#ifndef OFFSET2
	#define OFFSET2 0x00
#endif
#ifndef OFFSET3
	#define OFFSET3 0x00
#endif

enum values {
	VALUE_FG,
	VALUE_BG,
	VALUE_HI,
	VALUE_SH,
	
	VALUE_LENGTH
};

static unsigned char colors[] = {
	0xF0, 0x20,
	0xF0, 0x40,
	0x00, 0x40,
	0x80, 0x20, 0x00, 0x40,
	0x00, 0xC0,
	0xF0, 0x80,
	0x80, 0xC0,
	0xF0, 0x40,
	0x00, 0x00, 0xFF, 0x00,
	0xF0, 0xF0, 0xF0, 0x10,
	0x20, 0xF0,
	0xF0, 0x60,
	0xA0, 0x80, 0xA0, 0x20
};

static unsigned char offsets[3] = { OFFSET1, OFFSET2, OFFSET3 };

static unsigned char nextColor() {
	static unsigned char i = 0;
	if (i >= sizeof(colors)) {
		i = 0;
	}
	return colors[i++];
}

static unsigned char withOffset(
	unsigned char color,
	unsigned char offset
) {
	switch (color) {
		case 0xFF:
		case 0x00:
			return color;
		default:
			if (offsets[offset] >= (0xFF - color)) {
				return 0xFF;
			}
			break;
	}
	return color + offsets[offset];
}

int main() {
	char vals[VALUE_LENGTH][LENGTH_HEXCOLOR];
	unsigned char i, j;
	unsigned char color = 0;
	FILE *file;
	
	file = fopen(OUTPUT, "w");
	if (file == NULL) {
		perror("ERROR: Failed to open file");
		return 1;
	}
	
	for (i = 0; i < 14; i++) {
		for (j = 0; j < VALUE_LENGTH; j++) {
			vals[j][0] = 0;
		}
		
		switch (i) {
			case 8:
				continue;
			case 3:
			case 9:
			case 10:
			case 13:
				RCOLOR(VALUE_HI, VALUE_SH);
				break;
			default:
				break;
		}
		RCOLOR(VALUE_FG, VALUE_BG);
		
		fprintf(file, "Colorset %u fg %s, bg %s hi", i + 1, vals[0], vals[1]);
		if (vals[VALUE_HI][0]) {
			fprintf(file, " %s", vals[2]);
		}
		fprintf(file, ", sh");
		if (vals[VALUE_SH][0]) {
			fprintf(file, " %s", vals[3]);
		}
		fprintf(file, ", Plain, NoShape\n");
	}
	return 0;
}