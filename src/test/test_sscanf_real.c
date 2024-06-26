#include "test_me.h"

START_TEST(sscanf_spec_real_1) {
  char format[] = "%lf %lf %lf";
  char str[] = "123 +198 -87";
  double d1, d2;
  double q1, q2;
  double z1 = 0, z2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(d1, d2);
  ck_assert_double_eq(q1, q2);
  ck_assert_double_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_real_2) {
  char format[] = "%lfg %lf w%lfx";
  char str[] = "75g +19.8w -87.x";
  double d1, d2;
  double q1, q2;
  double z1 = 0, z2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(d1, d2);
  ck_assert_double_eq(q1, q2);
  ck_assert_double_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_real_3) {
  char format[] = "%lf %lf %lf %lf";
  char str[] = "NAN nan -INF +inf";
  double d1, d2;
  double q1, q2;
  double z1, z2;
  double w1, w2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_nan(d1);
  ck_assert_double_nan(d2);
  ck_assert_double_nan(q1);
  ck_assert_double_nan(q2);
  ck_assert_double_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_real_4) {
  char format[] = "%lf";
  char str[] = "Nap";
  double d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_real_5) {
  char format[] = "%lf";
  char str[] = "Np";
  double d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_real_6) {
  char format[] = "%lf";
  char str[] = "iNd";
  double d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_real_7) {
  char format[] = "%lf";
  char str[] = "id";
  double d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1);
  int16_t res2 = sscanf(str, format, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_real_8) {
  char format[] = "%lf %lf %lf %lf";
  char str[] = "34.56e3 83.2e-4 .43e+1 +2.43e3";
  double d1, d2;
  double q1, q2;
  double z1, z2;
  double w1, w2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(d1, d2);
  ck_assert_double_eq(q1, q2);
  ck_assert_double_eq(z1, z2);
  ck_assert_double_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_real_9) {
  char format[] = "%1lf %1lf %2lf %1lf";
  char str[] = "34.5+6e3 83.2e-4 .43e+1 +2.43e3";
  double d1, d2;
  double q1, q2;
  double z1, z2;
  double w1 = 0, w2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_double_eq(d1, d2);
  ck_assert_double_eq(q1, q2);
  ck_assert_double_eq(z1, z2);
  ck_assert_double_eq(w1, w2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_spec_real_10) {
  char format[] = "%*lf %7lf %*lf %*lf";
  char str[] = "34.5+6e3 83.2e-4 +43e+1 +2.43e3";
  double d1, d2;
  double q1 = 0, q2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1);
  int16_t res2 = sscanf(str, format, &d2, &q2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(d1, d2);
  ck_assert_double_eq(q1, q2);
}
END_TEST

START_TEST(sscanf_spec_real_11) {
  char format[] = "%lfr %7lf p";
  char str[] = "34.5r 83.2ep4";
  double d1, d2;
  double q1 = 0, q2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1);
  int16_t res2 = sscanf(str, format, &d2, &q2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(d1, d2);
  ck_assert_double_eq(q1, q2);
}
END_TEST

START_TEST(sscanf_spec_real_12) {
  char format[] = "%1lf %1lf %1lf %1lf";
  char str[] = "34 32. +45.e +23E3 -0.3e4";
  double d1, d2;
  double q1 = 0, q2 = 0;
  double z1 = 0, z2 = 0;
  double w1 = 0, w2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(d1, d2);
  ck_assert_double_eq(q1, q2);
  ck_assert_double_eq(z1, z2);
  ck_assert_double_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_real_13) {
  char format[] = "%2lf %2lf %2lf %2lf";
  char str[] = "34 3. +45.e +23E3 -0.3e4";
  double d1, d2;
  double q1 = 0, q2 = 0;
  double z1 = 0, z2 = 0;
  double w1 = 0, w2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(d1, d2);
  ck_assert_double_eq(q1, q2);
  ck_assert_double_eq(z1, z2);
  ck_assert_double_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_real_14) {
  char format[] = "%3lf %3lf %4lf %3lf";
  char str[] = "34 3. +45.e +23E3 -0.3e4";
  double d1, d2;
  double q1 = 0, q2 = 0;
  double z1 = 0, z2 = 0;
  double w1 = 0, w2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_double_eq(d1, d2);
  ck_assert_double_eq(q1, q2);
  ck_assert_double_eq(z1, z2);
  ck_assert_double_eq(w1, w2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_spec_real_15) {
  char format[] = "%4lf %4lf %4lf %4lf";
  char str[] = "34 3. +45.e +23E3 -0.3e4";
  double d1, d2;
  double q1 = 0, q2 = 0;
  double z1 = 0, z2 = 0;
  double w1 = 0, w2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_double_eq(d1, d2);
  ck_assert_double_eq(q1, q2);
  ck_assert_double_eq(z1, z2);
  ck_assert_double_eq(w1, w2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_spec_real_16) {
  char format[] = "%Lf %Lf %Lf %Lf";
  char str[] = "3410001.11150099 +45.e +23.123123123123123E3 -0.3e4";
  long double d1 = 0, d2 = 0;
  long double q1 = 0, q2 = 0;
  long double z1 = 0, z2 = 0;
  long double w1 = 0, w2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_ldouble_eq(d1, d2);
  ck_assert_ldouble_eq(q1, q2);
  ck_assert_ldouble_eq(z1, z2);
  ck_assert_ldouble_eq(w1, w2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_spec_real_17) {
  char format[] = "%15Lf %1Lf %*Lf %Lf";
  char str[] = "34100101001.0000009999 +45.e +23.123123123123123E3 -0.3e4";
  long double d1 = 0, d2 = 0;
  long double q1 = 0, q2 = 0;
  long double z1 = 0, z2 = 0;
  long double w1 = 0, w2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_ldouble_eq(d1, d2);
  ck_assert_ldouble_eq(q1, q2);
  ck_assert_ldouble_eq(z1, z2);
  ck_assert_ldouble_eq(w1, w2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_spec_real_18) {
  char format[] = "%lf %lfx %2lf1 %2lfx %*lf %*lf";
  char str[] = "1.1 2.x 1.1 2.x 1.1 2.x";
  double d1, d2;
  double q1 = 0, q2 = 0;
  double z1 = 0, z2 = 0;
  double w1 = 0, w2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(d1, d2);
  ck_assert_double_eq(q1, q2);
  ck_assert_double_eq(z1, z2);
  ck_assert_double_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_real_19) {
  char format[] = "%lf %4lf %5lfq %6lf %*lf q%*lf";
  char str[] = "1.3e1 1.4eq2 1.3e1q 1.4 1.3eq 1.4e2";
  double d1, d2;
  double q1 = 0, q2 = 0;
  double z1 = 0, z2 = 0;
  double w1 = 0, w2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(d1, d2);
  ck_assert_double_eq(q1, q2);
  ck_assert_double_eq(z1, z2);
  ck_assert_double_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_real_20) {
  char format[] = "%*Lf %4Lf %1Lf %2Lf";
  char str[] = "NaN -inf nan inf";
  long double d1 = 0, d2 = 0;
  long double q1 = 0, q2 = 0;
  long double z1 = 0, z2 = 0;
  long double w1 = 0, w2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_ldouble_eq(d1, d2);
  ck_assert_ldouble_eq(q1, q2);
  ck_assert_ldouble_eq(z1, z2);
  ck_assert_ldouble_eq(w1, w2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

Suite *test_sscanf_real(void) {
  Suite *s = suite_create("\033[45m-=S21_SSCANF_REAL=-\033[0m");
  TCase *tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, sscanf_spec_real_1);
  tcase_add_test(tc, sscanf_spec_real_2);
  tcase_add_test(tc, sscanf_spec_real_3);
  tcase_add_test(tc, sscanf_spec_real_4);
  tcase_add_test(tc, sscanf_spec_real_5);
  tcase_add_test(tc, sscanf_spec_real_6);
  tcase_add_test(tc, sscanf_spec_real_7);
  tcase_add_test(tc, sscanf_spec_real_8);
  tcase_add_test(tc, sscanf_spec_real_9);
  tcase_add_test(tc, sscanf_spec_real_10);
  tcase_add_test(tc, sscanf_spec_real_11);
  tcase_add_test(tc, sscanf_spec_real_12);
  tcase_add_test(tc, sscanf_spec_real_13);
  tcase_add_test(tc, sscanf_spec_real_14);
  tcase_add_test(tc, sscanf_spec_real_15);
  tcase_add_test(tc, sscanf_spec_real_16);
  tcase_add_test(tc, sscanf_spec_real_17);
  tcase_add_test(tc, sscanf_spec_real_18);
  tcase_add_test(tc, sscanf_spec_real_19);
  tcase_add_test(tc, sscanf_spec_real_20);

  suite_add_tcase(s, tc);
  return s;
}