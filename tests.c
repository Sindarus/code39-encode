#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "CUnit/Basic.h"
#include "CUnit/Basic.h"

#include "code39.h"

void test_is_codable(void){
    CU_ASSERT(is_codable("ABCD1234-$%./+"));
    CU_ASSERT(is_codable("ABCD1234-ERGG"));
    CU_ASSERT(is_codable("ABCD1234%ERGG"));
    CU_ASSERT(is_codable("ABCD1234+ERGG"));
    CU_ASSERT(is_codable("asdg1234+ERafzefeGG"));
    CU_ASSERT(!is_codable("ABCDéEF"));
    CU_ASSERT(!is_codable("ABC&DEDF"));
    CU_ASSERT(!is_codable("ABC)DEDF"));
    CU_ASSERT(!is_codable("ABC@DEDF"));
}

void test_prepare_for_coding(void){
    CU_ASSERT_STRING_EQUAL(prepare_for_coding("asdg1234ERafzefeGG+"), "*ASDG1234ERAFZEFEGG+*")
    CU_ASSERT_STRING_EQUAL(prepare_for_coding("Bonjour"), "*BONJOUR*")
    CU_ASSERT_STRING_EQUAL(prepare_for_coding("Bonjour1234"), "*BONJOUR1234*")
    // CU_ASSERT_STRING_EQUAL(!prepare_for_coding("ABCDéEF"), "*ABCDEEF*")
    // CU_ASSERT_STRING_EQUAL(!prepare_for_coding("ABC)DEDF"), "*ABC)DEDF*")
}

void test_get_code39_char_nb(void){
    CU_ASSERT(get_code39_char_nb('0') == 0);
    CU_ASSERT(get_code39_char_nb('A') == 10);
    CU_ASSERT(get_code39_char_nb('R') == 27);
    CU_ASSERT(get_code39_char_nb(' ') == 38);
    CU_ASSERT(get_code39_char_nb('%') == 42);
    CU_ASSERT(get_code39_char_nb('@') == -1);
    CU_ASSERT(get_code39_char_nb('&') == -1);
}

void test_code39_checksum(void){
    CU_ASSERT(code39_checksum("*000*") == 0);
    CU_ASSERT(code39_checksum("*123*") == 6);
    CU_ASSERT(code39_checksum("*ABC*") == 33);
    CU_ASSERT(code39_checksum("*/+*") == 38);
    CU_ASSERT(code39_checksum("*/+*&") == -1);
}

void test_add_code39_checksum(void){
    CU_ASSERT_STRING_EQUAL(add_code39_checksum("*000*"), "*000*0");
    CU_ASSERT_STRING_EQUAL(add_code39_checksum("*123*"), "*123*6");
    CU_ASSERT_STRING_EQUAL(add_code39_checksum("*ABC*"), "*ABC*X");
    CU_ASSERT_STRING_EQUAL(add_code39_checksum("*/+*"), "*/+* ");
}

int main(){
    CU_initialize_registry();
    CU_pSuite suite1 = CU_add_suite("suite test fonctions principales", 0, 0);

    CU_add_test(suite1, "test is_codable", test_is_codable);
    CU_add_test(suite1, "test prepare_for_coding", test_prepare_for_coding);
    CU_add_test(suite1, "test get_code39_char_nb", test_get_code39_char_nb);
    CU_add_test(suite1, "test code39_checksum", test_code39_checksum);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
