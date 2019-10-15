#include <stdio.h>
#include <string.h>

#define NMAX 100000
#define LMAX 20

unsigned int IPtoDecimal(char IP[LMAX])
{
	int len = strlen(IP), i;
	unsigned int subnumber = 0, result = 0, k = 3;
	for (i = 0; i < len; i++) {
		if (IP[i] == '.') {
			result += subnumber << (8 * k);
			k--; 
			subnumber = 0;
		} else {
			subnumber = subnumber * 10 + (IP[i] - '0');
		}
	}
	result += subnumber;

	return result;
}

unsigned int maskToDecimal(int mask)
{
	unsigned int i, result = 0;
	for (i = 32 - mask; i < 32; i++) {
		result += (1 << i);
	}

	return result;
}

unsigned int subString(unsigned int mask, int pos)
{
	unsigned int i, result = 0;
	for (i = pos; i < pos + 8; i++) {
		result += (mask & (1 << i));
	}
	result >>= pos;
	return result;
}

void printDecimalIP(unsigned int IP)
{
	printf("%u", subString(IP, 24));
	printf(".");
	printf("%u", subString(IP, 16));
	printf(".");
	printf("%u", subString(IP, 8));
	printf(".");
	printf("%u", subString(IP, 0));
}


void task0(char IP[LMAX], int mask)
{
	printf("-0 %s/%d\n", IP, mask);
}

void task1(int mask)
{
	unsigned int number = maskToDecimal(mask);
	printf("-1 ");
	printDecimalIP(number);
	printf("\n");

}

void printDecimalIPinOcta(unsigned int IP)
{
	printf("%o", subString(IP, 24));
	printf(".");
	printf("%o", subString(IP, 16));
	printf(".");
	printf("%o", subString(IP, 8));
	printf(".");
	printf("%o", subString(IP, 0));
}

void printDecimalIPinHexa(unsigned int IP)
{
	printf("%X", subString(IP, 24));
	printf(".");
	printf("%X", subString(IP, 16));
	printf(".");
	printf("%X", subString(IP, 8));
	printf(".");
	printf("%X", subString(IP, 0));
}

void task2(char mask[LMAX])
{
	printf("-2 ");
	unsigned int maskDecimal = IPtoDecimal(mask);
	printDecimalIPinOcta(maskDecimal);
	printf(" ");
	printDecimalIPinHexa(maskDecimal);
	printf("\n");
}

unsigned int getNetworkIP(char IP[LMAX], int mask)
{
	unsigned int ipDecimal = IPtoDecimal(IP);
	unsigned int maskDecimal = maskToDecimal(mask);
	return ipDecimal & maskDecimal;
}

void task3(char IP[LMAX], int mask)
{
	printf("-3 ");
	printDecimalIP(getNetworkIP(IP, mask));
	printf("\n");
}

unsigned int getBroadcastIP(char IP[LMAX], int mask)
{
	unsigned int ipDecimal = IPtoDecimal(IP);
	unsigned int maskDecimal = maskToDecimal(mask);
	return ipDecimal | (~maskDecimal);
}

void task4(char IP[LMAX], int mask)
{
	printf("-4 ");
	printDecimalIP(getBroadcastIP(IP, mask));
	printf("\n");
}

void task5(char IP1[LMAX], char IP2[LMAX], int mask)
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

	if (complementedMask & (complementedMask + 1)) {
		return 0;
	} else {
		return 1;
	}
}

void task6(char mask[LMAX])
{
	printf("-6 ");
	unsigned int maskDecimal = IPtoDecimal(mask);

	if (correctMask(maskDecimal)) {
		printf("DA\n");
	} else {
		printf("NU\n");
	}

}

void task7(char mask[LMAX])
{
	printf("-7 ");
	unsigned int maskDecimal = IPtoDecimal(mask);
	if (correctMask(maskDecimal)) {
		printf("%s", mask);
	} else {
		int i, j;
		for (i = 31; i >= 0; i--) {
			if ((maskDecimal & (1 << i)) == 0) {
				for (j = i - 1; j >= 0; j--) {
					if (maskDecimal & (1 << j)) {
						maskDecimal -=  1 << j;
					}
				}
				break;
			}
		}
		printDecimalIP(maskDecimal);
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

void task8(char IP[LMAX])
{
	printf("-8 ");
	unsigned int ipDecimal = IPtoDecimal(IP);
	printBinary(subString(ipDecimal, 24));
	printf(".");
	printBinary(subString(ipDecimal, 16));
	printf(".");
	printBinary(subString(ipDecimal, 8));
	printf(".");
	printBinary(subString(ipDecimal, 0));
	printf("\n");
}

void task9(int N, char net[NMAX][LMAX], char IP[LMAX])
{
	printf("-9 ");
	int i, netMask;
	unsigned int ipDecimal = IPtoDecimal(IP);
	unsigned int networkIP;
	char netIP[LMAX];

	for (i = 0; i < N; i++)
	{
		int j, len = strlen(net[i]);
		netMask = 0;
		for (j = 0; j < len; j++) {
			if (net[i][j] == '/') {
				break;
			} else {
				netIP[j] = net[i][j];
			}
		}
		netIP[j] = '\0'; 
		for (j++; j < len; j++) {
			netMask = netMask * 10 + net[i][j] - '0';
		}
		networkIP = getNetworkIP(netIP, netMask);
		unsigned int ipNetwork = getNetworkIP(IP, netMask);
		if (networkIP == ipNetwork) {
			printf("%d ", i);
		}
	}
	printf("\n");
}

int main()
{
	int T, i, N, MSK_2, K = 0;
	char MSK_1[LMAX], IP_1[LMAX], IP_2[LMAX], NET[NMAX][LMAX];
	scanf("%d", &T);
	printf("TUL:%d\n", T);
	while(T--) {
		scanf("%s %d", &MSK_1, &MSK_2);
		scanf("%s %s", &IP_1, &IP_2);
		scanf("%d", &N);
		for (i = 0; i < N; i++) {
			scanf("%s", &NET[i]);
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
		task9(N, NET, IP_2);
	}
	return 0;
}
