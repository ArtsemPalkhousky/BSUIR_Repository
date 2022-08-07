#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <iostream.h>
void interrupt far new_Interrupt(...); //functiya obrabotki prerivanii
void interrupt far (*old_Interrupt)(...); //ukazatel na obrabotchik prerivanii
 
void indicator(unsigned char mask); //functiya upravleniya indicatorami
void blinking(void); //functiya miganiya indikatorom
 
int isResend = 1; // error flag / neobhodimosti povtornoi peredachi dannih
int quitFlag = 0; // exit program flag
int blinkingON = 0; // flag miganiya indikatorami
int main()
{
 old_Interrupt = getvect(0x09);//zapominaem starii obrabotchik prerivania nomer 0x09 (t.e. ot klavi)
 setvect(0x09, new_Interrupt); //stavim novii obrabotchik (na to je prerivanie)
 while(!quitFlag) //poka ne ustanovlen flag vihoda
 {
    if(blinkingON) //esli ustanovlen flag miganiya indikatorom
        blinking();//migaem indikatorami
 }
 setvect(0X09, old_Interrupt);
 cout<<"Press any key..."<<endl;
 getch();
 return 0;
}
void interrupt far new_Interrupt(...)
{
 unsigned char value = 0;
// old_Interrupt(); //peredaem upravlenie staromu obrabotchiku
 value = inp(0x60); // poluchaem znachenie iz porta 60h
 if(value == 0x10)   //esli najata klaviwa 'q'
    quitFlag = 1; //ustanavlivaem flag vihoda
 if(value == 0x39 && blinkingON == 0) //esli najata klavisha 'space' i flag migalki 0
    blinkingON = 1;              //ustanavlivaem flag migalki v 1
 else if(value == 0x39 && blinkingON == 1) //esli najata klaviwa 'space' i flag migalki 1
    blinkingON = 0;                   //ustanavlivaem flag migalki v 0
 if(value != 0xfa && blinkingON == 1) //esli net podtverjdeniya uspewnogo vipolneniya komandi
    isResend = 1;            //ustanavlivaem flag povtormoi peredachi baita
 else isResend = 0;
 //value -= 32;
 cout << "Kod vozvrata: 0x "<<hex<<(int)value<<endl;
 outp(0x20, 0x20); // sbros controllera prerivanii
// old_Interrupt();
 }
 
 void indicator(unsigned char mask)
 {
 isResend = 1;
 while(isResend) //poka net podtverjdeniya uspeshnogo vipolneniya komandi
  {
   while((inp(0x64)&0x02) != 0x00);//ojidaem osvobojedeniya vhodnogo bufera klavi
   outp(0x60, 0xED); //zapisivaem v port komandu upravleniya indikatorom
   delay(50);
  }
 isResend = 1;
  while(isResend)//poka net podtverjdeniya uspeshnogo vipolneniya komandi
  {
   while((inp(0x64)&0x02)!=0x00);
   outp(0x60, mask); //zapisivaem v port bitovou masku dlya nastroiki indikatora
   delay(50);
  }
 }
 void blinking()
 {
     for (int i = 0; i < 10; i++)
     {
         indicator(0x04); //vkl. indicator Caps Lock
         delay(50);
         indicator(0x00); //vikl. vse indicatori
         delay(50);
     }
  cout<<"***"<<endl;
 }