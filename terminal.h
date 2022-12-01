/*#ifndef TERMINAL_H_INCLUDED
#define TERMINAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
#include"card.h"
typedef struct ST_terminalData_t
{
     float transAmount;
     float maxTransAmount;
     uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
     TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData); // Optional

void  getTransactionDatetest (void);
void isCardExpiredtest  ( void);
void  getTransactionAmounttest (void);
void isBelowMaxAmounttest (void);
void  setMaxAmounttest (void);
void  isValidCardPANtest  (void);

#endif // TERMINAL_H_INCLUDED*/
