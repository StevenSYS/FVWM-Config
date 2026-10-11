#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define LENGTH_CAPACITY 4
#define LENGTH_STATUS 16

static char *readFile(
	char *filePath,
	unsigned char length
) {
	FILE *file = fopen(filePath, "r");
	char *ret = malloc(length);
	
	if (
		ret == NULL ||
		file == NULL
	) {
		return NULL;
	}
	
	fgets(ret, length, file);
	
	if (ret[strlen(ret) - 1] == '\n') {
		ret[strlen(ret) - 1] = 0;
	}
	return ret;
}

int main() {
	const char *capacity = readFile(
		"/sys/class/power_supply/BAT0/capacity",
		LENGTH_CAPACITY
	);
	const char *status = readFile(
		"/sys/class/power_supply/BAT0/status",
		LENGTH_STATUS
	);
	
	if (capacity == NULL) {
		perror("Failed to open the battery capacity file");
		return 1;
	}
	
	if (status == NULL) {
		perror("Failed to open the battery status file");
		return 1;
	}
	
	printf("%s%% - %s\n", capacity, status);
	return 0;
}