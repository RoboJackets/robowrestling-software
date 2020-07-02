#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv) {
	uint8_t bytes[3];
	bytes[0] = 0x80;
	bytes[1] = 0;
	bytes[2] = 63;

	uint32_t crc;
	for(int i = 0; i < 3; i++) {
		crc = crc ^ (bytes[i] << 8);
		for (int j = 0; j < 8; j++) {
			if (crc & 0x8000) {
				crc = (crc << 1) ^ 0x1021;
			} else {
				crc = crc << 1;
			}
			printf("%u\n", crc);
		}
	}

	printf("%u\n", crc);
	printf("0x%02X 0x%02X\n", (crc >> 8) & 0xFF, crc & 0xFF);

	return 0;
}
