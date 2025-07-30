How It Works
Dynamic Key Generation:

A random key is generated for encryption (e.g., a sequence of numbers or characters). This key is derived from the input message in a reversible manner, ensuring security.
The key adjusts its value dynamically based on the message length and character positions.
Folding Technique:

The message is divided into chunks of equal length, and chunks are "folded" (reversed and shuffled) based on the key.
Folding rearranges the message structure, adding complexity.
Substitution and Modulo Operations:

Each character in the message is encrypted using a combination of:
A substitution step where the ASCII value of the character is altered using the key.
A modulo operation that wraps values around within printable ASCII characters (32–126).
Output Transformation:

The transformed chunks are joined, and padding is added if needed for equal block lengths during decryption.
Advantages
Every encryption session produces a unique key, so even if the same message is encrypted twice, the output will differ.
The cipher resists frequency analysis attacks due to dynamic substitutions and structure changes.
Example Walkthrough
Input: HELLO
Key (derived): 31415
Process:
Split into chunks (if applicable).
Substitute and shuffle based on key.
Encrypt and output.
Input:
Plaintext: HELLO
Key: Derived dynamically as 31415 (based on the length and ASCII sum of the message, for example).

Step 1: Divide into chunks (if needed)
For simplicity, we'll treat the entire string as one chunk because it's short.

Step 2: Dynamic Substitution
Each character in the plaintext is altered using the corresponding digit in the key. If the key is shorter than the message, it repeats cyclically.
The substitution formula:

sql
Copy code
New ASCII = (Old ASCII + Key Digit) % 126
If the result is less than 32 (non-printable ASCII), wrap it back:

sql
Copy code
New ASCII = New ASCII + 32
Transformation:

H (ASCII 72) + 3 = 75 → K
E (ASCII 69) + 1 = 70 → F
L (ASCII 76) + 4 = 80 → P
L (ASCII 76) + 1 = 77 → M
O (ASCII 79) + 5 = 84 → T
Result After Substitution: KFPMT

Step 3: Folding (Reversing and Shuffling)
Based on the key, we reverse the string and shuffle based on the key order.

Reverse: TMFPK
Shuffle based on the key sequence (3, 1, 4, 1, 5 → rearrange to indices [2, 0, 3, 1, 4]):
T → Position 3
M → Position 1
F → Position 4
P → Position 2
K → Position 5
Result After Folding: PFKTM

Step 4: Final Output Transformation (Optional)
We could further transform the ciphertext for added security, such as XOR with a static or dynamic salt. For now, the output is the encrypted text.

Ciphertext: PFKTM

Summary:
Plaintext: HELLO
Ciphertext: PFKTM
Decryption would follow the reverse process: unshuffle, reverse, and substitute with the inverse key operation.




