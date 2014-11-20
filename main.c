#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//A routine used to convert the PI code from RBDS block A to a station callsign
//Valid for the US only
//Source partially ported from http://www.w9wi.com/articles/rds.htm
uint8_t PiToCallsign(uint16_t picode, char *callsign);

int main()
{
    uint16_t picode;// = 0x66B6;
    char callsign[5];
    printf("Enter a 16-bit hexadecimal pi code: ");
    scanf("%x", &picode);

    printf("Converting code %x\n", picode);

    if(PiToCallsign(picode, callsign) == 0)
    {
        printf("Callsign is %s\n", callsign);
    }
    else
    {
        printf("Invalid PI code entered");
    }

    return 0;
}

/*  Convert a PI code to a four character station callsign
    picode:  The 16-bit program identification code recieved from RBDS
    string:  Pointer to a 4 character string (including null terminator)
    returns: 0 if code converted successfully, 1 if code was invalid
*/
uint8_t PiToCallsign(uint16_t picode, char *callsign)
{
    if ((picode > 4095) && (picode < 39247))
    {
        if (picode > 21671)
        {
            callsign[0] = 'W';
            picode -= 21672;
        }
        else
        {
            callsign[0] = 'K';
            picode -= 4096;
        }

        callsign[1] = (picode / 676) + 65;
        picode %= 676;
        callsign[2] = (picode / 26) + 65;
        picode %= 26;
        callsign[3] = picode + 65;
        callsign[4] = '\0';
        return 0;
	}
	else
    {
        callsign = "INVL";
        return 1;
    }
}
