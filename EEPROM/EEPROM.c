#include "inc/EEPROM.h"

uint32_t EEPROM_init(void) {
    uint32_t ui32Aux;
    SYSCTL_RCGCEEPROM_R = 1; // EEPROM Run Mode Clock Gating Control (RCGCEEPROM) - See pg. 356
    for(ui32Aux=0;ui32Aux<2;ui32Aux++){}
    while(EEPROM_EEDONE_R&EEPROM_EEDONE_WORKING == 0){} //
    if(EEPROM_EESUPP_R == 8 || EEPROM_EESUPP_R == 4){
        return(EEPROM_INIT_ERROR);
    }
    /*
    EEPROM Software Reset (SREEPROM) - See pg. 334
        Value Description
            0 EEPROM module is not reset.
            1 EEPROM module is reset.
    */
    SYSCTL_SREEPROM_R = 1;
    SYSCTL_SREEPROM_R = 0;
    for(ui32Aux=0;ui32Aux<2;ui32Aux++){}
    while(EEPROM_EEDONE_R&EEPROM_EEDONE_WORKING){}
    if(EEPROM_EESUPP_R == (1<<3) || EEPROM_EESUPP_R == (1<<2)){
    	return(EEPROM_INIT_ERROR);
    }

    return(EEPROM_INIT_OK);

}
uint32_t EEPROM_read(uint8_t block, uint8_t offset){
    /*
    EEOFFSET:
	* If read is no allowed the return is 0xFFFFFFFF;
	* If writing is no allowed the EEDONE register is configured to indicate an error.
    is used to select the EEPROM word to read or write within the block selected by the EEBLOCK Register.
    */
	while(EEPROM_EEDONE_R&EEPROM_EEDONE_WRBUSY==1||EEPROM_EEDONE_R&EEPROM_EEDONE_WKCOPY==1||EEPROM_EEDONE_R&EEPROM_EEDONE_WKERASE==1);
    EEPROM_EEBLOCK_R = (uint8_t)(1<<block);  // EEPROM Current Block (EEBLOCK), offset 0x004 - See pg. 561
    EEPROM_EEOFFSET_R = (uint8_t)offset; // EEPROM Current Offset (EEOFFSET), offset 0x008 -See pg. 562
    return (uint32_t)EEPROM_EERDWR_R;   // EEPROM Read-Write (EERDWR), offset 0x010 - See pg. 563
}

void EEPROM_write(uint8_t block, uint8_t offset, uint32_t word) {
	while(EEPROM_EEDONE_R&EEPROM_EEDONE_WRBUSY==1||EEPROM_EEDONE_R&EEPROM_EEDONE_WKCOPY==1||EEPROM_EEDONE_R&EEPROM_EEDONE_WKERASE==1);
	EEPROM_EEBLOCK_R =  (uint8_t)(1<<block); // EEPROM Current Block (EEBLOCK), offset 0x004 - See pg. 561
	EEPROM_EEOFFSET_R = (uint8_t)offset; // EEPROM Current Offset (EEOFFSET), offset 0x008 -See pg. 562
	EEPROM_EERDWR_R = (uint32_t)word; // EEPROM Read-Write (EERDWR), offset 0x010 - See pg. 563
}

uint8_t EEPROM_getblocks(uint8_t block, uint8_t offset){
	EEPROM_EEBLOCK_R = 1<<block; // EEPROM Current Block (EEBLOCK), offset 0x004 - See pg. 561
	//EEPROM_EEOFFSET_R = offset; // EEPROM Current Offset (EEOFFSET), offset 0x008 -See pg. 562
	return EEPROM_EESIZE_R&EEPROM_EESIZE_BLKCNT_M;
}

uint8_t EEPROM_getwords(uint8_t block, uint8_t offset){
	EEPROM_EEBLOCK_R = 1<<block; // EEPROM Current Block (EEBLOCK), offset 0x004 - See pg. 561
	//EEPROM_EEOFFSET_R = offset; // EEPROM Current Offset (EEOFFSET), offset 0x008 -See pg. 562
	return EEPROM_EESIZE_R&EEPROM_EESIZE_WORDCNT_M;
}
