<div align="left">
  <h1>IPv4-Addressing</h1>
  <h3>A C program that serves multiple tasks regarding IPv4 Addressing, using bits manipulation</h3>
</div>
<br/>
<br/>


## Input ##
The first line of the input file contains the number of tests T. The following T lines each contain
a test set.

A test set has the following format:

`MSK_1 MSK_2 IP_1 IP_2 N NET_1 NET_2 ... NET_N`

Where:
* MSK_1: a network mask
* MSK_2: number of set bits of the network mask for IP_1 and IP_2
* IP_1: an IP address
* IP_2: another IP address
* N: positive integer
* [NET_1 … NET_N]: list of N network addresses
<br><br><br>

## Output ##
A test set is preceded by its number.

For each test set, there are 10 tasks that the program solves:
* -0: prints IP_1 and MSK_2 in the format: `IP_1/MSK_2`
* -1: prints MSK_2 in an IP format
* -2: prints MSK_1 in base 8 and base 16
* -3: prints the Network address of IP_1
* -4: prints the Broadcast address of IP_1
* -5: finds if IP_1 and IP_2 share the same Network address
* -6: finds if MSK_1 is indeed a correct mask
* -7: if the previous answer was YES, print MSK_1, otherwise correct it
* -8: prints IP_1 in binary format
* -9: finds the indices of the Network addresses from the list [NET_1 ... NET_N] 
that IP_2 could be a part of
