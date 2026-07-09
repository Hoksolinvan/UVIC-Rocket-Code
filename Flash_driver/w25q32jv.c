// hello world
#include "w25q32jv.h"


void send_write_enable(void);
{
    uint8_t tx[1] = { WRITE_ENABLE }; 

    spi_cs_low();  
    spi_transfer(tx, NULL, 1);  
    spi_cs_high();   
}
