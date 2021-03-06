/*-------------------------------------------------------------------*/
/* 25th Oct 2020                                                     */
/* Project: Minecraft Torch                                          */
/* Author: RealBadDad                                                */
/* Platforms: Trinket                                                */
/*-------------------------------------------------------------------*/
/* Description:                                                      */
/* Flickering tourch light effect utilising WS2812 LEDs              */
/*                                                                   */
/*-------------------------------------------------------------------*/
/* License:                                                          */
/* Please see attached LICENSE.txt file for details.                 */
/*-------------------------------------------------------------------*/
#include <NeoPixelBrightnessBus.h>

/* XXXX->EDIT REQUIRED HERE<-XXXX - LED hardware                     */
/* Make sure you alter these settings for the hardware you are using */
const uint16_t  PixelCount = 9;

/* XXXX->EDIT REQUIRED HERE<-XXXX                                    */
/* Define where you have wired the data pin of the LEDs              */
const uint8_t   PixelPin   = 1;

/* XXXX->EDIT REQUIRED HERE<-XXXX                                    */
/* Alter the settings for the type of LEDs you have fittted.         */
/* Details on how to use the NeoPixelBus can be foud at              */ 
/* https://github.com/Makuna/NeoPixelBus/wiki                        */
NeoPixelBrightnessBus<NeoGrbFeature, NeoWs2812xMethod > LedStrip(PixelCount, PixelPin);

/* XXXX->EDIT REQUIRED HERE<-XXXX                                    */
/* Alter the base colour of the LEDs, type in the RGB colour code    */
/* you wan the torch to be lit up as.                                */
/* https://htmlcolorcodes.com/ is a good resource to create your     */
/* colour code                                                       */
/* Red - 255, Green = 50, Blue = 0 Gives a Orange Flame colour       */
const uint8_t RED_LEVEL    = 255;            
const uint8_t GREEN_LEVEL  = 50;  
const uint8_t BLUE_LEVEL   = 0;  

/* XXXX->EDIT REQUIRED HERE<-XXXX                                    */
/* By altering these values you can adjut the update rate and level  */
/* of flickerign of the LED effect                                   */
/* MaxBrightness must be above MinBrightness and no more than 255,   */    
/* this adjusts the level of the fliker                              */
/* Max delay must be > DelayMin and this adjuts the delay duration   */
/* between each LED beign updated.                                   */
const int MaxBrightness    = 255;
const int MinBrightness    = 10;
const int DelayMin         = 30;
const int DelayMax         = 200;

/* Application delay timer variables                                 */
/* StartTimeMillis will be loaded with the current millisecond       */
/* counter value when a delay is initiated. The requested delay      */
/* will be stored in ReqDelayMillis                                  */
struct DelaySettingsStruct {
  unsigned long StartTimeMillis; 
  unsigned long ReqDelayMillis;
};
DelaySettingsStruct DelaySettings = {0, 0};
                               
/*-------------------------------------------------------------------*/
/* setup                                                             */
/* Sets up the trinket and LED strip.                                */
/*-------------------------------------------------------------------*/
void setup() {
  /*Start LED library*/
  LedStrip.Begin();
  /*Update and clear all data stored in LEDs*/
  LedStrip.Show(); 
  /*Initiate delay timer, loads current millis into variable*/
  SetDelay(0);
}

/*-------------------------------------------------------------------*/
/* loop                                                              */
/* Main program loop - Only the call to the flicler routin in it     */
/*-------------------------------------------------------------------*/
void loop() {       
  Flicker();   
}

/*-------------------------------------------------------------------*/
/* SetDelay                                                          */
/* Sets a delay timer for the application in milli seconds           */
/*-------------------------------------------------------------------*/
void SetDelay(int req_delay)
{
  DelaySettings.StartTimeMillis = millis();
  DelaySettings.ReqDelayMillis = req_delay;
}

/*-------------------------------------------------------------------*/
/* SetDelay                                                          */
/* Checks if the delay has expired and returns true if it has        */
/*-------------------------------------------------------------------*/
bool DelayExpired(void)
{
  /*Check if the required delay has expired*/
  if ((millis() - DelaySettings.StartTimeMillis) >= DelaySettings.ReqDelayMillis)
  {
    /*Delay has expired*/
    return(true);
  }
  else
  {
    /*Delay has not expired*/
    return(false);
  }
}

/*-------------------------------------------------------------------*/
/* Flicker                                                           */
/* Creates a random flickering LED effet.                            */
/* At random intervals selects a random LED and sets its brightness  */
/* to a random level                                                 */
/*-------------------------------------------------------------------*/
void Flicker(void) 
{  
    /*Check if the delay timer has expired*/
    if(DelayExpired() == true)
    {
      /*Define a new random brightness level for the LED being edited*/
      int NewLevel = random(MinBrightness,MaxBrightness);
      /*Set the LEDs colour and brightness*/
      LedStrip.SetPixelColor(random(LedStrip.PixelCount()), RgbColor(NewLevel*RED_LEVEL/255, NewLevel*GREEN_LEVEL/255, NewLevel*BLUE_LEVEL/255));
      /* Update all the LEDs data */
      LedStrip.Show();
      /*Set new random delay to setting next LED level this gives*/  
      /*a more realistic uneaven update rate*/
      SetDelay(random(DelayMin, DelayMax));  
    }
}
