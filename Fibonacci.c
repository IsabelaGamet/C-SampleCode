/********************************************

    Project 2:      Fibonacci
    Created By:     Isabela C. Rangel   
    Date created:   05/29/19
    Date modified:  05/31/19

***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include "Fibonacci.h"
#include "limits.h"
#include <string.h>
#include <math.h>

// Prototype of helper functions
HugeInteger *createHugeInteger(int length);

/** hugeAdd
    Adds two hugeInteger structs together
    @param      p       hugeInteger to be added
    @param      q       hugeInteger to be added
    @return     result  sum of the two in hugeInteger format
*/
HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q)
{
    // Variable declarations
    int carry = 0, i, sum = 0;
    HugeInteger *result;

    // Checks if input is null
    if (p == NULL || q == NULL)
        return NULL;

    // calculates expected length of the number, with one extra place for carries
    int expectedLen = (p->length >= q->length) ? p->length + 1 : q->length + 1;

    // creates new huge integer based on expected length of result
    result = createHugeInteger(expectedLen);

    // If creation fails, returns null
    if(result == NULL || result->digits == NULL)
        return NULL;

    // For
    for(i = 0; i < expectedLen; i++)
    {
        // Sets x and y values to respective positions in the array
        int x = (i >= p->length) ? 0: p->digits[i];
        int y = (i >= q->length) ? 0: q->digits[i];
        // Sum is going to be equal to those two values plus any carry leftover
        sum = x + y + carry;
        // carry is the sum / 10
        carry = sum/10;
        // The digit is only the rightmost digit of the sum, as the result is already accounted for
        result->digits[i] = sum%10;
    }
    // If there's still a carry, add it
    if (carry > 0)
        result->digits[i - 1] = carry;
    // Otherwise free that space previously allocated for it and remove that number from the length
    if (result->digits[i - 1] <= 0)
        result->length--;

    // returns sum in hugeInteger format
    return result;
}
/** hugeDestroyer
    Frees up memory associated with previous hugeInt object
    @param      p
    @return     NULL
*/
HugeInteger *hugeDestroyer(HugeInteger *p)
{
    // Checks to see if input is null
    if(p == NULL)
        return NULL;

    // If not, frees array first
    free(p->digits);
    // Then free p
    free(p);

    // Returns null to confirm process
    return NULL;
}
/** Helper Function createHugeInteger
    Allocates space in the memory for a huge integer object O(1)
    @param     length   size of huge integer
    @return    hugeInt  address of space allocated
*/
HugeInteger *createHugeInteger(int length)
{
    // Creates and allocates space for a new hugeInteger
    HugeInteger *hugeInt = malloc(sizeof(HugeInteger));

    // If it fails, return null
    if(hugeInt == NULL)
        return NULL;

    // Allocates space for the array
    hugeInt->digits = malloc(sizeof(int) * length);

    // if array allocation fails, return null
    if(hugeInt->digits == NULL)
        return NULL;

    // Sets length to size specified
    hugeInt->length = length;

    // Returns address of newly allocated
    return hugeInt;
}
/** parseString
    Parses string content into huge integer struct
    @param  str      string to be parsed
    @return hugeInt  address of newly created object
*/
HugeInteger *parseString(char *str)
{
    // Variable declaration
    HugeInteger *hugeInt;
    int len;

    // If passed a null string, returns null
    if (str == NULL)
        return NULL;

    // Gets length of the string
    len = strlen(str);

    // Creates new hugeInt struct
    hugeInt = createHugeInteger(len);

    // if space allocation fails, return null
    if(hugeInt == NULL)
        return NULL;

    // Else go through each character and convert it into a number and assigns to array
    for(int i = 0; i < len; i++)
        hugeInt->digits[len - 1 - i] = str[i] - '0';

    // returns address of newly allocated hugeInt
    return hugeInt;
}
/** parseInt
    Parses int value into huge integer struct
    @param  n        number to be parsed
    @return hugeInt  address of newly created object
*/
HugeInteger *parseInt(unsigned int n)
{
    // Variable declaration
    int len = 0;
    int digits[12];
    unsigned int temp;
    HugeInteger *hugeInt;

    // If passed number is 0, assign 0 to the first position and change size
    if(n == 0)
    {
        digits[len] = n;
        len++;
    }
    else
    {
        // Assigns n to a temporary variable
        temp = n;
        while(temp > 0 && len < 12)
        {
            // Gets rightmost digit and adds it to array
            digits[len] = temp % 10;
            // Discards rightmost digit
            temp /= 10;
            // Increases length
            len++;
        }
    }
    // Allocates space for the hugeInteger
    hugeInt = createHugeInteger(len);

    // If allocation fails, return null
    if(hugeInt == NULL || hugeInt->digits == NULL)
        return NULL;

    // Otherwise assign digits
    for(int i = 0; i < len; i++)
        hugeInt->digits[i] = digits[i];

    // return address of newly created hugeInt
    return hugeInt;
}
/** toUnsignedInt
    transforms digits from a hugeInteger struct
    @param      p       Huge Integer to be parsed into unsigned integer
    @return     result  allocates space and stores resulting value for this function
*/
unsigned int *toUnsignedInt(HugeInteger *p)
{
    // Variable declaration
    unsigned int *result;
	int i;

    // If any of the passed values are null or the length is too great to be represented return null
    if (p == NULL || p->digits == NULL|| p->length > 10) // unsigned integers have 10 decimal places
        return NULL;
    // Allocates space
    result = malloc(sizeof(unsigned int));
    *result = 0;

    // Using the reverse process of parseInt, get the result in unsigned int
	for (i = p->length - 1; i >= 0; i--)
        *result += p->digits[i] * pow(10, i);

    // Returns address of where the result is stored
    return result;
}
/** fib
    Calculates fibonacci values regardless of how big they are
    @param      n           position of fibonacci number to be calculated
    @return     hugeInt     The value in hugeInteger format
*/
HugeInteger *fib(int n)
{
    // Array declaration
    HugeInteger *hugeInt[3];

    // Initializes first two values for the fibonnaci sequence
    hugeInt[0] = parseInt(0);
    hugeInt[1] = parseInt(1);

    // If any of those, return said value
    if(n == 0)
        return hugeInt[0];
    if(n == 1)
        return hugeInt[1];

    // Loops amount of times needed to get fibonacci nth number
    for(int i = 1; i < n ; i++)
    {
        // Calculates 3rd number in the sequence
        hugeInt[2] = hugeAdd(hugeInt[0], hugeInt[1]);
        // Destroys space from value we don't need anymore
        hugeDestroyer(hugeInt[0]);
        // Reassigns values so they move one place behind and leave 2 free for a new value
        hugeInt[0] = hugeInt[1];
        hugeInt[1] = hugeInt[2];
    }

    // Returns address of hugeInt
    return hugeInt[2];
}