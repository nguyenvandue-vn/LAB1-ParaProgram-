#include<stdio.h>
#include<string.h>

struct kniga {
	char cipher[20];
	char fullname[60];
	int year;
	char namebook[50];
	char pub[50];
}k;
struct kniga vvedit() {
	//char* NEXT_TOKEN = NULL;
	printf("Vvedi cipher:");
	fgets(k.cipher, 19, stdin);
	k.cipher[strcspn(k.cipher, "\n")] = 0;
	//strtok_s(k.cipher, "\n", &NEXT_TOKEN);
	printf("Vvedi fullname:");
	fgets(k.fullname, 59, stdin);
	k.fullname[strcspn(k.fullname, "\n")] = 0;
	//strtok_s(k.fullname, "\n", &NEXT_TOKEN);
	printf("Vvedi year:");
	scanf_s("%d", &k.year);
	getchar();
	printf("Vvedi namebook:");
	fgets(k.namebook, 49, stdin);
	k.namebook[strcspn(k.namebook, "\n")] = 0;
	//strtok_s(k.namebook, "\n", &NEXT_TOKEN);
	printf("Vvedi pub:");
	fgets(k.pub, 49, stdin);
	k.pub[strcspn(k.pub, "\n")] = 0;
	//strtok_s(k.pub, "\n", &NEXT_TOKEN);
	return k;
}
void write(char* infilename, kniga* list, int amount) {
	FILE* f;
	fopen_s(&f, infilename, "w");
	if (f == NULL)
		return;
	for (int i = 0; i < amount; i++)
	{
		fprintf(f, "%s\n%s\n%d\n%s\n%s\n", list[i].cipher, list[i].fullname, list[i].year, list[i].namebook, list[i].pub);
	}
	fclose(f);
}
void vuvod(kniga k) {
	printf("%-10s %-20s %-10d %-25s %-15s\n", k.cipher, k.fullname, k.year, k.namebook, k.pub);
}
void read(char* infilename, kniga* list, int* amount) {
	FILE* f;
	fopen_s(&f, infilename, "a+");
	char tx[10];
	int i = 0;
	if (f != NULL)
	{
		while (!feof(f))
		{
			fgets(list[i].cipher, 20, f);
			list[i].cipher[strcspn(list[i].cipher, "\n")] = 0;
			fgets(list[i].fullname, 60, f);
			list[i].fullname[strcspn(list[i].fullname, "\n")] = 0;
			fscanf_s(f, "%d", &list[i].year);
			fgets(tx, 10, f);
			fgets(list[i].namebook, 50, f);
			list[i].namebook[strcspn(list[i].namebook, "\n")] = 0;
			fgets(list[i].pub, 50, f);
			list[i].pub[strcspn(list[i].pub, "\n")] = 0;
			i++;
		}
		*amount = i - 1;
	}
	else *amount = 0;
	fclose(f);
}
void title() {
	printf("%-10s %-20s %-10s %-25s %-15s\n", "Cipher", "Author", "Year", "Namebook", "Publish");
}
bool findbooks(kniga* list, int amount, int* a, char* inf) {
	int timSV = 0;
	for (int i = 0; i < amount; i++) {
		if ((strcmp(inf, list[i].fullname) == 0) || (strcmp(inf, list[i].namebook) == 0)) {
			*a = i;
			title();
			vuvod(list[i]);
			timSV = 1;
		}
	}
	return timSV == 1;
}
int dataProces(kniga* list, int amount) {
	int choice = 0;
	char inf[60];
	int a = 0;

	do
	{
		if (amount > 0) {
			printf("\n#%d book:\n", a + 1);
			printf("%-10s %-20s %-10d %-25s %-15s\n", list[a].cipher, list[a].fullname, list[a].year, list[a].namebook, list[a].pub);

			printf("          ---------------MENU2------------\n");
			printf("          1)find inf previous book?\n          2)find inf next book?\n          3)add books?\n          4)delete book?\n          5)change information\n          6)back?\n");
			printf("\nPlease choice:");
			scanf_s("%d", &choice);
			switch (choice)
			{
			case 1:
				if (a > 0) {
					a--;
					printf("%-10s %-20s %-10d %-25s %-15s\n", list[a].cipher, list[a].fullname, list[a].year, list[a].namebook, list[a].pub);
				}
				else printf("\nNo previos book!");
				break;
			case 2:
				if (a < amount - 1) {
					a++;
					printf("%-10s %-20s %-10d %-25s %-15s\n", list[a].cipher, list[a].fullname, list[a].year, list[a].namebook, list[a].pub);
				}
				else printf("\nNext book does not exist!\n");
				break;
			case 3:
				printf("Enter new book!\n");
				rewind(stdin);
				list[amount++] = vvedit();
				vuvod(list[amount - 1]);
				break;
			case 4:
				for (int j = a; j < amount - 1; j++) {
					list[j] = list[j + 1];
				}
				amount--;
				break;
			case 5:
				printf("Enter new inf!\n");
				rewind(stdin);
				list[a] = vvedit();
				break;
			case 6:
				break;
			default:printf("vvedi iso raz!\n");
				break;
			}
		}
		else {
			printf("data does not exist.Please add book!\n");
			rewind(stdin);
			list[amount++] = vvedit();
		}
	} while (choice != 6);
	return  amount;
}
void saveresult(kniga* list, int amount, char* outfilename) {
	char a[50];
	int sum = 0;
	kniga b[10];

	printf("Enter the publisher's name:");
	fgets(a, 49, stdin);
	a[strcspn(a, "\n")] = 0;
	int timSV = 0;
	title();
	int j = 0;
	for (int i = 0; i < amount; i++) {
		if ((strcmp(a, list[i].pub) == 0)) {
			sum++;
			b[j++] = list[i];
			timSV = 1;
		}
	}
	if (timSV == 1) {
		for (int m = 0; m < sum; m++) {
			for (int n = sum - 1; n > m; n--) {
				if (b[n].year < b[n - 1].year)
				{
					kniga l = b[n];
					b[n] = b[n - 1];
					b[n - 1] = l;
				}
			}
		}
		for (int m = 0; m < sum; m++) {
			for (int n = sum - 1; n > m; n--) {
				if (b[n].year == b[n - 1].year) {
					if (strcmp(b[n].namebook, b[n - 1].namebook) < 0)
					{
						kniga x = b[n];
						b[n] = b[n - 1];
						b[n - 1] = x;
					}
				}
			}
		}
		printf("Sorted by year and by book title:\n");
		for (int m = 0; m < sum; m++) {
			vuvod(b[m]);
			printf("\n");
		}
	}
	FILE* f2;
	fopen_s(&f2, outfilename, "w");
	for (int i = 0; i < sum; i++)
	{
		fprintf(f2, "%s\n%s\n%d\n%s\n%s\n", b[i].cipher, b[i].fullname, b[i].year, b[i].namebook, b[i].pub);
	}
	fclose(f2);
}
int main() {
	int k;
	int vybirat = 0;
	kniga list[200];
	int amount = 0;
	char c[30], d[30];
	printf("Enter the name file:");
	fgets(d, 29, stdin);
	d[strcspn(d, "\n")] = 0;
	read(d, list, &amount);
	printf("          ---------------MENU1------------\n");
	printf("          1)Show data?\n          2)word with data?\n          3)save data?\n          4)save the processed results?\n          5)back?\n");
	do
	{
		printf("\nVybiraite:");
		scanf_s("%d", &vybirat);
		switch (vybirat)
		{
		case 1:
			title();
			for (int i = 0; i < amount; i++) {
				vuvod(list[i]);
			}
			break;
		case 2:
			k = dataProces(list, amount);
			amount = k;
			break;
		case 3:
			write(d, list, amount);
			break;
		case 4:
			rewind(stdin);
			printf("enter the outfile name:");
			fgets(c, 29, stdin);
			c[strcspn(c, "\n")] = 0;
			saveresult(list, amount, c);
			break;
		case 5:
			break;
		default:printf("vvedi iso raz!\n");
			break;
		}

	} while (vybirat != 5);
	return 0;
}