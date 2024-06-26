#include "s21_string.h"

valStruct reset_value(valStruct end, int *ptr_error) {
  end.width = 0;
  end.length = 0;
  if (*ptr_error == 2) *ptr_error = 0;

  return end;
}

valStruct value_init(valStruct nachalo, const char *format, const char *str) {
  nachalo.width = 0;
  nachalo.length = 0;
  nachalo.start = str;
  nachalo.result = 0;
  nachalo.procent_num = handle_format(format);

  return nachalo;
}

int handle_format(const char *format) {
  int percent_counter = 0;
  for (; *format != '\0'; format++) {
    if (*format == '%' && *(format + 1) != '%') percent_counter++;
  }
  return percent_counter;
}

const char *go_to_next_char(const char *str, valStruct *ptr_value) {
  str++;
  ptr_value->width--;
  return str;
}

int is_plus_minus(char ch) { return (ch == 43) || (ch == 45) ? 1 : 0; }

long add_int_part(long summ, const char *str, int *power) {
  int num = 0;
  num = (*str - 48);
  summ = summ * *power + num;
  *power = 10;

  return summ;
}

void get_specificator_width(const char **format, valStruct *ptr_value) {
  int power = 1;
  if ((*format)[1] == '*') {
    ptr_value->width = -1;
    (*format)++;
  } else if (isdigit((*format)[1])) {
    while (isdigit(*(++(*format)))) {
      ptr_value->width = add_int_part(ptr_value->width, *format, &power);
    }
    (*format)--;
  } else
    ptr_value->width = INT_MAX;
}

void get_specificator_length(const char **format, valStruct *ptr_value) {
  if (*((*format) + 1) == 'h') {
    ptr_value->length = 'h';
    (*format)++;
  } else if (*((*format) + 1) == 'l') {
    ptr_value->length = 'l';
    (*format)++;
  } else if (*((*format) + 1) == 'L') {
    ptr_value->length = 'L';
    (*format)++;
  }
  (*format)++;
}

const char *handle_plus_minus(const char *str, valStruct *ptr_value,
                              int *ptr_error, int *ptr_minus_flag) {
  ptr_value->width--;
  if (ptr_value->width < 1) {
    *ptr_error = 1;
  } else if (43 - *str) {
    *ptr_minus_flag = 1;
  }
  str++;

  return str;
}

void is_hexadecimal_notation(const char **str, valStruct *ptr_value) {
  if (**str == '0' && (*(*str + 1) == 'X' || *(*str + 1) == 'x')) {
    for (int i = 0; i < 2; i++) {
      *str = go_to_next_char(*str, ptr_value);
    }
  }
}

long write_number(const char **str, valStruct *ptr_value,
                  convers_to_system fn_ptr,
                  int *ptr_error) {  // добавить флаг хзхз
  long summ = 0;
  int power = 1, minus_flag = 0;

  if (is_plus_minus(**str)) {
    *str = handle_plus_minus(*str, ptr_value, ptr_error, &minus_flag);
  }
  if (fn_ptr == &char_to_hex_digit) {
    is_hexadecimal_notation(str, ptr_value);
  }
  if (!(*ptr_error)) {
    while (isxdigit(**str) && (ptr_value->width != 0) && !(*ptr_error)) {
      summ = fn_ptr(**str, summ, &power, ptr_error);
      if (*ptr_error == 2) {
        if (!minus_flag)
          summ = LONG_MAX;
        else
          summ = LONG_MIN;
      }
      *str = go_to_next_char(*str, ptr_value);
    }
    if (minus_flag) summ *= -1;
  }

  return summ;
}

const char *processing_d_specif(long **d, va_list *ap, const char *str,
                                valStruct *ptr_value, convers_to_system fn_ptr,
                                int *ptr_error) {
  while (isspace(*str)) str++;
  if (ptr_value->width != -1) {
    if (ptr_value->length == 'l')
      *d = va_arg(*ap, long *);
    else if (ptr_value->length == 'h')
      *d = (long *)va_arg(*ap, short int *);
    else
      *d = (long *)va_arg(*ap, int *);
    if (isdigit(*str) || is_plus_minus(*str)) {
      if (ptr_value->width == 1 && is_plus_minus(*str))
        *ptr_error = 3;
      else {
        if (ptr_value->length == 'l')
          *((long *)*d) = write_number(&str, ptr_value, fn_ptr, ptr_error);
        else if (ptr_value->length == 'h')
          *((short *)*d) =
              (short)write_number(&str, ptr_value, fn_ptr, ptr_error);
        else
          *((int *)*d) = (int)write_number(&str, ptr_value, fn_ptr, ptr_error);
        ptr_value->result++;
      }
    } else
      *ptr_error = 1;
  } else {
    ptr_value->width = INT_MAX;
    write_number(&str, ptr_value, fn_ptr, ptr_error);
  }
  while (isspace(*str)) str++;
  ptr_value->procent_num--;

  return str;
}

void processing_c_specif(char *c, va_list *ap, const char **str,
                         valStruct *ptr_value, const char **format) {
  if (ptr_value->width != -1) {
    c = va_arg(*ap, char *);
    *c = **str;
    ptr_value->result++;
    (*str)++;
  } else
    (*str)++;
  if (isspace(*(*format + 1)))
    while (isspace(**str)) (*str)++;
  ptr_value->procent_num--;
}

int detekt_nan(const char **str) {
  int detekt = 0;
  if (**str == 'n' || **str == 'N') {
    (*str)++;
    if (**str == 'a' || **str == 'A') {
      (*str)++;
      if (**str == 'n' || **str == 'N') {
        detekt = 1;
        (*str) -= 2;
      } else
        (*str) -= 2;
    } else
      (*str)--;
  }

  return detekt;
}

int detekt_inf(const char **str) {
  int detekt = 0;
  if ((**str == 'i' || **str == 'I')) {
    (*str)++;
    if ((**str == 'n' || **str == 'N')) {
      (*str)++;
      if (**str == 'f' || **str == 'F') {
        detekt = 1;
        (*str) -= 2;
      } else
        (*str) -= 2;
    } else
      (*str)--;
  }
  return detekt;
}

int point_for_double(const char **str, valStruct *value) {
  int flag = 0;
  if (**str == '.') {
    *str = go_to_next_char(*str, value);
    flag = 1;
  }
  return flag;
}

long double add_fraction_of_real(const char **str, long double summ,
                                 valStruct *ptr_value, int *power) {
  int num;
  long double fraction = 0.0;
  while (isdigit(**str) && ptr_value->width >= 1) {
    num = (**str - 48.0);
    fraction = (long double)num / *power;
    summ += fraction;
    *power *= 10;
    *str = go_to_next_char(*str, ptr_value);
  }
  return summ;
}

long double set_inf(const char **str, long double summ, valStruct *value,
                    int *ptr_error) {
  for (int i = 0; i < 3; i++) {
    *str = go_to_next_char(*str, value);
  }
  if (value->width >= 0)
    summ = INFINITY;
  else {
    *ptr_error = 1;
    value->result--;
  }
  return summ;
}

long double set_nan(const char **str, long double summ, valStruct *value,
                    int *ptr_error) {
  for (int i = 0; i < 3; i++) {
    *str = go_to_next_char(*str, value);
  }
  if (value->width >= 0)
    summ = NAN;
  else {
    *ptr_error = 1;
    value->result--;
  }
  return summ;
}

long double change_order_of_magnitude(long double summ, int degeree,
                                      int minus_flag) {  // nameing degeree flag
  if (!minus_flag) {
    for (int i = 0; i < degeree; i++) {
      summ = summ * 10;
    }
  } else {
    for (int i = 0; i < degeree; i++) {
      summ = summ / 10;
    }
  }
  return summ;
}

long double add_integer_of_real(const char **str, long double summ,
                                int *ptr_power, valStruct *ptr_value) {
  while (isdigit(**str) && ptr_value->width >= 1) {
    summ = add_int_part(summ, *str, ptr_power);
    *str = go_to_next_char(*str, ptr_value);
  }
  return summ;
}

long double write_real_number(const char **str, valStruct *ptr_value,
                              int *ptr_error) {
  long double summ = 0.0;
  int power = 1, minus_flag = 0;

  if (is_plus_minus(**str))
    *str = handle_plus_minus(*str, ptr_value, ptr_error, &minus_flag);
  if (detekt_inf(str)) {
    summ = set_inf(str, summ, ptr_value, ptr_error);
  } else if (detekt_nan(str)) {
    summ = set_nan(str, summ, ptr_value, ptr_error);
  } else {
    if (ptr_value->width >= 1 && point_for_double(str, ptr_value)) {
      power = 10;
      summ = add_fraction_of_real(str, summ, ptr_value, &power);
    } else {
      summ = add_integer_of_real(str, summ, &power, ptr_value);
      if (ptr_value->width >= 1 && point_for_double(str, ptr_value)) {
        summ = add_fraction_of_real(str, summ, ptr_value, &power);
      }
    }
    if (**str == 'e' || **str == 'E') {
      summ = handle_e_notation(summ, str, ptr_value, ptr_error);
    }
  }
  if (minus_flag) summ *= -1;

  return summ;
}

long double handle_e_notation(long double summ, const char **str,
                              valStruct *ptr_value, int *ptr_error) {
  int minus_flag = 0, degeree = 0, power = 1;

  *(str) = go_to_next_char(*str, ptr_value);
  if (is_plus_minus(**str))
    *str = handle_plus_minus(*str, ptr_value, ptr_error, &minus_flag);
  degeree = add_integer_of_real(str, degeree, &power, ptr_value);
  if (degeree != 0) {
    summ = change_order_of_magnitude(summ, degeree, minus_flag);
  } else
    *ptr_error = 1;

  return summ;
}

int is_octal(int c) { return (c > 47 && c < 56) ? 1 : 0; }

int is_sign_of_real_number(const char **str) {
  return (isdigit(**str) || is_plus_minus(**str) || **str == '.' ||
          detekt_nan(str) || detekt_inf(str))
             ? 1
             : 0;
}

const char *processing_f_specif(long double **f, va_list *ap, const char *str,
                                valStruct *ptr_value, int *ptr_error) {
  while (isspace(*str)) str++;
  if (ptr_value->width != -1) {
    if (ptr_value->length == 'L')
      *f = va_arg(*ap, long double *);
    else if (ptr_value->length == 'l')
      *((double **)f) = va_arg(*ap, double *);
    if (is_sign_of_real_number(&str)) {
      if (ptr_value->width == 1 && (is_plus_minus(*str) || *str == '.'))
        *ptr_error = 3;
      else {
        if (ptr_value->length == 'L')
          **f = write_real_number(&str, ptr_value, ptr_error);
        else if (ptr_value->length == 'l')
          *((double *)*f) =
              (double)write_real_number(&str, ptr_value, ptr_error);
        ptr_value->result++;
      }
    }
  } else {
    ptr_value->width = INT_MAX;
    write_real_number(&str, ptr_value, ptr_error);
  }
  while (isspace(*str)) str++;
  ptr_value->procent_num--;

  return str;
}

const char *processing_uxo_specif(unsigned long **ul, va_list *ap,
                                  const char *str, valStruct *ptr_value,
                                  convers_to_system fn_ptr, int *ptr_error) {
  while (isspace(*str)) str++;
  if (ptr_value->width != -1) {
    if (ptr_value->length == 'l')
      *ul = va_arg(*ap, unsigned long *);
    else if (ptr_value->length == 'h')
      *((unsigned short **)ul) = va_arg(*ap, unsigned short *);
    else
      *((unsigned int **)ul) = va_arg(*ap, unsigned int *);
    if (isxdigit(*str) || is_plus_minus(*str)) {
      if (ptr_value->width == 1 && is_plus_minus(*str))
        *ptr_error = 3;
      else {
        if (ptr_value->length == 'l')
          **ul = write_number(&str, ptr_value, fn_ptr, ptr_error);
        else if (ptr_value->length == 'h')
          *((unsigned short *)*ul) =
              (unsigned short)write_number(&str, ptr_value, fn_ptr, ptr_error);
        else
          *((unsigned int *)*ul) =
              (unsigned int)write_number(&str, ptr_value, fn_ptr, ptr_error);
        ptr_value->result++;
      }
    }
  } else {
    ptr_value->width = INT_MAX;
    write_number(&str, ptr_value, fn_ptr, ptr_error);
  }
  while (isspace(*str)) str++;
  ptr_value->procent_num--;

  return str;
}

long char_to_hex_digit(const char c, long summ, int *power, int *ptr_error) {
  int num = 0;
  if (isdigit(c))
    num = c - 48;
  else if (isxdigit(c) && islower(c))
    num = c - 87;
  else if (isxdigit(c) && isupper(c))
    num = c - 55;
  else
    *ptr_error = 1;
  if (num + 1) {
    summ = summ * *power + num;
    *power = 16;
  }

  return summ;
}

long char_to_oct_digit(const char c, long summ, int *power, int *ptr_error) {
  int num = 0;
  if (is_octal(c)) {
    num = c - 48;
    summ = summ * *power + num;
    *power = 8;
  } else
    *ptr_error = 1;

  return summ;
}

long char_to_dec_digit(const char c, long summ, int *power, int *ptr_error) {
  int num = 0;
  if (isdigit(c)) {
    if (summ >= (LONG_MAX / 10)) *ptr_error = 2;
    num = c - 48;
    if ((LONG_MAX - num < summ) && (*ptr_error != 2))
      *ptr_error = 2;
    else {
      summ = summ * *power + num;
      *power = 10;
    }
  } else
    *ptr_error = 1;

  return summ;
}

const char *processing_s_specif(char *c, va_list *ap, const char *str,
                                valStruct *ptr_value) {
  int i = 0;
  while (isspace(*str)) str++;
  c = va_arg(*ap, char *);
  if (ptr_value->width != -1) {
    if (ptr_value->width != INT_MAX) {
      while (!isspace(*str) && *str != '\0' && ptr_value->width > 0) {
        *(c + i) = *str;
        i++;
        str = go_to_next_char(str, ptr_value);
      }
    } else {
      while (!isspace(*str) && *str != '\0') {
        *(c + i) = *str;
        i++;
        str++;
      }
    }
    *(c + i) = '\0';
    if (i != 0) ptr_value->result++;
  } else {
    while (!isspace(*str) && *str != '\0') {
      str++;
    }
    *(c) = '\n';
    *(c + 1) = '\0';
  }
  while (isspace(*str)) str++;
  ptr_value->procent_num--;

  return str;
}

const char *processing_p_specif(unsigned long **v_ptr, va_list *ap,
                                const char *str, valStruct *ptr_value,
                                convers_to_system fn_ptr, int *ptr_error) {
  v_ptr = NULL;
  while (isspace(*str)) str++;
  if (ptr_value->width != -1) {
    v_ptr = va_arg(*ap, unsigned long **);
    *v_ptr = (unsigned long *)write_number(&str, ptr_value, fn_ptr, ptr_error);
    ptr_value->result++;
  } else {
    ptr_value->width = INT_MAX;
    write_number(&str, ptr_value, fn_ptr, ptr_error);
  }
  ptr_value->procent_num--;

  return str;
}

void processing_n_specif(int *d, va_list *ap, valStruct *ptr_value,
                         const char *str) {
  if (ptr_value->width != -1) {
    d = va_arg(*ap, int *);
    *d = (int)(str - ptr_value->start);
  }
  ptr_value->procent_num--;
}

int check_notempty_str(const char *str) {
  int notempty = 0;
  while (*str != '\0' && !notempty) {
    if (!isspace(*str)) {
      notempty = 1;
    }
    str++;
  }

  return notempty;
}

const char *handle_specif(const char *str, va_list *ap, const char **format,
                          valStruct *ptr_value, int *ptr_error) {
  unsigned long *ul = NULL, **v = NULL;
  int *d = NULL;
  char *c = NULL;
  long *l_d = NULL;
  long double *l_f = NULL;
  get_specificator_width(format, ptr_value);
  get_specificator_length(format, ptr_value);
  if (**format == FLAG_G || **format == FLAG_g || **format == FLAG_E ||
      **format == FLAG_e || **format == FLAG_f)
    str = processing_f_specif(&l_f, ap, str, ptr_value, ptr_error);
  else if (**format == FLAG_i || **format == FLAG_d)
    str = processing_d_specif(&l_d, ap, str, ptr_value, &char_to_dec_digit,
                              ptr_error);
  else if (**format == FLAG_c)
    processing_c_specif(c, ap, &str, ptr_value, format);
  else if (**format == FLAG_u)
    str = processing_uxo_specif(&ul, ap, str, ptr_value, &char_to_dec_digit,
                                ptr_error);
  else if (**format == FLAG_o)
    str = processing_uxo_specif(&ul, ap, str, ptr_value, &char_to_oct_digit,
                                ptr_error);
  else if (**format == FLAG_x || **format == FLAG_X)
    str = processing_uxo_specif(&ul, ap, str, ptr_value, &char_to_hex_digit,
                                ptr_error);
  else if (**format == FLAG_s)
    str = processing_s_specif(c, ap, str, ptr_value);
  else if (**format == FLAG_p)
    str = processing_p_specif(v, ap, str, ptr_value, &char_to_hex_digit,
                              ptr_error);
  else if (**format == FLAG_n)
    processing_n_specif(d, ap, ptr_value, str);
  else if (**format == FLAG_percent)
    str++;
  (*format)++;
  while (isspace(**format)) (*format)++;

  return str;
}

short s21_sscanf(const char *str, const char *format, ...) {
  valStruct value = {0};
  value = value_init(value, format, str);
  if (check_notempty_str(str)) {
    int error = 0;
    va_list ap;
    va_start(ap, format);
    while (*format && value.procent_num && error != 1) {
      value = reset_value(value, &error);
      if (*format == '%') {
        str = handle_specif(str, &ap, &format, &value, &error);
      } else {
        if (*str != *format) error = 1;
        format++;
        str++;
      }
    }
    va_end(ap);
  } else if (value.procent_num != 0)
    value.result = -1;
  return value.result;
}