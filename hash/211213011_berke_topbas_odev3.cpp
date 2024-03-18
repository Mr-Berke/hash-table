#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int takipNo;
    char gonderici[100];
    char alici[100];
    char kargoDurum[100];
} Kargo;

Kargo* hash_tablo[10];

int hash_fonk(int takipNo) {
	int sonuc=takipNo%10;
    return sonuc;
}

int hasf_fonk2(int takipNo){
	int sonuc=7-(takipNo%7);
	return sonuc;
}

int doubleHashing (int hashIndex1,int deneme,int hashIndex2){
	int sonuc=(hashIndex1 + deneme * hashIndex2) % 10;
	return sonuc;
}

void ekle(Kargo *kargo) {
    int index = hash_fonk(kargo->takipNo);
    int index2 = hasf_fonk2(kargo->takipNo);

    if (hash_tablo[index] == NULL) {
        hash_tablo[index] = kargo;
    } 
	else {
       int deneme=1;
       int index;
       
       while (1) {
            int index3 = doubleHashing(index, deneme,  index2);

            if (hash_tablo[index3] == NULL) {
                hash_tablo[index3] = kargo;
                break;
            }
            deneme++;

            if (deneme == 10) {
                printf("Tablo dolu!\n");
                break;
            }
        }
    }
}

void dosyadanOkuVeEkle() {
    FILE *dosya = fopen("veri.txt", "r");

    if (dosya == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    while (1) {
        Kargo *kargo = (Kargo *)malloc(sizeof(Kargo));
        if (fscanf(dosya, "%d %s %s %s", &kargo->takipNo, kargo->gonderici, kargo->alici, kargo->kargoDurum) == 4) {
            ekle(kargo);
        } 
		else {
            free(kargo); 
            break; 
        }
    }
    fclose(dosya);
}


Kargo* kargoOlustur(int takipNo, char *gonderici, char *alici, char *kargoDurum) {
    Kargo *kargo = (Kargo *)malloc(sizeof(Kargo));
    kargo->takipNo = takipNo;
    strcpy(kargo->gonderici, gonderici);
    strcpy(kargo->alici, alici);
    strcpy(kargo->kargoDurum, kargoDurum);
    return kargo;
}

void kargo_takip(int takipNo) {
    for (int i = 0; i < 10; i++) {
        if (hash_tablo[i] != NULL && hash_tablo[i]->takipNo == takipNo) {
            printf("%d. adimda bulundu\n", i + 1);
            printf("Gonderici: %s,\tAlici: %s,\tDurum: %s\n", hash_tablo[i]->gonderici, hash_tablo[i]->alici, hash_tablo[i]->kargoDurum);
        }
    }
}

void kargo_sil(int takipNo) {
    for (int i = 0; i < 10; i++) {
        if (hash_tablo[i] != NULL && hash_tablo[i]->takipNo == takipNo) {
            hash_tablo[i] = NULL;
            printf("kargo teslim edildi\n");
            return;
        }
    }
    printf("kargo bulunamadi");
}


int main() {
	
	int secim,numara,numara2 ;
	char gonderici[100],alici[100],kargoDurum[100];
	Kargo *yeniKargo;
	
	do {
		printf("\n1-dosyadan veri girisi\n2-listeleme \n3-kargo girisi\n4-kargo takip \n5-kargoyu teslim et\n6-cikis\n");
        scanf("%d", &secim);
        
        system("cls");
		
		switch(secim){
		case 1:
			dosyadanOkuVeEkle();
			printf("dosyadan veri girisi yapildi\n");
		break;
		
		case 2:
			for (int i = 0; i < 10; i++) {
	        if (hash_tablo[i] != NULL) {
	            printf("Index %d - Takip No: %d,\tGonderici: %s,\tAlici: %s,\tDurum: %s\n", i, hash_tablo[i]->takipNo, hash_tablo[i]->gonderici, hash_tablo[i]->alici, hash_tablo[i]->kargoDurum);
	        	}
    		}
		break;
		
		case 3:
			printf("Eklenecek kargonun takip numarasini girin: ");
            scanf("%d", &numara);
            printf("Eklenecek kargonun gondericisini girin: ");
            scanf("%s", gonderici);
            printf("Eklenecek kargonun alicisini girin: ");
            scanf("%s", alici);
            printf("Eklenecek kargonun durum bilgisini girin: ");
            scanf("%s", kargoDurum);
            
            yeniKargo = kargoOlustur(numara, gonderici, alici, kargoDurum);
   			ekle(yeniKargo);            
		break;		
		
		case 4:
			 printf("takip edilecek kargo numarasini giriniz:");
			 scanf("%d",&numara2);
			 kargo_takip(numara2);
		break;
		
		case 5:
			 printf("silinecek edilecek kargo numarasini giriniz:");
			 scanf("%d",&numara2);
			 kargo_sil(numara2);
		break;			
		
		case 6:
            exit(0);
        break;
		
		default:
			printf("hatali secim!!");			
		break;
		
			}	
		}while(secim!=6);
	       
    return 0;
}

