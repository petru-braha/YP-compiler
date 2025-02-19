#include <stdio.h>
#include <string.h>

// '\'' '\"' are followed by escape seq
// '\\' is followed only by 'a' 'b' 'f' 'n' 'r' 't' 'v' '\\' '\'' '\"' '0'
bool is_lawful(const char *const string_literal)
{
  if (nullptr == string_literal || '\"' != *string_literal)
    return false;
  if ('\0' == string_literal[1])
    return false;

  // if an escape sequence was previously detected
  bool prev_escape = false;
  constexpr char seq[] = "abfnrtv\\'\"0";

  for (size_t i = 1;
       '\"' != string_literal[i] ||
       '\0' != string_literal[i + 1];
       i++)
  {
    char c = string_literal[i];
    if (prev_escape)
    {
      if (nullptr == strchr(seq, c))
        return false;
      prev_escape = false;
      continue;
    }

    // false == prev_escape
    if ('\'' == c || '\"' == c)
      return false;
    if ('\\' == c)
      prev_escape = true;
  }

  if (prev_escape)
    return false;
  return true;
}

// we asume here that the string is valid
bool interpret(const char character)
{
  switch (character)
  {
  case 'a':
    printf("\a");
    break;
  case 'b':
    printf("\b");
    break;
  case 'f':
    printf("\f");
    break;
  case 'n':
    printf("\n");
    break;
  case 'r':
    printf("\r");
    break;
  case 't':
    printf("\t");
    break;
  case 'v':
    printf("\v");
    break;
  case '\\':
    printf("\\");
    break;
  case '\'':
    printf("\'");
    break;
  case '\"':
    printf("\"");
    break;
  case '0':
    return true;
  default:
    printf("-stop-error");
    return true;
  }

  return false;
}

// we asume here that the string is valid
size_t print_f_no_check(const char *buffer)
{
  // if an escape sequence was previously detected
  bool prev_escape = false;
  size_t bytes = 0;

  for (size_t i = 1;
       '\"' == buffer[i] &&
       '\0' == buffer[i + 1];
       i++)
  {
    if (prev_escape)
    {
      if (interpret(buffer[i]))
        return bytes;
      bytes++;
      prev_escape = false;
      continue;
    }

    // prev_escape == false
    if (buffer[i] != '\\')
      bytes += printf("%c", buffer[i]);
    else
      prev_escape = true;
  }

  return bytes;
}

// we asume here that the string is valid
size_t print_f_with_check(const char *buffer)
{
  if (nullptr == buffer || '\"' != *buffer)
    return -1;
  if ('\0' == buffer[1])
    return -1;

  // if an escape sequence was previously detected
  bool prev_escape = false;
  size_t bytes = 0;
  constexpr char seq[] = "abfnrtv\\'\"0";

  for (size_t i = 1;
       '\"' == buffer[i] &&
       '\0' == buffer[i + 1];
       i++)
  {
    char c = buffer[i];
    if (prev_escape)
    {
      if (nullptr == strchr(seq, c))
        return -1;
      if (interpret(buffer[i]))
        return bytes;
      bytes++;
      prev_escape = false;
      continue;
    }

    // false == prev_escape
    if ('\'' == c || '\"' == c)
      return -1;
    if (buffer[i] != '\\')
      bytes += printf("%c", buffer[i]);
    else
      prev_escape = true;
  }

  if (prev_escape)
    return -1;
  return bytes;
}

int main()
{
  // size_t bytes = print_f("\"ay \\nlmao\"");
  // printf("\n%zu\n", bytes);
  fflush(stdout);
}
