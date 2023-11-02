#include "main.h"

/**
 * conv_itoa - Converts an integer to a string.
 * @number: The integer number to convert.
 *
 * Return: The string representation of the integer.
 */
char *conv_itoa(int number)
{
	/* Declare an unsigned integer for calculations. */
	unsigned int n1;
	int len = get_length(number);
	char *buff;

	/* Allocate memory for the string. */
	buff = malloc(sizeof(char) * (len + 1));
	if (buff == 0)
		return (NULL);

	*(buff + len) = '\0';

	if (number < 0)
	{
		n1 = number * -1;
		buff[0] = '-'; /* Add a minus sign for negative numbers. */
	}
	else
		n1 = number;

	len--;

	/* Convert the integer to a string. */
	do {
	*(buff + len) = (n1 % 10) + '0';
		n1 = n1 / 10;
	len--;
	} while (n1 > 0);

	return (buff); /* Return the converted string. */
}

/**
 * get_length - Get the length of a number.
 * @number: The number for which to calculate the length.
 *
 * Return: The length of the number.
 */
int get_length(int number)
{
	unsigned int n1;
	int lenght = 1;

	if (number < 0)
	{
		lenght++;
		n1 = number * -1;
	}
	else
		n1 = number;
	while (n1 > 9)
	{
		lenght++;
		n1 = n1 / 10;
	}

	return (lenght);
}

/**
 * _atoi - Converts a string to an integer.
 * @str: Input string.
 *
 * Return: The converted integer.
 */
int _atoi(char *str)
{
	unsigned int counter = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(str + counter) != '\0')
	{
		if (size > 0 && (*(str + counter) < '0' || *(str + counter) > '9'))
			break;

		if (*(str + counter) == '-')
			pn *= -1;

		if ((*(str + counter) >= '0') && (*(str + counter) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		counter++;
	}

	for (i = counter - size; i < counter; i++)
	{
		oi = oi + ((*(str + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
