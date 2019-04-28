Instructions:
The first character must be one of the numbers representing 'S' for the following settings; it then must be followed by any additional data.
The cipher follows then after.
S: Action:					                 Notes:
0  Rotational encryption			         Followed by the key in two-digits
1  Rotational decryption with key		     Followed by the key in two-digits
2  Rotational decryption without key		 Nothing is to follow except the cipher
3  Substitutional encryption with key		 Followed by 26-characters being the key
4  Substitutional decryption with key		 Followed by 26-characters being the key
5  Substitutional decryption without key	 Nothing is to follow except the cipher
Required files:
- an 'input' file, called 'input.txt'
- a 'list' file, with the desired list of English words to be tested with
Notes:
- Substitutional decryption without the key is generally the more reliable the more words there are. This method relies on common frequencies in English, like 
'TH' as a common bigram. Generally, the bigger the cipher, the more chances of success. Some words, that are not in the list, e.g. fictitious proper nouns, and 
have a less common letter, e.g. 'Z', may return as incomplete. This is why the 'success' of the decryption is given and the underscores are kept.
- For the output, punctuation and any non-Latin letters are untouched. For the input, case is irrelevant, whilst whitespaces are relevant!
- There is an 'alternative-list.txt', which was utilised for testing.
- The 'input' file must not have more than 100000 characters not including spaces, and must not have more than 2147483647 words, and a word must not have more 
than 100 characters.
- if the 'input' file is empty, an error-message will occur.
Credits:
- This was made by Clayton John Carlon in 2019 at the University of Newcastle.