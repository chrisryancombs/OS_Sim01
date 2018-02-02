// Code Implementation File Information /////////////////////////////
/**
* @file utilities.c
*
* @brief Implementation file for utilities code
*
* @details Implements all necessary string utilities
*
* @version 1.00
* C.S. Student (2 February 2018)
* Initial development and testing of utilities code
*
* @note Requires utilities.h
*/


void string_copy(char *dest, char *src)
{
    int iter = 0;
    while(src[iter] != '\0')
    {
        dest[iter] = src[iter];
        iter++;
    }
}

int string_compare(char *str1, char *str2)
{
    int iter = 0;
    while(str1[iter] != '\0' || str2[iter] != '\0')
    {
        if(str1[iter] != str2[iter])
        {
            return 1;
        }
        iter++;
    }
    return 0;
}

void string_token_left(char *string, char* substring, char delim)
{
    int count = 0;
    while (string[count] != delim){
        substring[count] = string[count];
        count++;
        if(string[count] == '\n')
        {
            return;
        }
    }
    substring[count] = '\0';
}

void string_token_right(char *string, char* substring, char delim)
{
    int count = 0;
    while (string[count] != delim)
    {
        count++;
        if (string[count] == '\0')
        {
            string_copy(substring, string);
            return;
        }
    }
    count++;

    while (string[count] == ' ')
    {
        count++;
    }

    int end_count = count;
    while(string[end_count] != '\n'){
        substring[end_count - count] = string[end_count];
        end_count++;
    }
    substring[end_count - count] = '\0';
}

int string_to_integer(char *string)
{
    int result = 0;
    int iter = 0;

    while(string[iter] != '\0')
    {
        result = result * 10 + string[iter] - '0';
        iter++;
    }
    return result;
}
