#include <check.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include "s21_string.h"

START_TEST(memchr_test) {
    printf("---- s21_memchr test\n");
    char string1[] = "Bobolink";
    char string2[] = "Bobolink";
    s21_memchr(string1, 'o', 7);
    memchr(string2, 'o', 7);
    ck_assert_str_eq(string1, string2);
}
END_TEST

START_TEST(memcmp_test) {
    printf("---- s21_memcmp test\n");
    ck_assert(s21_memcmp("Smile", "Smile", 4) == memcmp("Smile", "Smile", 4));
    ck_assert(s21_memcmp("Smile", "Mignonette", 5)
               == memcmp("Smile", "Mignonette", 5));
    ck_assert(s21_memcmp("Aurora", "Guilt", 3) == memcmp("Aurora", "Guilt", 3));
}
END_TEST

START_TEST(memcpy_test) {
    printf("---- s21_memcpy test\n");
    char string1[] = "Harry";
    char string11[] = "Harry";
    char string2[] = "Cucumber";
    char string21[] = "Cucumber";

    s21_memcpy(string1, "1", 1);
    memcpy(string11, "1", 1);
    s21_memcpy(string2, "Pow", 2);
    memcpy(string21, "Pow", 2);

    ck_assert_str_eq(string1, string11);
    ck_assert_str_eq(string2, string21);
}
END_TEST

START_TEST(memmove_test) {
    printf("---- s21_memmove test\n");
    char string1[] = "Rawen";
    char string11[] = "Rawen";
    char string2[30] = "Smile";
    char string22[30] = "Smile";

    s21_memmove(string1, "Potato", 1);
    memmove(string11, "Potato", 1);
    memmove(string2, "Tranquility", 6);
    s21_memmove(string22, "Tranquility", 6);

    ck_assert_str_eq(string1, string11);
    ck_assert_str_eq(string2, string22);
}
END_TEST

START_TEST(memset_test) {
    printf("---- s21_memset test\n");
    char string1[] = "Harry";
    char string11[] = "Harry";
    char string2[30] = "Cucumber";
    char string22[30] = "Cucumber";

    s21_memset(string1, 'r', 3);
    memset(string11, 'r', 3);
    memset(string2, '%', 11);
    s21_memset(string22, '%', 11);

    ck_assert_str_eq(string1, string11);
    ck_assert_str_eq(string2, string22);
}
END_TEST

START_TEST(strcat_test) {
    printf("---- s21_strcat test\n");
    char str1[20] = "Bobolink";
    char str2[20] = "Bobolink";

    ck_assert_str_eq(s21_strcat(str1, "28"), strcat(str2, "28"));
}
END_TEST

START_TEST(strncat_test) {
    printf("---- s21_strncat test\n");
    char str1[20] = "Bobolink";
    char str2[20] = "Bobolink";

    ck_assert_str_eq(s21_strncat(str1, "Frog", 3),
                        strncat(str2, "Frog", 3));
}
END_TEST

START_TEST(strchr_test) {
    printf("---- s21_strchr test\n");
    char* str1 = strchr("Reconciliation 09", 'i');
    char* str2 = s21_strchr("Reconciliation 09", 'i');

    ck_assert(str1[0] == str2[0]);
    ck_assert_str_eq(strchr("Reconciliation 09", '0'), s21_strchr("Reconciliation 09", '0'));
    ck_assert_str_eq(strchr("Reconciliation 09", '\0'), s21_strchr("Reconciliation 09", '\0'));
}
END_TEST

START_TEST(strcmp_test) {
    printf("---- s21_strcmp test\n");
    ck_assert(s21_strcmp("Smile", "Smile") == 0);
    ck_assert(strcmp("Smile", "Smile") == 0);
    ck_assert(s21_strcmp("Aurora", "Guilt") < 0);
    ck_assert(strcmp("Aurora", "Guilt") < 0);
    ck_assert(s21_strcmp("Burora", "Auilt") > 0);
    ck_assert(strcmp("Burora", "Auilt") > 0);
    ck_assert(s21_strcmp("", "Auilt") < 0);
    ck_assert(strcmp("", "Auilt") < 0);
    ck_assert(s21_strcmp("Burora", "") > 0);
    ck_assert(strcmp("Burora", "") > 0);
}
END_TEST

START_TEST(strncmp_test) {
    printf("---- s21_strncmp test\n");
    ck_assert(s21_strncmp("solnce", "solnce", 4) == 0);
    ck_assert(strncmp("solnce", "solnce", 4) == 0);

    ck_assert(s21_strncmp("solnce", "Mignonette", 3) > 0);
    ck_assert(strncmp("solnce", "Mignonette", 3) > 0);

    ck_assert(s21_strncmp("aingle", "bolco", 3) < 0);
    ck_assert(strncmp("aingle", "bolco", 3) < 0);
}
END_TEST

START_TEST(strcpy_test) {
    printf("---- s21_strcpy test\n");
    char string1[] = "Harry";
    char string11[] = "Harry";
    char string2[] = "Cucumber";
    char string21[] = "Cucumber";

    s21_strcpy(string1, "1");
    strcpy(string11, "1");
    s21_strcpy(string2, "Pow");
    strcpy(string21, "Pow");

    ck_assert_str_eq(string1, string11);
    ck_assert_str_eq(string2, string21);
}
END_TEST

START_TEST(strncpy_test) {
    printf("---- s21_strncpy test\n");
    char string1[] = "Merry";
    char string11[] = "Merry";
    char string2[] = "Babacar";
    char string21[] = "Babacar";
    char string3[] = "Babacar";
    char string31[] = "Babacar";

    s21_strncpy(string1, "1", 1);
    strncpy(string11, "1", 1);
    s21_strncpy(string2, "Pow", 2);
    strncpy(string21, "Pow", 2);
    s21_strncpy(string3, "Pow", 5);
    strncpy(string31, "Pow", 5);

    ck_assert_str_eq(string1, string11);
    ck_assert_str_eq(string2, string21);
    ck_assert_str_eq(string3, string31);
}
END_TEST

START_TEST(strcspn_test) {
    printf("---- s21_strcspn test\n");
    ck_assert(strcspn("", "aw") == s21_strcspn("", "aw"));
    ck_assert(strcspn("Rawen", "Raw") == s21_strcspn("Rawen", "Raw"));
    ck_assert(strcspn("Rawen", "aw") == s21_strcspn("Rawen", "aw"));
    ck_assert(strcspn("this is a test", "siht ") == s21_strcspn("this is a test", "siht "));
    ck_assert(strcspn("12344444567", "4") == s21_strcspn("12344444567", "4"));
    ck_assert(strcspn("", "") == s21_strcspn("", ""));
    ck_assert(strcspn("", "1") == s21_strcspn("", "1"));
    ck_assert(strcspn("1", "") == s21_strcspn("1", ""));
}
END_TEST

START_TEST(strerror_test) {
    printf("---- s21_strerror test\n");
    ck_assert_str_eq(strerror(40), s21_strerror(40));
    ck_assert_str_eq(strerror(0), s21_strerror(0));
    ck_assert_str_eq(strerror(90), s21_strerror(90));
}
END_TEST

START_TEST(strlen_test) {
    printf("---- s21_strlen test\n");
    ck_assert(strlen("Constellation 12") == s21_strlen("Constellation 12"));
    ck_assert(strlen("") == s21_strlen(""));
}
END_TEST

START_TEST(strpbrk_test) {
    printf("---- s21_strpbrk test\n");
    char* str1 = strpbrk("Guilt", "Infinity");
    char* str2 = s21_strpbrk("Guilt", "Infinity");

    ck_assert(str1[0] == str2[0]);
    ck_assert_str_eq(strpbrk("Guil t", " "), s21_strpbrk("Guil t", " "));
}
END_TEST

START_TEST(strrchr_test) {
    printf("---- s21_strrchr test\n");
    char* str1 = strrchr("Reconciliation 09", 'i');
    char* str2 = s21_strrchr("Reconciliation 09", 'i');

    ck_assert(str1[0] == str2[0]);
    ck_assert_str_eq(strrchr("Reconciliation 09", '0'), s21_strrchr("Reconciliation 09", '0'));
    ck_assert_str_eq(strrchr("", '\0'), s21_strrchr("", '\0'));
    ck_assert_str_eq(strrchr("rerererere", 'r'), s21_strrchr("rerererere", 'r'));
}
END_TEST

START_TEST(strspn_test) {
    printf("---- s21_strspn test\n");
    ck_assert(strspn("Rawen", "aw") == s21_strspn("Rawen", "aw"));
    ck_assert(strspn("1234444455677", "1234") == s21_strspn("1234444455677", "1234"));
    ck_assert(strspn("1234444455677", "") == s21_strspn("1234444455677", ""));
    ck_assert(strspn("", "") == s21_strspn("", ""));
    ck_assert(strspn("", "qwe") == s21_strspn("", "qwe"));
    ck_assert(strspn("this is a test", "siht ") == strspn("this is a test", "siht "));
}
END_TEST

START_TEST(strstr_test) {
    printf("---- s21_strstr test\n");
    char* str1 = strstr("Rawen", "aw");
    char* str2 = s21_strstr("Rawen", "aw");
    ck_assert(str1[0] == str2[0]);
    ck_assert_str_eq(strstr("WallgWall", "Wall"), s21_strstr("WallgWall", "Wall"));
    ck_assert_str_eq(strstr("WalgWall", "Wall"), s21_strstr("WalgWall", "Wall"));
    ck_assert_str_eq(strstr("Wallgall", "Wall"), s21_strstr("Wallgall", "Wall"));
    ck_assert_str_eq(strstr("123456", "4"), s21_strstr("123456", "4"));
}
END_TEST

START_TEST(strtok_test) {
    printf("---- s21_strtok test\n");
    char str1[] = "Это не баг, это фича.";
    char str2[] = "Это не баг, это фича.";
    char *pch1 = s21_strtok(str1, " ,.");
    char *pch2 = strtok(str2, " ,.");
    while (pch1 != NULL) {
        pch1 = s21_strtok(NULL, " ,.");
        pch2 = strtok(NULL, " ,.");
        if (pch1 != NULL)
            ck_assert_str_eq(pch2, pch1);
    }
}
END_TEST

START_TEST(to_upper_test) {
    printf("---- s21_to_upper test\n");
    char *str = (char*)s21_to_upper("Up 0 TRyy");
    ck_assert_str_eq(str, "UP 0 TRYY");
    free(str);
    str = (char*)s21_to_upper("78-fok");
    ck_assert_str_eq(str, "78-FOK");
    free(str);
}
END_TEST

START_TEST(to_lower_test) {
    printf("---- s21_to_lower test\n");
    char *str = (char*)s21_to_lower("Up 0 TRyy");
    ck_assert_str_eq(str, "up 0 tryy");
    free(str);
    str = (char*)s21_to_lower("78-HI i");
    ck_assert_str_eq(str, "78-hi i");
    free(str);
}
END_TEST

START_TEST(insert_test) {
    printf("---- s21_insert test\n");
    char *str;
    str = (char*)s21_insert("i am Groot", "wuf", 5);
    ck_assert_str_eq(str, "i am wufGroot");
    free(str);
    str = (char*)s21_insert("dorov", "my nigggggers", 0);
    ck_assert_str_eq(str, "my nigggggersdorov");
    free(str);
}
END_TEST

START_TEST(trim_test) {
    printf("---- s21_trim test\n");
    char *str = (char*)s21_trim("^$ Go ^$ Bottle ", "^$");
    ck_assert_str_eq(str, " Go ^$ Bottle ");
    free(str);
    str = (char*)s21_trim("--hello--", "-");
    ck_assert_str_eq(str, "hello");
    free(str);
    str = (char*)s21_trim("--hello--", "");
    ck_assert_str_eq(str, "--hello--");
    free(str);
    str = (char*)s21_trim("-+- he+=-=l-+lo--+++ =-", "-+= ");
    ck_assert_str_eq(str, "he+=-=l-+lo");
    free(str);
    str = (char*)s21_trim("", "");
    ck_assert_str_eq(str, "");
    free(str);
}
END_TEST

START_TEST(sprintf_test_f) {
    printf("---- s21_sprintf_f test\n");
    char *str1 = (char*)malloc(50);
    char *str2 = (char*)malloc(50);
    sprintf(str1, "%hf", 123.43);
    s21_sprintf(str2, "%hf", 123.43);
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%10f", 123.43);
    s21_sprintf(str2, "%10f", 123.43);
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%.4lf", 123.4);
    s21_sprintf(str2, "%.4lf", 123.4);
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%-f", 123.43);
    s21_sprintf(str2, "%-f", 123.43);
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%+lf", 123.43);
    s21_sprintf(str2, "%+lf", 123.43);
    ck_assert_str_eq(str1, str2);
    free(str1);
    free(str2);
}
END_TEST

START_TEST(sprintf_test_proc) {
    printf("---- s21_sprintf_prod test\n");
    char *str1 = (char*)malloc(50);
    char *str2 = (char*)malloc(50);
    sprintf(str1, "%%", 123);
    s21_sprintf(str2, "%%", 123);
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%5%", 123);
    s21_sprintf(str2, "%5%", 123);
    ck_assert_str_eq(str1, str2);
    free(str1);
    free(str2);
}
END_TEST

START_TEST(sprintf_test_c) {
    printf("---- s21_sprintf_c test\n");
    char *str1 = (char*)malloc(50);
    char *str2 = (char*)malloc(50);
    sprintf(str1, "%10c", 'q');
    s21_sprintf(str2, "%10c", 'q');
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%c", 'q');
    s21_sprintf(str2, "%c", 'q');
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%c", ' ');
    s21_sprintf(str2, "%c", ' ');
    ck_assert_str_eq(str1, str2);
    free(str1);
    free(str2);
}
END_TEST


START_TEST(sprintf_test_d) {
    printf("---- s21_sprintf_d test\n");
    char *str1 = (char*)malloc(50);
    char *str2 = (char*)malloc(50);
    sprintf(str1, "%1.1ld", -123);
    s21_sprintf(str2, "%1.1ld", -123);
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%.5d", 53);
    s21_sprintf(str2, "%.5d", 53);
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%+d", -53);
    s21_sprintf(str2, "%+d", -53);
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%-hd", -87);
    s21_sprintf(str2, "%-hd", -87);
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%- 8d", 53);
    s21_sprintf(str2, "%- 8d", 53);
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%-+8.5d", 53);
    s21_sprintf(str2, "%-+8.5d", 53);
    ck_assert_str_eq(str1, str2);
    free(str1);
    free(str2);
}
END_TEST

START_TEST(sprintf_test_u) {
    printf("---- s21_sprintf_u test\n");
    char *str1 = (char*)malloc(50);
    char *str2 = (char*)malloc(50);
    sprintf(str1, "%1.1lu", -123);
    s21_sprintf(str2, "%1.1lu", -123);
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%.5u", 53);
    s21_sprintf(str2, "%.5u", 53);
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%hu", -53);
    s21_sprintf(str2, "%hu", -53);
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%-u", -87);
    s21_sprintf(str2, "%-u", -87);
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%-8u", 53);
    s21_sprintf(str2, "%-8u", 53);
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%-8.5u", 53);
    s21_sprintf(str2, "%-8.5u", 53);
    ck_assert_str_eq(str1, str2);
    free(str1);
    free(str2);
}
END_TEST

START_TEST(sprintf_test_s) {
    printf("---- s21_sprintf_s test\n");
    char *str1 = (char*)malloc(50);
    char *str2 = (char*)malloc(50);
    sprintf(str1, "%1.1s", "123");
    s21_sprintf(str2, "%1.1s", "123");
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%.5s", "qwe");
    s21_sprintf(str2, "%.5s", "qwe");
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%s", "eded");
    s21_sprintf(str2, "%s", "eded");
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%-.6s", "fffff");
    s21_sprintf(str2, "%-.6s", "fffff");
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%-8s", "ujuuj");
    s21_sprintf(str2, "%-8s", "ujuuj");
    ck_assert_str_eq(str1, str2);
    sprintf(str1, "%-8.5s", "      ");
    s21_sprintf(str2, "%-8.5s", "      ");
    ck_assert_str_eq(str1, str2);
    free(str1);
    free(str2);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");  // Объявляем сьюит
    SRunner *sr = srunner_create(s1);  // Лаунчер сьюита
    int failed_count;  // Статус тестов сьюита

    TCase *ViCase = tcase_create("ViTest");  // Новый кейс
    TCase *NiCase = tcase_create("NiTest");
    TCase *AlCase = tcase_create("AlTest");
    TCase *BonusCase = tcase_create("BonusTest");
    TCase *sprintfCase = tcase_create("sprintfTest");
    // TCase *errorCase = tcase_create("errorTest");
    suite_add_tcase(s1, ViCase);  // Добавляем кейс
    suite_add_tcase(s1, NiCase);
    suite_add_tcase(s1, AlCase);
    suite_add_tcase(s1, BonusCase);
    suite_add_tcase(s1, sprintfCase);
    // suite_add_tcase(s1, errorCase);
    tcase_add_test(ViCase, memchr_test);
    tcase_add_test(ViCase, memcmp_test);
    tcase_add_test(ViCase, memcpy_test);
    tcase_add_test(ViCase, memmove_test);
    tcase_add_test(ViCase, memset_test);
    tcase_add_test(ViCase, strcat_test);
    tcase_add_test(ViCase, strncat_test);

    tcase_add_test(AlCase, strchr_test);
    tcase_add_test(AlCase, strncmp_test);
    tcase_add_test(AlCase, strcmp_test);
    tcase_add_test(AlCase, strcpy_test);
    tcase_add_test(AlCase, strncpy_test);
    tcase_add_test(AlCase, strcspn_test);

    tcase_add_test(NiCase, strerror_test);
    tcase_add_test(NiCase, strlen_test);
    tcase_add_test(NiCase, strpbrk_test);
    tcase_add_test(NiCase, strrchr_test);
    tcase_add_test(NiCase, strspn_test);
    tcase_add_test(NiCase, strstr_test);
    tcase_add_test(NiCase, strtok_test);

    tcase_add_test(BonusCase, to_upper_test);
    tcase_add_test(BonusCase, to_lower_test);
    tcase_add_test(BonusCase, insert_test);
    tcase_add_test(BonusCase, trim_test);
    tcase_add_test(sprintfCase, sprintf_test_f);
    tcase_add_test(sprintfCase, sprintf_test_proc);
    tcase_add_test(sprintfCase, sprintf_test_c);
    tcase_add_test(sprintfCase, sprintf_test_d);
    tcase_add_test(sprintfCase, sprintf_test_u);
    tcase_add_test(sprintfCase, sprintf_test_s);

    srunner_run_all(sr, CK_ENV);
    failed_count = srunner_ntests_failed(sr);
    srunner_free(sr);

    return 0;
}
