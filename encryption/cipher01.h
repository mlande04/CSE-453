#pragma once
/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER01_H
#define CIPHER01_H

/********************************************************************
 * CLASS CIPHER01
 *******************************************************************/
class Cipher01 : public Cipher
{
public:
	virtual std::string getPseudoAuth() { return "Reynolds Kynaston"; }
	virtual std::string getCipherName() { return "Rail Fence Cipher"; }
	virtual std::string getEncryptAuth() { return "Michelle Landen"; }
	virtual std::string getDecryptAuth() { return "Jacob Johnson"; }

	/***********************************************************
	 * GET CIPHER CITATION
	 * Returns the citation from which we learned about the cipher
	 ***********************************************************/
	virtual std::string getCipherCitation()
	{
		std::string s;
		s += "cryptogram.org (2012), ";
		s += "\"The Cipher Exchange and Cipher Guidelines\', \n   retrieved: Dec. 11, 2020 ";
		s += "https://web.archive.org/web/20120105152732/http://cryptogram.org/cdb/aca.info/aca.and.you/chapter_09.pdf#RAILFE";
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
		// The encrypt pseudocode
		str =  " encrypt(text, password)          \n";
		str += "	key = sizeof(password) % 4 + 3\n";
		str += "	while(iter < sizeof(text))              \n";
		str += "		while(row < key)              \n";
		str += "			vector[row] += text[iter] \n";
		str += "			iter += 1                 \n";
		str += "			row += 1                  \n";
		str += "		while(row > 0)                \n";
		str += "			vector[row] += text[iter] \n";
		str += "			iter += 1                 \n";
		str += "			row -= 1                  \n";
		str += "	while(row < key)              \n";
		str += "		ciphertext += vector[row] \n";
		str += "	return ciphertext             \n\n\n";

		// The decrypt pseudocode
		str += " decrypt(ciphertext, password)          \n";
		str += "	key = sizeof(password) % 4 + 3\n";
		str += "	while(iter < sizeof(ciphertext))              \n";
		str += "		while(row < key)              \n";
		str += "			vector[row] += ciphertext[iter] \n";
		str += "			iter += 1                 \n";
		str += "			row += 1                  \n";
		str += "		while(row > 0)                \n";
		str += "			vector[row] += ciphertext[iter] \n";
		str += "			iter += 1                 \n";
		str += "			row -= 1                  \n";
		str += "	while(row < key)                  \n";
		str += "		iter = 0                      \n";
		str += "		while(iter < sizeof(vector[row]))              \n";
		str += "			vector[row] += ciphertext[iter] \n";
		str += "	end = 0                  \n";
		str += "	middle = 0                  \n";
		str += "	while(iter < sizeof(ciphertext))              \n";
		str += "		row = 0              \n";
		str += "		plaintext += vector[0][end]              \n";
		str += "		while(row + 1 < numRows - 1)              \n";
		str += "			plaintext += vector[row][middle] \n";
		str += "			row += 1                  \n";
		str += "		middle += 1              \n";
		str += "		while(row > 0)              \n";
		str += "			plaintext += vector[row][middle] \n";
		str += "			row -= 1                  \n";
		str += "		middle += 1              \n";
		str += "	return plaintext             \n";

		return str;
	}

	/**********************************************************
	 * ENCRYPT
	 * takes plaintext and translates into ciphertext with password as a key
	 **********************************************************/
	virtual std::string encrypt(const std::string & plainText,
		const std::string & password)
	{
		//C***E***Y
		//*I*H*R*E*
		//**P***K**

		//get key from password
		int numRows = password.length() % 5 + 3; // key is number 3-7. this is very weak because there are only 5 different encryptions
		int numLength = plainText.length();
		std::string cipherText;
		std::vector <std::string> fence;
		for (int j = 0; j < numRows; j++)
		{
			fence.push_back("");   // initialize vector
		}
		for (int i = 0; i < numLength;) {
			for (int j = 0; j < numRows; j++)
			{
				if (i < numLength) {
					fence[j] += plainText[i]; // insert going down rows
					i++;
				}
			} 
			for (int j = numRows - 2; j > 0; j--)
			{
				if (i < numLength) {
					fence[j] += plainText[i]; // insert going up rows
					i++;
				}
			}
		}
		for (int j = 0; j < numRows; j++)
		{
			cipherText += fence[j];   // combine vector into one string
		}

		return cipherText;
	}

	/**********************************************************
	 * DECRYPT
	 * takes ciphertext and translates into plaintext with password as a key
	 **********************************************************/
	virtual std::string decrypt(const std::string & cipherText,
		const std::string & password)
	{
		int numRows = password.length() % 5 + 3;
		int numLength = cipherText.length();
		std::string plainText;
		std::vector <std::string> fence;
		for (int j = 0; j < numRows; j++)
		{
			fence.push_back(""); // initialize vector
		}
		for (int i = 0; i < numLength;) {        // set each string in vector to same length as original vector, same method as encrypt()
			for (int j = 0; j < numRows; j++)
			{
				if (i < numLength) {
					fence[j] += cipherText[i]; 
					i++;
				}
			}
			for (int j = numRows - 2; j > 0; j--)
			{
				if (i < numLength) {
					fence[j] += cipherText[i];
					i++;
				}
			}
		}
		int k = 0;
		for (int j = 0; j < numRows; j++) {
			for (int i = 0; i < fence[j].length(); i++) {
					fence[j][i] = cipherText[k];           // insert ciphertext into the vector in correct orientation
					k++;
			}
		}

		int end = 0;
		int middle = 0;
		for (int i = 0; i < numLength;) {
			if (i < numLength) {
				plainText += fence[0][end];   // add top element
				i++;
			}
			for (int j = 1; j < numRows - 1; j++) {
				if (i < numLength) {
					plainText += fence[j][middle];  // add middle elements in down direction
					i++;
				}
			}
			middle++;
			if (i < numLength) {
				plainText += fence[numRows - 1][end];   // add bottom element
				end++;
				i++;
			}
			for (int j = numRows - 2; j > 0; j--) {
				if (i < numLength) {
					plainText += fence[j][middle];  // add middle elements in up direction
					i++;
				}
			}
			middle++;
		}

		return plainText;
	}
};

#endif // CIPHER01_H
