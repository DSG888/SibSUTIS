/*
Разработайте и отладьте программу a07_1.c, на вход которой поступает:
1. Максимальный размер пакета в сети (MTU).
2. Количество переданных пакетов (TX packets).
3. Количество принятых пакетов (RX packets).
Вывести информацию о сетевом интерфейсе wlan0, так как она приведена на слайде, заменив элементы, выделенные красным цветом, согласно введенной информации. При расчете RX/TX bytes, считать, что принимались и передавались только пакеты максимально возможного размера.
wlan0	Link encap:Ethernet HWaddr AA:BB:CC:DD:EE:FF
		inet addr:192.168.0.208 Bcast:192.168.0.255 Mask:255.255.255.0
		inet6 addr: fe80::6e88:14ff:fe62:87cc/64 Scope:Link
		UP BROADCAST RUNNING MULTICAST MTU:1500 Metric:1
		RX packets:2539966 errors:0 dropped:0 overruns:0 frame:0
		TX packets:16547  errors:0 dropped:0 overruns:0 carrier:0
		collisions:0 txqueuelen:1000
		RX bytes:3367045445 (3.3 GB) TX bytes:2146370 (2.1 MB)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* SizeByteToStr(long int a, long int b)
{
	char stroka[50];
	if (a*b < 1000)
		snprintf(stroka, 50, "%d b", a * b);
	if (1000 <= a * b < 1000000)
		snprintf(stroka,50,"%.1f KB", a * b / 1000.0);
	if (1000000 <= (a * b) < 1000000000)
		snprintf(stroka,50,"%.1f MB", a * b / 1000000.0);
	if (1000000000 <= a * b)
		snprintf(stroka, 50, "%.1lf GB", (a * b) / 1000000000.0);
	return stroka;
}

int main( int argc, char *argv[])
{
	int MTU = 1500, RXp = 2539966, TXp = 16547;
	printf("Введите MTU RXp TXp: ");
	scanf("%d %d %d", &MTU, &RXp, &TXp);
	char strtx[50], strrx[50];
	snprintf(strrx, 50, "%s",SizeByteToStr(MTU, RXp));
	snprintf(strtx, 50, "%s",SizeByteToStr(MTU, TXp));

	printf ("wlan0\tLink encap:Ethernet HWaddr AA:BB:CC:DD:EE:FF\n\tinet addr:192.168.0.208 Bcast:192.168.0.255 Mask:255.255.255.0\n\tinet6 addr: fe80::6e88:14ff:fe62:87cc/64 Scope:Link\n\tUP BROADCAST RUNNING MULTICAST MTU:%d Metric:1\n\tRX packets:%d errors:0 dropped:0 overruns:0 frame:0\n\tTX packets:%d errors:0 dropped:0 overruns:0 carrier:0\n\tcollisions:0 txqueuelen:1000\n\tRX bytes:%ld (%s) TX bytes:%ld (%s)\n\n", MTU, RXp, TXp, MTU*RXp, strrx, MTU*TXp, strtx);
	return 0;
}



