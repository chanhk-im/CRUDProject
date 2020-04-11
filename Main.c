#include <stdio.h>
#include <string.h>
#include "UsedProduct.h"

void CreateRecord();
void ReadRecord();
void UpdateRecord();
void PurchaseRecord();
void SearchRecord();
void SearchByPName();
void SearchBySName();
void SearchByBName();
void LoadRecord();
void SaveRecord();
void CreateReport();
void Settings();
void Debug();
void _ShowAll();

int main()
{
	int menu = 0;

	InitProduct();

	while (TRUE)
	{
		printf("\n[Menu] Input a number to select.\n");
		printf("===============================================\n");
		printf("1. Create  2. Read  3. Update  4. Purchase\n");
		printf("5. Search  X. Delete  7. Load  8. Save\n");
		printf("9. Report   10. Setting   0. Exit\n");
		printf("===============================================\n");
		printf(">> ");
		scanf("%d", &menu);

		switch (menu)
		{
		case 1:
			CreateRecord();
			break;
		
		case 2:
			ReadRecord();
			break;

		case 3:
			UpdateRecord();
			break;

		case 4:
			PurchaseRecord();
			break;

		case 5:
			SearchRecord();
			break;

		case 7:
			LoadRecord();
			break;

		case 8:
			SaveRecord();
			break;

		case 9:
			CreateReport();
			break;

		case 10:
			Settings();
			break;

#ifdef DEBUG		
		case 22:
			Debug();
			break;
#endif

		case 33:
			_ShowAll();
			break;

		case 0:
		default:
			break;
		}

		if (menu == 0)
		{
			printf("[Exit] Do you really want to quit? (0 to quit)\n");
			printf(">> ");
			scanf("%d", &menu);

			if (menu == 0)
				break;
		}
	}
}

void CreateRecord()
{
	int id;
	char prod[STR_LEN];
	char sell[STR_LEN];
	int price;
	
	getchar();

	printf("\n<< Create a Product >>\n");
	
	printf("Product Name >> ");
	fgets(prod, STR_LEN, stdin);
	printf("Seller Name >> ");
	fgets(sell, STR_LEN, stdin);
	printf("Price of Product >> ");
	scanf("%d", &price);

	prod[strlen(prod) - 1] = '\0';
	sell[strlen(sell) - 1] = '\0';
	
	if (ProductAdd(-1, prod, sell, price, FALSE, &id))
	{
		printf("\n[Create] Success to add a product!\n");
		printf("[Create] Your ID is %d, please don't forget it!\n", id);
	}
	else
		printf("\n[Create] Failed to add a product!\n");
}

void ReadRecord()
{
	int id;
	Product *find;

	getchar();

	printf("\n<< Read a Record >>\n");
	printf("\n[Read] Input id to read\n");
	printf(">> ");
	scanf("%d", &id);
	find = PFindByID(id);
	
	if (find == NULL)
	{
		printf("\n[Read] Not found!\n");
		return;
	
	}
	printf("\n==================================\n");
	
	if (PIsSold(find))
		printf("[SOLD]\n");

	printf("id: %d\n", PGetID(find));
	printf("Product Name: %s\n", PGetPName(find));
	printf("Seller Name: %s\n", PGetSName(find));
	printf("Price: %d\n", PGetPrice(find));
	
	if (PIsSold(find))
	{
		printf("Buyer Name: %s\n", PGetBName(find));
		printf("Satisfaction: %d\n", PGetSatisfaction(find));
	}
	printf("==================================\n");
}

void UpdateRecord()
{
	int id, yes, price, satis;
	Product *find;
	char prod[STR_LEN];
	char sell[STR_LEN];
	char buy[STR_LEN];

	printf("\n<< Update a Record >>\n");
	printf("\n[Update] Input id to update\n");
	printf(">> ");
	scanf("%d", &id);
	find = PFindByID(id);

	if (find == NULL)
	{
		printf("\n[Update] Not found!\n");
		return;
	}
	
	printf("\n[Update] A data is found! > %s\n", PToString(find));
	printf("[Update] Do you want to change this data?\n");
	printf("================\n");
	printf("1. Yes  2. No\n");
	printf("================\n");
	printf(">> ");
	scanf("%d", &yes);

	if (yes == 2)
		return;
	
	getchar();

	printf("Product Name >> ");
	fgets(prod, STR_LEN, stdin);
	printf("Seller Name >> ");
	fgets(sell, STR_LEN, stdin);
	printf("Price of Product >> ");
	scanf("%d", &price);
	prod[strlen(prod) - 1] = '\0';
	sell[strlen(sell) - 1] = '\0';
	

	if (PIsSold(find))
	{
		getchar();
		printf("Buyer Name >> ");
		fgets(buy, STR_LEN, stdin);
		printf("Satisfaction >> ");
		scanf("%d", &satis);
		buy[strlen(buy) - 1] = '\0';

		PUpdatePurchase(find, prod, sell, price, buy, satis);
	}
	else
		PUpdate(find, prod, sell, price);

#ifdef DEBUG
	printf("[DEBUG] Data updated to %s\n", PToString(find));
#endif
	printf("\n[Update] Data updated!\n");
}

void PurchaseRecord()
{
	int id, yes, satis;
	Product *find;
	char buy[STR_LEN];

	printf("\n<< Purchase >>\n");
	printf("\n[Purchase] Input id to purchase\n");
	printf(">> ");
	scanf("%d", &id);
	find = PFindByID(id);

	if (find == NULL)
	{
		printf("\n[Purchase] Not found!\n");
		return;
	}
	
	printf("\n[Purchase] A data is found! > %s\n", PToString(find));
	printf("[Purchase] Do you want to purchase this data?\n");
	printf("================\n");
	printf("1. Yes  2. No\n");
	printf("================\n");
	printf(">> ");
	scanf("%d", &yes);

	if (yes == 2)
		return;

	getchar();
	printf("Buyer Name >> ");
	fgets(buy, STR_LEN, stdin);
	printf("Satisfaction >> ");
	scanf("%d", &satis);
	buy[strlen(buy) - 1] = '\0';
	if (PPurchased(find, buy, satis))
	{
#ifdef DEBUG
		printf("\n[DEBUG] Data updated to %s\n", PToString(find));
#endif
		printf("\n[Purchase] Successed to purchase a product!\n");
	}
	else
		printf("[Purchase] This product was already purchased...\n");
}

void SearchRecord()
{
	int s_menu = 0;

	printf("\n<< Search Records >>\n");
	printf("\n[Search] What data will you search?\n");
	printf("=========================================================\n");
	printf("1. Product Name  2. Seller Name  3. Buyer Name  0. Cancel\n");
	printf("=========================================================\n");
	printf(">> ");
	scanf("%d", &s_menu);

	switch(s_menu)
	{
	case 1:
		SearchByPName();
		break;

	case 2:
		SearchBySName();
		break;

	case 3:
		SearchByBName();
		break;

	case 0:
	default:
		break;
	}
}

void SearchByPName()
{
	int cnt = 0;
	int s_cnt = 0;

	int s_sum = 0;
	int p_sum = 0;

	int max = 0;
	int min = 0;

	float s_avg = 0;
	float p_avg = 0;

	char p_name[STR_LEN];
	
	getchar();
	
	printf("\n[Search] Input a product name to read\n");
	printf(">> ");
	fgets(p_name, STR_LEN, stdin);
	p_name[strlen(p_name) - 1] = '\0';

	Product *all[GetCapacity()];
	PGetAllByPName(all, p_name);

	for (int i = 0; all[i] != NULL; i++)
	{
		cnt += 1;
		p_sum += PGetPrice(all[i]);

		if (PGetSatisfaction(all[i]) != -1)
		{
			s_sum += PGetSatisfaction(all[i]);
			s_cnt += 1;
		}


		if (cnt <= 1)
		{
			max = p_sum;
			min = max;
		}
		else
		{
			if (PGetPrice(all[i]) > max)
				max = PGetPrice(all[i]);

			if (PGetPrice(all[i]) < min)
				min = PGetPrice(all[i]);
		}
	}
	
	p_avg = p_sum / (float)cnt;
	if (s_cnt > 0)
		s_avg = s_sum / (float)s_cnt;
	else
		s_avg = 0;

	printf("\n[ Product %s's Information ]\n\n", p_name);
	printf("========================================\n");
	printf("Count: %d\n", cnt);
	printf("Sold Count: %d\n\n", s_cnt);
	printf("Average of Price: %.1f\n", p_avg);
	printf("Maximum Price: %d\n", max);
	printf("Minimum Price: %d\n\n", min);
	printf("Average of Satisfaction: %.1f\n", s_avg);
	printf("========================================\n\n");

	printf("==================================================\n");
	for (int i = 0; all[i] != NULL; i++)
		printf("%s\n", PToString(all[i]));
	printf("==================================================\n");
}

void SearchBySName()
{
	int cnt = 0;
	int s_cnt = 0;

	int s_sum = 0;
	int sum_price = 0;

	float s_avg = 0;

	char s_name[STR_LEN];
	
	getchar();
	
	printf("\n[Search] Input a seller name to read\n");
	printf(">> ");
	fgets(s_name, STR_LEN, stdin);
	s_name[strlen(s_name) - 1] = '\0';

	Product *all[GetCapacity()];
	PGetAllBySName(all, s_name);

	for (int i = 0; i < GetLength() && all[i] != NULL; i++)
	{
		cnt += 1;
		sum_price += PGetPrice(all[i]);
		if (PGetSatisfaction(all[i]) != -1)
		{
			s_sum += PGetSatisfaction(all[i]);
			s_cnt += 1;
		}
	}
	
	if (s_cnt > 0)
		s_avg = s_sum / (float)s_cnt;
	else
		s_avg = 0;

	printf("\n[ Seller %s's Information ]\n\n", s_name);
	printf("========================================\n");
	printf("Count: %d\n", cnt);
	printf("Sold Count: %d\n\n", s_cnt);
	printf("Average of Satisfaction: %.1f\n", s_avg);
	printf("Sum of Price: %d\n", sum_price);
	printf("========================================\n");

	printf("==================================================\n");
	for (int i = 0; all[i] != NULL; i++)
		printf("%s\n", PToString(all[i]));
	printf("==================================================\n");
}

void SearchByBName()
{
	int cnt = 0;
	int s_cnt = 0;

	int s_sum = 0;
	int sum_price = 0;

	float s_avg = 0;

	char b_name[STR_LEN];
	
	getchar();
	
	printf("\n[Search] Input a buyer name to read\n");
	printf(">> ");
	fgets(b_name, STR_LEN, stdin);
	b_name[strlen(b_name) - 1] = '\0';

	Product *all[GetCapacity()];
	PGetAllByBName(all, b_name);

	for (int i = 0; i < GetLength() && all[i] != NULL; i++)
	{
		cnt += 1;
		sum_price += PGetPrice(all[i]);

		if (PGetSatisfaction(all[i]) != -1)
		{
			s_sum += PGetSatisfaction(all[i]);
			s_cnt += 1;
		}
	}
	
	if (s_cnt > 0)
		s_avg = s_sum / (float)s_cnt;
	else
		s_avg = 0;

	printf("\n[ Buyer %s's Information ]\n\n", b_name);
	printf("========================================\n");
	printf("Count: %d\n", cnt);
	printf("Average of Satisfaction: %.1f\n", s_avg);
	printf("Sum of Price: %d\n", sum_price);
	printf("========================================\n");

	printf("==================================================\n");
	for (int i = 0; all[i] != NULL; i++)
		printf("%s\n", PToString(all[i]));
	printf("==================================================\n");
}

void LoadRecord()
{
	int yes;
	char file_name[STR_LEN];
	FILE *f;

	char p_name[STR_LEN], s_name[STR_LEN], b_name[STR_LEN];
	char check_null;
	int id, price, is_sold, satisfaction;

	printf("\n<< Load Records >>\n");
	printf("\n[Load] All data will be deleted and new records will be loaded.\n");
	printf("================\n");
	printf("1. Yes  2. No\n");
	printf("================\n");
	printf(">> ");
	scanf("%d", &yes);

	if (yes == 2)
		return;
	
	printf("\n[Load] Enter file name to load\n");
	printf(">> ");
	scanf("%s", file_name);

	PRemoveAll();

	f = fopen(file_name, "r");
	if (f == NULL)
	{
		printf("[Load] file load error!\n");
		return;
	}

	while (!feof(f))
	{
		int n = fscanf(f, "%c %d %s %s %d %d %s %d", &check_null, &id, p_name, s_name, &price, &is_sold, b_name, &satisfaction);
		if (n < 8)
		{
#ifdef DEBUG
			printf("[DEBUG] %d data read, check_null is %c\n", n, check_null);
#endif
			break;
		}

		if (check_null == 'N')
		{
			PAddNull();
#ifdef DEBUG
			printf("[DEBUG] null added!\n");
#endif
			fscanf(f, "%c", &check_null);
			continue;
		}

		if (PFindByID(id) != NULL)
		{
#ifdef DEBUG
			printf("[DEBUG] Duplicated id \"%d\"!\n", id);
#endif
			continue;
		}

		ProductAdd(id, p_name, s_name, price, TRUE, NULL);
		fscanf(f, "%c", &check_null);
		if (is_sold)
		{
			Product *purchase = PFindByID(id);
			PPurchased(purchase, b_name, satisfaction);
#ifdef DEBUG
			printf("[DEBUG] %s is sold product\n", s_name);
#endif
		}
#ifdef DEBUG
		printf("[DEBUG] id %d loaded!\n", id);
#endif
	}

	printf("[Load] %d records are loaded from file %s!\n", GetCount(), file_name);
	fclose(f);
}

void SaveRecord()
{
	FILE *f;
	char file_name[STR_LEN];

	printf("\n<< Save Records >>\n");
	printf("\n[Save] Enter file name to save\n");
	printf(">> ");
	scanf("%s", file_name);

	f = fopen(file_name, "w");
	if (f == NULL)
	{
		printf("[Save] file error!\n");
		return;
	}

	int size = GetLength();
	
	Product *all[GetLength()];
	PGetAll(all);

	for (int i = 0; i < size; i++)
	{
		Product *p = all[i];
		if (p == NULL)
		{
			fprintf(f, "N N N N -1 -1 N -1\n");
#ifdef DEBUG
			printf("[DEBUG] Saved null\n");
#endif
		}
		else
		{
			fprintf(f, "%s\n", GetStringToSave(p));
#ifdef DEBUG
			printf("[DEBUG] Save a string \"%s\"\n", GetStringToSave(p));
#endif
		}		
	}
	fclose(f);
}

void CreateReport()	
{
	FILE *f;
	char file_name[STR_LEN];

	printf("\n<< Create Report >>\n");
	printf("\n[Report] Enter file name to create a report\n");
	printf(">> ");
	scanf("%s", file_name);

	f = fopen(file_name, "w");
	if (f == NULL)
	{
		printf("[Report] file error!\n");
		return;
	}
	
	Product *all[GetCapacity()];
	PGetAll(all);

	fprintf(f, "<< Report >>\n\n\n");
	
	fprintf(f, "1. Summary\n\n");
	fprintf(f, " - Products Amount: %d\n", GetCount());
	
	int sold_count = 0;
	int prod_count = 0;
	int sell_count = 0;
	int buy_count = 0;
	
	for (int i = 0; i < GetLength(); i++)
	{
		if (all[i] == NULL)
			continue;
		if (PIsSold(all[i]))
		{
			sold_count += 1;
			buy_count += 1;
		}
#ifdef DEBUG
		printf("[DEBUG] %d: %s\n", i + 1, PGetPName(all[i]));
#endif
		for (int j = 0; j < i; j++)
		{
			if (strcmp(PGetPName(all[i]), PGetPName(all[j])) == 0)
			{
				prod_count -= 1;
				break;
			}
			
			if (strcmp(PGetSName(all[i]), PGetSName(all[j])) == 0)
			{
				sell_count -= 1;
				break;
			}
			if (PIsSold(all[i]))
			{
				if (strcmp(PGetBName(all[i]), PGetBName(all[j])) == 0)
				{
					buy_count -= 1;
					break;
				}
			}
		}
		printf("[DEBUG] %d\n", i + 1);
		prod_count++;
		sell_count++;
	}
#ifdef DEBUG
	printf("[DEBUG] Sold count: %d\n", sold_count);
	printf("[DEBUG] Product count: %d\n", prod_count);
	printf("[DEBUG] Seller count: %d\n", sell_count);
	printf("[DEBUG] Buyer count: %d\n", buy_count);
#endif

	fprintf(f, " - Sold Count: %d\n", sold_count);
	fprintf(f, " - Product Count: %d\n", prod_count);
	fprintf(f, " - Seller Count: %d\n", sell_count);
	fprintf(f, " - Buyer Count: %d\n", buy_count);
	fprintf(f, "\n\n");

	fprintf(f, "2. Information of Products\n\n");
	for (int i = 0; i < GetLength(); i++)
	{
		int is_exist;
		for (int j = 0; j < i; j++)
		{
			is_exist = FALSE;
			if (strcmp(PGetPName(all[i]), PGetPName(all[j])) == 0)
			{
#ifdef DEBUG
				printf("[DEBUG] %s already exist in %d!\n", PGetPName(all[i]), j);
#endif
				is_exist = TRUE;
				break;
			}
		}
		if (!is_exist)
		{
			int cnt = 0, s_cnt = 0;
			int max = 0, min;
			float p_avg, s_avg;
			int s_sum = 0, p_sum = 0;

			Product *all_f[GetCapacity()];
			PGetAllByPName(all_f, PGetPName(all[i]));
			

			for (int i = 0; all_f[i] != NULL; i++)
			{
				cnt += 1;
				p_sum += PGetPrice(all_f[i]);
	
				if (PGetSatisfaction(all_f[i]) != -1)
				{
					s_sum += PGetSatisfaction(all_f[i]);
					s_cnt += 1;
				}


				if (cnt <= 1)
				{
					max = p_sum;
					min = max;
				}
				else
				{
					if (PGetPrice(all_f[i]) > max)
						max = PGetPrice(all_f[i]);
					if (PGetPrice(all_f[i]) < min)
						min = PGetPrice(all_f[i]);
				}
			}
	
			p_avg = p_sum / (float)cnt;
			if (s_cnt > 0)
				s_avg = s_sum / (float)s_cnt;
			else
				s_avg = 0;
#ifdef DEBUG
			printf("[DEBUG] %s\n", PGetPName(all[i]));
#endif
			fprintf(f, " - Product %s's information:\n", PGetPName(all[i]));
			fprintf(f, "========================================\n");
			fprintf(f, " Count: %d\n", cnt);
			fprintf(f, " Sold Count: %d\n\n", s_cnt);
			fprintf(f, " Average of Price: %.1f\n", p_avg);
			fprintf(f, " Maximum Price: %d\n", max);
			fprintf(f, " Minimum Price: %d\n\n", min);
			fprintf(f, " Average of Satisfaction: %.1f\n", s_avg);
			fprintf(f, "========================================\n\n");
		}
	}
	fprintf(f, "\n\n");

	fprintf(f, "3. Information of Sellers\n\n");
	for (int i = 0; i < GetLength(); i++)
	{
		int is_exist;
		for (int j = 0; j < i; j++)
		{
			is_exist = FALSE;
			if (strcmp(PGetSName(all[i]), PGetSName(all[j])) == 0)
			{
#ifdef DEBUG
				printf("[DEBUG] %s already exist in %d!\n", PGetSName(all[i]), j);
#endif
				is_exist = TRUE;
				break;
			}
		}
		if (!is_exist)
		{
			int cnt = 0;
			int s_cnt = 0;
	
			int s_sum = 0;
			int sum_price = 0;

			float s_avg = 0;
	
			Product *all_f[GetCapacity()];
			PGetAllBySName(all_f, PGetSName(all[i]));

			for (int i = 0; i < GetLength() && all_f[i] != NULL; i++)
			{
				cnt += 1;
				sum_price += PGetPrice(all_f[i]);
				if (PGetSatisfaction(all_f[i]) != -1)
				{
					s_sum += PGetSatisfaction(all_f[i]);
					s_cnt += 1;
				}
			}
	
			if (s_cnt > 0)
				s_avg = s_sum / (float)s_cnt;
			else
				s_avg = 0;
#ifdef DEBUG
			printf("[DEBUG] %s\n", PGetSName(all[i]));
#endif
			fprintf(f, "\n[ Seller %s's Information ]\n\n", PGetSName(all[i]));
			fprintf(f, "========================================\n");
			fprintf(f, " Count: %d\n", cnt);
			fprintf(f, " Sold Count: %d\n\n", s_cnt);
			fprintf(f, " Average of Satisfaction: %.1f\n", s_avg);
			fprintf(f, " Sum of Price: %d\n", sum_price);
			fprintf(f, "========================================\n");
		}
	}
	fprintf(f, "\n\n");

	fprintf(f, "4. Information of Buyers\n\n");
	for (int i = 0; i < GetLength(); i++)
	{
		if (!PIsSold(all[i]))
			continue;

		int is_exist = FALSE;
		for (int j = 0; j < i; j++)
		{
			if (!PIsSold(all[j]))
				continue;

			is_exist = FALSE;
			if (strcmp(PGetBName(all[i]), PGetBName(all[j])) == 0)
			{
#ifdef DEBUG
				printf("[DEBUG] %s already exist in %d!\n", PGetBName(all[i]), j);
#endif
				is_exist = TRUE;
				break;
			}
		}
		if (!is_exist)
		{
			int cnt = 0;
	
			int s_sum = 0;
			int sum_price = 0;

			float s_avg = 0;
	
			Product *all_f[GetCapacity()];
			PGetAllByBName(all_f, PGetBName(all[i]));

			for (int i = 0; i < GetLength() && all_f[i] != NULL; i++)
			{
				cnt += 1;
				sum_price += PGetPrice(all_f[i]);
				if (PGetSatisfaction(all_f[i]) != -1)
					s_sum += PGetSatisfaction(all_f[i]);
			}
	
			if (cnt > 0)
				s_avg = s_sum / (float)cnt;
			else
				s_avg = 0;
#ifdef DEBUG
			printf("[DEBUG] %s\n", PGetBName(all[i]));
#endif
			fprintf(f, "\n[ Buyer %s's Information ]\n\n", PGetBName(all[i]));
			fprintf(f, "========================================\n");
			fprintf(f, " Count: %d\n", cnt);
			fprintf(f, " Average of Satisfaction: %.1f\n", s_avg);
			fprintf(f, " Sum of Price: %d\n", sum_price);
			fprintf(f, "========================================\n");
		}
	}
	fprintf(f, "\n\n");

	fprintf(f, "5. All of Products' List\n\n\n");
	fprintf(f, "==================================================\n");
	for (int i = 0; i < GetLength(); i++)
	{
		if (IsAvailable(all[i]))
			fprintf(f, " %s\n", PToString(all[i]));
	}
	fprintf(f, "==================================================\n");
}

void Settings()
{
	int menu, yes;
	
	while (TRUE)
	{
		printf("\n<< Setting >>\n");
		printf("\n[Setting] Input a number to select.\n");
		printf("=================================\n");
		printf("1. Collect  X. Sort  0. Exit\n");
		printf("=================================\n");
		printf(">> ");
		scanf("%d", &menu);

		if (menu == 1)
		{
			printf("[Setting 1] Do you want to collect this record?\n");
			printf("================\n");
			printf("1. Yes  2. No\n");
			printf("================\n");
			printf(">> ");
			scanf("%d", &yes);

			if (yes == 1)
			{
				ProductCollect();
#ifdef DEBUG
				printf("[DEBUG] Collection complete!\n");
#endif
			}
		}
		else if (menu == 0)
			return;
	}
}

void Debug()
{
	/*	
	Product *all[GetCapacity()];
	PGetAll(all);
	for (int i = 0; i < GetLength(); i++)
	{
		if (IsAvailable(all[i]))
			printf("%s\n", PGetPName(all[i]));
	}
	printf("[DEBUG] Success!\n");
	*/
}

void _ShowAll()
{
	Product *all[GetCapacity()];
	PGetAll(all);
	for (int i = 0; i < GetLength(); i++)
	{
		if (IsAvailable(all[i]))
			printf("%s\n", PToString(all[i]));
	}
	printf("[DEBUG] Success!\n");
}
