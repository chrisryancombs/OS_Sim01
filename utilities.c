void string_token_left(char *string, char* substring, char delim)
{
    int count = 0;
    while (string[count] != delim){
        printf("%c\n", string[count]);
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
    while (string[count] == ' ')
    {
        count++;
    }
    while (string[count] != delim)
    {
        count++;
        if (string[count] == '\n')
        {
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
        end_count++;
    }

    int iter = count;
    while (iter < end_count)
    {
        substring[iter - count] = string[iter];
        iter++;
    }
    substring[iter - count] = '\0';
}
