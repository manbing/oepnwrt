#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PORC_FILE "/proc/kernel_memleak"
#define TYPE 'j'
#define CMD_GET _IOR(TYPE, 1, int)
#define CMD_SET _IOW(TYPE, 2, int)

int main(void)
{
	int fd = 0, cmd = 0, ret = 0;

	fd = open(PORC_FILE, O_RDWR);

	assert(fd);

	while (1) {
		printf("\n\n\n");
		printf("function menu\n");
		printf("1. show\n");
		printf("\n");
		printf("please enter command which you want:\n");
		scanf("%d", &cmd);

		switch (cmd) {
		case 1:
			ret = ioctl(fd, CMD_GET, NULL);
			break;

		default:
			goto out;
		}
	}

out:
	close(fd);
	return 0;
}
