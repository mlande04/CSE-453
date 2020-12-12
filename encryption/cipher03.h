#pragma once
/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER03_H
#define CIPHER03_H
#include <map>

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher03 : public Cipher
{
public:
	virtual std::string getPseudoAuth() { return "Michelle Landen"; }
	virtual std::string getCipherName() { return "Keyword Cipher"; }
	virtual std::string getEncryptAuth() { return "Jacob Johnson"; }
	virtual std::string getDecryptAuth() { return "Reynolds Kynaston"; }

	/***********************************************************
	 * GET CIPHER CITATION
	 * Returns the citation from which we learned about the cipher
	 ***********************************************************/
	virtual std::string getCipherCitation()
	{
		std::string s;
		s += "B. Veitch, YouTube.com (2014), ";
		s += "\"Introduction to Cryptography 2 - Keyword Cipher\', \n   retrieved: ";
		s += "https://youtu.be/XreUs1I1ZdY";
		s += "\n\n";
		s += "J. Nicholl, Jnicholl.org, ";
		s += "\"Keyword Substitution Cipher\', \n   retrieved: ";
		s += "http://jnicholl.org/Cryptanalysis/Ciphers/KeywordSubstitution.php#:~:text=Keyword%20Substitution%20Cipher%201%20Description.%20A%20keyword%20substitution,...%203%20Recognition.%20This%20section%20is%20under%20construction.";
		s += "\n";

		return s;
	}

	/**********************************************************
	 * GET PSEUDOCODE
	 * Returns the pseudocode as a string to be used by the caller.
	 **********************************************************/
	virtual std::string getPseudocode()
	{
		std::string str;

		// TODO: please format your pseudocode
		// Helper routine: convert string password into cipher key
		str = "buildKey(password)\n";
		str += "    bool <- array[26]\n";
		str += "    for k is all values less than length of password\n";
		str += "        if password[k] is in the uppercase alphabet\n";
		str += "            if the password[k] is not already in the array\n";
		str += "                encodeKey <- password[k]\n";
		str += "        else if password[k] is in the lowercase alphabet\n";
		str += "            if the password[k] is not already in the array\n";
		str += "                encodeKey <- password[k]\n";
		str += "     for i is all values less than 26\n";
		str += "        if any characters remaining\n";
		str += "            encodeKey <- password[k]\n";
		str += "    RETURN encodeKey \n\n";

		// The encrypt pseudocode
		str += "encrypt(plainText, password)\n";
		str += "    encodeKey <- buildKey(password)\n";
		str += "    for s is all values less than length of plainText\n";
		str += "        if plainText[s] is in the lowercase alphabet\n";
		str += "            placeholder <- plainText[s] - 97\n";
		str += "            cipherText <- encodeKey[placeholder]\n";
		str += "        else if plainText[s] is in the uppercase alphabet\n";
		str += "            placeholder <- plainText[s] - 65\n";
		str += "            cipherText <- encodeKey[placeholder]\n";
		str += "        else cipherText <- plainText[s]\n";
		str += "    RETURN cipherText \n\n";

		// The decrypt pseudocode
		str += "decrypt(cipherText, password)\n";
		str += "    alphabet <- all uppercase alphabet values\n";
		str += "    map <- encodeKey\n";
		str += "    for e is all values less than the length of the encodeKey\n";
		str += "        map [encodeKey[e]] = index\n";
		str += "    for c is all values less than the length of the cipherText\n";
		str += "        if cipherText[c] is in the lowercase alphabet\n";
		str += "            placeholder <- map[cipherText[c] - 32]\n";
		str += "            plainText <- alphabet[placeholder]\n";
		str += "        else if cipherText[c] is in the uppercase alphabet\n";
		str += "            placeholder <- map[cipherText[c]]\n";
		str += "            plainText <- alphabet[placeholder]\n";
		str += "        else plainText <- cipherText[c]\n";
		str += "    RETURN plainText \n\n";

		return str;
	}

	/**********************************************************
	 * ENCODE KEY
	 * TODO: Utility function - Encodes password into key
	 **********************************************************/
	virtual std::string buildKey(const std::string& password)
	{
		std::string e = password;
		std::string encodeKey = "";
		bool arr[26] = { false };

		for (int i = 0; i < e.length(); i++)
		{
			if (e[i] >= 'A' && e[i] <= 'Z')
			{
				if (arr[e[i] - 65] == 0)
				{
					encodeKey += e[i];
					arr[e[i] - 65] = 1;
				}
			}
			else if (e[i] >= 'a' && e[i] <= 'z')
			{
				if (arr[e[i] - 97] == 0)
				{
					encodeKey += e[i] - 32;
					arr[e[i] - 97] = 1;
				}
			}
		}

		for (int i = 0; i < 26; i++)
		{
			if (arr[i] == 0)
			{
				arr[i] = 1;
				encodeKey += char(i + 65);
			}
		}

		return encodeKey;
	}

	/**********************************************************
	 * ENCRYPT
	 * TODO: Takes a key generated from the password input to
	 * encrypt plaintext and display the ciphertext
	 **********************************************************/
	virtual std::string encrypt(const std::string& plainText,
		const std::string& password)
	{
		std::string cipherText = "";

		// TODO - Add your code here
		std::string encryptKey = buildKey(password);

		for (int i = 0; i < plainText.length(); i++)
		{
			if (plainText[i] >= 'a' && plainText[i] <= 'z')
			{
				int x = plainText[i] - 97;
				cipherText += encryptKey[x];
			}
			else if (plainText[i] >= 'A' && plainText[i] <= 'Z')
			{
				int x = plainText[i] - 65;
				cipherText += encryptKey[x];
			}
			else
			{
				cipherText += plainText[i];
			}
		}

		return cipherText;
	}

	/**********************************************************
	 * DECRYPT
	 * TODO: Takes a key generated from the password input to
	 * decrypt ciphertext and display the plaintext
	 **********************************************************/
	virtual std::string decrypt(const std::string& cipherText,
		const std::string& password)
	{
		std::string plainText = "";

		// TODO - Add your code here
		std::string decryptKey = buildKey(password);
		std::string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

		for (int i = 0; i < cipherText.length(); i++)
		{
			if (cipherText[i] >= 'a' && cipherText[i] <= 'z')
			{
				//int x = hold[cipherText[i] - 32];
				for (int j = 0; j < decryptKey.length(); j++) {
					if (cipherText[i] == decryptKey[j])
						plainText += alpha[j];
				}
			}
			else if (cipherText[i] >= 'A' && cipherText[i] <= 'Z')
			{
				//int x = hold[cipherText[i]];
				for (int j = 0; j < decryptKey.length(); j++) {
					if (cipherText[i] == decryptKey[j])
						plainText += alpha[j];
				}
			}
			else
			{
				plainText += cipherText[i];
			}
		}

		return plainText;
	}
};

#endif // CIPHER03_H