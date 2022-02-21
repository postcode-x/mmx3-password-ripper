# mmx3-password-ripper
Fast multithreaded password ripper for the game MMX3 
 
## WIP
This is basically a rehash of [this project](https://github.com/postcode-x/mmx3-password-generator) but in this case I made it in C++, which is more performance oriented and currently capable of testing roughly 1 million passwords per second on an Intel Core i3 without file I/O, which is on the works and should be ready soon.

This is a pretty CPU and memory intensive application, so keep that in mind when running this on your machine.

## How long would it take to get all of the valid game passwords for a single computer?

Each MegamanX3 password consists of 16 items. Each item can be any number from  1 to 8. This means that all of the possible combinations for our case equals:

**8 ^ 16 = 281.474.976.710.656 total combinations**

Dividing that number by the current rate of the password ripper gives the total amount of seconds required to go through every possible combination:

**281.474.976.710.656 s** 

We divide by **60 * 60 * 24 * 365** to get the approximate number of years:

**9 years** 




