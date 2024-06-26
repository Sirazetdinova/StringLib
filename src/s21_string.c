#include "s21_string.h"

#include "s21_errno.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  s21_size_t i = 0;
  void *ptr = s21_NULL;

  for (; i < n; i++) {
    if (*((char *)str + i) == (char)c) {
      ptr = (char *)str + i;
      break;
    }
  }
  return ptr;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int result = 0;
  const char *s1 = str1;
  const char *s2 = str2;
  if ((int)n > 0) {
    for (int z = 0; z < (int)n; z++) {
      if (s1[z] != s2[z]) {
        result = s1[z] - s2[z];
        break;
      }
    }
  } else if ((int)n < 0) {
    for (int z = 0; z < (int)s21_strlen(str1) + 1; z++) {
      if (s1[z] != s2[z]) {
        result = s1[z] - s2[z];
        break;
      }
    }
  }
  return result;
}

// void *s21_memcpy(void *dest, const void *src, s21_size_t n) {   // m- f-
// //+++ C
//   s21_size_t len = s21_strlen((char *)dest) + 1;
//   if (len > n) {
//     s21_size_t i = 0;
//     for (; i < n; i++) {
//       *((char *)dest + i) = *((char *)src + i);
//     }
//   }

//   return dest;
// }

void *s21_memcpy(void *dest, const void *src,
                 s21_size_t n) {  ////////////////////////////////// VVV
  char *src_copy = (char *)src;
  char *dest_copy = (char *)dest;
  for (int i = 0; i < (int)n; i++) {
    dest_copy[i] = src_copy[i];
  }
  return dest;
}

void *s21_memset(void *str, int c, size_t n) {
  char a = c;
  char *s1 = str;
  for (int z = 0; z < (int)n; z++) {
    s1[z] = a;
  }
  return s1;
}

char *s21_strchr(const char *str, int c) {
  int z = 0;
  char a = c, *b = s21_NULL;
  for (z = 0; z < (int)s21_strlen(str) + 1; z++) {
    if (str[z] == a) {
      b = (char *)str + z;
      break;
    }
  }
  return b;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t len = 0;
  int flag = 0;

  for (; len < s21_strlen(str1) + 1; len++) {
    for (s21_size_t i = 0; i < s21_strlen(str2) + 1; i++)
      if (str1[len] == str2[i]) {
        flag = 1;
        break;
      }
    if (flag) break;
  }

  return len;
}

char *s21_strerror(int errnum) {
  char *err_s = s21_NULL;
  static char err_d[50] = {0};
#if defined __APPLE__ && defined __MACH__
  if ((errnum > 0 && errnum < 107)) {
    ER_MAC(err_s, errnum);
    for (int i = 0; i < (int)s21_strlen(err_s) + 1; i++) {
      err_d[i] = err_s[i];
    }
  } else if (errnum == 0) {
    s21_sprintf(err_d, "Undefined error: %d", errnum);
  } else {
    s21_sprintf(err_d, "Unknown error: %d", errnum);
  }
#elif __linux__
  if ((errnum > 0 && errnum < 125)) {
    ER_LINUKS(err_s, errnum);
    for (int i = 0; i < (int)s21_strlen(err_s) + 1; i++) {
      err_d[i] = err_s[i];
    }
  } else if (errnum == 0) {
    s21_sprintf(err_d, "Success");
  } else {
    s21_sprintf(err_d, "Unknown error %d", errnum);
  }
#endif
  return err_d;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  if (str != s21_NULL) {
    for (; str[len]; len++)
      ;
  }
  return len;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t len = s21_strlen(dest);

  for (s21_size_t i = 0; i < n; len++, i++) {
    if (src[i] != '\0') dest[len] = src[i];
  }

  return dest;
}

// int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {   // m+
// f-  //+++ C
//   int detect = 0;
//   if (n > 0) {
//     s21_size_t i = 0;
//     while ((i <= n) && !(str1[i] == '\0' && str2[i] == '\0') &&
//            ((detect = str1[i] - str2[i]) == 0)) {
//       i++;
//     }
//   }

//   return detect;
// }

int s21_strncmp(const char *str1, const char *str2,
                s21_size_t n) {  ////////////////////////////////// VVV
  int comp = 0;

  for (int i = 0; i < (int)n && comp == 0; i++) {
    int char1 = str1[i];
    int char2 = str2[i];
    comp = char1 - char2;
  }
  return comp;
}

char *s21_strncpy(char *dest, const char *src, size_t n) {
  for (int i = 0; i < (int)n; i++) {
    if (i < (int)s21_strlen(src) + 1) {
      dest[i] = src[i];
    } else if (i >= (int)s21_strlen(src) + 1) {
      dest[i] = 0;
    }
  }
  return dest;
}

// char *s21_strpbrk(const char *str1, const char *str2) {   // m+ f-  //+++ C
//   char *sim = s21_NULL;
//   if (str1[0] != 0 && str2[0] != 0) {
//     int flag = 0;
//     for (int i = 0; i < (int)s21_strlen(str1) + 1; i++) {
//       for (int j = 0; j < (int)s21_strlen(str2) + 1; j++) {
//         if (str1[i] == str2[j] && flag != 1) {
//           sim = (char *)str1 + i;
//           flag = 1;
//         }
//       }
//     }
//   }
//   return sim;
// }

char *s21_strpbrk(const char *str1,
                  const char *str2) {  ////////////////////////////////// VVV
  if (str1 != s21_NULL && str2 != s21_NULL) {
    while (*str1 != '\0') {
      const char *c = str2;
      while (*c != '\0') {
        if (*str1 == *c) {
          return (char *)str1;
        }
        c++;
      }
      str1++;
    }
  }

  return s21_NULL;
}

char *s21_strrchr(const char *str, int c) {
  char *cptr = s21_NULL;

  s21_size_t len = 0;

  for (; len < (s21_strlen(str) + 1); len++)
    if (str[len] == c) {
      cptr = (char *)str + len;
    }

  return cptr;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *sim = s21_NULL;
  if ((int)s21_strlen(needle) == 0) {
    sim = (char *)haystack;
  } else {
    int flag = 0;
    for (int i = 0; i < (int)s21_strlen(haystack) + 1; i++) {
      int a = i;
      int j = 0;
      while ((haystack[a] == needle[j] || needle[j] == '\0') && (flag != 1)) {
        a = a + 1;
        j = j + 1;
        if (needle[j] == '\0') {
          sim = (char *)haystack + i;
          flag = 1;
        }
      }
    }
  }
  return sim;
}

int is_delim(char c, const char *delim) {
  int flag = 0;
  while (*delim != '\0') {
    if (c == *delim) {
      flag = 1;
    }
    delim++;
  }
  return flag;
}

char *s21_strtok(char *str, const char *delim) {
  static char *backup_string;
  char *ret = s21_NULL;

  if (!str) {
    str = backup_string;
  }
  if (str == s21_NULL || *str == '\0') {
    ret = s21_NULL;
  } else {
    while (is_delim(*str, delim) && *str != '\0') {
      str++;
    }
    if (*str == '\0') {
      ret = s21_NULL;
    } else {
      ret = str;
      while (!is_delim(*str, delim) && *str != '\0') {
        str++;
      }

      if (*str == '\0') {
        backup_string = s21_NULL;
      } else {
        *str = '\0';
        backup_string = ++str;
      }
    }
  }

  return ret;
}

void *s21_to_upper(const char *str) {
  void *upper = s21_NULL;
  if (str != s21_NULL) {
    upper = calloc(sizeof(char), 500);
    for (s21_size_t i = 0; i != s21_strlen(str) + 1; i++) {
      if ((*(str + i) >= 'a' && *(str + i) <= 'z')) {
        *((char *)(upper + i)) = *((char *)(str + i)) - 32;
      } else
        *((char *)(upper + i)) = *((char *)(str + i));
    }
  }
  return upper;
}

void *s21_to_lower(const char *str) {
  void *lower = s21_NULL;
  if (str != s21_NULL) {
    lower = calloc(sizeof(char), 500);
    for (s21_size_t i = 0; i < s21_strlen(str) + 1; i++) {
      if (*(str + i) >= 'A' && *(str + i) <= 'Z') {
        *((char *)(lower + i)) = *((char *)(str + i)) + 32;
      } else
        *((char *)(lower + i)) = *((char *)(str + i));
    }
  }
  return lower;
}

// void *s21_insert(const char *src, const char *str,
//                  s21_size_t start_index) {    // m- f-  //+++ C
//   s21_size_t len_1 = s21_strlen(str) + 1;
//   void *insert = s21_NULL;
//   if (src != s21_NULL && str != s21_NULL &&
//       (start_index > 0 && start_index <= len_1)) {
//     s21_size_t len = len_1;
//     char lokal[len_1];
//     for (s21_size_t i = 0; i < len_1; i++) {
//       lokal[i] = *((char *)src + i);
//     }
//     for (s21_size_t i = 0; i < len; i++) {
//       if (i == start_index - 1) {
//         for (s21_size_t j = 0; j < len_1 - 1; j++) {
//           *((char *)src + (j + start_index - 1)) = *((char *)str + j);
//         }
//         i = start_index - 1;
//         *((char *)src + (i + len_1 - 1)) = lokal[i];
//         i = start_index;
//         *((char *)src + (i + len_1 - 1)) = lokal[i];
//       } else if (i > start_index - 1) {
//         *((char *)src + (i + len_1 - 1)) = lokal[i];
//       }
//     }
//     insert = (char *)src;
//   } else if (str == s21_NULL && src != s21_NULL && start_index <= len_1) {
//     insert = (char *)src;
//   }
//   return insert;
// }

void *s21_insert(
    const char *src, const char *str,
    s21_size_t start_index) {  ////////////////////////////////// VVV
  char *new_str = s21_NULL;
  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);

  if (start_index <= src_len && src != s21_NULL && str != s21_NULL) {
    s21_size_t new_str_len = src_len + str_len;
    new_str = (char *)malloc((new_str_len + 1) * sizeof(char));

    if (new_str == s21_NULL) return s21_NULL;
    s21_memcpy(new_str, src, start_index);
    s21_memcpy(new_str + start_index, str, str_len);
    s21_memcpy(new_str + start_index + str_len, src + start_index,
               src_len - start_index);

    new_str[new_str_len] = '\0';
  }

  return new_str;
}

// void *s21_trim(const char *src, const char *trim_chars) {  // m- f-
//   void *trim = s21_NULL;
//   if (trim_chars == s21_NULL || *trim_chars == '\0') trim_chars = " ";
//   if (src != s21_NULL) {
//     int index_for_start = 0;
//     int len = s21_strlen(src);
//     while (src[index_for_start] != 0) {
//       int j = 0, flag = 0;
//       while (trim_chars[j] != 0) {
//         if (src[index_for_start] == trim_chars[j]) {
//           flag = 1;
//         }
//         j++;
//       }
//       if (flag == 0) break;
//       index_for_start++;
//     }
//     int index_for_end = len - 1;
//     while (index_for_end != 0) {
//       int j = 0, flag = 0;
//       while (trim_chars[j] != 0) {
//         if (src[index_for_end] == trim_chars[j]) {
//           flag = 1;
//         }
//         j++;
//       }
//       if (flag == 0) break;
//       index_for_end--;
//     }
//     if(index_for_start == len || index_for_end - index_for_start < 0) {
//       index_for_start = 1;
//     }
//     trim = (char *)calloc(index_for_end - index_for_start + 1, sizeof(char));
//     if (trim != s21_NULL) {
//       s21_strncpy(trim, src + index_for_start, index_for_end -
//       index_for_start + 1);
//     }
//     if (trim == s21_NULL) trim = "";
//   }
//   return trim;
// }

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == NULL || trim_chars == NULL) return NULL;
  void *q = NULL;
  size_t src_length = s21_strlen(src);

  size_t start_index = 0;
  while (start_index < src_length &&
         s21_strchr(trim_chars, src[start_index]) != NULL) {
    ++start_index;
  }

  size_t end_index = src_length - 1;
  while (end_index > start_index &&
         s21_strchr(trim_chars, src[end_index]) != NULL) {
    --end_index;
  }

  size_t trimmed_length =
      (end_index >= start_index) ? (end_index - start_index + 1) : 0;

  char *result = (char *)calloc(trimmed_length + 1, sizeof(char));
  if (result != NULL) {
    for (size_t i = 0; i < trimmed_length; ++i) {
      result[i] = src[start_index + i];
    }

    result[trimmed_length] = '\0';
    q = result;
  }
  return q;
}

// void *s21_trim(const char *src, const char *trim_chars) {  // m- f-
//   void *trim = s21_NULL;
//   s21_size_t len = s21_strlen(src) + 1;
//   if (trim_chars == s21_NULL) trim_chars = " ";
//   if (src != s21_NULL) {
//     char lokal[len];
//     for (s21_size_t i = 0; i < len; i++) {
//       lokal[i] = *((char *)src + i);
//     }
//     int index_for_end = 0;
//     while (src[index_for_end] != 0) {
//       int j = 0, flag = 0;
//       while (trim_chars[j] != 0) {
//         if (src[index_for_end] == trim_chars[j]) {
//           flag = 1;
//         }
//         j++;
//       }
//       if (flag == 0) break;
//       index_for_end++;
//     }
//     for (s21_size_t z = 0; z < len - 1; z++) {
//       *((char *)src + z) = lokal[z + index_for_end];
//     }
//     int index_for_start = (int)s21_strlen(src) - 1;
//     while (index_for_start != 0) {
//       int j = 0, flag = 0;
//       while (trim_chars[j] != 0) {
//         if (src[index_for_start] == trim_chars[j]) {
//           flag = 1;
//         }
//         j++;
//       }
//       if (flag == 0) break;
//       index_for_start--;
//     }
//     for (int z = 0; z <= index_for_start; z++) {
//       if (z != index_for_start) {
//         *((char *)src + z) = lokal[z + index_for_end];
//       } else {
//         *((char *)src + z + 1) = '\0';
//       }
//     }
//     trim = (char *)src;
//   }
//   return trim;
// }