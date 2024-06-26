#include "test_me.h"

START_TEST(sscanf_spec_u_1) {
  char format[] = "%lu %hu";
  char str[] = "123123123 123123123123";
  unsigned int n1 = 0, n2 = 0;
  unsigned long m1 = 0, m2 = 0;

  int16_t res1 = s21_sscanf(str, format, &m1, &n1);
  int16_t res2 = sscanf(str, format, &m2, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(n1, n2);
  ck_assert_uint_eq(m1, m2);
}
END_TEST

START_TEST(sscanf_spec_u_2) {
  char format[] = "%lu %1hu";
  char str[] = "-123123123 +123123123123";
  unsigned int n1 = 0, n2 = 0;
  unsigned long m1 = 0, m2 = 0;

  int16_t res1 = s21_sscanf(str, format, &m1, &n1);
  int16_t res2 = sscanf(str, format, &m2, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(n1, n2);
  ck_assert_uint_eq(m1, m2);
}
END_TEST

Suite *test_sscanf_u(void) {
  Suite *s = suite_create("\033[45m-=S21_SSCANF_U=-\033[0m");
  TCase *tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, sscanf_spec_u_1);
  tcase_add_test(tc, sscanf_spec_u_2);

  suite_add_tcase(s, tc);
  return s;
}
