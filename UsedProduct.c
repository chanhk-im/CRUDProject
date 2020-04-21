#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UsedProduct.h"

Product **products;
int capacity = 0;
int p_length = 0;
int p_count = 0;
int cur_id = 0;

void InitProduct()
{
	capacity = 10;
	products = (Product **)calloc(capacity, sizeof(Product *));
}

int ProductAdd(int id, char *pro, char *s, int pri, int mode, int *store)
{
	PCheckCapacity();

	Product *newProduct = (Product *)malloc(sizeof(Product));
	if (id <= 0)
	{
		cur_id += 1;
		newProduct->id = cur_id;
	}
	else
	{
		newProduct->id = id;
		if (id > cur_id)
			cur_id = id;
	}
	strcpy(newProduct->p_name, pro);
	strcpy(newProduct->s_name, s);
	newProduct->price = pri;
	newProduct->is_sold = FALSE;
	strcpy(newProduct->b_name, "_null");
	newProduct->satisfaction = -1;
	
	if (store != NULL)
		*store = newProduct->id;
	*(products + PFirstAvailable(mode)) = newProduct;
	p_length += 1;
	p_count += 1;

	return TRUE;
}

int PAddNull()
{
	PCheckCapacity();
	Product *null = NULL;

	*(products + PFirstAvailable(TRUE)) = null;
	p_length += 1;

	return TRUE;
}

void PCheckCapacity()
{
	if (p_length >= capacity)
	{
		capacity *= 2;
		products = (Product **)realloc(products, sizeof(Product *) * capacity);
	}
}

int PFirstAvailable(int mode)
{
	if (mode == 1)
		return p_length;

	int i = 0;
	for (i = 0; i < p_length; i++)
	{
		if (products[i] == NULL)
		{
			p_length -= 1;
			return i;
		}
	}

	return i;
}

Product *PFindByID(int id)
{
	int i;
	for (i = 0; i < p_length; i++)
	{
		if (products[i] != NULL && products[i]->id == id)
			return products[i];
	}
	return NULL;
}

char *PToString(Product *p)
{
	static char str[140];
	if (PIsSold(p))
		sprintf(str, "[SOLD] %d / %s / %s / %d / %s / %d", p->id, p->p_name, p->s_name, p->price, p->b_name, p->satisfaction);
	else
		sprintf(str, "       %d / %s / %s / %d", p->id, p->p_name, p->s_name, p->price);
	
	return str;
}

int PGetID(Product *p)
{
	return p->id;
}

char *PGetPName(Product *p)
{
	return p->p_name;
}

char *PGetSName(Product *p)
{
	return p->s_name;
}

int PGetPrice(Product *p)
{
	return p->price;
}

int PIsSold(Product *p)
{
	return p->is_sold;
}

char *PGetBName(Product *p)
{
	return p->b_name;
}

int PGetSatisfaction(Product *p)
{
	return p->satisfaction;
}

int GetCount()
{
	return p_count;
}

int GetLength()
{
	return p_length;
}

int GetCapacity()
{
	return capacity;
}

int IsAvailable(Product *p)
{
	if (p == NULL)
		return FALSE;
	else
		return TRUE;
}

void PGetAll(Product *a[])
{
	for (int i = 0; i < p_length; i++)
		a[i] = products[i];
}

void PGetAllByPName(Product *a[], char *p)
{
	int cnt = 0;

	for (int i = 0; i < p_length; i++)
	{
		if (products[i] != NULL && strcmp(products[i]->p_name, p) == 0)
		{
			a[cnt] = products[i];
			cnt++;
		}
	}

	a[cnt] = NULL;
}

void PGetAllBySName(Product *a[], char *s)
{
	int cnt = 0;

	for (int i = 0; i < p_length; i++)
	{
		if (products[i] != NULL && strcmp(products[i]->s_name, s) == 0)
		{
			a[cnt] = products[i];
			cnt++;
		}
	}

	a[cnt] = NULL;
}

void PGetAllByBName(Product *a[], char *b)
{
	int cnt = 0;

	for (int i = 0; i < p_length; i++)
	{
		if (products[i] != NULL && strcmp(products[i]->b_name, b) == 0)
		{
			a[cnt] = products[i];
			cnt++;
		}
	}

	a[cnt] = NULL;
}

void PUpdate(Product *p, char *pro, char *s, int pri)
{
	strcpy(p->p_name, pro);
	strcpy(p->s_name, s);
	p->price = pri;
}

int PPurchased(Product *p, char *b, int sat)
{
	if (p->is_sold)
		return FALSE;

	p->is_sold = TRUE;
	strcpy(p->b_name, b);
	p->satisfaction = sat;
	return TRUE;
}

void PUpdatePurchase(Product *p, char *pro, char *s, int pri, char *b, int sat)
{
	strcpy(p->p_name, pro);
	strcpy(p->s_name, s);
	p->price = pri;
	strcpy(p->b_name, b);
	p->satisfaction = sat;
}

void ProductRemove(Product *p)
{
	for (int i = 0; i < p_length; i++)
	{
		if (products[i] == p)
		{
			free(products[i]);
			products[i] = NULL;
			p_count -= 1;
			return;
		}
	}
}

void PRemoveAll()
{
	for (int i = 0; i < p_length; i++)
		free(products[i]);	

	p_length = 0;
	p_count = 0;
	capacity = 10;
	products = (Product **)realloc(products, sizeof(Product *) * capacity);
}

void ProductCollect()
{
	for (int i = 0; i < p_length - 1; i++)
	{
		while (TRUE)
		{
			if (products[i] != NULL)
				break;
			for (int j = i; j < p_length - 1; j++)
				products[j] = products[j + 1];
			p_length--;
		}
	}
}

void ProductSwap(int i1, int i2)
{
	Product *temp = products[i1];
	products[i1] = products[i2];
	products[i2] = temp;
}

void ProductSort(int (*comp)(Product *p1, Product *p2))
{
	ProductCollect();

	for (int i = 0; i < p_length - 1; i++)
	{
		for (int j = i + 1; j < p_length; j++)
		{
#ifdef DEBUG
			printf("[DEBUG] %s %s %d\n", products[i]->p_name, products[j]->p_name, comp(products[i], products[j]));
#endif
			 if (comp(products[i], products[j]) == 1)
			 {
				 ProductSwap(i, j);
#ifdef DEBUG
				 printf("[DEBUG] swap %s %s\n", products[i]->p_name, products[j]->p_name);
#endif
			 }
		}
	}
}

char *GetStringToSave(Product *p)
{
	static char str[120];
	sprintf(str, "O %d %s %s %d %d %s %d", p->id, p->p_name, p->s_name, p->price, p->is_sold, p->b_name, p->satisfaction);
	return str;
}
