#include "main.h"

/**
 * rev_string - Reverses the characters in a given string.
 * @s: The input string to be reversed.
 *
 * Return: Void
 */
void rev_string(char *s)
{
	int count = 0, i, j;
	char *str, temp;

	/* Count the number of characters in the input string */
	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	/* Loop to reverse the string by swapping characters */
	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = temp;
		}
	}
}
