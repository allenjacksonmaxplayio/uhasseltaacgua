#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <string>
#include <exception>
#include <iostream>

namespace HovUni {

/**
 * This class is the base class for all exceptions.
 *
 * @author Olivier Berghmans
 */
class Exception: public std::exception
{
private:
	/** The exception message */
	std::string mMsg;

	/** A nested exception */
	Exception* mNested;

public:
	/**
	 * Constructor
	 *
	 * @param msg the exception message
	 */
	Exception(const std::string& msg);
	
	/**
	 * Constructor
	 *
	 * @param msg the exception message
	 * @param nested a nested exception
	 */
	Exception(const std::string& msg, const Exception& nested);
	
	/*
	 * Copy constructor
	 *
	 * @param ex the exception
	 */
	Exception(const Exception& ex);
	
	/**
	 * Destructor
	 */
	virtual ~Exception() throw();

	/**
	 * Assignment operator
	 *
	 * @param ex the exception to assign
	 * @return the result of the assignment
	 */
	Exception& operator=(const Exception& ex);

	/**
	 * Create an exact clone of the exception
	 *
	 * @return an exact clone
	 */
	virtual Exception* clone() const;

	/**
	 * Get the message for this exception
	 *
	 * @return the exception message
	 */
	std::string getMessage() const;

	/**
	 * Get the nested exception
	 *
	 * @return the nested exception or 0 if no nested exception exists
	 */
	const Exception* getNested() const;

	/**
	 * Get the name of the exception class
	 *
	 * @return the name of the class
	 */
	virtual const char* className() const;

	/**
	 * Output operator
	 *
	 * @param os the output stream
	 * @param ex the exception
	 */
	friend std::ostream& operator<<(std::ostream& os, const Exception& ex);

protected:
	/**
	 * Set the message for this exception
	 *
	 * @param msg the new message
	 */
	void message(const std::string& msg);

private:
	/**
	 * Returns a static string for describing the exception
	 *
	 * @return the description
	 */
	virtual const char* what() const throw();
};

/*
 * Macros for quickly declaring and implementing exception classes.
 */
#define HOVUNI_EXCEPTION_DECLARE(NEW, BASE) \
	class NEW: public BASE														\
	{																				\
	public:																			\
		NEW(const std::string& msg);												\
		NEW(const std::string& msg, const HovUni::Exception& nested);				\
		NEW(const NEW& ex);															\
		~NEW() throw();																\
		NEW& operator = (const NEW& ex);											\
		HovUni::Exception* clone() const;											\
		const char* className() const throw();										\
	};


#define HOVUNI_EXCEPTION_DEFINITION(NEW, BASE)														\
	NEW::NEW(const std::string& msg) : BASE(msg) { }												\
	NEW::NEW(const std::string& msg, const HovUni::Exception& nested) : BASE(msg, nested) { }		\
	NEW::NEW(const NEW& ex) : BASE(ex) { }															\
	NEW::~NEW() throw() { }																			\
	NEW& NEW::operator=(const NEW& ex) {															\
		BASE::operator=(ex);																		\
		return *this;																				\
	}																								\
	HovUni::Exception* NEW::clone() const {															\
		return new NEW(*this);																		\
	}																								\
	const char* NEW::className() const throw() {													\
		return typeid(*this).name();																\
	}

/*
 * Exception classes
 */
HOVUNI_EXCEPTION_DECLARE(NetworkException, Exception)

} // End of namespace

#endif
