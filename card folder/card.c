
#include"card.h"
ST_cardData_t     user2_cardData; //for function test
EN_cardError_t getCardHolderName(ST_cardData_t *cardData){

printf("enter your name\n");
gets(cardData->cardHolderName);


if(((cardData)==NULL)||( strlen((*cardData).cardHolderName)<20)||( strlen((*cardData).cardHolderName)>24))
return WRONG_NAME ;
else return OK;

}






EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){

printf("enter expiry date in this formate mm/yy\n");
scanf("%s",cardData->cardExpirationDate);

if( (((cardData)==NULL)||(cardData->cardExpirationDate[2]!='/')||(strlen(cardData->cardExpirationDate)<5)||(strlen(cardData->cardExpirationDate)>5)  ) || ( (cardData->cardExpirationDate[0]-'0'==0&&cardData->cardExpirationDate[1]-'0'>9) || (cardData->cardExpirationDate[0]-'0'==1&&cardData->cardExpirationDate[1]-'0'>2)   )
   ||  cardData->cardExpirationDate[0]-'0'> 1)
return WRONG_EXP_DATE ;

else return OK;

}
EN_cardError_t getCardPAN(ST_cardData_t *cardData){

printf("enter Primary Account Number\n ");
scanf("%s",cardData->primaryAccountNumber);

if (((cardData)==NULL)||(strlen(cardData->primaryAccountNumber)<16)||(strlen(cardData->primaryAccountNumber)>19) )
return WRONG_PAN;
else return OK;

}
void getCardHolderNametest(void){
char m =getCardHolderName( &user2_cardData);
if(m==0){  printf("name is valid");}
else {  printf("name is not valid");}
}
 void getCardExpiryDatetest(void){
 char m =getCardExpiryDate( &user2_cardData);
if(m==0){  printf(" expiry date is valid");}
else {  printf("expiry date is not valid");}
}


void getCardPANtest(void){
char m =getCardPAN( &user2_cardData);
if(m==0){  printf(" pan number is valid");}
else {  printf("pan number  is not valid");}

}
