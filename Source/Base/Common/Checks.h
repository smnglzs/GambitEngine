/*
	Checks: basic assertions and exceptions.
*/

#pragma once
#include <cassert>
#include <stdexcept>

#define gbCheckMsg(expr, msg) static_assert(expr, msg)
#define gbCheckRange(inRangeCond) if(!(inRangeCond)) gbThrowRange(#inRangeCond)
#define gbThrowRange(inRangeCond) throw std::out_of_range(#inRangeCond)

namespace gb
{
	namespace Exceptions
	{
        class LoadFailed : public std::exception
        {
        public:
            LoadFailed() : LoadFailed(__FUNCTION__) { }

            virtual const char* what() const throw() { return m_text.c_str(); }

        private:
            LoadFailed(const char* fname) : 
                std::exception("Load failed"), 
                m_text("Load failed in ")
            { 
                m_text += fname;
            };

        private:
            std::string m_text;
        };

        class NotImplemented : public std::logic_error
        {
        public:
            NotImplemented() : NotImplemented(__FUNCTION__) { }

            virtual const char* what() const throw() { return m_fname; }

        private:
            NotImplemented(const char* fname) : std::logic_error("Function not implemented") { m_fname = fname; };

        private:
            const char* m_fname;
        };

        // TODO: invalid_argument, length_error, runtime_error
	}
}