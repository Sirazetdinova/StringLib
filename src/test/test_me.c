#include "test_me.h"

int main(void) {
  int failed = 0;
  Suite *s21_string_test[] = {
      test_memchr(),  //   - структура, содержащая в себе все созданные тесты
      test_memcmp(),
      test_memcpy(),
      test_memset(),
      test_strncat(),
      test_strchr(),
      test_strncmp(),
      test_strncpy(),
      test_strcspn(),
      test_strlen(),
      test_strpbrk(),
      test_strrchr(),
      test_sprintf_c(),
      test_strstr(),
      test_strtok(),
      test_strerror(),
      test_sprintf_octal(),
      test_sprintf_percent(),
      test_sprintf_n(),
      test_sprintf_string(),
      test_sprintf_unsigned(),
      test_sprintf_HEX(),
      test_sprintf_hex(),
      test_sprintf_pointer(),
      test_sprintf_signed(),
      test_sprintf_signed_i(),
      test_sprintf_f1(),
      test_sprintf_f2(),
      test_sprintf_f3(),
      test_sprintf_f4(),
      test_sscanf_empty(),
      test_sscanf_c(),
      test_sscanf_d(),
      test_sscanf_i(),
      test_sscanf_o(),
      test_sscanf_x(),
      test_sscanf_p(),
      test_sscanf_u(),
      test_sscanf_real(),
      test_sscanf_n(),
      test_to_upper(),
      test_to_lower(),
      test_insert(),
      test_trim(),
      test_sprintf_e(),
      NULL};

  for (int i = 0; s21_string_test[i] != NULL; i++) {  // (&& failed == 0)
    SRunner *sr = srunner_create(
        s21_string_test[i]);  //   - передаём указатель на массив тестов

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);  //   - запускаем тесты

    failed +=
        srunner_ntests_failed(sr);  //   - в переменную "failed" записываем
                                    //   количество неудачных тестов
    srunner_free(sr);  //   - освобождаем память
  }
  printf("========= FAILED: %d =========\n",
         failed);  //   - выводим количество тестов

  return 0 /* failed == 0 ? 0 : 1 */;
}