#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main() {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  int flag = 1;
  while (1) {
    // Tulis program kalian di sini
	FILE *dibuka, *backup;

	char nama[80], putch;
	dibuka = fopen("/home/sin/Downloads/sisop-modul-2-master/diary.txt", "r");
	if(dibuka == NULL){
		printf("Invalid\n");
		exit(0);
	}
	snprintf(nama, 100, "/home/sin/Downloads/sisop-modul-2-master/diary.log.%d", flag);
	flag++;
	backup = fopen(nama, "w+");
	if(backup == NULL){
		printf("Invalid Output\n");
		fclose(backup);
		exit(0);
	}

	while((putch = fgetc(dibuka)) != EOF){
		fputc(putch, backup);
	}

	fclose(dibuka);
	fclose(backup);
	dibuka = fopen("/home/sin/Downloads/sisop-modul-2-master/diary.txt", "w");
	fclose(dibuka);

	sleep(10);
  }
}
