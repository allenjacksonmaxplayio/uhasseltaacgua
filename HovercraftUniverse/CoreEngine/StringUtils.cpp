#include "StringUtils.h"
#include <string>

namespace HovUni {
	std::string StringUtils::htmlSpecialChars(const std::string& subject) {
		std::string result = subject;
		const int size = 5;
		char characters[size] = {'<', '>', '\"', '\'', '&'};
		//char[5] characters = "<>\"\'&";
		std::string replaceVals[size] = {"&lt;", "&gt;", "&quot;", "&#039;", "&amp;"};

		for (int i = 0; i < size; i++) {
			int position = result.find(characters[i]);
			while (position != std::string::npos)  {
				result.replace(position, 1, replaceVals[i]);
				position = result.find(characters[i], position + 1);
			}
		}
		return result;
	}
}