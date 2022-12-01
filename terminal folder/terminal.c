
#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
#include<string.h>
#include"terminal.h"
#include"../card folder/card.h"
ST_terminalData_t  user2_terminalData; //for function test
ST_cardData_t     user22_cardData; //for function test

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
printf("enter your transaction  date in this formate DD/yy/xxx\n");
scanf("%s", termData->transactionDate);


if (((termData)==NULL)||(termData->transactionDate[2]!='/')||(termData->transactionDate[5]!='/')||(strlen(termData->transactionDate)<10) ||( (termData->transactionDate[3]-'0'==0&&termData->transactionDate[4]-'0'>9) || (termData->transactionDate[3]-'0'==1&&termData->transactionDate[4]-'0'>2)   )
     ||(termData->transactionDate[0]-'0'>3 ) ||(termData->transactionDate[3]-'0'>1 ) ||(strlen(termData->transactionDate)<10) )
return WRONG_DATE ;
else return TERMINAL_OK;

}







EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){
char* exmonth;    //for expiray month
   char* exyear;   //for expiray year

	char* transday;
	char* transmonth;
	char* transyear;
//convert each string to tokens

	exmonth = strtok(cardData->cardExpirationDate, "/");   // taking first token
	exyear = strtok(NULL, "/");     //taking other tokens
	transday = strtok(termData->transactionDate, "/");  //for taking first token
	transmonth = strtok(NULL, "/");   //the second one
	transyear = strtok(NULL, "/") +2; // i put +2 to remove first two chars in last token
//printf("%s\n",exmonth);
//printf("%s\n",exyear);
//printf("%s\n",transday);    //to ckeck
//printf("%s\n",transmonth);
//printf("%s\n",transyear);


	//convert each token to number
	int exmonth_num=   atoi(exmonth) ;
     int exyear_num=   atoi( exyear);
 int transday_num=   atoi(transday);
int transmonth_num=  atoi( transmonth);
 int transyear_num=  atoi( transyear);





	if ( exyear_num<transyear_num  )   { return EXPIRED_CARD;}     //year is before so not valid
	else if ((exyear_num==transyear_num)&&(exmonth_num<transmonth_num))  { return EXPIRED_CARD;}   //year is equal but month is before so also not valid

else{ return TERMINAL_OK;}





}
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){

printf("enter your transaction amount \n");
scanf("%f", &termData->transAmount);
if(termData->transAmount<=0 ) { return INVALID_AMOUNT;}
else { return TERMINAL_OK ; }

}



EN_terminalError_t setMaxAmount(ST_terminalData_t *termData,float maxAmount){

printf("enter your max transaction amount \n");
scanf("%f", &termData->maxTransAmount);
if(termData->maxTransAmount<=0 ) { return INVALID_MAX_AMOUNT;}
else { return TERMINAL_OK ; }
}





EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){


if (termData->transAmount > termData->maxTransAmount  ){ return EXCEED_MAX_AMOUNT;}
else { return TERMINAL_OK ; }
}

//EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData); // Optional

void  getTransactionDatetest (void){
char m =getTransactionDate(&user2_terminalData );
if (m==0){printf("valid data") ;}
else {printf("wrong data") ;}
}
void isCardExpiredtest  ( void){

  char  k= getTransactionDate(&user2_terminalData );
    printf("%d\n",k);
   char z= getCardExpiryDate( &user22_cardData);
    printf("%d\n",z);
   printf("%s\n",user22_cardData.cardExpirationDate);
    printf("%s\n",user2_terminalData.transactionDate);
    if (z==0&&k==0)
        {


    char m =isCardExpired( &user22_cardData,&user2_terminalData );
if (m==TERMINAL_OK){printf(" not expired card") ;}
else {printf(" expired card ") ;}
        }
    else {printf("wrong dates entered  ") ; }


}
void  getTransactionAmounttest (void){
char m =getTransactionAmount(&user2_terminalData );
if (m==0){printf("valid amount") ;}
else {printf("invalid amount") ;}

}
void isBelowMaxAmounttest (void){
char m =isBelowMaxAmount(&user2_terminalData );
if (m==0){printf("below max  amount valid ") ;}
else {printf("invalid   exceed max amount") ;}


}
void  setMaxAmounttest (void){
char m =setMaxAmount(&user2_terminalData,500 );
if (m==0){printf("valid  max amount") ;}
else {printf("invalid max  amount") ;}

}



