#pragma once
/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER02_H
#define CIPHER02_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher02 : public Cipher
{
public:
	Cipher02()
	{
		valueMinimum = 'A';
		valueMaximum = 'Z';
		sizeAlphabet = valueMaximum - valueMinimum + 1;
	}


	virtual std::string getPseudoAuth() { return "Jacob Johnson"; }
	virtual std::string getCipherName() { return "Vigenère Square Cipher"; }
	virtual std::string getEncryptAuth() { return "Reynolds Kynaston"; }
	virtual std::string getDecryptAuth() { return "Michelle Landen"; }

	/***********************************************************
	 * GET CIPHER CITATION
	 * Returns the citation from which we learned about the cipher
	 ***********************************************************/
	virtual std::string getCipherCitation()
	{
		std::string citation = "The Vigenère Cipher Encryption and Decryption";
		citation += "Dr. C.-K. Shene, Professor, Department of Computer Science, Michigan Technological University";
		citation += "Available Online: https://pages.mtu.edu/~shene/NSF-4/Tutorial/VIG/Vig-Base.html";
		return std::string(citation);
	}

	/**********************************************************
	 * GET PSEUDOCODE
	 * Returns the pseudocode as a string to be used by the caller.
	 **********************************************************/
	virtual std::string getPseudocode()
	{
		std::string str;

		// The encrypt pseudocode
		str = "encrypt(plainText, password)\n";
		str += "     convertedPlainText <- convertText(plainText)\n";
		str += "     convertedPassword <- convertText(password)\n";
		str += "     FOR each index in convertedPlainText\n";
		str += "         nextLetter <- (plainText[index] + password[index % password length]) % alphabetSize \n";
		str += "         nextLetter += 'A'";
		str += "         cipherText += nextLetter \n";
		str += "     RETURN cipherText\n\n";

		// The decrypt pseudocode
		str = "decrypt(cipherText, password)\n";
		str += "     convertedPassword <- convertText(password)\n";
		str += "     FOR each index in cipherText\n";
		str += "         nextLetter <- (cipherText[index] - password[index % password length] + alphabetSize) % alphabetSize \n";
		str += "         nextLetter += 'A'";
		str += "         plainText += nextLetter \n";
		str += "    RETURN plainText\n\n";

		// helper routine
		str += "convertText(plainText)\n";
		str += "   FOR p is all values of plainText\n";
		str += "     IF p is in alphabet";
		str += "     convertedText += uppercase(p)";
		str += "   RETURN convertedText \n\n";

		return str;
	}

	/**********************************************************
	 * ENCRYPT
	 * Shifts each character in the plainText by a different amount depending on the input password.
	 **********************************************************/
	virtual std::string encrypt(const std::string & plainText,
		const std::string & password)
	{
		std::string cipherText;
		std::string convertedPlainText = convertText(plainText);
		std::string convertedPassword = convertText(password);

		// convert the plaintext one character at a time
		for (int i = 0; i < convertedPlainText.length(); i++)
		{
			char nextLetter = (convertedPlainText[i] + convertedPassword[i % convertedPassword.length()]) % sizeAlphabet;
			nextLetter += 'A';
			cipherText += nextLetter;
		}

		return cipherText;
	}

	/**********************************************************
	 * DECRYPT
	 * Shifts each character in the cipherText by a different amount depending on the input password.
	 **********************************************************/
	virtual std::string decrypt(const std::string & cipherText,
		const std::string & password)
	{
		std::string plainText;
		std::string convertedCipherText = convertText(cipherText);
		std::string convertedPassword = convertText(password);

		// convert the plaintext one character at a time
		for (int i = 0; i < cipherText.length(); i++)
		{
			// converting in range 0-25
			char nextLetter = (convertedCipherText[i] - convertedPassword[i % convertedPassword.length()] + sizeAlphabet) % sizeAlphabet;

			// convert into alphabets(ASCII)
			nextLetter += 'A';
			plainText += nextLetter;
		}
		return plainText;
	}

private:

	/***************************************************
	 * CONVERT TEXT
	 * Removes any character from the input text that isn't in the alphabet, including removing spaces, and sets all letters to uppcase.
	 **************************************************/
	std::string convertText(const std::string & inputText)
	{
		std::string convertedText;
		for (std::string::const_iterator it = inputText.begin();
			it != inputText.end();
			++it) {
			if (*it >= valueMinimum && *it <= 'z')
				convertedText += toupper(*it);
		}
		return convertedText;
	}

	// minimum "printable" character
	char valueMinimum;

	// maximum "printable" character
	char valueMaximum;

	int sizeAlphabet;
};

#endif // CIPHER02_H