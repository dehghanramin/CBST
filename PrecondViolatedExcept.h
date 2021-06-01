// ============================================================================
// File: PrecondViolatedExcept.h
// ============================================================================
// Programmer: Ramin Dehghan
// Date: May 22, 2021
// Class: CSCI 133 ("Data Structures Using C++")
// Time: Online
// Instructor: Dr. Rodriguez
// Project: Project CBST
//
// Description:
// Header file for the class PrecondViolatedExcept
// ============================================================================

#ifndef PRECONDVIOLATEDEXCEPT_HEADER
#define PRECONDVIOLATEDEXCEPT_HEADER

#include <iostream>


class PrecondViolatedExcept
{
public:
    // ========================================================================
    //     Constructors and Destructor
    // ========================================================================

    /** Initializes m_errorMsg to errorMsg. */
    PrecondViolatedExcept(const std::string errorMsg);

    /** Compiler provided copy constructor and destructor will suffice.  */

    // ========================================================================
    //      Member Functions
    // ========================================================================

    /** Returns the message  of the class private data member
    @param Nothing.
    @return A string. */
    std::string GetMsg() const;
    
    /** Sets the error message of the class private data member
    @param errorMsg: A string (passed by value) to update m_errorMsg.
    @return Nothing. */
    void SetMsg(const std::string errorMsg);

private:
    // ========================================================================
    //      Data Members
    // ========================================================================
    std::string m_errorMsg;
};
#endif
