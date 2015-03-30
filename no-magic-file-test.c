#include <stdlib.h>
#include <stdio.h>
#include <magic.h>

int main(int argc, char* argv[]) {
  FILE *f;
  const char* mode = "r";
  const char* filename = __FILE__;
  char *source = NULL;
  size_t filesize = 0;

  magic_t magic;
  const char* binary_result = NULL;

  f = fopen(filename, mode);
  if (NULL == f) {
    fprintf(stderr, "Failed to open " __FILE__ "\n");
    return 1;
  };

  if (fseek(f, 0L, SEEK_END) == 0) {
    filesize = ftell(f);
    if (-1 == filesize) {
      fprintf(stderr, "Can not get filesize.\n");
      return 1;
    };

    source = malloc(sizeof(char) * (filesize + 1));
    if (fseek(f, 0L, SEEK_SET) != 0) {
      fprintf(stderr, "Error in fseek()\n");
      return 1;
    };

    size_t newLen = fread(source, sizeof(char), filesize, f);
    if (0 == newLen) {
        fputs("Error reading file\n", stderr);
    } else {
        source[++newLen] = '\0'; /* Just to be safe. */
    };
  };

  magic = magic_open(MAGIC_NO_CHECK_SOFT);
  if (NULL == magic) {
    fprintf(stderr, "Error in magic_open(): %s\n", magic_error(magic));
    return 1;
  };

  binary_result = magic_buffer(magic, source, filesize);
  if (NULL == binary_result) {
     printf("Error in magic_buffer(): %s\n", magic_error(magic));
  };

  magic_close(magic);
  free(source);
  return 0;
};