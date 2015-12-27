# ds18s20med
arduino library for read temperature from ds18b20 with multiple read and median value. Named 18s20 for error. It require SPI library.
 
Using DS18S20 with Arduino for read outside temperature i discovered that air is not so uniform in its temperature. so i implemented code to make more read and calculate the median value. Now, to make my code more easy to write i put this code in a library. More important part are copied from other and older library not by me.


# ------
Three are the more important funtions:

-getCurrentTemp (SENSOR) ;
just return  the value of one single read from sensor in binary form

-lettCycle (SENSOR) ;
make a reading cycle so made two read discarded (looks me that first read after some minute of not use is lower that other) than make more read and calculate the median value from them.

-DataConv (value);
convert the value in caracter sting oseful for send it on ethernet

# ------
You have to generate the class instance with three parameter
DS18S20MED mytest (shortDelay, shortLoop, lettTodo);

-shodtDelay ; 
delay in millisecond after the two discarded sensor read in cycle

-shortLoop ; 
delay after sensor read in useful reading in the cycle

-lettTodo ; 
the number of reading to do for calculare de median value. The two higher value and the two lower value are removed from values used for median. Two discarde read are not included in this value

