#ifndef H_CODE39
#define H_CODE39

#define AUTH_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 -$%./+\0"
#define CODE39_CHARS "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ-. $/+%"

bool is_codable(const char* str);
char* prepare_for_coding(const char* str);

int get_code39_char_nb(const char a);
int code39_checksum(const char* str);
char* add_code39_checksum(const char* str);

#endif
