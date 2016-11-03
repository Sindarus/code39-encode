#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>      // for toupper

#include "code39.h"

/**
* \fn bool is_codable(char* str);
* \brief Returns true if str is code39 encodable
* \param str is a null-terminated string
*/
bool is_codable(const char* str){
    int len = strlen(str);
    char c[] = {'?', '\0'};  // create a null-terminated string to send to strstr()
    for(int i = 0; i<len; i++){ // for each char of the string
        c[0] = str[i];          // prepare needle to send to strstr
        if(strstr(AUTH_CHARS, c) == NULL){
            return false;
        }
    }
    return true;
}

/**
* \fn prepare_for_coding(char* str);
* \brief Returns a string that is ready to be encoded using code39.
*        Memory is being allocated for this new string. Be careful to free
*        it eventually.
* \param str is a null-terminated string, that is code39 codable.
*/
char* prepare_for_coding(const char* str){
    int len = strlen(str);

    // allocate memory for code39 string. +2 because we add 2 stars, and +1 for
    // the null byte at the end
    char* ret_str = malloc((len + 2 + 1) * sizeof(char));

    ret_str[0] = '\0';  // make ret_str a null-terminated string
    strcat(ret_str, "*");
    strcat(ret_str, str);
    strcat(ret_str, "*");

    // make uppercase
    for(int i = 0; i<(len+2); i++){
        ret_str[i] = toupper(ret_str[i]);
    }

    return ret_str;
}

/**
* \fn int get_code39_char_nb(const char a);
* \brief Returns the id number of a char, as specified for code39 checksum
*        If a is not a code39 enabled character, -1 is returned
* \param a has to be a code39 enabled character.
*/
int get_code39_char_nb(const char a){
    for(int i = 0; i<43; i++){
        if(CODE39_CHARS[i] == a){
            return i;
        }
    }
    return -1;
}

/**
* \fn int code39_checksum(const char* str);
* \brief Returns the checksum of a code39 encoded string. If str is not a code39
*        encoded string, -1 is returned.
* \param
*/
int code39_checksum(const char* str){
    int checksum = 0;
    int c;
    for(unsigned int i = 1; i < strlen(str)-1; i++){
        c = get_code39_char_nb(str[i]);
        if(c == -1) return -1;
        else checksum += c;
    }
    return checksum % 43;
}

/**
* \fn char* add_code39_checksum(const char* str);
* \brief returns a new string that has code39's checksum at the end of the
*        code39 encoded string 'str'.
*        Memory is being allocated for this new string. Be careful to free
*        it eventually.
* \param
*/
char* add_code39_checksum(const char* str){
    int len = strlen(str);

    // allocate memory for new string
    // +1 for the checksum char and +1 for the null byte at the end
    char* ret_str = malloc((len + 1 + 1) * sizeof(char));

    ret_str[0] = '\0'; // make ret_str a null-terminated string
    strcat(ret_str, str);
    ret_str[len] = CODE39_CHARS[code39_checksum(str)];
    ret_str[len+1] = '\0';

    return ret_str;
}
