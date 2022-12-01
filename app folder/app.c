
#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
#include<string.h>
#include"app.h"
#define max_amout   10000

 extern ST_accountsDB_t  accountsDB[255] ;
 extern ST_transaction_t   transactionDB[255] ;
 extern ST_accountsDB_t accountRefrence ;

void appStart(void){
//card holder data
ST_cardData_t     user_cardData;

 EN_cardError_t      erorforname;
  EN_cardError_t      erorfordate;
   EN_cardError_t      erorforpan;
   do {
		erorforname  = getCardHolderName(&user_cardData);
	} while (erorforname  == WRONG_NAME);
	do {
		erorfordate= getCardExpiryDate(&user_cardData);
	} while (erorfordate == WRONG_EXP_DATE);
	do {
		erorforpan = getCardPAN(&user_cardData);
	} while (erorforpan== WRONG_PAN);
 //terminal data
 ST_terminalData_t  user_terminalData;
EN_terminalError_t  errorfortransdate;
 EN_terminalError_t  expirydatecheck;
 EN_terminalError_t  errorfortransamount;
 EN_terminalError_t    maxamountcheck  ;
 EN_terminalError_t    getmaxamount      ;
   do {
		errorfortransdate  = getTransactionDate(&user_terminalData);
	} while (errorfortransdate  == WRONG_DATE);

		expirydatecheck=  isCardExpired( &user_cardData,&user_terminalData);
	 if (expirydatecheck == EXPIRED_CARD){
	 	 printf("your card is expired");
	 	 return ;}

	do {
		errorfortransamount = getTransactionAmount(&user_terminalData);
	} while (errorfortransamount==INVALID_AMOUNT);
   do {
		  getmaxamount   = setMaxAmount(&user_terminalData,max_amout);
	} while (getmaxamount == INVALID_MAX_AMOUNT);

        maxamountcheck  = isBelowMaxAmount(&user_terminalData);
	if (maxamountcheck  == EXCEED_MAX_AMOUNT) {
	printf("you exceeded the amount\n");
	return ;
	}
 // then server

 EN_serverError_t      error_server;
error_server =isValidAccount(&user_cardData, &accountRefrence);
if ( error_server==ACCOUNT_NOT_FOUND)
    return ;
error_server = isAmountAvailable(&user_terminalData,&accountRefrence);
	if (error_server  == LOW_BALANCE )
		return;
 error_server =     isBlockedAccount(&accountRefrence);
		if (error_server  ==BLOCKED_ACCOUNT  )
		return;
//then save
  EN_transState_t transstate;
	ST_transaction_t  trans;
	trans.cardHolderData = user_cardData;
	trans.terminalData = user_terminalData;

transstate = recieveTransactionData(&trans);
	if (transstate == FRAUD_CARD) {
		printf("FRAUD_CARD\n");
	}
	else if (transstate == DECLINED_STOLEN_CARD) {
		printf("DECLINED_STOLEN_CARD\n");
	}
	else if (transstate == DECLINED_INSUFFECIENT_FUND) {
		printf("DECLINED_INSUFFECIENT_FUND\n");
	}
	else {
		printf(" succsed transation  .\n");
		printf("your new balance:%f\n",accountRefrence.balance);
	}

trans.transState=transstate;


error_server=saveTransaction(&trans);
if(error_server==SERVER_OK )
listSavedTransactions();

}
int main () {



appStart();



return 0;
}

