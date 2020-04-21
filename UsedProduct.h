#define STR_LEN 30
#define TRUE 1
#define FALSE 0

typedef struct _product
{
	int id;
	char p_name[STR_LEN];
	char s_name[STR_LEN];
	int price;
	int is_sold;
	char b_name[STR_LEN];
	int satisfaction;
} Product;

void InitProduct();
int ProductAdd(int id, char *pro, char *s, int pri, int mode, int *store);
int PAddNull();
void PCheckCapacity();
int PFirstAvailable(int mode);
Product *PFindByID(int id);
char *PToString(Product *p);
int PGetID(Product *p);
char *PGetPName(Product *p);
char *PGetSName(Product *p);
int PGetPrice(Product *p);
int PIsSold(Product *p);
char *PGetBName(Product *p);
int PGetSatisfaction(Product *p);
int GetCapacity();
int GetCount();
int GetLength();
int IsAvailable(Product *p);
void PGetAll(Product *a[]);
void PGetAllByPName(Product *a[], char *p);
void PGetAllBySName(Product *a[], char *s);
void PGetAllByBName(Product *a[], char *b);
void PUpdate(Product *p, char *pro, char *s, int pri);
int PPurchased(Product *p, char *b, int sat);
void PUpdatePurchase(Product *p, char *pro, char *s, int pri, char *b, int sat);
void ProductRemove(Product *p);
void PRemoveAll();
void ProductCollect();
void ProductSwap(int i1, int i2);
void ProductSort(int (*comp)(Product *p1, Product *p2));
char *GetStringToSave(Product *p);
