#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
typedef struct Ogrenci
{
	char ogrID[9];
	char ad[30];
	char soyad[30];
	int puan;
	struct Ogrenci * next;
	struct Ogrenci * prev;
}
OGRENCILER;
typedef struct Yazar
{
	int yazarID;
	char yazarAd[30];
	char yazarSoyad[30];
	struct Yazar * next;
}
YAZARLAR;
typedef struct Kitap
{
	char kitapAdi[30];
	char ISBN[15];
	int adet;
	struct Kitap * next;
	struct KitapOrnek * head;
}
KITAPLAR;
typedef struct KitapOrnek
{
	char EtiketNo[20];
	char Durum[9];
	struct KitapOrnek * next;
}
KITAPORNEK;
typedef struct KitapYazar
{
	char ISBN[15];
	int YazarID;
}
KITAPYAZAR;
typedef struct Tarih
{
	unsigned int gun: 5;
	unsigned int ay: 4;
	unsigned int yil: 12;
}
TARIH;
typedef struct KitapOdunc
{
	char EtiketNo[20];
	char ogrID[9];
	unsigned int islemTipi: 1;
	struct Tarih islemTarihi;
}
KITAP_ODUNC;
char *removeSpacesFromStr(char *string);
int compareByID(OGRENCILER *student, char *value);
int compareByName(OGRENCILER *student, char *value);
void changeID(OGRENCILER *a, char *b);
void changeName(OGRENCILER *a, char *b);
void changeSurname(OGRENCILER *a, char *b);
OGRENCILER* ogrenci_oku(char *filename);
void print_students(OGRENCILER *head);
void ogrenci_sil(OGRENCILER **head, char *value, int(*comparisonFunc)(OGRENCILER *, char *));
void ogrenci_guncelle(OGRENCILER **head, char *value, int(*comparisonFunc)(OGRENCILER *, char *), char *new_value, void(*changeFunc)(OGRENCILER *, char *));
void ogrenci_ekle(OGRENCILER **head);
int ogrenci_write(OGRENCILER *head, char *filename);
YAZARLAR* yazar_oku(char *filename);
void print_yazar(YAZARLAR *head);
int yazar_sil(YAZARLAR **head, char *name, KITAPYAZAR *dizi, int size);
void yazar_ekle(YAZARLAR **head);
int yazar_write(YAZARLAR *head, char *filename);
KITAPLAR* kitap_oku(char *filename, KITAP_ODUNC *kitapodunc, int size);
int kitap_ekle(KITAPLAR **head, KITAPYAZAR **kitapyazar, int *size);
void print_kitap(KITAPLAR *head);
int kitap_write(KITAPLAR *head, char *filename);
KITAPYAZAR* kitapyazar_oku(char *filename, int *size);
KITAP_ODUNC* kitapodunc_oku(char *filename, int *size);
void print_kitapyazar(KITAPYAZAR *head);
int kitapyazar_write(KITAPYAZAR *head, char *filename, int size);
void teslim_etmeyen_listele(OGRENCILER *ogrenci_head, KITAP_ODUNC *kitapodunc, int size);
void print_student_by_id(char *a, OGRENCILER *head, KITAP_ODUNC *head_2, int size);
void print_student_by_name(char *a, OGRENCILER *head, KITAP_ODUNC *head_2, int size);
void cezali_ogrencileri_listele(OGRENCILER *head);
KITAP_ODUNC* kitap_odunc_al(OGRENCILER *head, int *size, KITAP_ODUNC *kitapodunc, char *a, KITAPLAR *kitap_head);
int kitapodunc_write(KITAP_ODUNC *head, char *filename, int size);
int dayCalculator(TARIH date1, TARIH date2);
KITAP_ODUNC* kitap_teslim_et(OGRENCILER **head, int *size, KITAP_ODUNC *kitapodunc, char *a, KITAPLAR *kitap_head);
int yazar_guncelle(YAZARLAR **head);
int yazar_bilgisi_goruntule(YAZARLAR *head, KITAPYAZAR *kitapyazar, int size, KITAPLAR *kitap_head);
int kitap_guncelle(KITAPLAR **head);
int kitap_bilgisi_goruntule(KITAPLAR *head, YAZARLAR *yazar_head, KITAPYAZAR *kitapyazar, int size, char *a);
int raftaki_kitap_listele(KITAPLAR *kitap_head);
int zamaninda_teslim_etmeyen_listele(KITAP_ODUNC *kitapodunc, int size, KITAPLAR *kitap_head, YAZARLAR *yazar_head, KITAPYAZAR *kitapyazar, int size2);
int kitap_adet_bilgisi(KITAPLAR *kitap_head, char *a);
int kitap_yazar_guncelle(KITAPLAR *kitap_head, YAZARLAR *yazar_head, KITAPYAZAR **kitapyazar, int size);
int kitap_yazar_eslestir(KITAPLAR *kitap_head, YAZARLAR *yazar_head, KITAPYAZAR **kitapyazar, int *size);

int main()
{
	int menu = 0, y, altmenu = 0, ogrenci_sil_bilgisi, ogrenci_arama_bilgisi, ogrenci_degistirme_bilgisi = 5, size, size2, tmp, cntrl, control_3;
	char *ogrID = malloc(sizeof(char) *30), *new_value = malloc(sizeof(char) *30), *ogrID_9 = malloc(sizeof(char) *9), *new_value_9 = malloc(sizeof(char) *9);
	char *a = (char*) malloc(sizeof(char) *30);

	setlocale(LC_ALL, "Turkish");
	OGRENCILER * ogrenci_head,*ogrenci_tmp;
	YAZARLAR * yazar_head,*yazar_tmp;
	KITAPLAR * kitap_head,*kitap_tmp;
	KITAPYAZAR * kitapyazar;
	KITAP_ODUNC *kitapodunc;
	kitapodunc=kitapodunc_oku("KitapOdunc.csv",&size2);
	ogrenci_head = ogrenci_oku("Ogrenciler.csv");
	yazar_head = yazar_oku("Yazarlar.csv");
	kitap_head = kitap_oku("Kitaplar.csv", kitapodunc, size2);
	kitapyazar = kitapyazar_oku("KitapYazar.csv", &size);

	while (menu != 4)
	{
		system("cls");
		printf("KÜTÜPHANE OTOMASYONU              Yavuz Çetin 21011004\n\n\n\n\nYazar iþlemleri:1\nÖðrenci iþlemleri:2\nKitap iþlemleri:3\nProgramdan çýk:4\n\n\n\nYapmak istediðiniz iþlem numarasýný giriniz:");
		scanf("%d", &menu);
		system("cls");
		altmenu = 0;
		switch (menu)
		{
			case 1:
				while (altmenu != 5)
				{
					printf("\nYazar Ekle:1\nYazar Sil:2\nYazar güncelle:3\nYazar Bilgisi Görüntüleme:4\nAna Menüye Dön:5\n\n\n\nYapmak istediðiniz Yazar iþlemini giriniz:");
					scanf("%d", &altmenu);
					system("cls");
					switch (altmenu)
					{
						case 1:
							yazar_ekle(&yazar_head);
							yazar_write(yazar_head, "Yazarlar.csv");
							break;
						case 2:
							printf("Silmek istediðiniz yazarýn ismini veya soyadýný giriniz:");
							gets(ogrID);
							gets(ogrID);
							yazar_sil(&yazar_head, ogrID, kitapyazar, size);
							kitapyazar_write(kitapyazar, "KitapYazar.csv", size);
							yazar_write(yazar_head, "Yazarlar.csv");
							break;
						case 3:
							cntrl = yazar_guncelle(&yazar_head);
							if (cntrl == 0)
							{
								printf("Ýþlem baþarýlý");
								yazar_write(yazar_head, "Yazarlar.csv");
							}
							else
							{
								printf("Ýþlem baþarýsýz");
							}

							break;
						case 4:
							yazar_bilgisi_goruntule(yazar_head, kitapyazar, size, kitap_head);
							system("cls");
							break;
						case 5:
							break;
					}
				}

				break;
			case 2:
				while (altmenu != 10)
				{
					printf("\nÖðrenci Ekle:1\nÖðrenci Sil:2\nÖðrenci Bilgisi Güncelleme:3\nÖðrenci bilgisi görüntüleme:4\nKitap teslim etmeyenleri listele:5\nCezalý Öðrencileri listele:6\nTüm Öðrencileri listele:7\nKitap Ödünç al:8\nKitap teslim et:9\nAna menüye dön:10\n\n\n\nYapmak istediðiniz Öðrenci iþlemini giriniz:");
					scanf("%d", &altmenu);
					system("cls");
					switch (altmenu)
					{
						case 1:
							ogrenci_ekle(&ogrenci_head);
							ogrenci_write(ogrenci_head, "Ogrenciler.csv");
							break;
						case 2:
							ogrenci_sil_bilgisi = 0;
							while (ogrenci_sil_bilgisi != 1 && ogrenci_sil_bilgisi != 2)
							{
								system("cls");
								printf("Öðrenciyi ne ile silmek istersiniz?\nID:1\nAd veya Soyad:2\nInput:");
								scanf("%d", &ogrenci_sil_bilgisi);
							}

							system("cls");
							if (ogrenci_sil_bilgisi == 1)
							{
								printf("Silmek istediðiniz öðrencinin numarasýný giriniz:");
								gets(ogrID);
								gets(ogrID);
								ogrenci_sil(&ogrenci_head, ogrID, compareByID);
							}
							else
							{
								printf("Silmek istediðiniz öðrencinin ad veya soyadýný giriniz:");
								gets(ogrID);
								gets(ogrID);
								ogrenci_sil(&ogrenci_head, ogrID, compareByName);
							}

							ogrenci_write(ogrenci_head, "Ogrenciler.csv");
							break;
						case 3:
							ogrenci_sil_bilgisi = 5;
							ogrenci_degistirme_bilgisi = 5;
							ogrenci_arama_bilgisi=3;
							while (ogrenci_arama_bilgisi != 0 && ogrenci_arama_bilgisi != 1)
							{
								system("cls");
								printf("Bilgisini deðiþtirmek istediðiniz öðrenciyi ID:0 ile mi Ad veya Soyad:1 ile mi aramak istersiniz?\nInput:");
								scanf("%d", &ogrenci_arama_bilgisi);
							}

							system("cls");
							while (ogrenci_degistirme_bilgisi != 0 && ogrenci_degistirme_bilgisi != 1 && ogrenci_degistirme_bilgisi != 2)
							{
								system("cls");
								printf("Öðrencinin neyini deðiþtirmek istersiniz?\nID:0\nAd:1\nSoyad:2\nInput:");
								scanf("%d", &ogrenci_degistirme_bilgisi);
							}

							system("cls");
							if (ogrenci_arama_bilgisi == 0)
							{
								printf("Bilgisi deðiþtirelecek öðrencinin ID'sini giriniz:");
								gets(ogrID_9);
								gets(ogrID_9);
							}
							else
							{
								printf("Bilgisi deðiþtirelecek öðrencinin Ad veya Soyad giriniz:");
								gets(ogrID);
								gets(ogrID);
							}

							if (ogrenci_degistirme_bilgisi == 0)
							{
								printf("Öðrencinin yeni ID'sini giriniz:");
								gets(new_value_9);
							}
							else if (ogrenci_degistirme_bilgisi == 1)
							{
								printf("Öðrencinin yeni Ad giriniz: ");
								gets(new_value);
							}
							else
							{
								printf("Öðrencinin yeni Soyad giriniz: ");
								gets(new_value);
							}
                            if(ogrenci_arama_bilgisi==0){
                            	if (ogrenci_degistirme_bilgisi == 0)
								{
									ogrenci_guncelle(&ogrenci_head, ogrID_9, compareByID, new_value_9, changeID);
								}
								if(ogrenci_degistirme_bilgisi==1){
									ogrenci_guncelle(&ogrenci_head, ogrID_9, compareByID, new_value, changeName);
								}
								if(ogrenci_degistirme_bilgisi==2){
									ogrenci_guncelle(&ogrenci_head, ogrID_9, compareByID, new_value, changeSurname);
								}
							}
							if(ogrenci_arama_bilgisi==1){
                            	if (ogrenci_degistirme_bilgisi == 0)
								{
									ogrenci_guncelle(&ogrenci_head, ogrID, compareByName, new_value_9, changeID);
								}
								if(ogrenci_degistirme_bilgisi==1){
									ogrenci_guncelle(&ogrenci_head, ogrID, compareByName, new_value, changeName);
								}
								if(ogrenci_degistirme_bilgisi==2){
									ogrenci_guncelle(&ogrenci_head, ogrID, compareByName, new_value, changeSurname);
								}
							}

							ogrenci_write(ogrenci_head, "Ogrenciler.csv");
							break;
						case 4:
							ogrenci_arama_bilgisi = 0;
							printf("Bilgisi görüntülenecek olan öðrenciyi ne ile aramak istersiniz?\nID:1\nAd veya Soyad:2\nInput:");
							scanf("%d", &ogrenci_arama_bilgisi);
							if (ogrenci_arama_bilgisi == 1)
							{
								printf("Görüntülenecek öðrencinin id'sini giriniz:");
								gets(ogrID);
								gets(ogrID);
								system("cls");
								print_student_by_id(ogrID, ogrenci_head, kitapodunc, size2);
							}
							else if (ogrenci_arama_bilgisi == 2)
							{
								printf("Görüntülenecek öðrencinin Adýný veya Soyadýný giriniz:");
								gets(ogrID);
								gets(ogrID);
								system("cls");
								print_student_by_name(ogrID, ogrenci_head, kitapodunc, size2);
							}

							printf("\nGeri dönmek için her hangi bir sayý giriniz:");
							getch();
							system("cls");
							break;
						case 5:
							system("cls");
							printf("Kitap teslim etmeyen öðrencilerin listesi:\n\n\n");
							teslim_etmeyen_listele(ogrenci_head, kitapodunc, size2);
							printf("Geri dönmek için her hangi bir sayý giriniz:");
							scanf("%d", &tmp);
							system("cls");
							break;
						case 6:
							system("cls");
							printf("Cezalý öðrenciler aþaðýda listelenmiþtir.");
							cezali_ogrencileri_listele(ogrenci_head);
							printf("\nGeri dönmek için her hangi bir sayý giriniz:");
							getch();
							system("cls");
							break;
						case 7:
							system("cls");
							printf("Tüm öðrenciler aþaðýda listelenmiþtir.\n");
							print_students(ogrenci_head);
							printf("\nÇýkmak için herhangi bir sayý giriniz:");
							getch();
							system("cls");
							break;
						case 8:
							system("cls");
							printf("Kitap Ödünç Alma Ekraný\nID gir:1\nAd veya Soyad gir:2\nInput:");
							scanf("%d", &ogrenci_arama_bilgisi);
							if (ogrenci_arama_bilgisi == 1)
							{
								printf("Öðrencinin id giriniz:");
								gets(ogrID);
								gets(ogrID);
							}
							else if (ogrenci_arama_bilgisi == 2)
							{
								printf("Öðrencinin Ad veya Soyad giriniz:");
								gets(ogrID);
								gets(ogrID);
							}

							kitapodunc = kitap_odunc_al(ogrenci_head, &size2, kitapodunc, ogrID, kitap_head);
							printf("%s ",kitapodunc[0].EtiketNo);
							getch();
							//kitapodunc_write(kitapodunc, "KitapOdunc.csv", size2);
							printf("\nÇýkmak için herhangi bir sayý giriniz:");
							system("cls");
							break;
						case 9:
							system("cls");
							ogrenci_arama_bilgisi = 0;
							printf("Kitap Teslim Etme Ekraný\nID gir:1\nAd veya Soyad gir:2\nInput:");
							scanf("%d", &ogrenci_arama_bilgisi);
							if (ogrenci_arama_bilgisi == 1)
							{
								printf("Öðrencinin id giriniz:");
								gets(ogrID);
								gets(ogrID);
							}
							else if (ogrenci_arama_bilgisi == 2)
							{
								printf("Öðrencinin Ad veya Soyad giriniz:");
								gets(ogrID);
								gets(ogrID);
							}
                            //kitapodunc=kitapodunc_oku("KitapOdunc.csv",&size2);
							kitapodunc = kitap_teslim_et(&ogrenci_head, &size2, kitapodunc, ogrID, kitap_head);
							//kitapodunc_write(kitapodunc, "KitapOdunc.csv", size2);
							kitapodunc=kitapodunc_oku("KitapOdunc.csv",&size2);
							getch();
							system("cls");
							break;
						case 10:
							break;
					}
				}

				break;
			case 3:
				while (altmenu != 9)
				{
					printf("\nKitap Ekle:1\nKitap Sil:2\nKitap Bilgisi Güncelleme:3\nKitap bilgisi görüntüleme:4\nRaftaki kitaplarý listele:5\nZamanýnda teslim edilmeyen kitaplarý listele:6\nKitap-Yazar eþleþtir:7\nKitap Yazarýný güncelle:8\nAna menüye dön:9\n\n\n\nYapmak istediðiniz Kitap iþlemini giriniz:");
					scanf("%d", &altmenu);
					system("cls");
					switch (altmenu)
					{
						case 1:
							kitap_ekle(&kitap_head, &kitapyazar, &size);
							kitapyazar = kitapyazar_oku("KitapYazar.csv", &size);
							kitap_write(kitap_head, "Kitaplar.csv");
							break;
						case 2:
							ogrenci_sil_bilgisi = 0;
							while (ogrenci_sil_bilgisi != 1 && ogrenci_sil_bilgisi != 2)
							{
								system("cls");
								printf("Kitabý ne ile silmek istersiniz?\nÝsim:1\nISBN:2\nInput:");
								scanf("%d", &ogrenci_sil_bilgisi);
							}

							system("cls");
							if (ogrenci_sil_bilgisi == 1)
							{
								printf("Silmek istediðiniz kitabýn ismini giriniz:");
								gets(ogrID);
								gets(ogrID);
								kitap_sil(&kitap_head, ogrID);
							}
							else
							{
								printf("Silmek istediðiniz kitabýn ISBN giriniz:");
								gets(ogrID);
								gets(ogrID);
								kitap_sil(&kitap_head, ogrID);
							}

							kitap_write(kitap_head, "Kitap.csv");
							system("cls");
							break;
						case 3:
							kitap_guncelle(&kitap_head);
							kitap_write(kitap_head, "Kitap.csv");
							system("cls");
							break;
						case 4:
							printf("Bilgisi gösterilecek kitabýn ismini giriniz:");
							gets(a);
							gets(a);
							y = 1;
							y = kitap_bilgisi_goruntule(kitap_head, yazar_head, kitapyazar, size, a);
							y = kitap_adet_bilgisi(kitap_head, a);
							if (y == 0)
							{
								printf("\n\n\nÝþlem baþarýlý. Geri dönmek için herhangi bir tuþa basýn:");
								getch();
								system("cls");
							}
							else
							{
								printf("hata.");
								getch();
							}

							break;

						case 5:
							system("cls");
							raftaki_kitap_listele(kitap_head);
							system("cls");
							break;
						case 6:
							system("cls");
							zamaninda_teslim_etmeyen_listele(kitapodunc, size2, kitap_head, yazar_head, kitapyazar, size);
							system("cls");
							break;
						case 7:
							system("cls");
							control_3 = kitap_yazar_eslestir(kitap_head, yazar_head, &kitapyazar, &size);
							kitapyazar = kitapyazar_oku("KitapYazar.csv", &size);
							if (control_3 == 0)
							{
								printf("\nÝþlem baþarýlý geri dönmek için bir sayý girin:");
							}
							else
							{
								printf("\nHata.Bir sayý girin:");
							}

							getch();
							system("cls");
							break;
						case 8:
							system("cls");
							control_3 = kitap_yazar_guncelle(kitap_head, yazar_head, &kitapyazar, size);
							kitapyazar = kitapyazar_oku("KitapYazar.csv", &size);
							if (control_3 == 0)
							{
								printf("\nÝþlem baþarýlý geri dönmek için bir sayý girin:");
							}
							else
							{
								printf("\nHata.Bir sayý girin:");
							}

							getch();
							system("cls");
							break;
						case 9:
							break;
					}
				}
		}
	}
    while(ogrenci_head!=NULL){
    	ogrenci_tmp=ogrenci_head;
    	ogrenci_head=ogrenci_head->next;
    	free(ogrenci_head);
	}
	while(kitap_head!=NULL){
    	kitap_tmp=kitap_head;
    	kitap_head=kitap_head->next;
    	free(kitap_head);
	}
	while(yazar_head!=NULL){
    	yazar_tmp=yazar_head;
    	yazar_head=yazar_head->next;
    	free(kitap_head);
	}
	free(kitapyazar);
	free(kitapodunc);
	free(ogrID);
	free(new_value);
	free(ogrID_9);
	free(new_value_9);
	free(a);
	return 0;
}

OGRENCILER* ogrenci_oku(char *filename)
{
	OGRENCILER *current_node = NULL, *head = NULL, tmp, *node;
	FILE * ogrenci;
	ogrenci = fopen(filename, "r");

	while (fscanf(ogrenci, "%[^,],%[^,],%[^,],%d\n", &tmp.ogrID, &tmp.ad, &tmp.soyad, &tmp.puan) != EOF)
	{
		node = (OGRENCILER*) malloc(sizeof(OGRENCILER));
		strcpy(node->ogrID, tmp.ogrID);
		strcpy(node->ogrID, removeSpacesFromStr(node->ogrID));
		strcpy(node->ad, tmp.ad);
		strcpy(node->ad, removeSpacesFromStr(node->ad));
		strcpy(node->soyad, tmp.soyad);
		strcpy(node->soyad, removeSpacesFromStr(node->soyad));
		node->puan = tmp.puan;
		node->next = NULL;

		if (head == NULL)
		{
			node->prev = NULL;
			current_node = head = node;
		}
		else
		{
			node->prev = current_node;
			current_node = current_node->next = node;
		}
	}

	head->prev = current_node;
	fclose(ogrenci);
	return head;
}

void print_students(OGRENCILER *head)
{
	OGRENCILER *current = head;
	while (current != NULL)
	{
		printf("%s %s  %s (PUAN: %d)\n", current->ogrID, current->ad, current->soyad, current->puan);
		current = current->next;
	}
}

void ogrenci_ekle(OGRENCILER **head)
{
	OGRENCILER *newStudent = malloc(sizeof(OGRENCILER));
	printf("Öðrenci ID girin:");
	scanf("%s", newStudent->ogrID);

	printf("Öðrenci isim:");
	scanf("%s", newStudent->ad);

	printf("Öðrenci soyad:");
	scanf("%s", newStudent->soyad);

	printf("Öðrencinin puaný:");
	scanf("%d", &newStudent->puan);

	if (*head == NULL)
	{
		*head = newStudent;
		(*head)->prev = NULL;
		(*head)->next = NULL;
	}
	else
	{
		OGRENCILER *curr = *head;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}

		curr->next = newStudent;
		newStudent->prev = curr;
		newStudent->next = NULL;
	}
}

YAZARLAR* yazar_oku(char *filename)
{
	YAZARLAR *current_node = NULL, *head = NULL, tmp, *node;
	FILE * yazar;
	yazar = fopen(filename, "r");

	while (fscanf(yazar, "%d,%[^,],%s\n", &tmp.yazarID, &tmp.yazarAd, &tmp.yazarSoyad) != EOF)
	{
		node = (YAZARLAR*) malloc(sizeof(YAZARLAR));
		strcpy(node->yazarAd, tmp.yazarAd);
		strcpy(node->yazarAd, removeSpacesFromStr(node->yazarAd));
		strcpy(node->yazarSoyad, tmp.yazarSoyad);
		strcpy(node->yazarSoyad, removeSpacesFromStr(node->yazarSoyad));
		node->yazarID = tmp.yazarID;
		node->next = NULL;

		if (head == NULL)
		{
			current_node = head = node;
		}
		else
		{
			current_node = current_node->next = node;
		}
	}

	fclose(yazar);
	return head;
}

void print_yazar(YAZARLAR *head)
{
	YAZARLAR *current = head;
	while (current != NULL)
	{
		printf("%d %s  %s \n", current->yazarID, current->yazarAd, current->yazarSoyad);
		current = current->next;
	}
}

void yazar_ekle(YAZARLAR **head)
{
	YAZARLAR *newStudent = malloc(sizeof(YAZARLAR)), *tmp = *head;
	int i;
	while (tmp->next != NULL)
	{
		i = tmp->yazarID;
		tmp = tmp->next;
	}

	newStudent->yazarID = i + 2;
	printf("Yazar ismi girin: ");
	scanf("%s", newStudent->yazarAd);

	printf("Yazar soyad girin: ");
	scanf("%s", newStudent->yazarSoyad);

	if (*head == NULL)
	{
		*head = newStudent;
		(*head)->next = NULL;
	}
	else
	{
		YAZARLAR *curr = *head;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}

		curr->next = newStudent;
		newStudent->next = NULL;
	}
}

int ogrenci_write(OGRENCILER *head, char *filename)
{
	FILE *file = fopen(filename, "w");
	if (file == NULL)
	{
		printf("Error opening file");
		return -1;
	}

	OGRENCILER *curr = head;
	while (curr != NULL)
	{
		if (curr->next != NULL)
		{
			fprintf(file, "%s,%s,%s,%d\n", curr->ogrID, curr->ad, curr->soyad, curr->puan);
		}
		else
		{
			fprintf(file, "%s,%s,%s,%d", curr->ogrID, curr->ad, curr->soyad, curr->puan);
		}

		curr = curr->next;
	}

	fclose(file);
	return 0;
}

int yazar_write(YAZARLAR *head, char *filename)
{
	FILE *file = fopen(filename, "w");
	if (file == NULL)
	{
		printf("Error opening file");
		return -1;
	}

	YAZARLAR *curr = head;
	while (curr != NULL)
	{
		if (curr->next != NULL)
		{
			fprintf(file, "%d,%s,%s\n", curr->yazarID, curr->yazarAd, curr->yazarSoyad);
		}
		else
		{
			fprintf(file, "%d,%s,%s", curr->yazarID, curr->yazarAd, curr->yazarSoyad);
		}

		curr = curr->next;
	}

	fclose(file);
	return 0;
}

void ogrenci_sil(OGRENCILER **head, char *value, int(*comparisonFunc)(OGRENCILER *, char *))
{
	OGRENCILER *curr = *head;
	while (curr != NULL)
	{
		if (comparisonFunc(curr, value))
		{
			if (curr == *head)
			{ 	*head = curr->next;
			}

			if (curr->prev != NULL)
			{
				curr->prev->next = curr->next;
			}

			if (curr->next != NULL)
			{
				curr->next->prev = curr->prev;
			}

			OGRENCILER *temp = curr;
			curr = curr->next;
			free(temp);
		}
		else
		{
			curr = curr->next;
		}
	}
}

int compareByID(OGRENCILER *student, char *value)
{
	char *tmp;
	tmp=removeSpacesFromStr(student->ogrID);
	if(strcmp(tmp, value) == 0){
		return 1;
	}
	return 0;
}

int compareByName(OGRENCILER *student, char *value)
{
	char *tmp;
	tmp = removeSpacesFromStr(student->ad);
	if (strcmp(tmp, value) == 0)
	{
		return 1;
	}
	tmp = removeSpacesFromStr(student->soyad);
	if (strcmp(tmp, value) == 0)
	{
		return 1;
	}

	return 0;
}

char *removeSpacesFromStr(char *string)
{
	int k = 0, i;
	if (string[0] == ' ')
	{
		for (i = 1; string[i] != '\0'; i++)
		{
			string[i - 1] = string[i];
			k++;
		}

		string[k] = '\0';
	}

	return string;
}

void ogrenci_guncelle(OGRENCILER **head, char *value, int(*comparisonFunc)(OGRENCILER *, char *), char *new_value, void(*changeFunc)(OGRENCILER *, char *))
{
	OGRENCILER *curr = *head;
	while (curr != NULL)
	{
		if (comparisonFunc(curr, value))
		{
			changeFunc(curr, new_value);
		}
			curr = curr->next;
		
	}
}

void changeID(OGRENCILER *a, char *b)
{
	OGRENCILER *tmp = a;
	strcpy(tmp->ogrID, b);
}

void changeName(OGRENCILER *a, char *b)
{
	OGRENCILER *tmp = a;
	strcpy(tmp->ad, b);
}

void changeSurname(OGRENCILER *a, char *b)
{
	OGRENCILER *tmp = a;
	strcpy(tmp->soyad, b);
}

int yazar_sil(YAZARLAR **head, char *name, KITAPYAZAR *dizi, int size)
{
	YAZARLAR *current = *head;
	YAZARLAR *prev = NULL;
	char *tmp, *tmp_2;
	int ID, i;
	tmp = removeSpacesFromStr(current->yazarAd);
	tmp_2 = removeSpacesFromStr(current->yazarSoyad);

	while (current != NULL && strcmp(tmp, name) != 0 && strcmp(tmp_2, name) != 0)
	{
		prev = current;
		current = current->next;
		if (current != NULL)
		{
			tmp = removeSpacesFromStr(current->yazarAd);
			tmp_2 = removeSpacesFromStr(current->yazarSoyad);
		}
	}

	if (current == NULL)
	{
		free(current);
		printf("yazar bulunamadý.\n");
		return 1;
	}

	ID = current->yazarID;
	for (i = 0; i < size; i++)
	{
		if (dizi[i].YazarID == ID)
		{
			dizi[i].YazarID = -1;
		}
	}

	if (prev == NULL)
	{
		*head = current->next;
	}
	else
	{
		prev->next = current->next;
	}

	free(current);
	return 0;
}

KITAPLAR* kitap_oku(char *filename, KITAP_ODUNC *kitapodunc, int size)
{
	KITAPLAR *current_node = NULL, *head = NULL, tmp, *node;
	KITAPORNEK * new_list;
	char *str = (char*)(malloc(sizeof(char) *5)), *tmp_str = (char*)(malloc(sizeof(char) *20)), *a = (char*)(malloc(sizeof(char) *5));
	int temp, i, j;
	FILE * kitap;
	kitap = fopen(filename, "r");

	while (fscanf(kitap, "%[^,],%[^,],%d\n", tmp.kitapAdi, tmp.ISBN, &tmp.adet) != EOF)
	{
		node = (KITAPLAR*) malloc(sizeof(KITAPLAR));
		strcpy(node->kitapAdi, tmp.kitapAdi);
		strcpy(node->kitapAdi, removeSpacesFromStr(node->kitapAdi));
		strcpy(node->ISBN, tmp.ISBN);
		strcpy(node->ISBN, removeSpacesFromStr(node->ISBN));
		node->adet = tmp.adet;
		node->next = NULL;

		if (head == NULL)
		{
			current_node = head = node;
		}
		else
		{
			current_node = current_node->next = node;
		}
	}

	current_node = head;
	while (current_node != NULL)
	{
		temp = current_node->adet;
		new_list = (KITAPORNEK*) malloc(sizeof(KITAPORNEK) *temp);
		current_node->head = new_list;
		for (i = 0; i < temp; i++)
		{
			strcpy(str, "_");
			strcpy(a, "");
			itoa(i + 1, a, 10);
			strcat(str, a);
			strcpy(tmp_str, current_node->ISBN);
			strcat(tmp_str, str);
			strcpy(new_list[i].EtiketNo, tmp_str);
			strcpy(new_list[i].Durum, "Rafta");
			strcpy(tmp_str, removeSpacesFromStr(new_list[i].EtiketNo));
			strcpy(new_list[i].EtiketNo, tmp_str);
			for(j=0;j < size;j++){	
			if((strcmp(kitapodunc[j].EtiketNo,new_list[i].EtiketNo)==0)&&kitapodunc[j].islemTipi==0){	
			strcpy(new_list[i].Durum,kitapodunc[j].ogrID);
			}

			if((strcmp(kitapodunc[j].EtiketNo,new_list[i].EtiketNo)==0)&&kitapodunc[j].islemTipi==1){	
			strcpy(new_list[i].Durum,"Rafta");
			}

			}

			printf("%s %s\n", new_list[i].EtiketNo, new_list[i].Durum);
		}

		current_node = current_node->next;
	}

	free(str);
	free(a);
	free(tmp_str);
	fclose(kitap);
	return head;
}

void print_kitap(KITAPLAR *head)
{
	KITAPLAR *current = head;
	while (current != NULL)
	{
		printf("%s %s  %d \n", current->kitapAdi, current->ISBN, current->adet);
		current = current->next;
	}
}

int kitap_ekle(KITAPLAR **head, KITAPYAZAR **kitapyazar, int *size)
{
	KITAPLAR *newStudent = malloc(sizeof(KITAPLAR)), *tmp = *head;
	KITAPYAZAR *kitapyazar_tmp = *(kitapyazar);
	int control = 0, i, yazar_adet;
	char *a = (char*) malloc(sizeof(char) *5), *str = (char*) malloc(sizeof(char) *5), *tmp_str = (char*) malloc(sizeof(char) *20);
	KITAPORNEK * asd;
	KITAPLAR * curr;
	printf("Kitap ISBN: ");
	scanf("%s", newStudent->ISBN);
	while (tmp != NULL && control == 0)
	{
		if (strcmp(newStudent->ISBN, tmp->ISBN) == 0)
		{
			control = 1;
			printf("Bu kitaptan kaç tane eklenecek?: ");
			scanf("%d", &newStudent->adet);
			asd = tmp->head;
			asd = (KITAPORNEK*) realloc(asd, sizeof(KITAPORNEK) *(tmp->adet + newStudent->adet));
			if (asd == NULL)
			{
				printf("realloc sýrasýnda hata");
				getch();
				return 1;
			}

			for (i = tmp->adet; i < tmp->adet + newStudent->adet; i++)
			{
				strcpy(str, "_");
				strcpy(a, "");
				itoa(i + 1, a, 10);
				strcat(str, a);
				strcpy(tmp_str, newStudent->ISBN);
				strcat(tmp_str, str);
				strcpy(asd[i].EtiketNo, tmp_str);
				strcpy(asd[i].Durum, "Rafta");
				strcpy(tmp_str, removeSpacesFromStr(asd[i].EtiketNo));
				strcpy(asd[i].EtiketNo, tmp_str);
			}

			tmp->adet = tmp->adet + newStudent->adet;
			printf("Ayný ISBN li kitap olduðundan belirtilen adette kitap baþarýyla eklenmiþtir.Çýkmak iin herhangi bir sayý girin:");
			getch();
			return 0;
		}

		tmp = tmp->next;
	}

	printf("Bu kitapla ayný ISBN li kitap yok. Bu kitabýn adýný giriniz: ");
	gets(newStudent->kitapAdi);
	gets(newStudent->kitapAdi);
	printf("Kitabýn adedini giriniz.");
	scanf("%d", &newStudent->adet);
	asd = newStudent->head;
	asd = (KITAPORNEK*) malloc(sizeof(KITAPORNEK) *newStudent->adet);
	if (asd == NULL)
	{
		printf("malloc sýrasýnda hata. çýkmak için bir sayý giriniz:");
		getch();
		return 1;
	}

	for (i = 0; i < newStudent->adet; i++)
	{
		strcpy(str, "_");
		strcpy(a, "");
		itoa(i + 1, a, 10);
		strcat(str, a);
		strcpy(tmp_str, newStudent->ISBN);
		strcat(tmp_str, str);
		strcpy(asd[i].EtiketNo, tmp_str);
		strcpy(asd[i].Durum, "Rafta");
		strcpy(tmp_str, removeSpacesFromStr(asd[i].EtiketNo));
		strcpy(asd[i].EtiketNo, tmp_str);
	}

	printf("Kitabýn kaç yazarý var:");
	scanf("%d", &yazar_adet);
	kitapyazar_tmp = (KITAPYAZAR*) realloc(kitapyazar_tmp, sizeof(KITAPYAZAR) *(yazar_adet + *(size)));
	for (i = *(size); i<*(size) + yazar_adet; i++)
	{
		strcpy(kitapyazar_tmp[i].ISBN, newStudent->ISBN);
		printf("%d . yazarýn id'sini giriniz:", i - *(size) + 1);
		scanf("%d", &kitapyazar_tmp[i].YazarID);
	}

	*(size) = *(size) + yazar_adet;
	kitapyazar_write(kitapyazar_tmp, "KitapYazar.csv", *(size));
	if (*head == NULL)
	{
		*head = newStudent;
		(*head)->next = NULL;
	}
	else
	{
		curr = *head;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}

		curr->next = newStudent;
		newStudent->next = NULL;
	}
}

int kitap_sil(KITAPLAR **head, char *name)
{
	KITAPLAR *current = *head;
	KITAPLAR *prev = NULL;
	char *tmp;
	tmp = removeSpacesFromStr(current->ISBN);
	while (current != NULL && strcmp(tmp, name) != 0 && strcmp(current->kitapAdi, name) != 0)
	{
		prev = current;
		current = current->next;
		if (current != NULL)
		{
			tmp = removeSpacesFromStr(current->ISBN);
		}
	}

	if (current == NULL)
	{
		printf("kitap bulunamadý.\n");
		return 1;
	}

	if (prev == NULL)
	{
		*head = current->next;
	}
	else
	{
		prev->next = current->next;
	}

	free(current);
	return 0;
}

int kitap_write(KITAPLAR *head, char *filename)
{
	FILE *file = fopen(filename, "w");
	if (file == NULL)
	{
		printf("Error opening file");
		return -1;
	}

	KITAPLAR *curr = head;
	while (curr != NULL)
	{
		if (curr->next != NULL)
		{
			fprintf(file, "%s,%s,%d\n", curr->kitapAdi, curr->ISBN, curr->adet);
		}
		else
		{
			fprintf(file, "%s,%s,%d", curr->kitapAdi, curr->ISBN, curr->adet);
		}

		curr = curr->next;
	}

	fclose(file);
	return 0;
}

KITAPYAZAR* kitapyazar_oku(char *filename, int *size)
{
	KITAPYAZAR tmp, *dizi;
	FILE *yazar = NULL;
	yazar = fopen(filename, "r");
	if (yazar == NULL)
	{
		printf("Dosya açýlamadý bir sayý girin:");
		getch();
		return dizi;
	}

	int count = 0, i = 0;
	char c;
	for (c = getc(yazar); c != EOF; c = getc(yazar))
	{
		if (c == '\n')
			count = count + 1;
	}

	count = count + 1;
	*(size) = count;
	dizi = (KITAPYAZAR*) malloc(sizeof(KITAPYAZAR) *(count));
	fclose(yazar);
	yazar = fopen(filename, "r");
	if (yazar == NULL)
	{
		printf("Dosya açýlamadý bir sayý girin:");
		getch();
		return dizi;
	}

	while (fscanf(yazar, "%[^,],%d\n", tmp.ISBN, &tmp.YazarID) != EOF)
	{
		strcpy(dizi[i].ISBN, tmp.ISBN);
		dizi[i].YazarID = tmp.YazarID;
		i = i + 1;
	}

	fclose(yazar);
	return dizi;
}

void print_kitapyazar(KITAPYAZAR *head)
{
	int i;
	for (i = 0; i < 9; i++)
	{
		printf("%s %d\n", head[i].ISBN, head[i].YazarID);
	}
}

int kitapyazar_write(KITAPYAZAR *head, char *filename, int size)
{
	FILE *file = fopen(filename, "w");
	int i;
	if (file == NULL)
	{
		printf("Error opening file");
		return -1;
	}

	for (i = 0; i < size; i++)
	{
		if (i != size - 1)
		{
			fprintf(file, "%s,%d\n", head[i].ISBN, head[i].YazarID);
		}
		else
		{
			fprintf(file, "%s,%d", head[i].ISBN, head[i].YazarID);
		}
	}

	fclose(file);
	return 0;
}

KITAP_ODUNC* kitapodunc_oku(char *filename, int *size)
{
	KITAP_ODUNC *kitapOdunc_2, kitapOdunc;
	int kitap_count = 0;
	FILE *yazar = NULL;
	int fieldIndex, dateIndex;
	char *field, *line, *dateField;
	int count = 0, i = 0,count2=0;
	char c;
	yazar = fopen(filename, "r");
	if (yazar == NULL)
	{
		printf("Dosya açýlamadý. Bir sayý girin:");
		getch();
		return kitapOdunc_2;
	}

	for (c = getc(yazar); c != EOF; c = getc(yazar))
	{
		count2=1;
		if (c == '\n')
			count = count + 1;
	}
    if(count2==0){
    	count=count-1;
	}
	count = count + 1;
	*(size) = count;
	kitapOdunc_2 = (KITAP_ODUNC*) malloc(sizeof(KITAP_ODUNC) *(count));
	fclose(yazar);
	yazar = fopen(filename, "r");
	if (yazar == NULL)
	{
		printf("Dosya açýlamadý");
		getch();
		return kitapOdunc_2;
	}

	line = (char*) malloc(sizeof(char) *1024);
	while (fgets(line, 1024, yazar))
	{
		field = strtok(line, ",");
		fieldIndex = 0;
		while (field)
		{
			switch (fieldIndex)
			{
				case 0:
					strcpy(kitapOdunc.EtiketNo, field);
					break;
				case 1:
					strcpy(kitapOdunc.ogrID, field);
					strcpy(kitapOdunc.ogrID, removeSpacesFromStr(kitapOdunc.ogrID));
					break;
				case 2:
					kitapOdunc.islemTipi = atoi(field);
					break;
				case 3:
					{
						dateField = strtok(field, ".");
						dateIndex = 0;
						while (dateField)
						{
							switch (dateIndex)
							{
								case 0:
									kitapOdunc.islemTarihi.gun = atoi(dateField);
									break;
								case 1:
									kitapOdunc.islemTarihi.ay = atoi(dateField);
									break;
								case 2:
									kitapOdunc.islemTarihi.yil = atoi(dateField);
									break;
							}

							dateField = strtok(NULL, ".");
							dateIndex++;
						}

						break;
					}
			}

			field = strtok(NULL, ",");
			fieldIndex++;
		}

		kitapOdunc_2[kitap_count] = kitapOdunc;
		kitap_count++;
	}

	free(line);
	fclose(yazar);
	return kitapOdunc_2;
}

void teslim_etmeyen_listele(OGRENCILER *ogrenci_head, KITAP_ODUNC *kitapodunc, int size)
{
	char *buffer = malloc(sizeof(char) *9);
	int i, j, count = 0;
	for (i = 0; i < size; i++)
	{
		strcpy(buffer, "");
		if (kitapodunc[i].islemTipi == 0)
		{
			strcpy(buffer, kitapodunc[i].ogrID);
			for (j = i + 1; j < size; j++)
			{
				if (strcmp(kitapodunc[j].EtiketNo, kitapodunc[i].EtiketNo) == 0 && (kitapodunc[j].islemTipi == 1) && strcmp(kitapodunc[j].ogrID, kitapodunc[i].ogrID) == 0)
				{
					strcpy(buffer, "");
				}
			}

			print_student_by_id(buffer, ogrenci_head, kitapodunc, size);
			printf(" Kitap Etiket No:%s\n", kitapodunc[i].EtiketNo);
			count = count + 1;
		}
	}

	if (count == 0)
	{
		printf("Kitap teslim etmeyen yoktur.\n");
	}

	free(buffer);
}

void print_student_by_id(char *a, OGRENCILER *head, KITAP_ODUNC *head_2, int size)
{
	OGRENCILER *tmp = head;
	int i;
	while (tmp != NULL)
	{
		if ((strcmp(a, tmp->ogrID) == 0))
		{
			printf("Ad:%s, Soyad:%s, ID:%s, Puan:%d", tmp->ad, tmp->soyad, tmp->ogrID, tmp->puan);
			printf("\nÖðrencinin kitap iþlemleri:\n");
			for (i = 0; i < size; i++)
			{
				if (strcmp(head_2[i].ogrID, tmp->ogrID) == 0)
				{
					printf("Kitap alma/verme:%d Kitap etiket no:%s Tarih:%d.%d.%d\n", head_2[i].islemTipi, head_2[i].EtiketNo, head_2[i].islemTarihi.gun, head_2[i].islemTarihi.ay, head_2[i].islemTarihi.yil);
				}
			}
		}

		tmp = tmp->next;
	}
}

void print_student_by_name(char *a, OGRENCILER *head, KITAP_ODUNC *head_2, int size)
{
	OGRENCILER *tmp = head;
	int i;
	while (tmp != NULL)
	{
		if ((strcmp(a, tmp->ad) == 0) || (strcmp(a, tmp->soyad) == 0))
		{
			printf("Ad:%s, Soyad:%s, ID:%s, Puan:%d", tmp->ad, tmp->soyad, tmp->ogrID, tmp->puan);
			printf("\nÖðrencinin kitap iþlemleri:\n");
			for (i = 0; i < size; i++)
			{
				if (strcmp(head_2[i].ogrID, tmp->ogrID) == 0)
				{
					printf("Kitap alma/verme:%d Kitap etiket no:%s Tarih:%d.%d.%d\n", head_2[i].islemTipi, head_2[i].EtiketNo, head_2[i].islemTarihi.gun, head_2[i].islemTarihi.ay, head_2[i].islemTarihi.yil);
				}
			}
		}

		tmp = tmp->next;
	}
}

void cezali_ogrencileri_listele(OGRENCILER *head)
{
	OGRENCILER *tmp = head;
	int count = 0;
	while (tmp != NULL)
	{
		if (tmp->puan < 0)
		{
			printf("\nAd:%s, Soyad:%s, ID:%s, Puan:%d\n", tmp->ad, tmp->soyad, tmp->ogrID, tmp->puan);
			count = count + 1;
		}

		tmp = tmp->next;
	}

	if (count == 0)
	{
		printf("\nCezalý öðrenci yoktur.");
	}
}

KITAP_ODUNC* kitap_odunc_al(OGRENCILER *head, int *size, KITAP_ODUNC *kitapodunc, char *a, KITAPLAR *kitap_head)
{
	int i = 0, control = 0, control_2 = 0, adet, gun, ay, yil, control_3 = 0, lastsize;
	char *kitapismi = (char*) malloc(sizeof(char) *30), *z = (char*) malloc(sizeof(char) *20);
	OGRENCILER *tmp = head, *tmp_2;
	char f,temp_c;
	KITAPLAR *kitap_tmp = kitap_head, *kitap_tmp_2 = NULL;
	KITAPORNEK * kitapornek_tmp;
	KITAP_ODUNC * tmpe;
	

	while (tmp != NULL && control == 0)
	{
		if ((strcmp(tmp->ad, a)==0 || strcmp(tmp->soyad, a)==0 || strcmp(tmp->ogrID, a)==0) && tmp->puan >= 0)
		{
			control = 1;
			control_3=1;
			tmp_2 = tmp;
		}

		tmp = tmp->next;
	}

	if (control_3 == 0)
	{
		printf("Öðrencinin puaný 0'dan düþük olduðundan kitap alamaz.");
		return kitapodunc;
	}
	printf("Eklenecek kitabýn Ýsmini Giriniz:");
	gets(kitapismi);
	gets(kitapismi);
	printf("Kitap ayin hangi günü alýndý?:");
	scanf("%d", &gun);
	printf("Kitap hangi ay alýndý?:");
	scanf("%d", &ay);
	printf("Kitap hangi yil alýndý?:");
	scanf("%d", &yil);

	while (kitap_tmp != NULL && control == 1 && control_2 == 0)
	{
		if (strcmp(kitapismi, removeSpacesFromStr(kitap_tmp->kitapAdi)) == 0)
		{
			kitap_tmp_2 = kitap_tmp;
			control_2 = 1;
		}

		kitap_tmp = kitap_tmp->next;
	}

	if (kitap_tmp_2 == NULL)
	{
		printf("Bu isimde kitap bulunamadý. Çýkmak için bir sayý girin:");
		getch();
		return kitapodunc;
	}

	adet = kitap_tmp_2->adet;
	kitapornek_tmp = kitap_tmp_2->head;
	while (control_2 == 1 && i < adet)
	{
		if (strcmp(removeSpacesFromStr(kitapornek_tmp[i].Durum), "Rafta") == 0)
		{
			control_2 = 0;
			strcpy(kitapornek_tmp[i].Durum, tmp_2->ogrID);
			strcpy(z, kitapornek_tmp[i].EtiketNo);
			lastsize = *(size) + 1;
			tmpe = (KITAP_ODUNC*) realloc(kitapodunc, (lastsize) *sizeof(KITAP_ODUNC));
			*(size) = lastsize;
			if (tmpe == NULL)
			{
				printf("Realloc esnasýnda hata. Bir sayý girin");
				getch();
				return kitapodunc;
			}

			kitapodunc = tmpe;
			kitapodunc[lastsize - 1].islemTipi = 0;
			kitapodunc[lastsize - 1].islemTarihi.gun = gun;
			kitapodunc[lastsize - 1].islemTarihi.ay = ay;
			kitapodunc[lastsize - 1].islemTarihi.yil = yil;
			strcpy(kitapodunc[lastsize - 1].EtiketNo, removeSpacesFromStr(z));
			strcpy(kitapodunc[lastsize - 1].ogrID, removeSpacesFromStr(kitapornek_tmp[i].Durum));
		}

		i = i + 1;
	}

	if (control_2 == 1)
	{
		printf("Boþta kitap yok.");
		return kitapodunc;
	}
	kitapodunc_write(kitapodunc, "KitapOdunc.csv", *(size));
	return kitapodunc;
}

int kitapodunc_write(KITAP_ODUNC *head, char *filename, int size)
{
	FILE *file = fopen(filename, "w");
	int i, tmp_1, tmp_2, tmp_3;
	if (file == NULL)
	{
		printf("Error opening file");
		return -1;
	}

	getch();

	for (i = 0; i < size; i++)
	{
		tmp_1 = head[i].islemTarihi.gun;
		tmp_2 = head[i].islemTarihi.ay;
		tmp_3 = head[i].islemTarihi.yil;
		if (i == size - 1)
		{
			fprintf(file, "%s,%s,%d,%d.%d.%d", head[i].EtiketNo, head[i].ogrID, head[i].islemTipi, tmp_1, tmp_2, tmp_3);
		}
		else
		{
			fprintf(file, "%s,%s,%d,%d.%d.%d\n", head[i].EtiketNo, head[i].ogrID, head[i].islemTipi, tmp_1, tmp_2, tmp_3);
		}
	}

	fclose(file);
	return 0;
}

int dayCalculator(TARIH date1, TARIH date2)
{
	int months1 = date1.yil *12 + date1.ay, months2 = date2.yil *12 + date2.ay, monthsDifference, daysDifference;
	monthsDifference = months2 - months1;
	daysDifference = date2.gun + monthsDifference *30 - date1.gun;
	if (daysDifference < 0)
	{
		daysDifference = -1 * daysDifference;
	}

	return daysDifference;
}

KITAP_ODUNC* kitap_teslim_et(OGRENCILER **head, int *size, KITAP_ODUNC *kitapodunc, char *a, KITAPLAR *kitap_head)
{
	OGRENCILER *tmp = *(head), *tmp_2;
	KITAPLAR *kitap_tmp = kitap_head, *kitap_tmp2 = NULL;
	KITAPORNEK *ornek_tmp, *ornek_tmp_2;
	int control = 0, i, j, control_2 = 0, control_3 = 0, gun, ay, yil, control_5 = 0, size_new, control_6 = -1;
	char *buffer = (char*) malloc(sizeof(char) *9);
	char *buffer_2 = (char*) malloc(sizeof(char) *20);
	char *w_ptr, *new_string;
	int w_index;

	while (tmp != NULL)
	{
		if ((strcmp(a, tmp->ogrID) == 0) || (strcmp(a, tmp->soyad) == 0) || (strcmp(a, tmp->ad) == 0))
		{
			control = 1;
			tmp_2 = tmp;
		}

		tmp = tmp->next;
	}

	if (control == 0)
	{
		printf("Öðrenci bulunamadý.");
		free(buffer);
		free(buffer_2);
		return kitapodunc;
	}
	strcpy(buffer,removeSpacesFromStr(tmp_2->ogrID));
	
	printf("Adý:%s, Soyad:%s, ID:%s\nTeslim edilebilecek kitaplar aþaðýdadýr.\n", tmp_2->ad, tmp_2->soyad, tmp_2->ogrID);
	for (i = 0; i<*(size); i++)
	{
		control_2 = 0;
		if (strcmp(kitapodunc[i].ogrID, buffer) == 0 && (kitapodunc[i].islemTipi == 0))
		{
			control_2 = 2;
			for (j = i + 1; j<*(size); j++)
			{
				if (strcmp(kitapodunc[j].EtiketNo, kitapodunc[i].EtiketNo) == 0)
				{
					control_2 = 1;
				}
			}

			if (control_2 == 2)
			{
				printf("Kitap etiket no:%s Teslim Alýnan tarih:%d.%d.%d\n", kitapodunc[i].EtiketNo, kitapodunc[i].islemTarihi.gun, kitapodunc[i].islemTarihi.ay, kitapodunc[i].islemTarihi.yil);
				control_3 = control_3 + 1;
			}
		}
	}
	if (control_3 == 0)
	{
		printf("Teslim edilebilecek kitap yoktur. Çýkmak için herhangi bir sayý giriniz:");
		return kitapodunc;
	}
	else
	{
		printf("Teslim edilecek kitabin etiket no giriniz:");
		gets(buffer_2);
		printf("Bugün ayýn hangi günü olduðunu girin:");
		scanf("%d", &gun);
		printf("Bugün yýlýn kaçýncý ayý olduðunu girin:");
		scanf("%d", &ay);
		printf("Yýlý giriniz:");
		scanf("%d", &yil);
		w_ptr = strchr(buffer_2, '_');
		w_index = w_ptr - buffer_2;
		new_string = (char*) malloc(sizeof(char) *(w_index + 1));
		strncpy(new_string, buffer_2, w_index);
		new_string[w_index] = '\0';
		while (kitap_tmp != NULL)
		{
			if (strcmp(kitap_tmp->ISBN, new_string) == 0)
			{
				kitap_tmp2 = kitap_tmp;
			}

			kitap_tmp = kitap_tmp->next;
		}

		if (kitap_tmp2 == NULL)
		{
			printf("Kitap bulunamadý.");
			return kitapodunc;
		}

		ornek_tmp = kitap_tmp2->head;
		i = 0;
		size_new = kitap_tmp2->adet;
		while (i < (size_new) && control_5 == 0)
		{
			if (strcmp(ornek_tmp[i].EtiketNo, buffer_2) == 0)
			{
				control_5 = 1;
				strcpy(ornek_tmp[i].Durum, "Rafta");
				*(size) = *(size) + 1;
				kitapodunc = (KITAP_ODUNC*) realloc(kitapodunc, *(size) *sizeof(KITAP_ODUNC));
				if (kitapodunc == NULL)
				{
					printf("Realloc esnasýnda hata.");
					return kitapodunc;
				}

				strcpy(kitapodunc[*size - 1].EtiketNo, buffer_2);
				strcpy(kitapodunc[*size - 1].ogrID, tmp_2->ogrID);
				kitapodunc[*size - 1].islemTarihi.gun = gun;
				kitapodunc[*size - 1].islemTarihi.ay = ay;
				kitapodunc[*size - 1].islemTarihi.yil = yil;
				kitapodunc[*size - 1].islemTipi = 1;
				kitapodunc_write(kitapodunc, "KitapOdunc.csv", *size);
				j = 0;
				while (j<*size && control_6 == -1)
				{
					if (strcmp(kitapodunc[j].EtiketNo, buffer_2) == 0)
					{
						control_6 = j;
					}

					j++;
				}

				control_6 = dayCalculator(kitapodunc[control_6].islemTarihi, kitapodunc[*size - 1].islemTarihi);
				if (control_6 > 15)
				{
					tmp_2->puan = tmp_2->puan - 10;
					ogrenci_write(*(head), "Ogrenciler.csv");
				}
			}

			i++;
		}
	}
    kitapodunc_write(kitapodunc, "KitapOdunc.csv", *(size));
	free(buffer);
	free(buffer_2);
	free(new_string);
	return kitapodunc;
}

int yazar_guncelle(YAZARLAR **head)
{
	char *a = (char*) malloc(sizeof(char) *30), *yeniad = (char*) malloc(sizeof(char) *30);
	YAZARLAR *tmp = *(head), *tmp_2;
	int girdi = 0, control = 0;
	system("cls");
	printf("Bilgisi deðiþtirilecek olan yazarýn Ad veya Soyad giriniz:");
	gets(a);
	gets(a);
	while (tmp != NULL && control != 1)
	{
		if (strcmp(tmp->yazarAd, a) == 0 || strcmp(tmp->yazarSoyad, a) == 0)
		{
			tmp_2 = tmp;
			control = 1;
		}

		tmp = tmp->next;
	}

	if (control == 0)
	{
		printf("Bu isimde yazar bulunamadý. Çýkmak için bir tuþa basýn.");
		free(a);
		free(yeniad);
		getch();
		return 1;
	}

	while (girdi != 1 && girdi != 2)
	{
		system("cls");
		printf("Hangi Bilgi Deðiþtirilecek?\nÝsim:1\nSoyad:2\nInput");
		scanf("%d", &girdi);
	}

	if (girdi == 1)
	{
		printf("Yazarýn yeni Adýný giriniz:");
		gets(yeniad);
		gets(yeniad);
		strcpy(tmp_2->yazarAd, yeniad);
	}
	else
	{
		printf("Yazarýn yeni Soyadýný giriniz:");
		gets(yeniad);
		gets(yeniad);
		strcpy(tmp_2->yazarSoyad, yeniad);
	}

	yazar_write(*head, "Yazar_guncel.csv");
	free(a);
	free(yeniad);
	system("cls");
	return 0;
}

int yazar_bilgisi_goruntule(YAZARLAR *head, KITAPYAZAR *kitapyazar, int size, KITAPLAR *kitap_head)
{
	YAZARLAR *yazar_tmp = head, *yazar_tmp_2 = NULL;
	KITAPLAR *kitap_tmp = kitap_head, *kitap_tmp2 = kitap_head;
	int control = 0, i, control_2 = 0;
	char *a = (char*) malloc(sizeof(char) *30);
	printf("Bilgisi görüntülenecek olan yazarýn Ad veya Soyad giriniz:\nInput:");
	gets(a);
	gets(a);
	while (yazar_tmp != NULL && control == 0)
	{
		if (strcmp(yazar_tmp->yazarAd, a) == 0 || strcmp(yazar_tmp->yazarSoyad, a) == 0)
		{
			yazar_tmp_2 = yazar_tmp;
			control = 1;
		}

		yazar_tmp = yazar_tmp->next;
	}

	if (control == 0)
	{
		return 1;	//yazar bulunamadý
	}

	printf("\nYazarýn ID:%d Yazarýn Adý:%s Yazarýn Soyadý:%s \n\nYazarýn kitaplarý aþaðýda listelenmiþtir.\n", yazar_tmp_2->yazarID, yazar_tmp_2->yazarAd, yazar_tmp_2->yazarSoyad);
	for (i = 0; i < size; i++)
	{
		if (kitapyazar[i].YazarID == yazar_tmp_2->yazarID)
		{
			control_2 = 1;
			kitap_tmp = kitap_tmp2;
			while (kitap_tmp != NULL)
			{
				if (strcmp(kitapyazar[i].ISBN, kitap_tmp->ISBN) == 0)
				{
					printf("Kitap adý:%s Kitap ISBN:%s Kitap Adedi:%d\n", kitap_tmp->kitapAdi, kitap_tmp->ISBN, kitap_tmp->adet);
				}

				kitap_tmp = kitap_tmp->next;
			}
		}
	}

	if (control_2 == 0)
	{
		printf("Yazarýn kitabý yoktur.");
	}

	printf("\nÇýkmak için herhangi bir sayý girin.");
	getch();
	free(a);
	return 0;
}

int kitap_guncelle(KITAPLAR **head)
{
	KITAPLAR *temp = *(head), *temp_2 = NULL;
	int bilgi, control = 0;
	char *a;
	printf("Bilgisi deðiþtirilecek kitabý ne ile aramak istersiniz?\nISBN:1\nKitap Adý:2\nInput:");
	scanf("%d", &bilgi);
	if (bilgi == 1)
	{
		a = (char*) malloc(sizeof(char) *15);
		printf("Bilgisi deðiþecek kitabýn ISBN giriniz:");
		gets(a);
		gets(a);
	}
	else
	{
		a = (char*) malloc(sizeof(char) *30);
		printf("Bilgisi deðiþecek kitabýn Adýný giriniz:");
		gets(a);
		gets(a);
	}

	if (a == NULL)
	{
		printf("Malloc sýrasýnda hata. Çýkmak için bir sayý giriniz.");
		getch();
		return 1;
	}

	while (temp != NULL && control == 0)
	{
		if (bilgi == 1 && strcmp(temp->ISBN, a) == 0)
		{
			temp_2 = temp;
			control = 1;
		}
		else if (bilgi == 2 && strcmp(temp->kitapAdi, a) == 0)
		{
			temp_2 = temp;
			control = 1;
		}

		temp = temp->next;
	}

	if (temp_2 == NULL)
	{
		printf("Bu bilgiyle kitap bulunamadý. Çýkmak için herhangi bir sayý girin.");
		free(a);
		getch();
		return 1;
	}

	printf("Kitap bulundu. Kitabýn yeni adýný giriniz:");
	gets(a);
	strcpy(temp_2->kitapAdi, a);
	printf("\nÝþlem baþarýlý. Çýkmak için bir sayý giriniz:");
	free(a);
	getch();
	return 0;
}

int kitap_bilgisi_goruntule(KITAPLAR *head, YAZARLAR *yazar_head, KITAPYAZAR *kitapyazar, int size, char *a)
{
	KITAPLAR *kitap_tmp = head, *kitap_tmp2 = NULL;
	YAZARLAR *yazar_tmp = yazar_head, *yazar_tmp2 = yazar_head;
	int control = 0, i, control_2 = 0, b;
	//char *a =(char*)malloc(sizeof(char)*30);
	//printf("Bilgisi gösterilecek kitabýn adýný giriniz:");
	//gets(a);
	//gets(a);
	while (kitap_tmp != NULL)
	{
		if (strcmp(kitap_tmp->kitapAdi, a) == 0)
		{
			control = 1;
			kitap_tmp2 = kitap_tmp;
		}

		kitap_tmp = kitap_tmp->next;
	}

	if (kitap_tmp2 == NULL)
	{
		printf("Kitap bulunamadý. Çýkmak için herhangi bir sayý giriniz:");
		getch();
		return 1;
	}

	printf("Kitabýn Adý:%s Kitabýn ISBN:%s Kitabýn adedi:%d Kitabýn yazarlarý:", kitap_tmp2->kitapAdi, kitap_tmp2->ISBN, kitap_tmp2->adet);
	for (i = 0; i < size; i++)
	{
		if (strcmp(removeSpacesFromStr(kitapyazar[i].ISBN), removeSpacesFromStr(kitap_tmp2->ISBN)) == 0)
		{
			b = kitapyazar[i].YazarID;
			yazar_tmp = yazar_tmp2;
			while (yazar_tmp != NULL)
			{
				if (yazar_tmp->yazarID == b)
				{
					printf(" %s %s,", yazar_tmp->yazarAd, yazar_tmp->yazarSoyad);
				}

				yazar_tmp = yazar_tmp->next;
			}
		}
	}

	return 0;
}

int raftaki_kitap_listele(KITAPLAR *kitap_head)
{
	int i, count = 0;
	KITAPLAR *kitap_tmp = kitap_head;
	KITAPORNEK * ornek_tmp;
	system("cls");
	printf("Raftaki kitaplar aþaðýda listelenmiþtir.\n");
	while (kitap_tmp != NULL)
	{
		printf("Kitap adý:%s ISBN:%s\nRafta Bulunanlar:\n", kitap_tmp->kitapAdi, kitap_tmp->ISBN);
		count = 0;
		for (i = 0; i < kitap_tmp->adet; i++)
		{
			ornek_tmp = kitap_tmp->head;
			if (strcmp(ornek_tmp[i].Durum, "Rafta") == 0)
			{
				printf("Etiket no:%s\n", ornek_tmp[i].EtiketNo);
				count = 1;
			}
		}

		if (count == 0)
		{
			printf("\nRafta bu kitaptan yok.");
		}

		kitap_tmp = kitap_tmp->next;
	}

	printf("\nÇýkmak için bir sayý giriniz:");
	getch();
	return 0;
}

int zamaninda_teslim_etmeyen_listele(KITAP_ODUNC *kitapodunc, int size, KITAPLAR *kitap_head, YAZARLAR *yazar_head, KITAPYAZAR *kitapyazar, int size2)
{
	int gun, z, ay, yil, i, j, count = 0, control = 0, control_2 = 0;
	char *buffer = malloc(sizeof(char) *30);
	char *w_ptr, *new_string;
	int w_index;
	TARIH abcd;
	KITAPLAR *kitap_tmp = kitap_head, *kitap_tmp2 = kitap_head;
	printf("Bugün ayýn hangi günü olduðunu girin:");
	scanf("%d", &gun);
	printf("Bugün yýlýn kaçýncý ayý olduðunu girin:");
	scanf("%d", &ay);
	printf("Yýlý giriniz:");
	scanf("%d", &yil);
	abcd.gun = gun;
	abcd.ay = ay;
	abcd.yil = yil;

	for (i = 0; i < size; i++)
	{
		if (kitapodunc[i].islemTipi == 0)
		{
			control = 0;
			for (j = i + 1; j < size; j++)
			{
				if (strcmp(kitapodunc[j].EtiketNo, kitapodunc[i].EtiketNo) == 0 && (kitapodunc[j].islemTipi == 1) && strcmp(kitapodunc[j].ogrID, kitapodunc[i].ogrID) == 0)
				{
					control = 1;
				}
			}

			if (control == 0)
			{
				kitap_tmp = kitap_tmp2;
				control_2 = 0;
				w_ptr = strchr(kitapodunc[i].EtiketNo, '_');
				w_index = w_ptr - kitapodunc[i].EtiketNo;
				new_string = (char*) malloc(sizeof(char) *(w_index + 1));
				strncpy(new_string, kitapodunc[i].EtiketNo, w_index);
				new_string[w_index] = '\0';

				while (kitap_tmp != NULL && control_2 == 0)
				{
					if (strcmp(new_string, kitap_tmp->ISBN) == 0)
					{
						control_2 = 1;
						strcpy(buffer, kitap_tmp->kitapAdi);
					}

					kitap_tmp = kitap_tmp->next;
				}

				if (control_2 == 1&&dayCalculator(kitapodunc[i].islemTarihi,abcd)>15)
				{
					z = kitap_bilgisi_goruntule(kitap_head, yazar_head, kitapyazar, size2, buffer);
					printf(" Etiket no:%s", kitapodunc[i].EtiketNo);
					printf("\n");
					count = count + 1;
				}
			}
		}
	}

	if (count == 0)
	{
		printf("Teslim edilmemiþ kitap yoktur.Geri dönmek için bir sayý girin");
	}
	else
	{
		printf("Ýþlem baþarýlý. Geri dönmek için bir sayý girin:");
	}

	getch();
	free(buffer);
	return 0;
}

int kitap_adet_bilgisi(KITAPLAR *kitap_head, char *a)
{
	KITAPLAR *kitap_tmp = kitap_head, *kitap_tmp2 = NULL;
	KITAPORNEK * abcd;
	int control = 0, c, i;
	while (kitap_tmp != NULL && control == 0)
	{
		if (strcmp(kitap_tmp->kitapAdi, a) == 0)
		{
			control = 1;
			kitap_tmp2 = kitap_tmp;
		}

		kitap_tmp = kitap_tmp->next;
	}

	if (control == 0)
	{
		printf("\nKitap bulunamadý\n");
		return 1;
	}
	c = kitap_tmp2->adet;
	abcd = kitap_tmp2->head;
	printf("\n");
	for (i = 0; i < c; i++)
	{
		printf("%s %s\n", abcd[i].EtiketNo, abcd[i].Durum);
	}

	return 0;
}
int kitap_yazar_guncelle(KITAPLAR *kitap_head, YAZARLAR *yazar_head, KITAPYAZAR **kitapyazar, int size)
{
	char *a = (char*) malloc(sizeof(char) *30);
	char *b = (char*) malloc(sizeof(char) *30);
	char *c = (char*) malloc(sizeof(char) *30);
	char *ISBN = (char*) malloc(sizeof(char) *15);
	KITAPYAZAR *kitapyazar_tmp = *(kitapyazar);
	YAZARLAR *yazar_tmp = yazar_head, *yazar_tmp2 = yazar_head;
	KITAPLAR *kitap_tmp = kitap_head, *kitap_tmp2 = NULL;
	int control = 1, control_2 = 0, control_4 = 0, yazarid, new_yazar_id, i;
	if (a == NULL || b == NULL || c == NULL || ISBN == NULL)
	{
		printf("Malloc esnasýnda hata.");
		return 1;
	}
	while (control != 0)
	{
		printf("Yazarý güncellenecek olan kitabýn adýný giriniz:");
		gets(a);
		gets(a);
		control = kitap_bilgisi_goruntule(kitap_head, yazar_head, *(kitapyazar), size, a);
		if (control == 0)
		{
			while (kitap_tmp != NULL && control_4 == 0)
			{
				if (strcmp(a, kitap_tmp->kitapAdi) == 0)
				{
					control_4 = 1;
					strcpy(ISBN, kitap_tmp->ISBN);
				}

				kitap_tmp = kitap_tmp->next;
			}
		}
	}
	while (control_2 == 0)
	{
		printf("\nHangi yazar deðiþtirelecek? Adýný veya Soyadýný giriniz:");
		gets(b);
		gets(b);
		control_2 = 0;
		yazar_tmp = yazar_tmp2;
		while (yazar_tmp != NULL && control_2 == 0)
		{
			if (strcmp(b, removeSpacesFromStr(yazar_tmp->yazarAd)) == 0 || strcmp(b, removeSpacesFromStr(yazar_tmp->yazarSoyad)) == 0)
			{
				control_2 = 1;
				yazarid = yazar_tmp->yazarID;
			}
			yazar_tmp = yazar_tmp->next;
		}
		if (control_2 == 0)
		{
			printf("Bu isimde yazar yoktur. Lütfen devam etmek için bir sayý girin:");
			getch();
		}
	}
	control_2 = 0;
	while (control_2 == 0)
	{
		printf("\nYeni yazarýn Adýný veya Soyadýný giriniz:");
		gets(c);
		gets(c);
		control_2 = 0;
		yazar_tmp = yazar_tmp2;
		while (yazar_tmp != NULL && control_2 == 0)
		{
			if (strcmp(c, yazar_tmp->yazarAd) == 0 || strcmp(c, yazar_tmp->yazarSoyad) == 0)
			{
				control_2 = 1;
				new_yazar_id = yazar_tmp->yazarID;
			}
			yazar_tmp = yazar_tmp->next;
		}
		if (control_2 == 0)
		{
			printf("Bu isimde yazar yoktur. Lütfen devam etmek için bir sayý girin:");
			getch();
		}
	}
	for (i = 0; i < size; i++)
	{
		if (strcmp(kitapyazar_tmp[i].ISBN, ISBN) == 0 && yazarid == kitapyazar_tmp[i].YazarID)
		{
			kitapyazar_tmp[i].YazarID = new_yazar_id;
		}
	}
	kitapyazar_write(kitapyazar_tmp, "KitapYazar.csv", size);

	free(ISBN);
	free(c);
	free(b);
	free(a);
	return 0;
}
int kitap_yazar_eslestir(KITAPLAR *kitap_head, YAZARLAR *yazar_head, KITAPYAZAR **kitapyazar, int *size)
{
	char *a = (char*) malloc(sizeof(char) *30);
	char *b = (char*) malloc(sizeof(char) *30);
	char *ISBN = (char*) malloc(sizeof(char) *15);
	KITAPYAZAR *kitapyazar_tmp = *(kitapyazar);
	YAZARLAR *yazar_tmp = yazar_head, *yazar_tmp2 = yazar_head;
	KITAPLAR *kitap_tmp = kitap_head;
	int control = 1, control_2 = 0, control_4 = 0, yazarid, i, adet;
	if (a == NULL || b == NULL)
	{
		printf("\nMalloc esnasýnda hata.\n");
		return 1;
	}
	while (control != 0)
	{
		printf("\nKitap adý giriniz:");
		gets(a);
		gets(a);
		control = kitap_bilgisi_goruntule(kitap_head, yazar_head, *(kitapyazar), *(size), a);
		if (control == 0)
		{
			while (kitap_tmp != NULL && control_4 == 0)
			{
				if (strcmp(a, kitap_tmp->kitapAdi) == 0)
				{
					control_4 = 1;
					strcpy(ISBN, kitap_tmp->ISBN);
				}

				kitap_tmp = kitap_tmp->next;
			}
		}
	}
	while (control_2 == 0)
	{
		printf("\nBu kitaba eklenecek yazarý giriniz:");
		gets(b);
		control_2 = 0;
		yazar_tmp = yazar_tmp2;
		while (yazar_tmp != NULL && control_2 == 0)
		{
			if (strcmp(b, yazar_tmp->yazarAd) == 0 || strcmp(b, yazar_tmp->yazarSoyad) == 0)
			{
				control_2 = 1;
				yazarid = yazar_tmp->yazarID;
			}

			yazar_tmp = yazar_tmp->next;
		}
		if (control_2 == 0)
		{
			printf("Bu isimde yazar yoktur. Lütfen devam etmek için bir sayý girin:");
			getch();
		}
	}
	*(size) = *(size) + 1;
	adet = *size;
	kitapyazar_tmp = (KITAPYAZAR*) realloc(kitapyazar_tmp, sizeof(KITAPYAZAR) *adet);
	if (kitapyazar_tmp == NULL)
	{
		printf("Realloc esnasýnda hata");
		getch();
		return 1;
	}
	kitapyazar_tmp[adet - 1].YazarID = yazarid;
	strcpy(kitapyazar_tmp[adet - 1].ISBN, ISBN);
	kitapyazar_write(kitapyazar_tmp, "KitapYazar.csv", *(size));
	free(a);
	free(b);
	free(ISBN);
	return 0;
}
