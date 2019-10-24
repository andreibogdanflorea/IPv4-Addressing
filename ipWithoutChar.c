#include <stdio.h>
#include <string.h>

#define NMAX 100000

unsigned int IPtoDecimal(unsigned int groupA, unsigned int groupB, unsigned int groupC, unsigned int groupD)
{
	return (groupA << 24) + (groupB << 16) + (groupC << 8) + groupD;
}

void printIPv4(unsigned int IP)
{
	unsigned char maskChar = ~0; //masca 11111111, care ne da acces asupra unui octet 
	unsigned int mask = maskChar << 24; //pentru prima grupare
	printf("%u", (IP & mask) >> 24);
	printf(".");
	mask >>= 8; //pentru al doilea octet
	printf("%u", (IP & mask) >> 16);
	printf(".");
	mask >>= 8; //al treilea
	printf("%u", (IP & mask) >> 8);
	printf(".");
	mask >>= 8; //al patrulea
	printf("%u", IP & mask);
}


void task0(unsigned int IP, unsigned int mask)
{
	printf("-0 ");
	printIPv4(IP);
	printf("/%u\n", mask);
}

unsigned int maskToDecimal(unsigned int mask)
{
	unsigned int result = (1 << mask) - 1; //punem 1 pe ultimele *mask* pozitii
	result <<= 32 - mask; //shiftam bitii de 1 pe primele pozitii

	return result;
}

void task1(unsigned int mask)
{
	unsigned int maskInDecimal = maskToDecimal(mask);
	printf("-1 ");
	printIPv4(maskInDecimal);
	printf("\n");
}

void printIPinOcta(unsigned int IP)
{
	unsigned char maskChar = ~0;
	unsigned int mask = maskChar << 24;
	printf("%o", (IP & mask) >> 24);
	printf(".");
	mask >>= 8;
	printf("%o", (IP & mask) >> 16);
	printf(".");
	mask >>= 8;
	printf("%o", (IP & mask) >> 8);
	printf(".");
	mask >>= 8;
	printf("%o", IP & mask);
}

void printIPinHexa(unsigned int IP)
{
	unsigned char maskChar = ~0;
	unsigned int mask = maskChar << 24;
	printf("%X", (IP & mask) >> 24);
	printf(".");
	mask >>= 8;
	printf("%X", (IP & mask) >> 16);
	printf(".");
	mask >>= 8;
	printf("%X", (IP & mask) >> 8);
	printf(".");
	mask >>= 8;
	printf("%X", IP & mask);
}

void task2(unsigned int mask)
{
	printf("-2 ");
	printIPinOcta(mask);
	printf(" ");
	printIPinHexa(mask);
	printf("\n");
}

unsigned int getNetworkIP(unsigned int IP, unsigned int mask)
{
	unsigned int maskDecimal = maskToDecimal(mask);
	return IP & maskDecimal;
}

void task3(unsigned int IP, unsigned int mask)
{
	printf("-3 ");
	printIPv4(getNetworkIP(IP, mask));
	printf("\n");
}

unsigned int getBroadcastIP(unsigned int IP, unsigned int mask)
{
	unsigned int maskDecimal = maskToDecimal(mask);
	return IP | (~maskDecimal);
}

void task4(unsigned int IP, unsigned int mask)
{
	printf("-4 ");
	printIPv4(getBroadcastIP(IP, mask));
	printf("\n");
}

void task5(unsigned int IP1, unsigned int IP2, unsigned int mask)
{
	printf("-5 ");
	unsigned int networkIP1 = getNetworkIP(IP1, mask);
	unsigned int networkIP2 = getNetworkIP(IP2, mask);
	if (networkIP1 == networkIP2) {
		printf("DA\n");
	} else {
		printf("NU\n");
	}
}

int correctMask(unsigned int mask)
{
	unsigned int complementedMask = ~mask;
	//pentru o masca corecta, complementul este de forma 00..0011..1, deci complementul + 1 este de forma 00..0100..0,
	//si facand & intre complement si complement + 1, obtinem 0 (daca masca este corecta)
	if (complementedMask & (complementedMask + 1)) {
		return 0;
	}
	return 1;
}

void task6(unsigned int mask)
{
	printf("-6 ");

	if (correctMask(mask)) {
		printf("DA\n");
	} else {
		printf("NU\n");
	}

}

void task7(unsigned int mask)
{
	printf("-7 ");
	
	if (correctMask(mask)) {
		printIPv4(mask);
	} else {

		int i;
		for (i = 31; i >= 0; i--) {
			if ((mask & (1 << i)) == 0) {
				mask &= ~((1 << i) - 1);
				//am construit o masca cu 1 pe primele pozitii, de la 31 la i, si 0 in rest, si, facand & intre
				//ea si masca pe care o corectam, obtinem zerouri la dreapta celui mai semnificativ zero
				break;
			}
		}
		printIPv4(mask);
	}
	printf("\n");
}

void printBinary(unsigned int number)
{
	int i;
	for (i = 7; i >= 0; i--) {
		printf("%d", (number & (1 << i)) >> i);
	}
}

void task8(unsigned int IP)
{
	printf("-8 ");
	unsigned char maskChar = ~0;
	unsigned int mask = maskChar << 24;
	printBinary((IP & mask) >> 24);
	printf(".");
	mask >>= 8;
	printBinary((IP & mask) >> 16);
	printf(".");
	mask >>= 8;
	printBinary((IP & mask) >> 8);
	printf(".");
	mask >>= 8;
	printBinary(IP & mask);
	printf("\n");
}

void task9(int N, unsigned int net[NMAX], unsigned int netMask[NMAX], unsigned int IP)
{
	printf("-9 ");
	unsigned int netIP, IPNetwork;
	int i;

	for (i = 0; i < N; i++)
	{
		netIP = getNetworkIP(net[i], netMask[i]);
		IPNetwork = getNetworkIP(IP, netMask[i]);
		if (netIP == IPNetwork) {
			printf("%d ", i);
		}
	}
	printf("\n");
}

int main()
{
	int T, i, N, K = 0;
	unsigned int MSKa, MSKb, MSKc, MSKd, MSK_2;
	unsigned int IP_1a, IP_1b, IP_1c, IP_1d;
	unsigned int IP_2a, IP_2b, IP_2c, IP_2d;
	unsigned int NETa, NETb, NETc, NETd;
	unsigned int MSK_1, IP_1, IP_2, NET[NMAX], netMask[NMAX];
	
	scanf("%d", &T);

	while(T--) {
		scanf("%u.%u.%u.%u %u", &MSKa, &MSKb, &MSKc, &MSKd, &MSK_2); //se citesc pe grupari IP-urile de forma a.b.c.d
		scanf("%u.%u.%u.%u", &IP_1a, &IP_1b, &IP_1c, &IP_1d);
		scanf("%u.%u.%u.%u", &IP_2a, &IP_2b, &IP_2c, &IP_2d);
		
		//functie care transforma cele 4 grupari intr-un numar intreg
		MSK_1 = IPtoDecimal(MSKa, MSKb, MSKc, MSKd);
		IP_1 = IPtoDecimal(IP_1a, IP_1b, IP_1c, IP_1d);
		IP_2 = IPtoDecimal(IP_2a, IP_2b, IP_2c, IP_2d);

		scanf("%d", &N);
		for (i = 0; i < N; i++) {
			scanf("%u.%u.%u.%u/%u", &NETa, &NETb, &NETc, &NETd, &netMask[i]);
			NET[i] = IPtoDecimal(NETa, NETb, NETc, NETd);
		}

		printf("%d\n", ++K);

		task0(IP_1, MSK_2);
		task1(MSK_2);
		task2(MSK_1);
		task3(IP_1, MSK_2);
		task4(IP_1, MSK_2);
		task5(IP_1, IP_2, MSK_2);
		task6(MSK_1);
		task7(MSK_1);
		task8(IP_1);
		task9(N, NET, netMask, IP_2);
	}
	return 0;
}
