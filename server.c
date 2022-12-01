/*#include<string.h>
#include"server.h"

ST_cardData_t     user_cardData;  //for test function
ST_terminalData_t  user_terminalData;
ST_accountsDB_t  accountsDB[255] =  { { 15000,RUNNING , "58965487962103654"}, { 145600, BLOCKED,"1487962035874165" },
	{ 1854.3,RUNNING, "87496315478932198" }, { 78900,RUNNING, "1548796320158745" },
	{ 3824,BLOCKED, "8791459875214698" }, { 506090 ,RUNNING, "8547962103658945" },
	{ 800,BLOCKED, "78412039874102563" }, { 5200,BLOCKED, "7895142361258745" },
	{ 500, RUNNING,"15478963017896304" }, { 4823,RUNNING, " 1236547895210564" } };

ST_transaction_t   transactionDB [255]= { {{0,0,0},{0,0,0},0,0}, {{0,0,0},{0,0,0},0,0},
{ {0,0,0},{0,0,0},0,0}, {{0,0,0},{0,0,0},0,0},
{{0,0,0},{0,0,0},0,0}, {{0,0,0},{0,0,0},0,0},
{{0,0,0},{0,0,0},0,0}, {{0,0,0},{0,0,0},0,0},
{{0,0,0},{0,0,0},0,0}, {{0,0,0},{0,0,0},0,0} };
ST_accountsDB_t  accountsDB[255] ;
ST_transaction_t   transactionDB[255] ;
ST_accountsDB_t accountRefrence={0} ;
ST_transaction_t transs;
EN_transState_t recieveTransactionData(ST_transaction_t *transData){


// since in rubric we was Assuming that the connection between the terminal and server is always connected and that it will return SERVER_OK in saving fun.
// so all transaction can be saved
if ( isValidAccount(&transData->cardHolderData, &accountRefrence )   )

{
transData->transState =FRAUD_CARD ;


    return FRAUD_CARD;
}

else if ( isAmountAvailable(&transData->terminalData, &accountRefrence )   )

{
    transData->transState =DECLINED_INSUFFECIENT_FUND ;
    return DECLINED_INSUFFECIENT_FUND;
}

else if ( isBlockedAccount(&accountRefrence)  )

{   transData->transState =DECLINED_STOLEN_CARD ;
    return  DECLINED_STOLEN_CARD;
}
else
   {transData->transState =APPROVED;
 return APPROVED ;
   }



}
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence){


for (int ac =0;ac<10;ac++){

    if (  strcmp (cardData->primaryAccountNumber ,(accountsDB[ac].primaryAccountNumber) )  ) {continue;}
    else {  *accountRefrence =accountsDB[ac];

            return SERVER_OK ; }
}

printf("account not found\n");

return ACCOUNT_NOT_FOUND;

}
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
if (  accountRefrence->state ==BLOCKED )  { return BLOCKED_ACCOUNT   ;  }
else { return SERVER_OK ;}

}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence){
if ( termData->transAmount  > accountRefrence->balance     )  {  return LOW_BALANCE; }
else  {
        accountRefrence->balance=accountRefrence->balance-termData->transAmount;
        return SERVER_OK ; }

}
EN_serverError_t saveTransaction(ST_transaction_t *transData){

    static int seq_num =0;
    seq_num ++;
  transData->transactionSequenceNumber  = seq_num ;
  static int i =0;

 if (i<255){
  transactionDB [i].transactionSequenceNumber= transData->transactionSequenceNumber  ;
    strcpy(   transactionDB [i].terminalData.transactionDate ,transData->terminalData.transactionDate);
   transactionDB [i].terminalData.transAmount =transData->terminalData.transAmount;
      transactionDB [i].transState =transData->transState;
transactionDB [i].terminalData.maxTransAmount =transData->terminalData.maxTransAmount;
      strcpy(  transactionDB [i]. cardHolderData.cardHolderName ,transData->cardHolderData.cardHolderName);
   strcpy(     transactionDB [i].cardHolderData.primaryAccountNumber,transData->cardHolderData.primaryAccountNumber);
strcpy (transactionDB [i].cardHolderData.cardExpirationDate ,transData->cardHolderData.cardExpirationDate);

  }
  i++;
  return  SERVER_OK ;



}
void listSavedTransactions(void){
   int i =0;
      // while(  (transactionDB [i])!= {0,0,0},{0,0,0},0,0   &&( i<255 )  )        {



       printf("Transaction Sequence Number:%d\n",transactionDB [i].transactionSequenceNumber) ;
       printf("Transaction Date:%s\n",transactionDB [i].terminalData.transactionDate) ;
       printf("Transaction Amount:%f\n",transactionDB [i].terminalData.transAmount) ;
       printf("Transaction State:%d\n",transactionDB [i].transState) ;
       printf("Terminal Max Amount:%f\n",transactionDB [i].terminalData.maxTransAmount);
       printf("Cardholder Name:%s\n",transactionDB [i].cardHolderData.cardHolderName );
       printf("PAN:%s\n",transactionDB [i].cardHolderData.primaryAccountNumber);

//i++;

   // }
   i++;
}
void recieveTransactionDatatest(void){
char m =recieveTransactionData(&transs);
if (m == FRAUD_CARD) {
		printf("FRAUD_CARD\n");
	}
	else if (m == DECLINED_STOLEN_CARD) {
		printf("DECLINED_STOLEN_CARD\n");
	}
	else if (m == DECLINED_INSUFFECIENT_FUND) {
		printf("DECLINED_INSUFFECIENT_FUND\n");
	}
	else {
		printf(" approved .\n");

	}

}
void isValidAccounttest(void){
printf("plese enter your pan number\n");
scanf("%s",user_cardData.primaryAccountNumber);
char m =isValidAccount(&user_cardData, &accountRefrence);
if ( m==0){ printf("account is valid\n");}

else { printf("account is not valid\n");}

}
void  isBlockedAccounttest (void ){
char m =isBlockedAccount(&accountRefrence);
if ( m==0){ printf("account is running\n");}


else { printf("account is blocked\n");}
printf("%d",  accountRefrence.state);

}
void  isAmountAvailabletest (void){

printf("enter your transaction amount \n");
scanf("%f", &user_terminalData.transAmount);
char m =isAmountAvailable( &user_terminalData, &accountRefrence   ) ;
printf("%d\n",m);
if ( m==0){ printf("amount is available\n");
  printf(" your new balance:%f",  accountRefrence.balance); }
else { printf("amount is not avaliable");
}
}
void  saveTransactiontest (void){
char m=saveTransaction( &transs);
if (m==0)
printf( "saved");
else printf("not saved");
}
void listSavedTransactionstest  (void){
//listSavedTransaction();
}


*/

