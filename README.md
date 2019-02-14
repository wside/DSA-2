# DSA-2
**Program1- Hash Table**
    
Features:  
-simple hash function  
-linear probing  
-dynamic resizing   

Note:  
-uses lazy deletion*    
-*but when inserting, if detects deleted slot (even though says occupied) will fill. This makes it slightly more efficient (?). True lazy deletion would skip over a deleted slot because it would say occupied.     
-**SEE PROGRAM 2 FOR SIMPLIFIED (BETTER) HASH TABLE that implements true lazy deletion. Makes it much easier to build binary heap off (also in Program 2) off of.

Suggestions:   
-findPos returns a pair value to shorten code. Some people might prefer them seperate.     
-Should seperate main using a dictionary-load-code function and a spell-check function so main isn't one long blob.
