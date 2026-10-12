#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define LENGTH_CAPACITY 4
#define LENGTH_STATUS 16

#define PATH_CAPACITY "/sys/class/power/supply/BAT0/capacity"
#define PATH_STATUS "/sys/class/power/supply/BAT0/status"

static void errExit() {
	perror("ERROR: Failed to get battery info");
	printf("Failed to get info");
	exit(1);
	return;
}

static char *readFile(
	char *filePath,
	unsigned char length
) {
	size_t endPos = 0;
	char *ret = NULL;
	FILE *file = NULL;
	
	ret = malloc(length);
	if (ret == NULL) { errExit(); }
	
	file = fopen(filePath, "r");
	if (file == NULL) {
		free(ret);
		errExit();
	}
	
	fgets(ret, length, file);
	endPos = strnlen(ret, length) - 1;
	
	if (ret[endPos] == '\n') {
		ret[endPos] = 0;
	}
	
	fclose(file);
	return ret;
}

int main() {
	char *capacity;
	char *status;
	
	capacity = readFile(
		"/sys/class/power_supply/BAT0/capacity",
		LENGTH_CAPACITY
	);
	
	status = readFile(
		"/sys/class/power_supply/BAT0/status",
		LENGTH_STATUS
	);
	
	printf("%s%% - %s\n", capacity, status);
	
	free(status);
	free(capacity);
	return 0;
}