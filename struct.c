
#define SPADE 0
#define HEART 1
#define CLUB 2
#define DIAMOND 3

struct CARD
{
    char    suit;
    int     rank; 
};

struct CARD Jack, Jill;

Jack.suit = HEART;
Jack.rank = 9;

Jill.suit = SPADE;
Jill.rank = 2;

union TEMP
{
    struct
    {
        char AD_LSB;    
        char AD_MSB;    
    }
    int Temperature;    
};

union TEMP AD_TEMPERATURE;

AD_TEMPERATURE.Temperature = ADREG;
AD_TEMPERATURE.AD_LSB = ADREGL;
AD_TEMPERATURE.AD_MSB = ADREGH;
