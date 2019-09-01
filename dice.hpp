#ifndef __DICE__
#define __DICE__

#include <stdint.h> 
//! configuration 
#define RND_RATE 0X006   
#define DICE_SIZE (RND_RATE - 0X001)             
#define TWO      0X02                           //! PIN 2 # TWO 
#define THREE    0X03                           //! PIN 3 # THREE 
#define FOUR     0X04                           //! PIN 4 # FOUR 
#define FIVE     DICE_SIZE                      //! THE FIVE IS EQUAL TO THE DICE SIZE 
#define B_IPUP   0X0A                           //! PIN 10 Button INPUT_PULLUP  
#define T_SHIFT  0XC8                           //! TIME SHIFT 200 
#define RAND_INIT()   randomSeed(analogRead(0)) //! INITIALISE THE RANDOM SEQUENCE   
#define RAND(arg_num)  random(arg_num)          //! GENERATE RANDOM NUMBER 
#define MAX_T_DEL  0xbb8                        //! MAX TIME DELAY  3000 millisecs 
#define ANIM_SPEED 0x64                         //! ANIMATION  SPEED 100 millisecs 
#define DTimer(timeDelay) delay(timeDelay)      //! TIME DELAY OR SLEEP 

//!----redifine Serial  
#define LOG(arg) Serial.println(arg)
#define LOG_(arg)Serial.print(arg) 

//! --- dice Patern 
uint8_t _one     = 0x0003 ; 
uint8_t two[2]   = {4,5} ; 
uint8_t three[3] = {3,4,5} ; 
uint8_t four[4]  = {2,4,5,6} ;

typedef struct  {
    uint8_t _one;
    uint8_t two[2];  
    uint8_t three[3];
    uint8_t four[4] ; 
} _IO_digital ;

void dice_init(uint8_t [] ) ; 
void dice_blink(uint8_t []) ; 

static void turn_off_between() ;  
static void dice_illuminate(uint8_t []  , uint8_t ) ; 


namespace dice_patern  {
    void one   (uint8_t& , uint32_t  = MAX_T_DEL) ;   
    void two   (uint8_t [],uint32_t  = MAX_T_DEL) ; 
    void three (uint8_t [],uint32_t  = MAX_T_DEL) ; 
    void four  (uint8_t [],uint32_t  = MAX_T_DEL) ; 
    void five  (uint8_t [],uint32_t  = MAX_T_DEL) ; 
    void zero  (uint8_t []) ;  
}  

void dice_throw(
        uint8_t& ,
        uint8_t []  //! only zero partern use it 
        ) ; 

void leds_init(uint8_t []);  

/*! 
 * Animation patern  : show the animation led on start 
 */
static void amination_patern(uint8_t&  , uint8_t[] ) ; 

// ! check input pull up status  
void vdbg(bool&);
// ! show the loader in the console 
void loader() ; 
void showResult(uint8_t &) ; 
#endif 
