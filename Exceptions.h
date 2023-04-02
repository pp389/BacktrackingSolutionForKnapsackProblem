#pragma once
#include <exception>
#include <string>

namespace Exceptions {

	class FileOpenException : public std::exception {
	public:
		virtual const char* what() const throw() {
			return "Error opening file.";
		}
	};

	class InvalidInputValueException : public std::exception {
	public:
		virtual const char* what() const throw() {
			return "One of the input values is ivalid.";
		}
	};

}