#include<iostream>
#include<conio.h>

#include "ConsoleHandler.h"
#include "user.h"



ConsoleHandler::ConsoleHandler(){ }              //constructor 


ConsoleHandler::newUser(){}                    //Not done Will define it later

                         



menuSelection ConsoleHandler::mainMenu()
{
              int  ch;

                     cout<<"\n\n\n\n\n";
     cout<<"\t\t--------------------------------------------\n";
     cout<<"\t\t|\t\t   STOCK\t           |\n";
     cout<<"\t\t|   \t\t\t\t\t   |\n";
     cout<<"\t\t|   \t\t\t\t\t   |\n";
     
     if(connected)                                            //checks internet connectivity in main menu
       cout<<"\t\t|\t1. Buy Stocks\t                   |\n";
     else
       cout<<"\t\t|\t*. Buy Stocks\t                   |\n";
     cout<<"\t\t|   \t\t\t\t\t   |\n";
     
     if(connected)
     cout<<"\t\t|\t2. Sell Stocks\t                   |\n";
     else
     cout<<"\t\t|\t*. Sell Stocks\t                   |\n";
     
     cout<<"\t\t|   \t\t\t\t\t   |\n";
     cout<<"\t\t|\t3. PortFolio\t                   |\n";    
     cout<<"\t\t|   \t\t\t\t\t   |\n";    
     cout<<"\t\t|\t4. View status\t                   |\n";
     cout<<"\t\t|   \t\t\t\t\t   |\n";   
     cout<<"\t\t|\t5. Exit        \t                   |\n";
        cout<<"\t\t|   \t\t\t\t\t   |\n";   
      cout<<"\t\t--------------------------------------------\n";
     
     cout<<"\n\t\t\t#enter your option\n";
     cout<<"\n\t\t\t>";
     cin>>>ch;
     
     
     switch(ch)
     {
               case 1: return(BUY);
               break;
               case 2: return(SELL);
               break;
               case 3: return(PORTFOLIO);
               break;
               case 4: return(STATUS);
               break;
               case 5:return(EXIT);
               break;
               
     }
     
     
}
