#include "s21_string.h"

// В "str" записывается форматированный вариант "format"

int s21_sprintf(char *str, const char *format, ...) {
  char spec[] = "cdieEfosuxXpn%";
  char *start = str;       // 1
  va_list args;            // 2
  va_start(args, format);  // 3

  while (*format) {
    if (*format == '%') {  // 4
      format += 1;
      SPECS spec1 = {0};
      spec1.syst_num = 10;
      format = set_specs(&spec1, format, &args);  // 5
      while (!s21_strchr(spec, *format)) format += 1;
      str = parser(str, start, spec1, format, &args);
    } else {  // 6
      *str = *format;
      str += 1;
    }
    format += 1;
  }
  *str = '\0';
  va_end(args);  // 7
  return (str - start);
}
// 1 - записали стартовое значения, для возможности вывода кол-ва записанных
// 2 - специальный тип данных, позволяющий обрабатывать нефексированный набор
// данных грубо говоря "va_list" - указатель на необязательный параметр
// 3 - направляет "va_list" на адрес первого необязательного параметра args -
// первый необязательный параметр format - последний обязательный параметр
// 4 - если *format = % - идём в парсер
// 5 - парс префиксов(флагов) спецификаторов
// 6 - если нет, записываем *format в поданную строку по указателю
// 7 - позволяет выйти из функции с переменным списком

const char *set_specs(SPECS *spec1, const char *format, va_list *args) {
  format = get_flags_for_specs(spec1, format);      // 1
  format = get_width(&spec1->width, format, args);  // 2
  if (*format == '.') {                             // 3
    spec1->dot = 1;
    format += 1;
    format = get_width(&spec1->accuracy, format,
                       args);  // 4
  }
  if (*format == 'l') {
    spec1->length = 'l';  // 5
  } else if (*format == 'L') {
    spec1->length = 'L';  // 6
  } else if (*format == 'h')
    spec1->length = 'h';  // 7
  if (spec1->length != 0) format += 1;

  return format;
}
// 1 - ищем/определяем флаги спецификаторов
// 2 - ищем/определяем ширину
// 3 - если увидели точку, считываем точность
// 4 - ищем/определяем точность по той же логике, что и с шириной
// 5 - флаг на переменную типа long int
// 6 - флаг на переменную типа long double
// 7 - флаг на переменную типа short int

const char *get_flags_for_specs(SPECS *spec1, const char *format) {
  while (*format) {
    if (*format == '-') {
      spec1->minus = 1;
    } else if (*format == '+') {
      spec1->plus = 1;
    } else if (*format == ' ') {
      spec1->space = 1;
    } else if (*format == '#') {
      spec1->sharp = 1;
    } else if (*format == '0') {
      spec1->zero = 1;
    } else {
      break;
    }
    format += 1;
  }
  if (spec1->space && spec1->plus) spec1->space = 0;  // 1
  if (spec1->zero && spec1->minus) spec1->zero = 0;   // 2
  return format;
}
// 1 - плюс перекрывает пробел
// 2 - минус перекрывает ноль

const char *get_width(int *width, const char *format, va_list *args) {
  if (*format == '*') {
    *width = va_arg(*args, int);  // 1
    format += 1;
  }
  while (format && *format >= '0' && *format <= '9') {
    *width *= 10;             // 2
    *width += *format - '0';  // 3
    format += 1;
  }
  return format;
}
// 1 - берёт значение из одного из необязательных параметров,
// переменную типа "int"
// 2 - перевод значения ширины на следующий знак
// 3 - переводим чаровский символ цифры в числовой, вычетая 0-ём 48
// из индекса чара

char *parser(char *str, char *start, SPECS spec1, const char *format,
             va_list *args) {  // парсинг спецификаторов

  if (*format == 'd' || *format == 'i') {  // целочисленные
    str = di_print(str, spec1, args);
  } else if (*format == 'u' || *format == 'o' || *format == 'x' ||
             *format == 'X') {  // беззнаковые
    spec1 = syst_num_check(spec1, *format);
    str = uxXo_print(str, spec1, args);
  } else if (*format == 'c') {  // чары
    int sym = va_arg(*args, int);
    str = c_print(str, spec1, sym);
  } else if (*format == 's') {  // строки
    str = s_print(str, spec1, args);
  } else if (*format == 'p') {  // указатели
    str = p_print(str, &spec1, args);
  } else if (*format == 'n') {  // 1
    int *n = va_arg(*args, int *);
    *n = (int)(str - start);  // из данного положения вычетаем начальное
  } else if (*format == 'f' || *format == 'e' || *format == 'E') {
    spec1 = options_for_double(spec1, *format);  // десятичные
    str = f_or_eg_print(str, spec1, args);
  } else if (*format == '%') {  // если "%%" записываем "%" в строку
    str = c_print(str, spec1, '%');
  } else
    str = s21_NULL;
  if (!str) *start = '\0';
  return str;
}
// 1 - определяет количество ранее успешно записанных символов

char *di_print(char *str, SPECS spec1, va_list *args) {
  long int num = 0;
  if (spec1.length == 'l') {  // 1
    num = (long int)va_arg(*args, long int);
  } else if (spec1.length == 'h') {
    num = (short)va_arg(*args, int);
  } else {
    num = (int)va_arg(*args, int);
  }
  str = work_with_line(str, spec1, num);  // 2
  return str;
}
// 1 - исход из флагов смотрим, какого типа переменную надо взять
// 2 - реализация спецификатора

char *uxXo_print(char *str, SPECS spec1, va_list *args) {
  unsigned long int num = 0;
  if (spec1.length == 'l') {  // 1
    num = (unsigned long int)va_arg(*args, unsigned long int);
  } else if (spec1.length == 'h') {
    num = (unsigned short)va_arg(*args, unsigned int);
  } else {
    num = (unsigned int)va_arg(*args, unsigned int);
  }
  str = work_with_line(str, spec1, num);  // 2
  return str;
}
// 1 - исход из флагов смотрим, какого типа переменную надо взять
// 2 - реализация спецификатора

char *p_print(char *str, SPECS *spec1, va_list *args) {
  // 1
  unsigned long int temp = (unsigned long int)va_arg(*args, unsigned long int);
  // 2
  spec1->p = 1;
  spec1->uns_int = 1;
  spec1->sharp_for_x = 1;
  spec1->syst_num = 16;
  spec1->sharp = 1;
  spec1->char_reg = 0;
  str = work_with_line(str, *spec1, temp);  // 3
  return str;
}
// 1 - берём адрес из необязательного параметра
// 2 - устанавливаем настройки для обработки адреса переменной
// 3 - реализация спецификатора

char *f_or_eg_print(char *str, SPECS spec1, va_list *args) {
  long double num = 0;
  int e_num = 0;
  if (spec1.length == 'L') {  // 1
    num = (long double)va_arg(*args, long double);
  } else {
    num = (double)va_arg(*args, double);
  }
  if (spec1.accuracy == 0 && !spec1.dot) spec1.accuracy = 6;  // 2
  if (spec1.e) {                                              // 3
    e_num = restruct(&num, &spec1);                           // 4
  }
  // выделяем память для динамического буфера под записываемое число
  s21_size_t size_dnum_buf = get_size_int_num(&spec1, num);
  char *buf_for_dnum = calloc(size_dnum_buf + MEM_BUFFER, sizeof(char));

  if (buf_for_dnum) {
    // переводим число в строку
    int i = dnum_to_string(spec1, num, buf_for_dnum, size_dnum_buf, e_num);
    // записываем число в строку и передвигаем ссылку
    str += add_buf_to_str(spec1.width, &i, buf_for_dnum, str);
    free(buf_for_dnum);
  }
  return str;
}
// 1 - исход из флагов смотрим, какого типа переменную надо взять
// 2 - если нет точки -> нет точности, стандартная точность 6
// 3 - реализация е спец.
// 4 - сокращаем число и возвращаем степень 10 по размеру сокращения

char *work_with_line(char *str, SPECS spec1, long int num) {
  // выделяем память для динамического буфера под записываемое число
  s21_size_t size_int_num_buf = get_size_int_num(&spec1, num);
  char *buf_for_num = calloc(size_int_num_buf + MEM_BUFFER, sizeof(char));

  if (buf_for_num) {
    // переводим число в строку
    int i = num_to_string(spec1, num, buf_for_num, size_int_num_buf);
    // записываем число в строку и передвигаем ссылку
    str += add_buf_to_str(spec1.width, &i, buf_for_num, str);
    free(buf_for_num);
  }
  return str;
}

int add_buf_to_str(int width, int *i, const char *buf_for_num, char *str) {
  int link_offset = 0;
  for (int j = *i - 1; j >= 0; j--) {  // 1
    *str = buf_for_num[j];
    str += 1;
    link_offset += 1;
  }
  while (*i < width) {  // 2
    *i += 1;
    *str = ' ';
    str += 1;
    link_offset += 1;  // 3
  }
  return link_offset;
}
// 1 - перезаписываем символы в правильном порядке
// 2 - добавляем пробелы справа если нужно
// 3 - на сколько передвинули ссылку

s21_size_t get_size_int_num(SPECS *spec1, long double num) {
  s21_size_t size = 0;
  long double num1 = num;
  if (num1 < 0) num1 *= -1;
  long double second_part = num1 - (long int)num1;
  if (second_part != 0 && spec1->double_check) {  // 1
    size += 1;
    second_part -= NEXT_MEMORY_CELL;  // 2
    while (second_part - (long int)second_part > 0 && size < MEMORY_CELL_SIZE) {
      size += 1;
      second_part *= 10;
    }
    if ((int)size < spec1->accuracy + 1) size = spec1->accuracy + 1;
  }
  while ((long int)num1 > 0) {  // 3
    num1 = (long int)num1 / 10;
    size += 1;
  }
  if (spec1->width > (int)size) size = spec1->width;
  if (spec1->accuracy > (int)size) size = spec1->accuracy;
  if (size == 0 && num1 == 0 && !spec1->accuracy && !spec1->width &&
      !spec1->space && !spec1->dot) {
    size += 1;
  }
  if (spec1->space || spec1->plus || num < 0) {
    if (spec1->zero && !spec1->accuracy) spec1->dop_check = 1;
    spec1->flag_to_size = 1;  // 5
    size += 1;
  }
  get_size_for_dop_flags(spec1, num1, &size);  // 6
  return size;
}
// 1 - считаем кол-во знаков дробной части числа
// 2 - отчищаем некст ячейку памяти для домножения
// 3 - считаем кол-во знаков целой части числа
// 4 - если в числе 1 цифра
// 5 - доп места для " " | "-" | "+"
// 6 - выделение места для доп флагов

void get_size_for_dop_flags(SPECS *spec1, long double num1, s21_size_t *size) {
  if (spec1->e == 1 || spec1->e == 2) {  // 1
    *size += 4;
  } else if (spec1->e == 3) {
    *size += 5;
  }
  if (spec1->sharp_for_o && spec1->sharp) {
    spec1->dop_check = 1;
  }
  if (num1 == 0 && spec1->double_check && spec1->dot && spec1->accuracy != 0)
    *size += 2;  // 2
  if (spec1->double_check && spec1->zero && (int)*size > spec1->width)
    *size = spec1->width;  // 3
}
// 1 - выделение места под "00e" | "000e" при спецификаторе е
// 2 - выделение места под "0." если десятичное число == 0
// 3 - переназначаем размер по ширине при флаге "0" у дробных

int num_to_string(SPECS spec1, long int num, char *buf_for_num,
                  s21_size_t size_int_num_buf) {
  int fl_minus = 0, i = 0, len = 0;
  if (!spec1.uns_int) {  // для "d" флага
    if (num < 0) {
      fl_minus = 1;
      num *= -1;
    }
  } else
    dop_size(&spec1);
  long int num1 = num;
  // 1 - если num = 0
  if ((num == 0 && (spec1.accuracy || (spec1.width && !spec1.dot) ||
                    (spec1.width && spec1.space))) ||
      (num == 0 && !spec1.accuracy && !spec1.width && !spec1.space &&
       !spec1.dot)) {
    if (!spec1.uns_int || spec1.u_fl ||
        (spec1.uns_int && !spec1.u_fl && !spec1.sharp)) {
      inster_cut(buf_for_num, &i, &size_int_num_buf, '0');
    }
  }
  // 2 - если num != 0
  while (num1 != 0 && buf_for_num && size_int_num_buf) {
    char sim = get_num_or_char(num1 % spec1.syst_num, spec1.char_reg);
    inster_cut(buf_for_num, &i, &size_int_num_buf, sim);
    num1 /= spec1.syst_num;  // 2
    if (spec1.uns_int && (size_int_num_buf == 0 && num1 != 0)) {
      size_int_num_buf += 1;
    }          // 3
    len += 1;  // 4
  }
  num_to_string_for_hex(spec1, num, len, &size_int_num_buf);           // 5
  post_work(spec1, num, buf_for_num, size_int_num_buf, &i, fl_minus);  // 6
  return i;
}
// 1 - буферные ячейки для o/x/X сп при флаге "#"
// 2 - переходим на следующий символ
// 3 - у беззнаковых, если при переводе в 10 систему исчисления, кол-во
// символов увеличилось - увеличиваем выделенную память
// 4 - для будущей обработки кол-ва символов беззнаковых чисел
// 5 - подготовка беззнаковых чисел к пост-обработке
// 6 - пост-обработка - печать "0" | " " и дополнительных символов

void num_to_string_for_hex(SPECS spec1, long int num, int len,
                           s21_size_t *size_int_num_buf) {
  if (spec1.sharp_for_x && *size_int_num_buf != 0) {
    *size_int_num_buf = 0;                                           // 1
    if (spec1.accuracy > spec1.width && spec1.accuracy - len > 0) {  // 2
      *size_int_num_buf = spec1.accuracy - len;
      if (spec1.dot && num == 0) *size_int_num_buf -= 1;
    } else if (spec1.width > spec1.accuracy && spec1.width - len > 0) {  // 3
      *size_int_num_buf = spec1.width - len;
      if (!spec1.dot && num == 0) *size_int_num_buf -= 1;
    }
    if (spec1.plus || spec1.space) *size_int_num_buf += 1;
    if (spec1.dot && spec1.sharp) *size_int_num_buf += 2;
  }
}
// 1 - обнуляем размер выделенной памяти, дабы избежать ошибок
// 2 - если точность больше ширины и после записи числа точность не равна нулю
// 3 - если ширина больше точночти и после записи числа ширина не равна нулю

void post_work(SPECS spec1, long double num, char *buf_for_num,
               s21_size_t size_int_num_buf, int *i, int fl_minus) {
  int fl_zero = 0;
  if (fl_minus) num *= -1;  // 1
  if (spec1.p == 1)         // 2
    spec1.zero = 0;
  if (spec1.accuracy - *i > 0) {
    spec1.accuracy -= *i;
    spec1.zero = 1;
  } else {
    fl_zero = 1;
  }
  if (spec1.sharp_for_o && spec1.sharp)  // 3
    size_int_num_buf += 1;
  if (spec1.sharp_for_x && spec1.sharp) size_int_num_buf += 2;
  if (num != NAN && num != INFINITY) {
    for_zero(spec1, buf_for_num, &size_int_num_buf, i, fl_zero);  // 4
  }
  if (!spec1.uns_int) {  // 5
    check_dopflags(buf_for_num, i, &size_int_num_buf, spec1, num);
  } else {  // 6
    print_dop_sims(buf_for_num, i, &size_int_num_buf, spec1, num);
  }
  for_space(spec1, buf_for_num, &size_int_num_buf, i, num);  // 7
}
// 1 - вернули оригинальное значение
// 2 - у поинтеров флаг ноль не работает
// 3 - добавляем беззнаковым место на "0" | "0x" | "0X"
// 4 - печать "0" слева от числа
// 5 - печать доп символов для чисел со знаком
// 6 - печать доп символов для беззнаковых чисел
// 7 - печать пробелов слева

void for_zero(SPECS spec1, char *buf_for_num, s21_size_t *size_int_num_buf,
              int *i, int fl_zero) {
  int flag = 0;
  //если нет места под 0, но флаг zero поднят
  if (*size_int_num_buf == 1 && spec1.zero == 1 && spec1.flag_to_size == 1)
    spec1.zero = 0;
  if (spec1.zero && !spec1.double_check) {  // 1
    while (buf_for_num &&
           (*size_int_num_buf - spec1.flag_to_size - spec1.dop_check > 0) &&
           (spec1.accuracy || fl_zero) && !flag) {
      if (*size_int_num_buf == 1 && spec1.flag_to_size == 1)  // 2
        flag = 1;
      inster_cut(buf_for_num, i, size_int_num_buf, '0');
      spec1.accuracy -= 1;
    }
  } else if (*size_int_num_buf > 0 && spec1.zero) {  // 3
    while ((*size_int_num_buf - spec1.flag_to_size > 0) && buf_for_num &&
           (spec1.width - *i > 0)) {
      inster_cut(buf_for_num, i, size_int_num_buf, '0');
    }
  }
}
// 1 - печать нулей для целочисленных
// 2 - оставить место для доп знаков
// 3 - печать нулей для дробных

void for_space(SPECS spec1, char *buf_for_num, s21_size_t *size_int_num_buf,
               int *i, long int num) {
  if ((*size_int_num_buf > 0 && !spec1.minus && !spec1.double_check) &&
      (!spec1.p && (!spec1.plus || !spec1.space || num != 0))) {  // 1
    while ((*size_int_num_buf - spec1.flag_to_size > 0) && buf_for_num) {
      inster_cut(buf_for_num, i, size_int_num_buf, ' ');
    }
  } else if (*size_int_num_buf > 0 && !spec1.minus) {  // 2
    while ((*size_int_num_buf - spec1.flag_to_size > 0) && buf_for_num &&
           (spec1.width - *i > 0)) {
      inster_cut(buf_for_num, i, size_int_num_buf, ' ');
    }
  }
}
// 1 - печать пробелов для целочисленных
// 2 - печать пробелов для дробных

int dnum_to_string(SPECS spec1, long double num, char *buf_for_dnum,
                   s21_size_t size_dnum_buf, int e_num) {
  int i = nan_inf_check(buf_for_dnum, num, spec1);  // 1
  int flag = 0;
  if (!i) {
    if (spec1.e)  // 2
      e_print(spec1, buf_for_dnum, &size_dnum_buf, e_num, &i);
    if (num < 0) {
      flag = 1;
      num *= -1;
    }
    if (num != 0) {  // 3
      frac_work(spec1, buf_for_dnum, &size_dnum_buf, num, &i);
    } else {                 // 4
      if (spec1.accuracy) {  // 5
        while (spec1.accuracy > 0) {
          inster_cut(buf_for_dnum, &i, &size_dnum_buf, '0');
          spec1.accuracy -= 1;
        }
        inster_cut(buf_for_dnum, &i, &size_dnum_buf, '.');
      }
      inster_cut(buf_for_dnum, &i, &size_dnum_buf, '0');
    }
  }
  post_work(spec1, num, buf_for_dnum, size_dnum_buf, &i, flag);  // 6
  return i;
}
// 1 - проверка на поданное число, если "не инфинити и не нан"
// 2 - записываем "e" с вычесленной степенью
// 3 - запись самого числа, если оно не "0"
// 4 - запись самого числа, если оно "0"
// 5 - если есть точность, пишем доп нули
// 6 - пост-обработка - печать "0" | " " и дополнительных символов

void frac_work(SPECS spec1, char *buf_for_num, s21_size_t *size_dnum_buf,
               long double num, int *i) {
  int sec_fl = 0;
  // 1
  long double first_part = (long int)num;
  long double second_part = num - first_part;
  int accur = spec1.accuracy;
  int cop_sec_p = second_part;
  int z = 0;
  while (z < MEMORY_CELL_SIZE && (long)cop_sec_p != 0) {
    cop_sec_p *= 10;
    z += 1;
  }
  if (second_part >= 0.95 && dnum_sec_p_round(second_part, spec1) < 0)
    sec_fl = 1;  // 3
  if (accur != 0 && !sec_fl) {
    while (accur > 0) {  // 4
      second_part *= 10;
      accur -= 1;
    }
  } else if ((spec1.dot && accur == 0) || sec_fl) {  // 5
    second_part = 0;
    first_part += 1;
  }
  if ((second_part * 10) >= 4.5) {  // 6
    second_part = roundl(second_part);
  } else {
    second_part = (long int)second_part;
  }
  decm_print(spec1, buf_for_num, size_dnum_buf, i, first_part,
             second_part);  // 7
}
// 1 - делим на дробную и целую часть
// 2 - сокращаем лишние нули (дальше 15 след яч памяти)
// 3 - смотрим нужно ли сокращать или обрезать число типа 0.9999
// если точность больше дробной части - не сокращаем
// 4 - переводим дробную часть в целую, для возможности деления с остатком
// 5 - сокращаем дробную часть у чисел типа 0.9999 если нужно
// 6 - сокращаем дробную или обрезаем дробную часть у иных вариантов чисел
// от 5 сокращается в +, менее в -
// 7 - записываем десятичное число в буфер

int dnum_sec_p_round(long double second_part, SPECS spec1) {
  int size = 0;
  second_part -= NEXT_MEMORY_CELL;
  while (second_part - (long int)second_part > 0.1 &&
         size != MEMORY_CELL_SIZE) {  // 1
    size += 1;
    second_part *= 10;
  }
  size = spec1.accuracy - size;  // 2
  return size;
}
// 1 - считаем кол-во знаков дробной части
// 2 - возвращаем разницу кол-ва и точности

void decm_print(SPECS spec1, char *buf_for_num, s21_size_t *size_dnum_buf,
                int *i, long int first_part, long int second_part) {
  long int copi_fr = first_part, copi_sec = second_part;
  // 1
  if (copi_sec != 0) {
    while (copi_sec != 0) {
      inster_cut(buf_for_num, i, size_dnum_buf,
                 get_num_or_char(copi_sec % spec1.syst_num, spec1.char_reg));
      copi_sec /= 10;
    }
    inster_cut(buf_for_num, i, size_dnum_buf, '.');
  } else if ((spec1.dot && spec1.sharp) ||  // 2
             (spec1.length == 'L' && spec1.accuracy != 0)) {
    while (spec1.accuracy != 0) {  // записываем число пока 0
      inster_cut(buf_for_num, i, size_dnum_buf, '0');
      spec1.accuracy -= 1;
    }
    inster_cut(buf_for_num, i, size_dnum_buf, '.');
  }
  // 3
  while (copi_fr != 0) {  // записываем число пока 0
    inster_cut(buf_for_num, i, size_dnum_buf,
               get_num_or_char(copi_fr % spec1.syst_num, spec1.char_reg));
    copi_fr /= 10;
  }
}
// 1 - запись дробной части
// 2 - записываем нулевую дробную часть, если ....
// 3 - записываем целую часть

void e_print(SPECS spec1, char *buf_for_num, s21_size_t *size_dnum_buf,
             int e_num, int *i) {
  int copi_e = e_num;
  if (copi_e == 0) {
    inster_cut(buf_for_num, i, size_dnum_buf,
               get_num_or_char(copi_e % spec1.syst_num, spec1.char_reg));
  }
  while (copi_e != 0) {
    inster_cut(buf_for_num, i, size_dnum_buf,
               get_num_or_char(copi_e % spec1.syst_num, spec1.char_reg));
    copi_e /= 10;
  }
  if (e_num < 10) {  // 1
    inster_cut(buf_for_num, i, size_dnum_buf, '0');
  }
  if (spec1.e == 2 || e_num == 0) {
    inster_cut(buf_for_num, i, size_dnum_buf, '+');
  } else {
    inster_cut(buf_for_num, i, size_dnum_buf, '-');
  }
  if (spec1.char_reg) {
    inster_cut(buf_for_num, i, size_dnum_buf, 'E');
  } else {
    inster_cut(buf_for_num, i, size_dnum_buf, 'e');
  }
}
// 1 - если 0 < "e" < 10 записывается дополнительный 0 перед числом
// 2 - знак степени "e" контролируется величиной параметра структуры "e"

char get_num_or_char(int num, int char_reg) {
  char flag = 0;
  switch (num) {  // 1
    case 10:
      flag = (char)('a' - char_reg * 32);
      break;
    case 11:
      flag = (char)('b' - char_reg * 32);
      break;
    case 12:
      flag = (char)('c' - char_reg * 32);
      break;
    case 13:
      flag = (char)('d' - char_reg * 32);
      break;
    case 14:
      flag = (char)('e' - char_reg * 32);
      break;
    case 15:
      flag = (char)('f' - char_reg * 32);
      break;
  }
  if (num >= 0 && num <= 9)   // 2
    flag = (char)(num + 48);  // 3
  return flag;
}
// 1 - для 16-ти ричной системы исчесления
// 2 - для 10-ти и 8-и ричной
// 3 - получаем из чара число

void inster_cut(char *buf_for_num, int *i, s21_size_t *size_num_buf, char sim) {
  buf_for_num[*i] = sim;  // 1
  *i += 1;                // 2
  *size_num_buf -= 1;     // 3
}
// 1 - вставляем символ в буферную строку
// 2 - перемещаем индекс
// 3 - уменьшаем объём выделенных ячеек

void check_dopflags(char *buf_for_num, int *i, s21_size_t *size_int_num_buf,
                    SPECS spec1, long double num) {
  //по флагам "+" "-" " "
  if (spec1.space && num >= 0 && size_int_num_buf) {
    inster_cut(buf_for_num, i, size_int_num_buf, ' ');
  }
  if (num < 0 && size_int_num_buf && num != NAN && num != INFINITY) {
    inster_cut(buf_for_num, i, size_int_num_buf, '-');
  }
  if (spec1.plus && num >= 0 && size_int_num_buf) {
    inster_cut(buf_for_num, i, size_int_num_buf, '+');
  }
}

SPECS syst_num_check(SPECS spec1, char format) {
  spec1.uns_int = 1;
  if (format == 'o') {  // 1
    spec1.syst_num = 8;
    spec1.sharp_for_o = 1;
  } else if (format == 'x' || format == 'X') {
    spec1.syst_num = 16;
    spec1.sharp_for_x = 1;
  } else if (format == 'u') {
    spec1.u_fl = 1;
  }
  if (format == 'X') spec1.char_reg = 1;

  return spec1;
}
// 1 - определяем систему счисления по спец. для дальнейшего делени на
// определённый коэффициент

void dop_size(SPECS *spec1) {
  if (spec1->uns_int && (spec1->sharp && spec1->syst_num == 8)) {  // 1
    spec1->flag_to_size = 1;
  } else if (spec1->uns_int && (spec1->sharp && spec1->syst_num == 16)) {
    spec1->flag_to_size = 2;
  }
}
// 1 - выделение доп места для "0" | "0x|X" у беззнаковых

void print_dop_sims(char *buf_for_num, int *i, s21_size_t *size_int_num_buf,
                    SPECS spec1, long int num) {
  if (spec1.sharp && spec1.syst_num == 8) {  // 1
    inster_cut(buf_for_num, i, size_int_num_buf, '0');
  } else if (spec1.sharp && spec1.syst_num == 16 && spec1.char_reg) {
    if (spec1.p || num != 0) {
      inster_cut(buf_for_num, i, size_int_num_buf, 'X');
    } else {
      size_int_num_buf -= 1;
    }
    inster_cut(buf_for_num, i, size_int_num_buf, '0');
  } else if (spec1.sharp && spec1.syst_num == 16 && !spec1.char_reg) {
    if (spec1.p || num != 0) {
      inster_cut(buf_for_num, i, size_int_num_buf, 'x');
    } else {
      size_int_num_buf -= 1;
    }
    inster_cut(buf_for_num, i, size_int_num_buf, '0');
  }
}
// 1 - запись доп символов "0" | "0x|X" у беззнаковых

char *c_print(char *str, SPECS spec1, int sym) {  // 1
  char *buf = s21_NULL;
  if (!spec1.minus) {  // 2
    while (spec1.width - 1 > 0) {
      if (spec1.zero) {
        *str = '0';
      } else {
        *str = ' ';
      }
      str += 1;
      spec1.width -= 1;
    }
  }
  *str = sym;  // 3
  str += 1;
  if (spec1.minus) {  // 4
    while (spec1.width - 1 > 0) {
      *str = ' ';
      str += 1;
      spec1.width -= 1;
    }
  }
  buf = str;
  return buf;
}
// 1 - обработка и запись чаров
// 2 - запись доп знаков справа
// 3 - запись самого символа
// 4 - запись доп знаков слева

char *s_print(char *str, SPECS spec1, va_list *args) {  // 1
  char *buf = str;
  char *main_str = va_arg(*args, char *);  // 2
  if (main_str) {
    int s_len = spec1.width, spaces = 0;
    if ((s21_size_t)spec1.width < s21_strlen(main_str) && !spec1.dot) {  // 3
      spec1.width = s21_strlen(main_str);
      spaces = spec1.width - s21_strlen(main_str);  // 4
    } else if ((s21_size_t)spec1.width >= s21_strlen(main_str)) {
      spaces = spec1.width - s21_strlen(main_str);
    } else
      spaces = spec1.width;
    if (!spec1.dot && spec1.accuracy == 0) spec1.accuracy = spec1.width;
    if (spec1.accuracy != 0 && spec1.accuracy < s_len) {
      spaces = s_len - spec1.accuracy;
    }  // 5
    while (spaces && !spec1.minus) {
      if (spec1.zero) {
        *str = '0';
      } else {
        *str = ' ';
      }
      str += 1;
      spaces -= 1;
    }  // 6
    while (*main_str != '\0' && spec1.accuracy != 0) {
      *str = *main_str;
      str += 1;
      main_str += 1;
      spec1.accuracy -= 1;
    }  // 7
    while (spaces && spec1.minus) {
      *str = ' ';
      str += 1;
      spaces -= 1;
    }  // 8
  } else {
    str = non_str(str, spec1);  // 9
  }
  if (buf) buf = str;
  return buf;
}
// 1 - обработка и запись строк
// 2 - считали ссылку на строку
// 3 - ширина < длинны строки, то ширина равна длинне строки
// 4 - кол-во " " - "ширина - длинна строки"
// 5 - если точность меньше ширины - печатаем пробелы по точности
// 6 - если флага минус нет - доп пробелы слева
// 7 - печать самой строки
// 8 - если флаг минус есть - доп пробелы справа
// 9 - не удалось считать строку

char *non_str(char *str, SPECS spec1) {  // 1
  char Nul[] = "(null)";
  if (!spec1.dot)  // 2
    spec1.accuracy = s21_strlen(Nul);
  int space = spec1.width - spec1.accuracy;
  if ((spec1.accuracy && !spec1.space && spec1.dot) || (!spec1.dot)) {
    for (int i = 0; i < space; i++) {  // 3
      *str = ' ';
      str += 1;
    }
    if ((s21_size_t)spec1.accuracy > s21_strlen(Nul))
      spec1.accuracy = s21_strlen(Nul);
    for (int i = 0; i < spec1.accuracy; i++) {
      *str = Nul[i];
      str += 1;
    }
  } else if (!spec1.space) {
    for (int i = 0; i < space; i++) {
      *str = ' ';
      str += 1;
    }
  } else if (!spec1.dot) {
    *str = ' ';
    str += 1;
  }
  return str;
}
// 1 - обработка случая, если строка не считалась
// 2 - если нет флага "." или есть ".", но нет " " - печатаем "(null)"
// иначе печатаем " "
// 3 - печать пробелов слева

SPECS options_for_double(SPECS spec1, char format) {  // 1
  spec1.double_check = 1;
  if (format == 'g' || format == 'G') {
    spec1.g = 1;
  } else if (format == 'e' || format == 'E') {
    spec1.e = 1;
  }
  if (format == 'G' || format == 'E') spec1.char_reg = 1;
  return spec1;
}
// 1 - установка флагов для обработки десятичных чисел

long double restruct(long double *num, SPECS *spec1) {  // 1
  int i = 0;
  if (*num != NAN && *num != INFINITY) {
    if (fabsl(*num) > 1) {
      while (fabsl(*num) > 10) {  // 12345 -> 1.2345e+04
        *num /= 10;
        i++;
        spec1->e = 2;  // 2
      }
    } else if (fabsl(*num) < 1) {
      while (fabsl(*num) < ALMOST_ONE && *num != 0) {  // 0,12345 -> 1.2345e-01
        *num *= 10;
        i++;
        spec1->e = 1;  // 3
      }
    } else {
      spec1->e = 2;
    }
    if (i > 100) {  // 4
      spec1->e = 3;
    }
  }
  return i;  // 5
}
// 1 - приведение числа к виду экспоненциальной записи
// 2 - значит, что число больше 1 -> положительная степень
// 3 - значит, что число меньше 1 -> отрицательная степень
// 4 - для выделения доп ячеек памяти
// 5 - возвращаемая i - это степень, на которую было произведено сокращение

int nan_inf_check(char *buf_for_dnum, long double num, SPECS spec1) {  // 1
  int i = 0;
  char *nan1 = "nan", *nan2 = "NAN", *inf1 = "fni", *inf2 = "FNI";
  for (int j = 0; j < 4; j++) {
  }
  if (isnan(num) != 0) {  // 2
    while (nan1[i] != '\0') {
      if (!spec1.char_reg) {
        buf_for_dnum[i] = nan1[i];
      } else {
        buf_for_dnum[i] = nan2[i];
      }
      i += 1;
    }
  } else if (isinf(num) != 0) {  // 3
    while (inf1[i] != '\0') {
      if (!spec1.char_reg) {
        buf_for_dnum[i] = inf1[i];
      } else {
        buf_for_dnum[i] = inf2[i];
      }
      i += 1;
    }
  }
  return i;
}
// 1 - проверка поданных десятичных чисел на "nan" и "inf"
// 2 - если i = NAN - записать nan
// 3 - если i = INFINITY - записать inf