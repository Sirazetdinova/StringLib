#ifndef S21_STRING
#define S21_STRING

#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define s21_NULL ((void *)0)
#define MEM_BUFFER 10
#define MEMORY_CELL_SIZE 15
#define NEXT_MEMORY_CELL 0.00000000000000999999
#define ALMOST_ONE 0.999999

typedef struct {
  int minus;
  int plus;
  int space;
  int sharp;
  int zero;
  int width;
  int accuracy;
  char length;
  int syst_num;
  int flag_to_size;
  int dot;
  int char_reg;
  int g;
  int e;
  int p;
  int uns_int;
  int u_fl;
  int sharp_for_o;
  int sharp_for_x;
  int double_check;
  int dop_check;
} SPECS;

enum Flags {
  FLAG_c = (int)'c',
  FLAG_d = (int)'d',
  FLAG_i = (int)'i',
  FLAG_e = (int)'e',
  FLAG_E = (int)'E',
  FLAG_f = (int)'f',
  FLAG_g = (int)'g',
  FLAG_G = (int)'G',
  FLAG_o = (int)'o',
  FLAG_s = (int)'s',
  FLAG_u = (int)'u',
  FLAG_x = (int)'x',
  FLAG_X = (int)'X',
  FLAG_p = (int)'p',
  FLAG_n = (int)'n',
  FLAG_percent = (int)'%'
};

typedef struct {
  int width;
  int length;
  const char *start;
  int procent_num;
  short result;

} valStruct;

typedef long (*convers_to_system)(const char c, long summ, int *power,
                                  int *error);

typedef long unsigned s21_size_t;

char *s21_strerror(int errnum);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
s21_size_t s21_strlen(const char *str);
int is_delim(char c, const char *delim);
char *s21_strchr(const char *str, int c);
char *s21_strrchr(const char *str, int c);
void *s21_memset(void *str, int c, size_t n);
char *s21_strtok(char *str, const char *delim);
int s21_sprintf(char *str, const char *format, ...);
char *s21_strpbrk(const char *str1, const char *str2);
void *s21_memchr(const void *str, int c, s21_size_t n);
void *s21_trim(const char *src, const char *trim_chars);
char *s21_strncpy(char *dest, const char *src, size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
void *s21_insert(const char *src, const char *str, size_t start_index);

void dop_size(SPECS *spec1);
char *non_str(char *str, SPECS spec1);
char get_num_or_char(int num, int char_reg);
char *c_print(char *str, SPECS spec1, int sym);
SPECS syst_num_check(SPECS spec1, char format);
SPECS options_for_double(SPECS spec1, char format);
int s21_sprintf(char *str, const char *format, ...);
char *s_print(char *str, SPECS spec1, va_list *args);
long double restruct(long double *num, SPECS *spec1);
char *p_print(char *str, SPECS *spec1, va_list *args);
char *di_print(char *str, SPECS spec1, va_list *args);
char *uxXo_print(char *str, SPECS spec1, va_list *args);
int dnum_sec_p_round(long double second_part, SPECS spec1);
s21_size_t get_size_int_num(SPECS *spec1, long double num);
char *work_with_line(char *str, SPECS spec1, long int num);
char *f_or_eg_print(char *str, SPECS spec1, va_list *args);
int nan_inf_check(char *buf_for_dnum, long double num, SPECS spec1);
const char *get_flags_for_specs(SPECS *spec1, const char *format);
int add_buf_to_str(int width, int *i, const char *buf_for_num, char *str);
const char *get_width(int *width, const char *format, va_list *args);
const char *set_specs(SPECS *spec1, const char *format, va_list *args);
void get_size_for_dop_flags(SPECS *spec1, long double num1, s21_size_t *size);
void inster_cut(char *buf_for_num, int *i, s21_size_t *size_num_buf, char sim);
char *parser(char *str, char *start, SPECS spec1, const char *format,
             va_list *args);
void e_print(SPECS spec1, char *buf_for_num, s21_size_t *size_dnum_buf,
             int e_num, int *i);
void frac_work(SPECS spec1, char *buf_for_num, s21_size_t *size_dnum_buf,
               long double num, int *i);
void for_zero(SPECS spec1, char *buf_for_num, s21_size_t *size_int_num_buf,
              int *i, int fl_zero);
void for_space(SPECS spec1, char *buf_for_num, s21_size_t *size_int_num_buf,
               int *i, long int num);
int num_to_string(SPECS spec1, long int num, char *buf_for_num,
                  s21_size_t size_int_num_buf);
void print_dop_sims(char *buf_for_num, int *i, s21_size_t *size_int_num_buf,
                    SPECS spec1, long int num);
void check_dopflags(char *buf_for_num, int *i, s21_size_t *size_int_num_buf,
                    SPECS spec1, long double num);
void num_to_string_for_hex(SPECS spec1, long int num, int len,
                           s21_size_t *size_int_num_buf);
int dnum_to_string(SPECS spec1, long double num, char *buf_for_dnum,
                   s21_size_t size_dnum_buf, int e_num);
void post_work(SPECS spec1, long double num, char *buf_for_num,
               s21_size_t size_int_num_buf, int *i, int fl_minus);
void decm_print(SPECS spec1, char *buf_for_num, s21_size_t *size_dnum_buf,
                int *i, long int first_part, long int second_part);

int is_octal(int c);
int is_plus_minus(char ch);
int detekt_inf(const char **str);
int detekt_nan(const char **str);
int handle_format(const char *format);
int is_sign_of_real_number(const char **str);
int check_notempty_str(const char *str);
valStruct reset_value(valStruct end, int *ptr_error);
void get_specificator_width(const char **format, valStruct *ptr_value);
void get_specificator_length(const char **format, valStruct *ptr_value);
const char *go_to_next_char(const char *str, valStruct *ptr_value);
short s21_sscanf(const char *str, const char *format, ...);
void is_hexadecimal_notation(const char **str, valStruct *ptr_value);
long char_to_oct_digit(const char c, long summ, int *power, int *ptr_error);
long char_to_hex_digit(const char c, long summ, int *power, int *ptr_error);
long char_to_dec_digit(const char c, long summ, int *power, int *ptr_error);
void processing_n_specif(int *d, va_list *ap, valStruct *ptr_value,
                         const char *str);
long double change_order_of_magnitude(long double summ, int degeree,
                                      int minus_flag);
long double set_inf(const char **str, long double summ, valStruct *value,
                    int *ptr_error);
long double set_nan(const char **str, long double summ, valStruct *value,
                    int *ptr_error);
long double add_integer_of_real(const char **str, long double summ,
                                int *ptr_power, valStruct *ptr_value);
long double write_real_number(const char **str, valStruct *ptr_value,
                              int *ptr_error);
valStruct value_init(valStruct nachalo, const char *format, const char *str);
const char *processing_s_specif(char *c, va_list *ap, const char *str,
                                valStruct *ptr_value);
const char *handle_plus_minus(const char *str, valStruct *ptr_value,
                              int *ptr_error, int *ptr_minus_flag);
long double handle_e_notation(long double summ, const char **str,
                              valStruct *ptr_value, int *ptr_error);
long write_number(const char **str, valStruct *ptr_value,
                  convers_to_system fn_ptr, int *ptr_error);
void processing_c_specif(char *c, va_list *ap, const char **str,
                         valStruct *ptr_value, const char **format);
long double add_fraction_of_real(const char **str, long double summ,
                                 valStruct *ptr_value, int *power);
const char *processing_f_specif(long double **f, va_list *ap, const char *str,
                                valStruct *ptr_value, int *ptr_error);
const char *handle_specif(const char *str, va_list *ap, const char **format,
                          valStruct *ptr_value, int *ptr_error);
const char *processing_d_specif(long **d, va_list *ap, const char *str,
                                valStruct *ptr_value, convers_to_system fn_ptr,
                                int *ptr_error);
const char *processing_p_specif(unsigned long **v_ptr, va_list *ap,
                                const char *str, valStruct *ptr_value,
                                convers_to_system fn_ptr, int *ptr_error);
const char *processing_uxo_specif(unsigned long **ul, va_list *ap,
                                  const char *str, valStruct *ptr_value,
                                  convers_to_system fn_ptr, int *ptr_error);

#endif