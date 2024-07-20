#include "s21_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <pcre.h>

static char *olds;

char* s21_convert(unsigned int, int, int);
char *s21_DoubleToString(long double num, int tochnost);

int errlist_length = 107;

char *errlist[] = {
"Undefined error 0",
"Operation not permitted",
"No such file or directory",
"No such process",
"Interrupted system call",
"Input/output error",
"Device not configured",
"Argument list too long",
"Exec format error",
"Bad file descriptor",
"No child processes",
"Resource deadlock avoided",
"Cannot allocate memory",
"Permission denied",
"Bad address",
"Block device required",
"Resource busy",
"File exists",
"Cross-device link",
"Operation not supported by device",
"Not a directory",
"Is a directory",
"Invalid argument",
"Too many open files in system",
"Too many open files",
"Inappropriate ioctl for device",
"Text file busy",
"File too large",
"No space left on device",
"Illegal seek",
"Read-only file system",
"Too many links",
"Broken pipe",
"Numerical argument out of domain",
"Result too large",
"Resource temporarily unavailable",
"Operation now in progress",
"Operation already in progress",
"Socket operation on non-socket",
"Destination address required",
"Message too long",
"Protocol wrong type for socket",
"Protocol not available",
"Protocol not supported",
"Socket type not supported",
"Operation not supported",
"Protocol family not supported",
"Address family not supported by protocol family",
"Address already in use",
"Can't assign requested address",
"Network is down",
"Network is unreachable",
"Network dropped connection on reset",
"Software caused connection abort",
"Connection reset by peer",
"No buffer space available",
"Socket is already connected",
"Socket is not connected",
"Can't send after socket shutdown",
"Too many references: can't splice",
"Operation timed out",
"Connection refused",
"Too many levels of symbolic links",
"File name too long",
"Host is down",
"No route to host",
"Directory not empty",
"Too many processes",
"Too many users",
"Disc quota exceeded",
"Stale NFS file handle",
"Too many levels of remote in path",
"RPC struct is bad",
"RPC version wrong",
"RPC prog. not avail",
"Program version wrong",
"Bad procedure for program",
"No locks available",
"Function not implemented",
"Inappropriate file type or format",
"Authentication error",
"Need authenticator",
"Device power is off",
"Device error",
"Value too large to be stored in data type",
"Bad executable (or shared library)",
"Bad CPU type in executable",
"Shared library version mismatch",
"Malformed Mach-o file",
"Operation canceled",
"Identifier removed",
"No message of desired type",
"Illegal byte sequence",
"Attribute not found",
"Bad message",
"EMULTIHOP (Reserved)",
"No message available on STREAM",
"ENOLINK (Reserved)",
"No STREAM resources",
"Not a STREAM",
"Protocol error",
"STREAM ioctl timeout",
"Operation not supported on socket",
"Policy not found",
"State not recoverable",
"Previous owner died",
"Interface output queue is full",
};

// Vi
// Выполняет поиск первого вхождения символа c (беззнаковый тип)
// в первых n байтах строки, на которую указывает аргумент str.
void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *tmp = NULL;
  for (s21_size_t i = 0; i < n; i++) {
    if (*((char*)str + i) == c) {
      tmp = (char*)str + i;
      break;
    }
  }
  return tmp;
}

// Сравнивает первые n байтов str1 и str2.
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const char* csrc1 = (const char*)str1;
  const char* csrc2 = (const char*)str2;
  int flag1 = 0, flag2 = 0, res = 0;

  for (s21_size_t i = 0; i < n; i++, csrc1++, csrc2++) {
    if (*csrc1 < *csrc2 && flag2 == 0) {
      flag1 = -1;
    } else if (*csrc1 > *csrc2 && flag1 == 0) {
      flag2 = 1;
    }
  }
  if (flag1 == -1)
    res = -1;
  else if (flag2 == 1)
    res = 1;
  else
    res = 0;

  return res;
}

// Копирует n символов из src в dest.
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char* cdest = (char*)dest;
  const char* csrc = (const char*)src;
  for (s21_size_t i = 0; i < n; i++)
    *cdest++ = *csrc++;

  return (char*)dest;
}

// Еще одна функция для копирования n символов из str2 в str1.
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  if (dest < src) {
    char* cdest = (char*)dest;
    const char* csrc = (const char*)src;
    for (s21_size_t i = 0; i < n; i++)
      *cdest++ = *csrc++;
  } else {
    char* cdest = (char*)dest + n;
    const char* csrc = (const char*)src + n;
    for (s21_size_t i = 0; i < n; i++)
      *--cdest = *--csrc;
  }

  return dest;
}

// Копирует символ c (беззнаковый тип) в первые n символов строки,
// на которую указывает аргумент str.
void *s21_memset(void *str, int c, s21_size_t n) {
  char* tmp_mem = (char*)str;
  for (s21_size_t i = 0; i < n; i++) {
    *tmp_mem++ = c;
  }

  return str;
}

// Добавляет строку, на которую указывает src, в конец строки, на которую указывает dest.
char *s21_strcat(char *dest, const char *src) {
  char *cdest = dest;
  while (*cdest)
    cdest++;

  if (s21_strlen(src))
    while ((*cdest++ = *src++)) {}

  return dest;
}

// Добавляет строку, на которую указывает src, в конец строки,
// на которую указывает dest, длиной до n символов.
char *s21_strncat(char *dest, const char *src,  s21_size_t n) {
  s21_size_t i, j;
  for (i = 0; dest[i] != '\0';)
  i++;

  for (j = 0; j < n; j++)
    dest[i + j] = src[j];

  return dest;
}

// Al
// Выполняет поиск первого вхождения символа c (беззнаковый тип)
// в строке, на которую указывает аргумент str.
char *s21_strchr(const char *str, int c) {
  char *src = NULL;
  do {
    if (*str == c)
      src = (char*)str;
  } while (*str++ && src == NULL);
  return src;
}

// Сравнивает строку, на которую указывает str1, со строкой, на которую указывает str2.
int s21_strcmp(const char *str1, const char *str2) {
  int j = 2;
  int temp = 0;
  for (int i = 0; temp == 0; i++) {
    if (str2[i] == '\0' && str1[i] == '\0') {
      j = 0;
      temp = 1;
    } else if (str1[i] < str2[i]) {
      j = str1[i] - str2[i];
      temp = 1;
    } else if (str1[i] > str2[i]) {
      j = str1[i] - str2[i];
      temp = 1;
    }
    if (str1[i] == '\0' || str2[i] == '\0') {
      temp = 1;
    }
  }
  return j;
}

// Сравнивает не более первых n байтов str1 и str2.
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int j = 2;
  s21_size_t i = 0;
  do {
    if ((str1[i] == '\0' && str2[i] == '\0') || i >= n)
      j = 0;
    else if (str1[i] > str2[i])
      j = str1[i] - str2[i];
    else if (str1[i] < str2[i])
      j = str1[i] - str2[i];
    i++;
  } while (j == 2);
  return j;
}

// Копирует строку, на которую указывает src, в dest.
char *s21_strcpy(char *dest, const char *src) {
  int i;
  for (i = 0; src[i]; i++)
    dest[i] = src[i];
  dest[i] = src[i];
  return dest;
}

// Копирует до n символов из строки, на которую указывает src, в dest.
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  int temp = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (temp == 0)
      dest[i] = src[i];
    else
      dest[i] = '\0';
    if (src[i] == '\0')
      temp = 1;
  }
  return dest;
}

// Вычисляет длину начального сегмента str1,
// который полностью состоит из символов, не входящих в str2.
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int i = 0;
  int t = 0;
  for (i = 0; str1[i] && t == 0; i++) {
    for (int j = 0; str2[j]; j++) {
      if (str1[i] == str2[j]) {
        t = 1;
      }
    }
  }
  return i - t;
}

// Ni
// Выполняет поиск во внутреннем массиве номера ошибки errnum и
// возвращает указатель на строку с сообщением об ошибке.
char *s21_strerror(int errnum) {
  static char s[30];
  if (errnum >= errlist_length || errnum <= 0) {
    s21_sprintf(s, "Undefined error: %d", errnum);
  } else {
    s21_sprintf(s, "%s", errlist[errnum]);
  }
  return s;
}

// Вычисляет длину строки str, не включая завершающий нулевой символ.
s21_size_t s21_strlen(const char *str) {
  s21_size_t size = 0;
  for (; str[size]; size++) {}
  return size;
}

// Находит первый символ в строке str1, который соответствует любому символу,
// указанному в str2.
char *s21_strpbrk(const char *str1, const char *str2) {
  char *str = NULL;
  for (; *str1 && str == NULL; str1++) {
    const char *tmp = str2;
    for (; *tmp && str == NULL; tmp++)
      if (*tmp == *str1)
        str = (char*)str1;
    }
    return str;
}

// Выполняет поиск последнего вхождения символа c (беззнаковый тип)
// в строке, на которую указывает аргумент str.
char *s21_strrchr(const char *str, int c) {
  char *tmp = NULL;
  do {
    if (*str == c)
      tmp = (char*)str;
  } while (*str++);
  return tmp;
}

// Вычисляет длину начального сегмента str1, который полностью состоит из символов str2.
s21_size_t s21_strspn(const char *str1, const char *str2) {
  int i = 0;
  int t = 1;
  for (i = 0; str1[i] && t == 1; i++) {
    t = 0;
    for (int j = 0; str2[j]; j++) {
      if (str1[i] == str2[j]) {
        t = 1;
      }
    }
    if (t == 0)
      i--;
  }
  return i;
}

// Находит первое вхождение всей строки needle (не включая завершающий нулевой символ),
// которая появляется в строке haystack.
char *s21_strstr(const char *haystack, const char *needle) {
  char *str = NULL;
  if (haystack != NULL && needle != NULL) {
    for (int i = 0; i < (int)(s21_strlen(haystack) - s21_strlen(needle) + 1) && str == NULL; i++) {
      int flag = 1;
      for (int j = 0; j < s21_strlen(needle); j++) {
        if (haystack[i + j] != needle[j])
          flag = 0;
      }
      if (flag) {
        str = (char *)haystack;
        for (int k = 0; k < i; k++) {
          char t = *str++;
        }
      }
    }
  }
  return str;
}

// Разбивает строку str на ряд токенов, разделенных delim.
char *s21_strtok(char *str, const char *delim) {
  char *token = NULL;
  int flag = 0;

  if (str == NULL)
    str = olds;

  str += s21_strspn(str, delim);
  if (*str == '\0') {
    olds = str;
    flag = 1;
  }
  if (flag == 0) {
    token = str;
    str = s21_strpbrk(token, delim);
    if (str == NULL) {
      olds = s21_memchr(token, '\0', s21_strlen(token) + 1);
    } else {
      *str = '\0';
      olds = ++str;
    }
  }
  return token;
}

// C#
// Возвращает копию строки (str), преобразованной в верхний регистр.
// В случае какой-либо ошибки следует вернуть значение NULL
void *s21_to_upper(const char *str) {
  char *new_str = NULL;
  if (str != NULL) {
    int size = 1;
    new_str = (char*)malloc(sizeof(char));
    for (int i = 0; str[i]; i++) {
      size++;
      new_str = (char*)realloc(new_str, size * sizeof(char));
      if (str[i] >= 'a' && str[i] <= 'z') {
        new_str[i] = str[i] - 'a' + 'A';
      } else {
        new_str[i] = str[i];
      }
    }
    new_str[size - 1] = '\0';
  }
  return new_str;
}

// Возвращает копию строки (str), преобразованной в нижний регистр.
// В случае какой-либо ошибки следует вернуть значение NULL
void *s21_to_lower(const char *str) {
  char *new_str = NULL;
  if (str != NULL) {
    int size = 1;
    new_str = (char*)malloc(sizeof(char));
    for (int i = 0; str[i]; i++) {
      size++;
      new_str = (char*)realloc(new_str, size * sizeof(char));
      if (str[i] >= 'A' && str[i] <= 'Z') {
        new_str[i] = str[i] - 'A' + 'a';
      } else {
        new_str[i] = str[i];
      }
    }
    new_str[size - 1] = '\0';
  }
  return new_str;
}

// Возвращает новую строку, в которой указанная строка (str)
// вставлена в указанную позицию (start_index) в данной строке (src).
// В случае какой-либо ошибки следует вернуть значение NULL
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *new_str = NULL;
  if (!(src == NULL || str == NULL || start_index < 0 || start_index > s21_strlen(src))) {
    new_str = (char*)malloc((s21_strlen(src) + s21_strlen(str) + 1) * sizeof(char));
    int j = 0;
    for (int i = 0; i < s21_strlen(src) + s21_strlen(str); i++) {
      if (i < start_index || i >= start_index + s21_strlen(str)) {
        new_str[i] = src[i - j];
      } else {
        new_str[i] = str[j++];
      }
    }
    new_str[s21_strlen(src) + s21_strlen(str)] = '\0';
  }
  return new_str;
}

// Возвращает новую строку, в которой удаляются все начальные
// и конечные вхождения набора заданных символов (trim_chars) из данной строки (src).
// В случае какой-либо ошибки следует вернуть значение NULL
void *s21_trim(const char *src, const char *trim_chars) {
  char *new_str = NULL;
  if (src != NULL && trim_chars != NULL) {
    int leftPoint = 0;
    int rightPoint = 0;
    int flag = 1;
    for (leftPoint = 0; leftPoint < s21_strlen(src) && flag == 1; leftPoint++) {
      flag = 0;
      for (int j = 0; j < s21_strlen(trim_chars); j++) {
        if (src[leftPoint] == trim_chars[j])
          flag = 1;
      }
      if (flag == 0)
        leftPoint--;
    }
    flag = 1;
    for (rightPoint = s21_strlen(src) - 1; rightPoint >= 0 && flag == 1; rightPoint--) {
    flag = 0;
    for (int j = 0; j < s21_strlen(trim_chars); j++) {
      if (src[rightPoint] == trim_chars[j])
        flag = 1;
    }
    if (flag == 0)
      rightPoint++;
    }
    int strSize;
    if (rightPoint == -1) {
      strSize = 0;
    } else {
      strSize = rightPoint - leftPoint + 1;
    }
    new_str = (char*)malloc(1);
    new_str = (char*)realloc(new_str, strSize + 1);
    for (int i = 0; i < strSize; i++)
      new_str[i] = src[leftPoint + i];
    new_str[strSize] = '\0';
  }
  return new_str;
}

// Отправляет форматированный вывод в строку, на которую указывает str
int s21_sprintf(char *str, const char *format, ...) {
  char specifiers[] = "cdifsu%";
  char *new_str = (char*)malloc(sizeof(char));
  int size = 1;

  va_list arg;
  va_start(arg, format);

  for (int i = 0; format[i] != '\0';) {
    while (format[i] != '%' && format[i] != '\0') {
      new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
      new_str[size - 1] = format[i];
      size++;
      i++;
    }
    if (format[i] != '\0') {
      i++;
      char flag_plus = 'a';
      char flag_minus = 'a';
      char flag_probel = 'a';
      int width = 0;
      int tochka = 0;
      int tochnost = 0;
      char length = 'a';
      int stop = 0;
      do {
        for (int j = 0; j < s21_strlen(specifiers); j++)
        if (format[i] == specifiers[j])
          stop = 1;
        if (stop == 0) {
          if (format[i] == '+') {
            flag_plus = format[i];
          } else if (format[i] == '-') {
            flag_minus = format[i];
          } else if (format[i] == ' ') {
            flag_probel = format[i];
          } else if (format[i] == '.') {
            tochka = 1;
          } else if (format[i] >= '0' && format[i] <= '9' && tochka == 0) {
            width *= 10;
            width += format[i] - '0';
          } else if (format[i] >= '0' && format[i] <= '9' && tochka == 1) {
            tochnost *= 10;
            tochnost += format[i] - '0';
          } else if (format[i] == 'h' || format[i] == 'l' || format[i] == 'L') {
            length = format[i];
          }
          i++;
        }
      } while (!stop);
        if (format[i] == 'c') {
          int ch = va_arg(arg, int);
          for (int j = 0; j < width - 1 && flag_minus != '-'; j++) {
            new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
            new_str[size - 1] = ' ';
            size++;
          }
          new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
          new_str[size - 1] = ch;
          size++;
          if (flag_minus == '-') {
            for (int j = 0; j < width - 1; j++) {
              new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
              new_str[size - 1] = ' ';
              size++;
            }
          }
        } else if (format[i] == 'd' || format[i] == 'i') {
          long int ch;
          if (length == 'h')
            ch = (short int)va_arg(arg, int);
          else if (length == 'l')
            ch = va_arg(arg, long int);
          else
            ch = va_arg(arg, int);
          if (!(ch == 0 && tochka == 1 && tochnost == 0)) {
            int symbol = 0;
            if (ch < 0 || flag_plus == '+' || flag_probel == ' ')
              symbol = 1;
            char *str_num;
            str_num = s21_convert(labs(ch), 10, 0);
            int IF0 = tochnost * tochka - s21_strlen(str_num);
            if (IF0 < 0) IF0 = 0;
            int IF_ = width - s21_strlen(str_num) - symbol;
            if (IF_ < 0) IF_ = 0;
            for (int j = 0; j < IF_ - IF0 && flag_minus != '-'; j++) {
              new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
              new_str[size - 1] = ' ';
              size++;
            }
            if (ch < 0) {
              ch = -ch;
              new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
              new_str[size - 1] = '-';
              size++;
            } else if (flag_plus == '+' || flag_probel == ' ') {
              new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
              if (flag_plus == '+')
                new_str[size - 1] = '+';
              else
                new_str[size - 1] = ' ';
              size++;
            }
            for (int j = 0; j < IF0; j++) {
              new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
              new_str[size - 1] = '0';
              size++;
            }
            new_str = (char*)realloc(new_str, (size + s21_strlen(str_num)) * sizeof(char));
            new_str[size - 1] = '\0';
            s21_strcat(new_str, str_num);
            size += s21_strlen(str_num);
            if (flag_minus == '-') {
              for (int j = 0; j < IF_ - IF0; j++) {
                new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
                new_str[size - 1] = ' ';
                size++;
              }
            }
          }
        } else if (format[i] == 'f') {
            int symbol = 0;
            double flt;
            if (length == 'L')
              flt = va_arg(arg, double);
            else
              flt = (float)va_arg(arg, double);
            if (flt < 0 || flag_plus == '+' || flag_probel == ' ')
              symbol = 1;
            char *s;
            int toch = 6;
            if (tochka == 1)
              toch = tochnost;
            s = s21_DoubleToString(flt, toch);
            int IF = width - s21_strlen(s) - symbol;
            for (int j = 0; j < IF && flag_minus != '-'; j++) {
              new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
              new_str[size - 1] = ' ';
              size++;
            }
            if (flt < 0) {
              flt = -flt;
              new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
              new_str[size - 1] = '-';
              size++;
            } else if (flag_plus == '+' || flag_probel == ' ') {
              new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
              if (flag_plus == '+')
                new_str[size - 1] = '+';
              else
                new_str[size - 1] = ' ';
              size++;
            }
            new_str = (char*)realloc(new_str, (size + s21_strlen(s)) * sizeof(char));
            new_str[size - 1] = '\0';
            s21_strcat(new_str, s);
            size += s21_strlen(s);
            if (flag_minus == '-') {
              for (int j = 0; j < IF; j++) {
                new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
                new_str[size - 1] = ' ';
                size++;
              }
            }
            free(s);
          } else if (format[i] == 'u') {
            long int ch;
            if (length == 'h')
              ch = (unsigned short int)va_arg(arg, unsigned int);
            else if (length == 'l')
              ch = va_arg(arg, unsigned long int);
            else
              ch = va_arg(arg, unsigned int);
            if (!(ch == 0 && tochka == 1 && tochnost == 0)) {
              char *str_num;
              str_num = s21_convert(ch, 10, 0);
              int IF0 = tochnost * tochka - s21_strlen(str_num);
              if (IF0 < 0) IF0 = 0;
              int IF_ = width - s21_strlen(str_num);
              if (IF_ < 0) IF_ = 0;
              for (int j = 0; j < IF_ - IF0 && flag_minus != '-'; j++) {
                new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
                new_str[size - 1] = ' ';
                size++;
              }
              for (int j = 0; j < IF0; j++) {
                new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
                new_str[size - 1] = '0';
                size++;
              }
              new_str = (char*)realloc(new_str, (size + s21_strlen(str_num)) * sizeof(char));
              new_str[size - 1] = '\0';
              s21_strcat(new_str, str_num);
              size += s21_strlen(str_num);
              if (flag_minus == '-') {
                for (int j = 0; j < IF_ - IF0; j++) {
                  new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
                  new_str[size - 1] = ' ';
                  size++;
                }
              }
            }
          } else if (format[i] == 's') {
            char *s;
            s = va_arg(arg, char *);
            int lenS = s21_strlen(s);
            int IF = width - lenS;
            if (lenS > tochnost && tochka == 1)
              IF += lenS - tochnost;
            for (int j = 0; j < IF && flag_minus != '-'; j++) {
              new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
              new_str[size - 1] = ' ';
              size++;
            }
            for (int i = 0; i < lenS && !(tochka == 1 && i >= tochnost); i++) {
              new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
              new_str[size - 1] = s[i];
              size++;
            }
            if (flag_minus == '-') {
              for (int j = 0; j < IF; j++) {
                new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
                new_str[size - 1] = ' ';
                size++;
              }
            }
          } else if (format[i] == '%') {
            int ch;
            ch = va_arg(arg, int);
            for (int j = 0; j < width - 1 && flag_minus != '-'; j++) {
              new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
              new_str[size - 1] = ' ';
              size++;
            }
            new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
            new_str[size - 1] = '%';
            size++;
            if (flag_minus == '-') {
            for (int j = 0; j < width - 1; j++) {
              new_str = (char*)realloc(new_str, (size + 1) * sizeof(char));
              new_str[size - 1] = ' ';
              size++;
          }
        }
      }
    i++;
    }
  }
  new_str[size - 1] = '\0';
  int j = 0;
  for (; new_str[j] != '\0'; j++) {
    str[j] = new_str[j];
  }
  str[j] = new_str[j];
  free(new_str);
  va_end(arg);
  return 0;
}

char *s21_DoubleToString(long double num, int tochnost) {
  if (tochnost < 0)
    tochnost = 0;
  char *str = (char*)malloc(1);
  int size = 1;
  int int_part = num;
  char statArrInt[50];
  char *arrInt = &statArrInt[49];
  *arrInt = '\0';
  if (num < 0.0)
    num *= -1.0;
  // создаём строку из целой части
  do {
    *--arrInt = (int_part % 10) + '0';
    int_part /= 10;
  } while (int_part != 0);
  // создаём стркоу из дробной части
  char *arrDouble = (char*)malloc(tochnost + 1);
  arrDouble[tochnost] = '\0';
  long double num_float = num - (long double)(unsigned long)num;
  for (int i = 0; i < tochnost; i++) {
    num_float *= 10.0;
    arrDouble[i] = ((unsigned int)num_float)  + '0';
    num_float -= (long double)(unsigned long)num_float;
  }
  // ---
  for (; *arrInt; size++) {
    str = (char*)realloc(str, size + 1);
    str[size - 1] = *arrInt++;
  }
  str = (char*)realloc(str, size + 1);
  str[size - 1] = '.';
  size++;
  for (int j = 0; arrDouble[j]; size++) {
    str = (char*)realloc(str, size + 1);
    str[size - 1] = arrDouble[j];
    j++;
  }
  str[size - 1] = '\0';
  free(arrDouble);
  return str;
}

char *s21_convert(unsigned int num, int base, int flag) {
  static char Representation[]= "0123456789ABCDEF";
  static char Representation_lower[]= "0123456789abcdef";
  static char buffer[50];
  char *ptr;
  ptr = &buffer[49];
  *ptr = '\0';

  do {
    if (flag == 1)
      *--ptr = Representation[num % base];
    else
      *--ptr = Representation_lower[num % base];
    num /= base;
    } while (num != 0);
  return(ptr);
}
