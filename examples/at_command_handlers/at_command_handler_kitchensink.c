//
// Created by steve on 4/27/22.
//
#include <stdint.h>
#include <printing_help.h>
#include <trakid.h>
#include <i2c.h>
#include <flash.h>

uint8_t at_command_handler_setftm_read(void){
    log_debug_stringln("FTM READ CALLED");

    #define FLAGS_SECTOR_START_ADDRESS 0x08004000
    uint32_t flagsdataword =
            * ( (volatile uint32_t*) FLAGS_SECTOR_START_ADDRESS);

    // Check the flags sector to see if
    // factory test has passed.
    // if the data is all zero, then no pass
    if(0 == flagsdataword){
        PRINT_STRINGLN("0")
    }
    else{
        PRINT_STRINGLN("1")
    }

    return 0;
}
uint8_t at_command_handler_setftm_write(uint8_t **args){
    log_debug_stringln("FTM WRITE CALLED");

    // sector 4 = 0x4000 is the flags section
    log_debug_stringln("ERASE SECTOR 4");
    flash_erase_sector(4);
    log_debug_stringln("WRITE TO SECTOR 4");
    flash_write(0x4000, "ABCD1234", 8);
    NVIC_SystemReset();
}

//debug
uint8_t at_command_handler_setdebug_read(void){
    if(is_log_debug_enabled())
        PRINT_STRINGLN("DEBUG IS ENABLED")
    else
        PRINT_STRINGLN("DEBUG IS DISABLED")
    return 0;
}
uint8_t at_command_handler_setdebug_write(uint8_t **args){
    int8_t arg = parse_num_arg(args[0]);
    if(arg == 1){
        enable_log_debug();
        return 0;
    }
    else if(arg == 0){
        disable_log_debug();
        return 0;
    }
    else {
        return 1;
    }
}


uint8_t at_command_handler_pwrctrl(uint8_t **line){
    return 0;
}

uint8_t at_command_handler_pwrfault(uint8_t **line){
    return 0;
}

uint8_t at_command_handler_uartctl(uint8_t * line){
    return 0;
}

uint8_t at_command_handler_selband(uint8_t **line){
    return 0;
}

uint8_t at_command_handler_bandpres(uint8_t **line){
    return 0;
}

uint8_t at_command_handler_bookgpio(uint8_t **line){
    return 0;
}


/* AT*BANDID
 *
 *  NOTE THE EXTERN DECL NOT AT THE TOP
 *  TODO FACTOR OUT ACCESS TO EE_DATA_FILE
 *  COPIED THE STRUCT DEF HERE.. NOT GOOD!!
 */


typedef union {
    struct {
        uint8_t firmware_version[10];
        uint8_t traker_id[8];
        uint8_t ip_addr[5][17];
        uint8_t ip_cnt;
        uint8_t ip_ptr;
        uint8_t ip_valid[5];
        uint8_t secret_key[21];
        uint16_t position_update_rate;
        uint16_t charger_cycle_count;
        uint8_t send_mfg_flag;
        uint8_t led_green_red_fix[10]; /**GO** Color correction byte for each of the 9 LEDs.*/
        uint8_t band_ip[17];

    } ee_var;
    uint8_t ee_data[250];//uint8_t ee_data[400]; /**GO**/
} EEPROM_DATA;

extern EEPROM_DATA ee_data_file;

/*
 * ASSUMING THE PARAMETER IS A ASCII STRING
 * ONLY CAPITAL LETTERS A-Z and DIGITS 0-9 ARE ALLOWED
 * MAX LENGTH IS 4 out of 8
 * Default is JTMP 00 00 ff ff
 */
uint8_t at_command_handler_bandid_write(uint8_t **args){
    MX_I2C3_Init();

#define NUM_ARGS 1
    if(args[NUM_ARGS - 1] == 0){
        log_debug_stringln("NEED 1 ARGS, FAIL");
        return 1;
    }

    uint8_t * bandid_param_string = args[0];

    // Check for invalid characters IN THE INPUT
    // WE DO NOT KNOW HOW MANY CHARACTERS THERE ARE
    uint8_t charok = true;
    for(int i=0;
        bandid_param_string[i] != '\n' && bandid_param_string[i] != 0;
        i++){
        uint8_t tid = bandid_param_string[i];
        if(tid < '0') {
            charok = false;
        } else if((tid > '9') && (tid < 'A')){
            charok = false;
        } else if(tid > 'Z') {
            charok = false;
        }
    }

    if(false == charok){
        log_debug_stringln("BAD CHARACTER");
        return 1;
    }

    // LOADING THE EEPROM BUFFER.
    // CLEAR IT TO ZERO FIRST
    // ASSUMES SIZE OF TRACKER ID IS 8 BYTES
    for(int i=0; i<8; i++){
        ee_data_file.ee_var.traker_id[i] = 0;
    }

    int i;
    for(i=0; bandid_param_string[i] != '\n' && bandid_param_string[i] != 0; i++){
        ee_data_file.ee_var.traker_id[i] = bandid_param_string[i];
    }

    // STICK A ZERO ON THE END
    ee_data_file.ee_var.traker_id[i] = 0;
    log_debug_stringln(ee_data_file.ee_var.traker_id);

    log_debug_stringln("SAVING PARAMETERS TO EEPROM");
    save_parameters_to_eeprom();
    log_debug_stringln("DUMMY WRITE");
    return 0;
}
uint8_t at_command_handler_bandid_read(void){
    log_debug_stringln("I2C3 INIT");
    MX_I2C3_Init();

    log_debug_stringln("load_check_system_parameters");
    load_check_system_parameters();

//    log_debug_stringln("firmware_version");
//    printbuf_until_newline_or_zero(ee_data_file.ee_var.firmware_version);

    log_debug_stringln("traker_id");
    printbuf_until_newline_or_zero(ee_data_file.ee_var.traker_id);
    PRINT_STRING("\n")


//    uint8_t ip_addr[5][17];
//    uint8_t ip_cnt;
//    uint8_t ip_ptr;
//    uint8_t ip_valid[5];
//    log_debug_stringln("secret_key");
//    printbuf_until_newline_or_zero(ee_data_file.ee_var.secret_key);
//    uint16_t position_update_rate;
//    uint16_t charger_cycle_count;
//    uint8_t send_mfg_flag;
//    uint8_t led_green_red_fix[10]; /**GO** Color correction byte for each of the 9 LEDs.*/
//    uint8_t band_ip[17];

    return 0;
}

