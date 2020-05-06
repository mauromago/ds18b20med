# ds18b20med
arduino library for read temperature from ds18b20 with multiple read and median value.
 
Using DS18B20 with Arduino for read outside temperature I discovered that air is not so uniform in its temperature. so I implemented code to make more read and calculate the median value. Now, to make my code more easy to write I put this code in a library. More important part are copied from other and older library not wrote by me.

# Update
Correceted some bug
This library can work on one sensor per pin only. Library don't check interupt, so not suggested to use if your code use int.
It don't check CRC too
Removed useless shrt loop
Need to be used with Arduino IDE greater that 1


# ------
Three are the more important funtions:

-getCurrentTemp (SENSOR) ;
just return  the value of one single read from sensor in binary form

-lettCycle (SENSOR) ;
Make a reading cycle. So made more read and calculate the median value from them.

-DataConv (value);
convert the value in caracter sting oseful for send it on ethernet

# ------
You have to generate the class instance with three parameter
DS18B20MED mytest (shortDelay, lettTodo);

-shodtDelay ; 
delay in millisecond after the two discarded sensor read in cycle

-lettTodo ; 
the number of reading to do for calculare de median value. The two higher value and the two lower value are removed from values used for median. Two discarded read are not included in this value

