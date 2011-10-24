
#include "stm32f10x.h"
#include "startup.h"
#include "beep.h"
#include "Com_TIM.h"
#include "main.h"
#include "pwm_TIM.h"

extern uint16_t forced_period;
extern uint16_t speed;
extern uint16_t minpwm;
extern uint8_t newConfig;

uint16_t tetris[2][203] = {{659,494,523,587,659,587,523,494,440,440,523,659,587,523,494,523,587,659,523,440,440,123,131,147,587,698,880,784,698,659,523,659,587,523,494,494,523,587,659,523,440,440,  0,659,494,523,587,659,587,523,494,440,440,523,659,587,523,494,523,587,659,523,440,440,123,131,147,587,698,880,784,698,659,523,659,587,523,494,494,523,587,659,523,440,440,  0,330,330,262,330,294,330,247,330,262,330,220,330,208,330,247,330,330,262,330,294,330,247,330,262,330,220,330,208,330,247,659,494,523,587,659,587,523,494,440,440,523,659,587,523,494,523,587,659,523,440,440,123,131,147,587,698,880,784,698,659,523,659,587,523,494,494,523,587,659,523,440,440,0  ,659,494,523,587,659,587,523,494,440,440,523,659,587,523,494,523,587,659,523,440,440,123,131,147,587,698,880,784,698,659,523,659,587,523,494,494,523,587,659,523,440,440,0},
                           {400,200,200,200,100,100,200,200,400,200,200,400,200,200,600,200,400,400,400,400,400,200,200,200,400,200,400,200,200,600,200,400,200,200,400,200,200,400,400,400,400,400,400,400,200,200,200,100,100,200,200,400,200,200,400,200,200,600,200,400,400,400,400,400,200,200,200,400,200,400,200,200,600,200,400,200,200,400,200,200,400,400,400,400,400,400,200,200,200,200,200,200,200,200,200,200,200,200,200,200,400,200,200,200,200,200,200,200,200,200,200,200,200,200,200,400,400,200,200,200,100,100,200,200,400,200,200,400,200,200,600,200,400,400,400,400,400,200,200,200,400,200,400,200,200,600,200,400,200,200,400,200,200,400,400,400,400,400,400,400,200,200,200,100,100,200,200,400,200,200,400,200,200,600,200,400,400,400,400,400,200,200,200,400,200,400,200,200,600,200,400,200,200,400,200,200,400,400,400,400,400,400}};
uint16_t elise[2][210] =  {{659,622,659,622,659,494,587,523,440,110,165,220,262,330,440,494, 82,165,208,330,415,494,523,110,165,220,330,659,622,659,622,659,494,587,523,440,110,165,220,262,330,440,494,82,165,208,330,415,494,523,110,165,220,330,494,523,587,659,131,196,262,392,698,659,587,196,247,294,349,659,587,523,110,165,220,330,587,523,494,82,165,330,330,659,330,659,659,622,659,622,659,622,659,622,659,622,659,494,587,523,440,110,165,220,262,330,440,494,82,165,208,330,415,494,523,110,165,220,330,659,622,659,622,659,494,587,523,440,110,165,220,262,330,440,494,82,165,208,330,415,494,523,110,165,220,330,494,523,587,659,131,196,262,392,698,659,587,196,247,294,349,659,587,523,110,165,220,330,587,523,494,82,165,330,330,659,330,659,659,622,659,622,659,622,659,622,659,494,587,523,440,110,165,220,262,330,440,494,82,165,208,330,415,494,523,110,165,220,330},
                           {200,200,200,200,200,200,200,200,400,200,200,200,200,200,200,400,200,200,200,200,200,200,400,200,200,200,400,200,200,200,200,200,200,200,200,400,200,200,200,200,200,200,400,200,200,200,200,200,200,400,200,200,200,400,200,200,200,400,200,200,200,200,200,200,400,200,200,200,200,200,200,400,200,200,200,200,200,200,400,200,200,200,200,200,200,200,400,200,200,200,200,400,200,200,200,200,200,200,200,200,400,200,200,200,200,200,200,400,200,200,200,200,200,200,400,200,200,200,400,200,200,200,200,200,200,200,200,400,200,200,200,200,200,200,400,200,200,200,200,200,200,400,200,200,200,400,200,200,200,400,200,200,200,200,200,200,400,200,200,200,200,200,200,400,200,200,200,200,200,200,400,200,200,200,200,200,200,200,200,200,200,200,200,400,200,200,200,200,200,200,400,200,200,200,200,200,200,400,200,200,200,200,200,200,400,200,200,200,400}};
uint16_t crazytrain[2][68] =  {{185,185,277,185,294,185,277,185,  0,247,220,208,220,247,220,208,165,185,185,277,185,294,185,277,185,  0,247,220,208,220,247,220,208,165,185,185,277,185,294,185,277,185,0,247,220,208,220,247,220,208,165,185,185,277,185,294,185,277,185,0,247,220,208,220,247,220,208,165},
                               {200,200,200,200,200,200,200,200, 10,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200, 10,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,10,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,10,200,200,200,200,200,200,200,200}};
uint16_t clocks[2][172] = {{1245,932,784,0,1245,932,784,0,1245,932,0,1109,932,698,0,1109,932,698,0,1109,932,0,1109,932,698,0,1109,932,698,0,1109,932,0,1047,831,698,0,1047,831,698,0,1047,831,1245,932,784,0,1245,932,784,0,1245,932,0,1109,932,698,0,1109,932,698,0,1109,932,0,1109,932,698,0,1109,932,698,0,1109,932,0,1047,831,698,0,1047,831,698,0,1047,831,1245,932,784,0,1245,932,784,0,1245,932,0,1109,932,698,0,1109,932,698,0,1109,932,0,1109,932,698,0,1109,932,698,0,1109,932,0,1047,831,698,0,1047,831,698,0,1047,831,1245,932,784,0,1245,932,784,0,1245,932,0,1109,932,698,0,1109,932,698,0,1109,932,0,1109,932,698,0,1109,932,698,0,1109,932,0,1047,831,698,0,1047,831,698,0,1047,831},
                           {200,200,200,10,200,200,200,10,200,200,10,200,200,200,10,200,200,200,10,200,200,10,200,200,200,10,200,200,200,10,200,200,10,200,200,200,10,200,200,200,10,200,200,200,200,200,10,200,200,200,10,200,200,10,200,200,200,10,200,200,200,10,200,200,10,200,200,200,10,200,200,200,10,200,200,10,200,200,200,10,200,200,200,10,200,200,200,200,200,10,200,200,200,10,200,200,10,200,200,200,10,200,200,200,10,200,200,10,200,200,200,10,200,200,200,10,200,200,10,200,200,200,10,200,200,200,10,200,200,200,200,200,10,200,200,200,10,200,200,10,200,200,200,10,200,200,200,10,200,200,10,200,200,200,10,200,200,200,10,200,200,10,200,200,200,10,200,200,200,10,200,200}};
uint16_t bumblebee[2][397] = {{1319,1245,1175,1109,1175,1109,1047,988,1047,988,932,880,831,784,740,698,659,622,587,554,587,554,523,494,523,494,466,440,415,392,370,349,330,311,294,277,294,277,262,247,330,311,294,277,294,277,262,247,330,311,294,277,262,349,330,311,330,311,294,277,262,277,294,311,330,311,294,277,262,349,330,311,330,311,294,277,262,277,294,311,330,311,294,277,294,277,262,247,262,277,294,311,330,349,330,294,330,311,294,277,294,277,262,247,262,277,294,311,330,370,392,415,440,415,392,370,349,466,440,415,440,415,392,370,349,370,392,415,440,415,392,370,349,466,440,415,440,415,392,370,349,370,392,415,440,415,392,370,392,370,349,330,349,370,392,415,440,466,440,415,440,415,392,370,392,370,349,330,349,370,392,415,440,466,440,415,440,220,220,220,220,220,220,233,233,233,233,233,233,233,233,220,220,220,220,220,220,220,220,233,233,233,233,233,233,233,233,220,220,220,220,233,233,233,233,220,220,208,233,196,247,262,277,262,247,233,220,233,247,262,277,262,247,233,220,247,262,277,294,294,294,294,294,294,294,311,311,311,311,311,311,311,311,294,294,294,294,294,294,294,311,311,311,311,311,311,311,311,294,294,294,294,311,311,311,311,294,294,277,311,262,330,247,349,370,349,330,311,294,311,330,349,370,349,330,311,294,247,262,277,587,554,523,494,466,622,622,587,554,587,554,523,494,466,494,523,554,587,554,523,494,523,494,466,440,466,494,523,554,523,554,587,622,659,622,587,554,587,554,523,494,523,494,466,440,415,392,370,349,330,349,330,311,165,131,110,98,110,131,165,165,131,110,98,110,131,165,294,277,262,247,262,247,233,220,208,196,185,175,165,175,165,156,659,523,440,349,440,523,659,1319,1047,880,698,880,1047,1319},
                              {94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,188,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,188,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,188,188,188,188,188,188,375,188,188,188,188,188,188,375,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,188,188,188,188,188,188,375,188,188,188,188,188,188,375}};
uint16_t axelf[2][25] = {{676,804,676,676,902,676,602,676,1012,676,676,1071,1012,804,676,1012,1351,676,602,602,506,758,676,676,0},
                         {460,340,230,110,230,230,230,460,340,230,110,230,230,230,230,230,230,110,230,110,230,230,460,460,230}};
uint16_t popcorn[2][32] = {{523,466,523,392,311,392,262,  0,523,466,523,392,311,392,262,  0,523,587,622,587,622,523,587,523,587,466,523,466,523,466,523,  0},
                           {200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200}};



void beep(uint16_t frequency, uint16_t delay)
{
  forced_period = frequency;
  ADC_Cmd(ADC1, DISABLE);
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
  setPW(BEEP_PWM);
  Com_enable();
  TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);
  Delay(delay);
  TIM_ITConfig(TIM2, TIM_IT_CC1, DISABLE);
  TIM_CtrlPWMOutputs(TIM1, DISABLE);
  setPW(0);
  Com_disable();
  ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC);
  ADC_Cmd(ADC1, ENABLE);
}


void startbeep(void)
{ 
  beep(1000,200);
  Delay(100);
  beep(1000,100);
  Delay(50);
  beep(1000,100);
  Delay(50);
  beep(700,500);
}


void Beep(uint16_t frequency, uint16_t time)
{
  beep(1500000/frequency,time);
}





void Beepsong(uint16_t *song, uint16_t ele_count)
{
  uint16_t j;
  for(j = 0 ;j<= ele_count ; j++)
  {
    if(speed < minpwm && !newConfig)
    {
      if(j == (ele_count))
        j = 0;
      if(*(song + j) != 0)
      {
        Beep(*(song+ j),*(song +  ele_count + j));
      }
      else
      {
        Delay(*(song + ele_count + j));
      }
    }
  }
}




void idle(uint8_t song_select)
{

  if(!song_select)    //if zero
  {
    song_select = (rand() % 7); //play random song
    song_select++;
  }
  switch(song_select)
  {
    case 1:
      Beepsong((uint16_t*)crazytrain,sizeof(crazytrain)/4);
      break;
    case 2:
      Beepsong((uint16_t*)elise,sizeof(elise)/4);
      break;
    case 3:
      Beepsong((uint16_t*)tetris,sizeof(tetris)/4);
      break;
    case 4:
      Beepsong((uint16_t*)clocks,sizeof(clocks)/4);
      break;
    case 5:
      Beepsong((uint16_t*)bumblebee,sizeof(bumblebee)/4);
      break;
    case 6:
      Beepsong((uint16_t*)axelf,sizeof(axelf)/4);
      break;
    case 7:
      Beepsong((uint16_t*)popcorn,sizeof(popcorn)/4);
    default:
      break;
  }
}
