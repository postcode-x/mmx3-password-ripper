# mmx3-password-ripper

**Disclaimer: This information is strictly for educational purposes.** 

You can see the concepts behind this code being applied here: https://www.youtube.com/watch?v=WZTNGIcVez4

![alt text](https://github.com/postcode-x/mmx3-password-generator/blob/main/screenshot.png)


## Fast multithreaded password ripper for the game Megaman X3

Currently capable of testing roughly 1 million passwords per second on an Intel Core i3 with 16GB of RAM.


## Notes

This is a pretty CPU and memory intensive application, so keep that in mind before running this app on your machine.


## How long would it take to get all of the valid passwords for a single Intel i3 processor?

Each **Megaman X3** password consists of 16 items. Each item can be any number from  1 to 8. This means that all of the possible combinations for our case equals:

>**8 ^ 16 = 281.474.976.710.656 total combinations**

Dividing that number by the current rate of the password ripper gives the total amount of seconds required to go through every possible combination:

>**281.474.976 seconds** 

We divide by **60 * 60 * 24 * 365** to get the approximate number of years:

>**9 years** 


## How many valid passwords are you expecting to find?

>**Proportion of valid passwords ~ 1/127**

>**Complete set of valid passwords = 2.218.022.816.479 or roughly 2.2 Trillion**

We divide by 4 because each state can be stored in 4 different ways, so:

>**# of non repeated valid passwords = 554.505.704.120 or roughly 554 Billion**


## How much storage space would that take?

We do not know which passwords map to the same game state, so we need to store the complete set of functional passwords. So, assuming each password takes 16 bytes, it would take about **32 Terabytes** of storage.

