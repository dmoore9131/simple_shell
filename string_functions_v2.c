#include "shell.h"

/**
 * string_length - Calculate the length of a string.
 * @str: The string whose length to calculate.
 *
 * Return: The length of the string.
 */
int string_length(const char *str)
{
    int length = 0;

    if (!str)
        return 0;

    while (str[length] != '\0')
    {
        length++;
    }

    return length;
}

/**
 * string_compare - Compare two strings.
 * @str1: The first string to compare.
 * @str2: The second string to compare.
 * 
 * Return: 0 if @str1 and @str2 are equal,
 *         a negative value if @str1 is less than @str2,
 *         or a positive value if @str1 is greater than @str2.
 */
int string_compare(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2)
    {
        str1++;
        str2++;
    }

    return (int)(*str1) - (int)(*str2);
}

/**
 * string_n_compare - Compare two strings up to a specified length.
 * @str1: The first string to compare.
 * @str2: The second string to compare.
 * @n: The maximum number of characters to compare.
 *
 * Return: 0 if the strings are equal up to n characters, a negative value
 *         if str1 is less than str2, or a positive value if str1 is greater than str2.
 */
int string_n_compare(const char *str1, const char *str2, size_t n)
{
    while (n > 0 && *str1 != '\0' && *str2 != '\0' && *str1 == *str2)
    {
        str1++;
        str2++;
        n--;
    }

    if (n == 0 || *str1 == '\0' || *str2 == '\0')
        return 0;

    return (int)(*str1) - (int)(*str2);
}

/**
 * string_find_substring - Find a substring in a string.
 * @str: The string to search in.
 * @substring: The substring to find.
 *
 * Return: A pointer to the first occurrence of the substring in the string,
 * or NULL if the substring is not found.
 */
char *string_find_substring(char *str, char *substring)
{
    while (*str != '\0')
    {
        char *start = str;
        char *sub = substring;

        while (*str != '\0' && *sub != '\0' && *str == *sub)
        {
            str++;
            sub++;
        }

        if (*sub == '\0')
            return start;

        str++;
    }

    return NULL;
}

/**
 * string_find_character - Find the first occurrence of a character in a string.
 * @str: The string to search in.
 * @ch: The character to find.
 *
 * Return: A pointer to the first occurrence of the character in the string,
 * or NULL if the character is not found.
 */
char *string_find_character(char *str, char ch)
{
    while (*str != '\0')
    {
        if (*str == ch)
            return str;
        
        str++;
    }

    if (*str == ch)
        return str;

    return NULL;
}

