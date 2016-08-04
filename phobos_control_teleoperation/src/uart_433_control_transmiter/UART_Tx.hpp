#ifndef UART_TX_HPP_
#define UART_TX_HPP_

#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include <stdlib.h>
#include <string.h>

class UART_Tx{
    int uart0_filestream;
    struct termios options;

public:
    UART_Tx(const char* device_addres){
        // Open UART device
        uart0_filestream = -1;
        uart0_filestream = open(device_addres, O_WRONLY | O_NOCTTY | O_NDELAY);
        if(uart0_filestream == -1){
            printf("ERROR - Unable to acces UART\n");
        }

        // UART device settings
        tcgetattr(uart0_filestream, &options);
        options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
        options.c_iflag = IGNPAR;
        options.c_oflag = 0;
        options.c_lflag = 0;
        tcflush(uart0_filestream, TCIFLUSH);
        tcsetattr(uart0_filestream, TCSANOW, &options);
    }

    ~UART_Tx(){
        close(uart0_filestream);
    }

    void Transmit(FrameTeleoperation* WORD){
        // Transmiting bytes
        if (uart0_filestream != -1){
            int count = write(uart0_filestream, (const void*)WORD, sizeof(*WORD));
            if(count < 0){
                printf("'UART TX error code: %d'\n", count);
            }
        }
    }

    int32_t ControlSum(FrameTeleoperation* WORD){
        int32_t control_sum = 0;

        // Control sum calculated as sum of all WORD elements
        for(int i = 0; i < TELEOPERATION_DATA_NUM; i++){
            control_sum += *(WORD->begin + i);
        }
        return control_sum;
    }

    void Close(){
        close(uart0_filestream);
        printf("'Closing uart'");
    }

};

#endif
