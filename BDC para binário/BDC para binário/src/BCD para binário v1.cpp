#include <iostream>

// TESTE1, tudo junto, TESTE2, método de separação 1, TESTE (ou diferente) metódo de separação 2
#define TESTE

// TEXTO (ou diferente) argumentos de linha, TEXTO1 Digitar no prompt
#define TEXTO1

/*
		Basicamente, vamos dividir um número por dois até que ele não seja divisível por 2
	(caso o resultado da divisão for 1 ou 0),.

		Cada divisão, salva o valor do resto em "Binario[]" e o resultado em "Texto[]",
	a única diferença é que em "Binario[]" cada vez que salva é um para frente.
		já no "Texto[]" sempre salva no mesmo lugar..
		No final, salva o resultado de "Texto[]" (1 ou 0) em "Binario[]".
*/

// Extremidade do bit: Menos significativo para o mais significativo
// Menor primeiro (little endian) 1 2 4 8 / 16 32 64 128

int main(int argc, char* argv[])
{
	char Texto[230] = { 0 };
	unsigned char cTexto[230] = { 0 }; // Cópia de "Texto[]"
	unsigned char Binario[230] = { 0 };

	int bNum = 0;		// Posição da matriz "Binario[]"
	int byteNum = 0;	// Quantos bytes foram escritos, para organizar assim, 2 bytes por linha

#ifdef TEXTO1
	std::cout << "Entre uma palavra: ";
	std::cin.getline(Texto, sizeof Texto);
		
#else
	for (int i = 0; argv[1][i] != 0; i++)
		Texto[i] = argv[1][i];
#endif

	for (int i = 0; Texto[i] != 0; i++)
		cTexto[i] = Texto[i];

	//for (auto& i : cTexto)
	for (int temp = 0; cTexto[temp]; temp++)
	{
		do {
			Binario[bNum] = cTexto[temp] % 2;

			cTexto[temp] = cTexto[temp] / 2;

			++bNum;
		}
		while (cTexto[temp] > 1);

		Binario[bNum] = cTexto[temp];
		
			bNum = 8 * (temp + 1);
	}

	for (int Letras = 0; Texto[Letras]; ++Letras)
	{
		if (byteNum % 2 == 0)	// OK
			std::cout << '\n';
		
		std::cout << byteNum << " - ";	// OK

#ifdef TESTE1			// Tudo junto
		for (short temp = 0; temp < 8; ++temp)	// OK (Esse ++temp não dá problema não?, Por algum motivo não tá sendo pré incrementado)
			std::cout << (short)Binario[temp + (Letras * 8)];

#elif defined(TESTE2)	// Separado 1
		for (short temp = 0; temp < 8; ++temp)	// OK (Esse ++temp não dá problema não?, Por algum motivo não tá sendo pré incrementado)
		{
			if (temp == 4)
				std::cout << ' ';

			std::cout << (short)Binario[temp + (Letras * 8)];
		}

		// Eu talvez poderia usar até o mesmo "temp"
#else					// Separado 2
		for (short temp = 0; temp < 4; ++temp)
			std::cout << (short)Binario[temp + (Letras * 8)];

		std::cout << ' ';

		for (short temp = 4; temp < 8; ++temp)
			std::cout << (short)Binario[temp + (Letras * 8)];

#endif

		std::cout << " `" << Texto[Letras] << "` ";	// OK

		++byteNum;
	}

	std::cout << '\n';

	//std::cin.get();

	return 0;
}