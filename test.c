// Intento de traductor (conversor) de input de texto a morse
//Código arreglado por Kingcreek --> (el PUTÍSIMO AMO)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# include <readline/readline.h>

/*
	FUNCION AUXILIAR PARA DIVIDIR LA CADENA DE ENTRADA EN CHAR **
*/
static int		unleah(char **str, int size)
{
	while (size--)
		free(str[size]);
	return (-1);
}

static int		count_words(const char *str, char charset)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i + 1] == charset || str[i + 1] == '\0') == 1
				&& (str[i] == charset || str[i] == '\0') == 0)
			words++;
		i++;
	}
	return (words);
}

static void		write_word(char *dest, const char *from, char charset)
{
	int	i;

	i = 0;
	while ((from[i] == charset || from[i] == '\0') == 0)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

static int		write_split(char **split, const char *str, char charset)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == charset || str[i] == '\0') == 1)
			i++;
		else
		{
			j = 0;
			while ((str[i + j] == charset || str[i + j] == '\0') == 0)
				j++;
			if ((split[word] = (char*)malloc(sizeof(char) * (j + 1))) == NULL)
				return (unleah(split, word - 1));
			write_word(split[word], str + i, charset);
			i += j;
			word++;
		}
	}
	return (0);
}

char			**split(const char *str, char c)
{
	char	**res;
	int		words;

	words = count_words(str, c);
	if ((res = (char**)malloc(sizeof(char*) * (words + 1))) == NULL)
		return (NULL);
	res[words] = 0;
	if (write_split(res, str, c) == -1)
		return (NULL);
	return (res);
}



int main()
{
	char *respuesta;
	int i;

	char *letters[] = {
		"·-", "-···", "-·-·", "-··", "·", "··-·", "--·", "····", "··", "·---", "-·-", "·-··", "--", "-·", "---", "·--·", "--·-", "·-·", "···", "-", "··-", "···-", "·--", "-··-", "-·--", "--··"
	};

	char *numbers[] = {
		"-----", "·----", "··---", "···--", "····-", "·····", "-····", "--···", "---··", "----·"
	};

	printf("\nIntroduce el codigo morse a convertir y pulsa [ENTER].\nPara ver la leyenda de los símbolos pulsa [+] y luego [ENTER].\nPara salir pulsa [-] (guión) y luego [ENTER].\n\n");

	while (1)
	{
		respuesta = readline("Escribe premo 👉 ");
		//se separa el texto por sus espacios
		char **splits = split(respuesta, ' ');
		//se recorren cada elemento del split
		int pos_split =	0;
		int pos = 		0;

		while(splits[pos_split])
		{
			pos = 0;
			//por cada elemento del split, se recorre el array de letras para ver si alguno coincide
			while(pos < 26)
			{
				if(strcmp(splits[pos_split], letters[pos]) == 0)//se compara el split con la letra
				{
					printf("%c", pos + 'a');
					break;
				}
				pos++;
			}

			//por cada elemento del split, se recorre el array de numeros para ver si alguno coincide
			pos = 0;
			while(pos < 10)
			{
				if(strcmp(splits[pos_split], numbers[pos]) == 0)//se compara el split con la letra
				{
					printf("%c", pos + '0');
					break;
				}
				pos++;
			}
			//la ñ traviesa
			if(strcmp(splits[pos_split], "--·--") == 0)//se compara el split con la letra
			{
				printf("ñ ");
			}
			pos_split++;
		}
		printf("\n");
	}

	/*
	printf("\nIntroduce el texto a convertir y pulsa [ENTER].\nPara ver la leyenda de los símbolos pulsa [+] y luego [ENTER].\nPara salir pulsa [-] (guión) y luego [ENTER].\n\n");

	while (1)
	{
		i = 0;
		//scanf("%s", respuesta);
		respuesta = readline("Escribe premo 👉 ");
		while (respuesta[i] != '\0')
		{
			if (respuesta[i] >= 'A' && respuesta[i] <= 'Z')
			{
				printf("%s ", letters[respuesta[i] - 'A']);
			}
			else if(respuesta[i] >= 'a' && respuesta[i] <= 'z')
			{
				printf("%s ", letters[respuesta[i] - 'a']);
			}
			else if(respuesta[i] >= '0' && respuesta[i] <= '9')
			{
				printf("%s ", numbers[respuesta[i] - '0']);
			}
			else if(strchr("ñ", respuesta[i]) != 0 || strchr("Ñ", respuesta[i]) != 0)
			{
				printf("--·-- ");
				i++;
			}
			if (respuesta[i] == '-')
			{
				printf("\nPrograma cerrado.\n\n");
				free(respuesta);
				return 0;
			}

			if (respuesta[i] == '+')
			{
				printf("\nLEYENDA:\n[—]: Señal larga [raya]\n[·]: Señal corta [punto]\nInformación sobre la interpretación de código Morse:\nEl espacio entre palabras equivale a 5 señales cortas [5 puntos]\nEl espacio entre letras equivale a 3 señales cortas [3 puntos]\n\n");
			}

			i++;
			printf (" ");
		}
		printf("\n");
	}
	*/
}