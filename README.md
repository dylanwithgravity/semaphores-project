# semaphores-project
Interprocess Synchronization using Semaphores

Two processes of producer and consumer execute in parallel. The producer produces an item and stores it in an empty buffer and
consumer consumes the buffer by simply getting the content of the buffer and printing it. The total number of buffers is three
and the item produced by the producer is a message that is one character long. The character is chosen from the English alphabet
letters randomly. Each new item generated by the producer will be printed in a new line by the producer before it is loaded into
a buffer.

Determine the location in the alphabet the character is.
if it is odd, the consumer consumes the letter and prints it
if it is even, locate the 2 nearest vowels and add them to the message then find the largest distance between the vowels and char
add add those to the message as well
