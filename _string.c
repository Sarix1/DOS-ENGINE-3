int strcmptok(char* str, char* token, char delim)
{
    int index = 0; // position in str
    // skip delimeter character(s) in the beginning
    while (*str == delim)
    {
        str++;
        index++;
    }
    // compare str and token
    while (*str == *token)
    {
        // end of token reached and strings were identical;
        // return index in str where the token string ends (final character+1)
        if (*token == '\0')
            return index;

        str++;
        token++;
        index++;
    }
    // when the strings diverge, return -1 (token not found)
    return -1;
}