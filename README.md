# Basic Substitution Cipher Encryption/Decryption Tool

This C++ program implements a basic substitution cipher for encrypting and decrypting text. The program allows users to perform encryption, decryption with a known key, and decryption without a key (with a 3-character length guess).

## Features:
- **Encryption:** Encrypt a given text with a specified key.
- **Decryption:** Decrypt an encrypted text with the corresponding key.
- **Decryption without Key:** Attempt to decrypt without knowing the key (3-character length guess required).
- **Vowel Check:** Ensures that the decrypted text has at least one vowel, improving the likelihood of meaningful results.
- **Similarity Check:** Evaluate the similarity between a guessed plaintext and the decrypted text.

## Usage:
1. Choose an operation:
   - Enter `1` for encryption.
   - Enter `2` for decryption with a known key.
   - Enter `3` for decryption without a key (requires a 3-character length guess).

2. Follow the prompts:
   - For encryption and decryption with a key, enter the text and key as prompted.
   - For decryption without a key, provide the encrypted text and optionally a guess for the plaintext.

3. View the results:
   - Encrypted or decrypted text will be displayed.
   - For decryption without a key, the program will attempt to find possible plaintexts and display them along with their similarity ratios.

## Example:
```plaintext
what do you want to do?
1.      encryption
2.      decryption
3.      decryption without key (length of key must 3)
0.      quit
>> 1
enter a text to encrypt:        Hello
enter a key:    ABC
-----------------------------
encrypted text: HFNLP
