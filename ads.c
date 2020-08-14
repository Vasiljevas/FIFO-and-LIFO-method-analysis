#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ads_proceduros.h"
#include "queue.h"

/*
Grūdų sandėlis (ADT: stekas, eilė). Įmonė aktyviai prekiauja grūdais. Kiekvieną dieną įmonė
perka ir sandėliuoja grūdus bei juos parduoda (atsitiktinai nuo 0 iki 100% sandėlyje turimų grūdų). Yra
nustatyta per dieną superkamų grūdų norma (pvz., 100 t) ir supirkimo kaina (pvz., 200 LT/t), bet
natūralu, kad ne visomis dienomis vienodai sekasi, todėl ekspertiškai žinomas superkamų grūdų kiekio
maksimalus nuokrypis (pvz., 15%, tai reiškia, kad kiekvieną dieną įmonė superka 85-115 t grūdų) ir
maksimalus grūdų supirkimo kainos nuokrypis (pvz., 5%, tai reiškia, kad įmonė superka gūdus po 190-
210 LT/t). Parduodama grūdus įmonė ima nustatytą antkainį (pvz., 10%) nuo apskaitinės grūdų kainos.
Gali būti naudojami tokie atsargų apskaitos metodai: 1) FIFO supirkimo: pirmiausia parduodami
seniausiai įsigyti grūdai, apskaitinė grūdų kaina lygi supirkimo kainai; 2) LIFO svertinių vidurkių:
pirmiausia parduodami šviežiausi grūdai; apskaitinė gautų grūdų kaina nustatoma kaip tuo metu
sandėlyje turimų grūdų kainų svertinis vidurkis (pvz., jei sandėlyje turėjome 200 t grūdų, kurių
apskaitinė kaina 95 LT/t ir įsigijome dar 100 t po 110 LT/t, tai įsigytų grūdų apskaitinė kaina yra 100
LT/t = (200 * 95 + 100 * 110) / (200 + 100)). Tikslas: patyrinėti, kurį grūdų apskaitos metodą
naudodama įmonė gauna didesnį pelną.
*/


int randfrom(int min, int max) 
{
    int range = (max - min); 
    int div = RAND_MAX / range;
    return min + (rand() / div);
}
int getProfitAverage(int fullProfits[], int j)
{
  int sum = 0;
    for(int i = 0; i< j; i++){
      sum+=fullProfits[i];
    }
    return sum/j;
}


int main()
{

    //per dieną superkamų grūdų norma
    int amount = 100; //tonnes
    //supirkimo kaina
    int price = 200; //LT/t
    //superkamų grūdų kiekio maksimalus nuokrypis
    int amountDeviation = 15; // 15%
    //maksimalus grūdų supirkimo kainos nuokrypis
    int priceDeviation = 5; //5%
    //pardavimo antkainis
    int surcharge = 10; //10%

    int input;
    
    int daysToTest = 10; //kiek dienu vyks prekyba
    
    int rytis = 0;

    int fullProfits[daysToTest];
    int j=0;


  while(1) {
    if(j == daysToTest) {

      break;
    }

    printf("Ivesk '1' FIFO metodui, '2' LIFO metodui, '0' baigtis programai \n");

    scanf("%d", &input);

    int profit = 0; //pradzioje 0, rodo prekybos pelna
    int totalAmount = 0;
    int dayNumber = 0;
    int days = daysToTest;

    if(input == 1) {
      //FIFO metodas, naudoti eile (?)
      /*
        pirmiausia parduodami
        seniausiai įsigyti grūdai, 
        apskaitinė grūdų kaina lygi
        supirkimo kainai
      */
        printf("Bandome FIFO metoda\n");
        //vienas eiles elementas - vienai dienai
        queue* que=makeQueue(); 
        
        int leftovers[days];
        int sellingPrice;
        memset( leftovers, 0, days*sizeof(int) );

        do {
            printf("%d_________________%d\n", dayNumber+1,dayNumber+1);


            int randAmountToBuy = (amount * 
            (randfrom(amountDeviation - amountDeviation * 2 , amountDeviation) + 100))
             / 100; 

            sellingPrice = (price * 
            (randfrom(amountDeviation - amountDeviation * 2 , amountDeviation) + 100))
             / 100; 
            randfrom(priceDeviation - priceDeviation * 2, priceDeviation) + 100;
            //profit -= randAmountToBuy*sellingPrice;
            totalAmount += randAmountToBuy;
            int amountToSell = totalAmount * randfrom(0, 100) / 100;
            totalAmount -= amountToSell;
            printf("Nusipirkta grudu: %d\n", randAmountToBuy);
            printf("Pardavimo kaina: %d\n", sellingPrice);
            printf("Grudu parduota bus: %d\n", amountToSell);
            printf("islaidos: %d\n", randAmountToBuy*sellingPrice );
            printf("------------------------\n");

            if(isQueueEmpty(que)) {
            
              randAmountToBuy-=amountToSell;
              profit += amountToSell*sellingPrice * (100+surcharge) / 100;

              if(randAmountToBuy > 0) {
                //idedam likuti
                enQueue(randAmountToBuy, que);
              }

            } else {
          
            int ats = amountToSell; // the same thing
              //istustinam leftoverius || amountToSell ==0

              for(int i = 0; i < dayNumber; i++) {
                if(leftovers[i] > 0) {
                 
                  if(leftovers[i] <= ats) {
                    ats-=leftovers[i];
                    profit += leftovers[i] *sellingPrice * (100+surcharge) / 100;
                  } else {
                    leftovers[i] = leftovers[i] - ats;
                    profit += ats * sellingPrice * (100+surcharge) /100;
                    ats = 0;
                  }
                }
              }
              //imam atsargas is eiles
              while(ats > 0) {
                if(isQueueEmpty(que)==1) { 
                  
                  break;
                }
               
                int temp = getHead(que);
                
                deQueue(que, &rytis);
                if(temp <= ats) {
                  ats -= temp;
                  profit += temp * sellingPrice * (100+surcharge) / 100;
                  
                 
                } else {  //temp>ats
                  leftovers[dayNumber] = temp - ats;
                  profit += ats * sellingPrice * (100+surcharge) /100;
                  ats = 0;

                  enQueue(leftovers[dayNumber], que);
                }
              }


              if(ats > 0) {
                randAmountToBuy-=ats;
                profit += ats * sellingPrice * (100+surcharge) /100;
                if(randAmountToBuy > 0) {
                  
                  enQueue(randAmountToBuy,que);
                }
              }

            
            } 
            printf("------------------------\n");
            printQueue(que);
            days--;
            dayNumber++;
            printf("Siandien parduota %d tonu grudu \n", amountToSell);
            printf("neparduota svieziu grudu %d tonu \n", randAmountToBuy);
            printf("atsargu bendrai yra %d tonu \n", totalAmount);
            printf("pelnas (profit) yra %d.\n", profit);


        } while (days > 0);
            printf("______________________\n");
            printf("FIFO prekyba baigta!\n");
            printf("Pelnas: %d \n", profit);
            printf("jeigu siandien parduotumeme likusius grudus tai pelnas butu: %d\n", profit + totalAmount*sellingPrice);
            fullProfits[j] = profit;
            j++;
    } else if (input == 2) {
      //LIFO metodas, naudoti steka (?)
      /*
      pirmiausia parduodami šviežiausi grūdai;
      apskaitinė gautų grūdų kaina nustatoma
      kaip tuo metu sandėlyje turimų grūdų
      kainų svertinis vidurkis
      pvz., jei sandėlyje turėjome 200 t grūdų, kurių
      apskaitinė kaina 95 LT/t ir įsigijome dar 100 t po 110 LT/t, tai įsigytų grūdų apskaitinė kaina yra 100
      LT/t = (200 * 95 + 100 * 110) / (200 + 100)
      */
         printf("Bandome LIFO metoda\n");
         Stack *top = NULL; //sukuriam steka?
         int sellingPrice;
         
         do {
            printf("%d_________________%d\n", dayNumber+1,dayNumber+1);


            int randAmountToBuy = (amount * 
            (randfrom(amountDeviation - amountDeviation * 2 , amountDeviation) + 100))
            / 100; 

            int randPrice = (price * 
            (randfrom(amountDeviation - amountDeviation * 2 , amountDeviation) + 100))
            / 100; 
            randfrom(priceDeviation - priceDeviation * 2, priceDeviation) + 100;
            //profit -= randAmountToBuy*randPrice;
            totalAmount += randAmountToBuy;
            int amountToSell = totalAmount * randfrom(0, 100) / 100;
            totalAmount -= amountToSell;

            

            //skaiciuojam pardavimo kaina
            int temp1=0; // (200 * 95 + 100 * 110)
            int temp2=0; // (200 + 100)
            int help[dayNumber]; // am
            int help2[dayNumber]; // pr
            int help3=0;
            
            while(!isStackEmpty(top)) {
                
                int pr = peek(top);
                
                pop(&top);
                int am = peek(top);
                
                pop(&top);
                temp2 += am;
                temp1 += pr*am;
                help[help3] = am;
                help2[help3] = pr;
                help3++;
            }
            
            for(int i=help3; i > 0; i--) {
                
                push(help[i-1], &top);
                
                push(help2[i-1], &top);

            }

            temp2+=randAmountToBuy;
            temp1+=randPrice*randAmountToBuy;

            sellingPrice = temp1 / temp2;
            printf("Nusipirkta grudu: %d\n", randAmountToBuy);
            printf("Siandien pirkta uz tokia kaina: %d\n", randPrice);
            printf("Apskaitos pardavimo kaina: %d\n", sellingPrice);
            printf("Grudu parduota bus: %d\n", amountToSell);
            printf("islaidos: %d\n", randAmountToBuy*randPrice );
            printf("------------------------\n");
            //parduodam
            if(randAmountToBuy >= amountToSell) {
                profit += amountToSell*sellingPrice * (100+surcharge) / 100;
                randAmountToBuy-=amountToSell;
               
                if(randAmountToBuy > 0) {
                  push(randAmountToBuy, &top);
                  push(randPrice, &top);
              }
            } else {
                int atss = amountToSell;
                profit += randAmountToBuy * sellingPrice * (100+surcharge) / 100;
                atss -= randAmountToBuy;
                
                while(atss > 0) {
                    
                    int tempPr = peek(top);
                    
                    pop(&top);

                    int tempAm = peek(top);
                    
                    pop(&top);
                    if(tempAm > atss) {
                      profit+= atss * sellingPrice * (100+surcharge) / 100;
                      tempAm-=atss;
                      atss=0;
                      push(tempAm, &top);
                      push(tempPr, &top);
                    } else {
                      atss -= tempAm;
                      profit += tempAm * sellingPrice * (100+surcharge) / 100;
                    }
                }

          }
        
          printf("------------------------\n");
          dayNumber++;
          days--;
          printf("Siandien parduota %d tonu grudu \n", amountToSell);
          printf("neparduota svieziu grudu %d tonu \n", randAmountToBuy);
          printf("atsargu bendrai yra %d tonu \n", totalAmount);
          printf("pelnas (profit) yra %d.\n", profit);

         } while (days > 0);

          printf("______________________\n");
          printf("LIFO prekyba baigta!\n");
          printf("Pelnas: %d \n", profit);
          printf("jeigu siandien parduotumeme likusius grudus tai pelnas butu: %d\n", profit + totalAmount*sellingPrice);
          
          fullProfits[j] = profit;
          j++;
    } else if(input == 0) {
        
        break;
         
    } else {
        printf("Bloga ivestis, bandyk dar kart\n");
    }
  } 

  printf("Darbas baigtas!\n" );
  printf("pelno vidurkis atliktu bandymu: %d \n", getProfitAverage(fullProfits, j));

  return 0;
}
