#include<stdio.h>
#include<math.h>
																				/* Veriler veri.txt dosyasında tutulmaktadır. X1 ve X2 verileri bir telekominikasyon şirketine ait
																					iki pazarlamacanın günlük potansiyel müşteri arama sayısılarını tutmaktadır.
																					Y verisi de aranan müşteri sayısına karşılık günlük kazanılan abone sayısını tutmaktadır.
																					Txt dosyasına veri eklenip çıkarılabilir. Kod dinamik biçimde oluşturulmuştur. */



float korelasyon_katsayisi(int x1[], int x2[], int y[], int egitim_sayi, int n ){			//Eğitim verilerini kullanarak korelasyon katsayısını buluyoruz.
	
	int toplam_x1 = 0, toplam_x2, toplam_y = 0, toplam_x1y = 0, toplam_x2y =0, tahmin_y[100], SSE = 0;
	
	int tahmin_yTest[100], SSE_test = 0;
    
	int squareSum_x1 = 0, squareSum_x2 = 0, squareSum_y = 0;		//Verilein çarpımını tutan değişkenler
    
	float a, b , x1_orta = 0, x2_orta = 0, y_orta = 0, lxx = 0, lyy = 0;		//lxx ve lyy korelasyon katsayısının hesabında kullanılacak
 
    for (int i = 0; i < egitim_sayi ; i++)
    {
      
        toplam_x1 = toplam_x1 + x1[i];

		toplam_x2 = toplam_x2 + x2[i]; 
        
        toplam_y = toplam_y + y[i];
	
			 
        toplam_x1y = toplam_x1y + x1[i] * y[i];
        
        toplam_x2y = toplam_x2y + x2[i] * y[i];
 
        
        squareSum_x1 = squareSum_x1 + x1[i] * x1[i];
        
		squareSum_x2 = squareSum_x2 + x2[i] * x2[i];
        
		squareSum_y = squareSum_y + y[i] * y[i];
    }

    
    	x1_orta = toplam_x1 / egitim_sayi;
		
		x2_orta = toplam_x2 / egitim_sayi;
		
		y_orta = toplam_y / egitim_sayi;  
		
		
    
    float korelasyon1 = (float)(toplam_x1y - egitim_sayi * x1_orta * y_orta) 
						/ sqrt((squareSum_x1 - egitim_sayi * x1_orta * x1_orta) * (squareSum_y - egitim_sayi * y_orta * y_orta));
					
						printf("r1 => (x1,y) = %f\n\n",korelasyon1); 
						
	float korelasyon2 = (float)(toplam_x2y - egitim_sayi * x2_orta * y_orta) 
						/ sqrt((squareSum_x2 - egitim_sayi * x2_orta * x2_orta) * (squareSum_y - egitim_sayi * y_orta * y_orta));	
							
						printf("r2 => (x2,y) = %f\n\n",korelasyon2);
	
	
	if(korelasyon1 > korelasyon2){
	 
		printf("r1 > r2 => Korelasyon katsayisi: %f\n\n",korelasyon1);  
			 
		for(int i = 0; i < egitim_sayi; i++){
			
			lxx += (x1[i] - x1_orta) * (x1[i] - x1_orta);						//Regresyon denkleminin hesabı
			lyy += (y[i] - y_orta) * (y[i] - y_orta);
		}
		
		b = lyy / lxx;
		a = y_orta - b * x1_orta;
		
		printf("Regresyon modeli => Y = %0.2f + %0.2fx\n\n", a, b);			//Regresyon denkleminin yazdırılması
		
		printf("\t\n----Y Tahmin Degerleri----\n\t");  
		
		for(int i = 0; i < egitim_sayi; i++){
			
			tahmin_y[i] = a + b * x1[i];		//Regresyon denklemine göre eğitim verileri için tahmin dizisinin hesabı ve yazdırılması
			printf("%d\t",tahmin_y[i]);
			
			SSE += (y[i] - tahmin_y[i]) * (y[i] - tahmin_y[i]) ; 	//SSE hesaplanması
 
		}		
		
		printf("\nSSE : %d\n",SSE );
		
	//	printf("\n\n"); 
		
		printf("\t\n----Y Test Tahmin Degerleri----\n\t");
		
		for(int i = egitim_sayi; i < n; i++){
			
			tahmin_yTest[i] = a + b * x1[i];							//%30 luk test verileri için tahmin değerleri ve SSE hesabı
			printf("%d\t",tahmin_yTest[i]);
			
			SSE_test += (y[i] - tahmin_yTest[i]) * (y[i] - tahmin_yTest[i]); 
			
		}
		
		printf("\n");
		printf("\nSSE_Test : %d\n",SSE_test );
		 
		return korelasyon1 ;
	} 
	
	else
	
		printf("r2 > r1 => Korelasyon katsayisi: %f",korelasyon2);
	
		for(int i = 0; i < egitim_sayi; i++){
			
			lxx += (x2[i] - x1_orta) * (x1[i] - x1_orta);
			lyy += (y[i] - y_orta) * (y[i] - y_orta);
		}
		
		b = lyy / lxx;
		a = y_orta - b * x1_orta;
		
		printf("Regresyon modeli => Y = %0.2f + %0.2fx\n\n", a, b);
		
		printf("\t\n----Y Tahmin Degerleri----\n\t");  
		
		for(int i = 0; i < egitim_sayi; i++){
			
			tahmin_y[i] = a + b * x2[i];
			printf("%f\t",tahmin_y[i]);
 
 			SSE += (y[i] - tahmin_y[i]) * (y[i] - tahmin_y[i]) ;
		}	
		
		printf("\nSSE : %d\n",SSE );
		
		printf("\t\n----Y Test Tahmin Degerleri----\n\t");
		
		for(int i = egitim_sayi; i < n; i++){
			
			tahmin_yTest[i] = a + b * x2[i];							//%30 luk test verileri için tahmin değerleri ve SSE hesabı
			printf("%d\t",tahmin_yTest[i]);
			
			SSE_test += (y[i] - tahmin_yTest[i]) * (y[i] - tahmin_yTest[i]); 
			
		}
		
		printf("\n");
		printf("\nSSE_Test : %d\n",SSE_test );
		
	return korelasyon2;
}

int main(){

	int n = 0, i = 0;             //n => Genel terim sayısı
	
	int x1[120], x2[120], y[120];  //Verileri tuttuğumuz diziler
	
	FILE *fp;
	fp = fopen("veri.txt","r");
	if(fp != NULL)
	{
		while(!feof(fp))			
		{
			fscanf(fp,"%d %d %d ",&x1[i] ,&x2[i] ,&y[i]);		//Veileri dosyadan okuma işlemi
			
			n++;
			i++;		
		}
 
	}
	else
	{
		printf("Dosya bulunamadi!"); 
	}
	
	int egitim_sayi; //Eğitim verilerini %70 olarak ayarlamak için bu değeri kullanıyorum
	
	egitim_sayi = (n * 7) / 10;	//%70 hesabı
	
	printf("\nKorelasyon Katsayisi :%2f", korelasyon_katsayisi(x1, x2, y, egitim_sayi,n)); 
	
	fclose(fp);   //Dosyayı kapatıyoruz
}

