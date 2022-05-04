#include <iostream>

// TEXTO (ou diferente) argumentos de linha, TEXTO1 Digitar no prompt
#define TEXTO1

/*
		Usar uma mascara de bits para analisar cada bit do caractére.
		Usando um AND, eu posso analisar individualmente cada bit, se
	ele for 1, tem resultado 1, se ele for 0 tem resultado 0 e assim
	eu imprimo se tem o bit ou não.

		Além de que eu implementei uma maneira de escolher a exremidade do bit,
	pois a maneira de leitura dos bits faz com que essa mudança sejá fácil.
*/

// Extremidade do bit: Mais significativo para o menos significativo
// Maior primeiro (big endian) 128 64 32 16 \ 8 4 2 1

int main(int argc, char* argv[])
{
	char end = 0;
	char Texto[230] = { 0 };
	unsigned char BitMask = 0b00000000;	// Para transformar em menor primeiro (little endian), 0b00000001

	short bit;
	int byteNum = 0;
		
	// Escolher a ordem dos bits será mostrado
	std::cout << "Menor primeiro (l) ou Maior primeiro (b): ";
	std::cin >> end;

	switch (end)
	{
	case 'l':
		BitMask = 0b00000001;
		break;
	case 'b':
		BitMask = 0b10000000;
		break;
	default:
		std::cout << "Houve uma entrada incorreta.";
		return 0;
	}

#ifdef TEXTO1
	std::cout << "Entre uma palavra: ";
	std::cin >> Texto;

#else
	// Argumentos de linha de comando
	if (argc != 2)
	{
		std::cout << "Uma quantidade diferente de argumentos foram inseridos.";
		return 0;
	}

	for (int i = 0; argv[1][i] != 0; i++)
		Texto[i] = argv[1][i];

#endif


	// Mostra os bits
	if (BitMask == 0b10000000)
		for (int Letras = 0; Texto[Letras]; ++Letras)
		{
			//if ((byteNum % 2 == 0) && byteNum)	// Só faz sentido usar, se houver argumentos de linha
			if (byteNum % 2 == 0)
				std::cout << '\n';

			std::cout << byteNum << " - ";

			for (short i = 0; i < 4; i++)
			{
				bit = Texto[Letras] & BitMask;

				std::cout << (bit ? 1 : 0);

				BitMask >>= 1;
			}

			std::cout << ' ';

			for (short i = 4; i < 8; i++)
			{
				bit = Texto[Letras] & BitMask;

				std::cout << (bit ? 1 : 0);

				BitMask >>= 1;
			}

			BitMask = 0b10000000;

			std::cout << " `" << Texto[Letras] << "` ";

			++byteNum;
		}
	else if (BitMask == 0b00000001)
		for (int Letras = 0; Texto[Letras]; ++Letras)
		{
			//if ((byteNum % 2 == 0) && byteNum)	// Só faz sentido usar, se houver argumentos de linha
			if (byteNum % 2 == 0)
				std::cout << '\n';

			std::cout << byteNum << " - ";

			// Escre os bits (eu separei eles de 4 e 4 por costume e pq eu acho mais legível)
			for (short i = 0; i < 4; i++)
			{
				bit = Texto[Letras] & BitMask;

				std::cout << (bit ? 1 : 0);

				BitMask <<= 1;
			}

			std::cout << ' ';

			for (short i = 4; i < 8; i++)
			{
				bit = Texto[Letras] & BitMask;

				std::cout << (bit ? 1 : 0);

				BitMask <<= 1;
			}

			BitMask = 0b00000001;

			std::cout << " `" << Texto[Letras] << "` ";

			++byteNum;
		}
	else
		std::cout << "Mascara de bits errada.\n";

	return 0;
}